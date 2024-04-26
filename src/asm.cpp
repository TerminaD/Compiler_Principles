#include <cassert>
#include <iostream>

#include "koopa.h"
#include "asm.hpp"


auto reg(int reg_ctr) {
  switch (reg_ctr % 15) {
    case 0: return "t0";
		case 1: return "t1";
		case 2: return "t2";
		case 3: return "t3";
		case 4: return "t4";
		case 5: return "t5";
		case 6: return "t6";
		case 7: return "a0";
		case 8: return "a1";
		case 9: return "a2";
		case 10: return "a3";
		case 11: return "a4";
		case 12: return "a5";
		case 13: return "a6";
		case 14: return "a7";
		default: assert(false);
  }
}

int generate_asm(const char *irp, std::ofstream &out) {
  // Convert IR to memory form
  koopa_program_t program;
  koopa_error_code_t koopa_ret = koopa_parse_from_string(irp, &program);
  assert(koopa_ret == KOOPA_EC_SUCCESS);
  koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
  koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
  koopa_delete_program(program);

  int *global_reg_ctr = new int;
  *global_reg_ctr = 0;

  Visit(raw, out, global_reg_ctr);

  // Release memory
  koopa_delete_raw_program_builder(builder);

  return 0;
}

// 访问 raw program
void Visit(const koopa_raw_program_t &program, 
           std::ofstream &out, 
           int *global_reg_ctr) {
  // 执行一些其他的必要操作
  // .data 存放数据？暂时不用
  #ifdef PRINT
    std::cout << "visiting program" << std::endl;
  #endif

  out << "  .text" << std::endl;
  out << "  .globl";

  // 访问所有全局变量，暂时不用
  Visit(program.values, out, global_reg_ctr, false);

  // 访问所有函数
  Visit(program.funcs, out, global_reg_ctr, false);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice, 
           std::ofstream &out, 
           int *global_reg_ctr,
           bool ret_only) {
  #ifdef PRINT
    const char *kind_str;
    switch (slice.kind) {
      case KOOPA_RSIK_FUNCTION:
        kind_str = "func";
        break;
      case KOOPA_RSIK_BASIC_BLOCK:
        kind_str = "bb";
        break;
      case KOOPA_RSIK_VALUE:
        kind_str = "val";
        break;
      default:
        kind_str = "unsupported";
        break;
    }
    std::cout << "visiting slice of type: " << kind_str << ", of len: " <<slice.len << std::endl; 
  #endif

  int *reg_ctr1 = new int;

  for (size_t i = 0; i < slice.len; ++i) {
    auto ptr = slice.buffer[i];
    // 根据 slice 的 kind 决定将 ptr 视作何种元素
    switch (slice.kind) {
      case KOOPA_RSIK_FUNCTION:
        // 访问函数
        Visit(reinterpret_cast<koopa_raw_function_t>(ptr), out, global_reg_ctr);
        break;

      case KOOPA_RSIK_BASIC_BLOCK:
        // 访问基本块
        Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr), out, global_reg_ctr);
        break;

      case KOOPA_RSIK_VALUE:
        // 访问指令
        Visit(reinterpret_cast<koopa_raw_value_t>(ptr), out, global_reg_ctr, reg_ctr1);
        break;

      default:
        // 我们暂时不会遇到其他内容, 于是不对其做任何处理
        assert(false);
    }
  }
}

// 访问函数
void Visit(const koopa_raw_function_t &func, 
           std::ofstream &out, 
           int *global_reg_ctr) {
  // 执行一些其他的必要操作
  //! There is only 1 function for now, thus this implementation is ok.
  //! For more than 1 functions, a rewrite is needed!

  #ifdef PRINT
    std::cout << "visiting function: " << func->name << std::endl;
  #endif

  // Write function name to `globl`, `+1` to skip @ at the beginning of func name
  auto func_name = func->name + 1;
  out << ' ' << func_name << std::endl;

  // Function entry point
  out << func_name << ':' << std::endl;
  
  // 访问所有基本块, function contents
  Visit(func->bbs, out, global_reg_ctr, false);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb, 
           std::ofstream &out, 
           int *global_reg_ctr) {
  // 执行一些其他的必要操作
  // ...

  #ifdef PRINT
    std::cout << "visiting basic block: " << bb->name << std::endl;
  #endif  

  // 访问所有指令
  Visit(bb->insts, out, global_reg_ctr, true);
}

// 访问指令
void Visit(const koopa_raw_value_t &value, 
           std::ofstream &out, 
           int *global_reg_ctr,
           int *reg_ctr) {
  #ifdef PRINT
    const char *kind_str;
    switch (value->kind.tag) {
      case KOOPA_RVT_RETURN:
        kind_str = "return";
        break;
      case KOOPA_RVT_INTEGER:
        kind_str = "integer";
        break;
      case KOOPA_RVT_BINARY:
        kind_str = "binary";
        break;
      default:
        kind_str = "unsupported";
        break;
    }
    std::cout << "visiting value of kind: " << kind_str << std::endl;
  #endif

  // 根据指令类型判断后续需要如何访问
  const auto &kind = value->kind;
  switch (kind.tag) {
    case KOOPA_RVT_RETURN:
      // 访问 return 指令, type: koopa_raw_return_t
      Visit(kind.data.ret, out, global_reg_ctr);
      break;

    case KOOPA_RVT_INTEGER:
      // 访问 integer 指令, type: koopa_raw_integer_t
      Visit(kind.data.integer, out, global_reg_ctr, reg_ctr);
      break;

    case KOOPA_RVT_BINARY:
      // Binary op, type: koopa_raw_binary_t
      Visit(kind.data.binary, out, global_reg_ctr, reg_ctr);
      break;

    default:
      // 其他类型暂时遇不到
      assert(false);
  }
}

// 访问对应类型指令的函数定义略
// 视需求自行实现
// Return instructions
void Visit(const koopa_raw_return_t &ret, 
           std::ofstream &out, 
           int *global_reg_ctr) {
  #ifdef PRINT
    std::cout << "visiting return instruction" << std::endl;
  #endif

  int *reg_ctr1 = new int;
  Visit(ret.value, out, global_reg_ctr, reg_ctr1);

  out << "mv a0, " << reg(*reg_ctr1) << '\n';
  out << "ret" << std::endl;
}

// Integer
void Visit(const koopa_raw_integer_t &integer, 
           std::ofstream &out,
           int *global_reg_ctr,
           int *reg_ctr) {
  auto int_val = integer.value;

  #ifdef PRINT
    std::cout << "visiting integer of value: " << int_val << std::endl;
  #endif

  out << "li " << reg(*global_reg_ctr) << ", " << int_val << '\n';
  *reg_ctr = *global_reg_ctr;
  *global_reg_ctr += 1;
}

// Binary instruction
void Visit(const koopa_raw_binary_t &bin, 
           std::ofstream &out, 
           int *global_reg_ctr,
           int *reg_ctr) {
  #ifdef PRINT
    std::cout << "visiting binary instruction of op type: " << bin.op << std::endl;
  #endif

  int *reg_ctr1 = new int;
  Visit(bin.lhs, out, global_reg_ctr, reg_ctr1);

  int *reg_ctr2 = new int;
  Visit(bin.rhs, out, global_reg_ctr, reg_ctr2);

  switch (bin.op) {
    case KOOPA_RBO_NOT_EQ:
      out << "sub " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      out << "snez " << reg(*global_reg_ctr + 1) << ", " << reg(*global_reg_ctr) << '\n';
      *reg_ctr = *global_reg_ctr + 1;
      *global_reg_ctr += 2;
      break;

    case KOOPA_RBO_EQ:
      out << "sub " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      out << "seqz " << reg(*global_reg_ctr + 1) << ", " << reg(*global_reg_ctr) << '\n';
      *reg_ctr = *global_reg_ctr + 1;
      *global_reg_ctr += 2;
      break;

    case KOOPA_RBO_GT:
      out << "sgt " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_LT:
      out << "slt " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_GE:
      out << "slt " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      out << "xori " << reg(*global_reg_ctr + 1) << ", " << reg(*global_reg_ctr) << ", 1\n";
      *reg_ctr = *global_reg_ctr + 1;
      *global_reg_ctr += 2;
      break;

    case KOOPA_RBO_LE:
      out << "sgt " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      out << "xori " << reg(*global_reg_ctr + 1) << ", " << reg(*global_reg_ctr) << ", 1\n";
      *reg_ctr = *global_reg_ctr + 1;
      *global_reg_ctr += 2;
      break;

    case KOOPA_RBO_ADD:
      out << "add " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_SUB:
      out << "sub " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_MUL:
      out << "mul " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_DIV:
      out << "div " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_MOD:
      out << "rem " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_AND:   //! Bit-wise and
      out << "and " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_OR:    //! Bit-wise or
      out << "or " << reg(*global_reg_ctr) << ", " << reg(*reg_ctr1) << ", " << reg(*reg_ctr2) << '\n';
      *reg_ctr = *global_reg_ctr;
      *global_reg_ctr += 1;
      break;

    case KOOPA_RBO_XOR:
      std::cerr << "error: unsupported binary op XOR" << std::endl;
      exit(-1);

    case KOOPA_RBO_SHL:
      std::cerr << "error: unsupported binary op SHL" << std::endl;
      exit(-1);

    case KOOPA_RBO_SHR:
      std::cerr << "error: unsupported binary op SHR" << std::endl;
      exit(-1);

    case KOOPA_RBO_SAR:
      std::cerr << "error: unsupported binary op SAR" << std::endl;
      exit(-1);
  };
}
