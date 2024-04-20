#include <cassert>
#include <iostream>

#include "koopa.h"
#include "asm.hpp"


int generate_asm(const char *irp, std::ofstream &out) {
  // Convert IR to memory form
  koopa_program_t program;
  koopa_error_code_t koopa_ret = koopa_parse_from_string(irp, &program);
  assert(koopa_ret == KOOPA_EC_SUCCESS);
  koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
  koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
  koopa_delete_program(program);

  Visit(raw, out);

  // Release memory
  koopa_delete_raw_program_builder(builder);

  return 0;
}

// 访问 raw program
void Visit(const koopa_raw_program_t &program, std::ofstream &out) {
  // 执行一些其他的必要操作
  // .data 存放数据？暂时不用
  #ifdef PRINT
    std::cout << "visiting program" << std::endl;
  #endif

  out << "  .text" << std::endl;
  out << "  .globl";

  // 访问所有全局变量，暂时不用
  Visit(program.values, out);

  // 访问所有函数
  Visit(program.funcs, out);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice, std::ofstream &out) {
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

  for (size_t i = 0; i < slice.len; ++i) {
    auto ptr = slice.buffer[i];
    // 根据 slice 的 kind 决定将 ptr 视作何种元素
    switch (slice.kind) {
      case KOOPA_RSIK_FUNCTION:
        // 访问函数
        Visit(reinterpret_cast<koopa_raw_function_t>(ptr), out);
        break;

      case KOOPA_RSIK_BASIC_BLOCK:
        // 访问基本块
        Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr), out);
        break;

      case KOOPA_RSIK_VALUE:
        // 访问指令
        Visit(reinterpret_cast<koopa_raw_value_t>(ptr), out);
        break;

      default:
        // 我们暂时不会遇到其他内容, 于是不对其做任何处理
        assert(false);
    }
  }
}

// 访问函数
void Visit(const koopa_raw_function_t &func, std::ofstream &out) {
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
  Visit(func->bbs, out);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb, std::ofstream &out) {
  // 执行一些其他的必要操作
  // ...

  #ifdef PRINT
    std::cout << "visiting basic block: " << bb->name << std::endl;
  #endif  

  // 访问所有指令
  Visit(bb->insts, out);
}

// 访问指令
void Visit(const koopa_raw_value_t &value, std::ofstream &out) {
  #ifdef PRINT
    const char *kind_str;
    switch (value->kind.tag) {
      case KOOPA_RVT_RETURN:
        kind_str = "return";
        break;
      case KOOPA_RVT_INTEGER:
        kind_str = "integer";
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
      Visit(kind.data.ret, out);
      break;

    case KOOPA_RVT_INTEGER:
      // 访问 integer 指令, type: koopa_raw_integer_t
      Visit(kind.data.integer, out);
      break;

    default:
      // 其他类型暂时遇不到
      assert(false);
  }
}

// 访问对应类型指令的函数定义略
// 视需求自行实现
// Return instructions
void Visit(const koopa_raw_return_t &ret, std::ofstream &out) {
  #ifdef PRINT
    std::cout << "visiting return instruction" << std::endl;
  #endif

  Visit(ret.value, out);

  out << "  ret" << std::endl;
}

// Integer
void Visit(const koopa_raw_integer_t &integer, std::ofstream &out) {
  auto int_val = integer.value;

  #ifdef PRINT
    std::cout << "visiting integer of value: " << int_val << std::endl;
  #endif

  out << "  li a0, " << int_val << std::endl;
}
