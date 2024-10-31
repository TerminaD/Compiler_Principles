# Compiler Principles Project

## 0 Repo Overview
This repo contains the code for the project of the Compiler Principles course. In this project, I impelmented an end-to-end compiler for the SysY language, which is a subset of C, in C++.

To run this project, follow the instructions in https://pku-minic.github.io/online-doc/#/.

## 1. Overview of the Compiler

### 1.1 Basic Functions

This compiler basically has the following functions:
1. Compiles SysY language code to Koopa IR.
2. Performs certain optimizations on Koopa IR code, with some thoughts and partial implementation on further optimization and register allocation.
3. Compiles Koopa IR code to RISC-V assembly code.

### 1.2 Main Features

The main features of this compiler are its simple and clear implementation, high correctness, and certain performance optimizations and register allocation.

In the two stages of compilation, this compiler recursively uses the AST data structure and the in-memory form of Koopa IR for code generation, and significantly restricts the parameter interface of functions.

This compiler performs some optimizations on binary operations and local array initialization, and plans to use a linear scan-based algorithm for register allocation. Unfortunately, due to limited time, this feature was not fully implemented.

This compiler passes all but 2 Koopa IR test cases, all but 4 RISC-V assembly test cases, passes all performance tests, and passes all self-collected test cases, achieving a high correctness rate.

## 2. Compiler Design

### 2.1 Main Modules

The compiler consists of four main modules:

`sysy.l` and `sysy.y` work together for lexical and syntax analysis.

`ast.cpp` and `ast.hpp` traverse the AST to generate Koopa IR code.

`asm.cpp` and `asm.hpp` were originally planned to optimize Koopa IR code and traverse the in-memory form of Koopa IR to generate RISC-V assembly code.

`symtab.cpp` and `symtab.hpp` manage the symbol table.

### 2.2 Main Data Structures

The most important data structures in the compiler are the AST, symbol table, in-memory form of Koopa IR, and the custom `val2name` and `name2offset` mappings.

Each node of the AST corresponds to one or more rules of the syntax analyzer, and their classes inherit from `BaseAST`, defined as follows:
```c++
class BaseAST {
public:
  virtual ~BaseAST() = default;

  std::string name;
  bool is_init_val_leaf;
  bool is_f_param_arr;

  virtual void Dump() const {};

  virtual void GenIR(bool *skip) {};
  virtual int GenIRVal() { return 0; };
  virtual void GenIRFParams(bool *skip, std::string func_ret_type) {};

  virtual int Eval() { return 0; };
};
```
The `name` can store string representations of integers, names of temporary symbols, and variable names. `is_init_val_leaf` and `is_f_param_arr` are used to mark whether the node is a leaf in the array initialization value tree and whether it is a formal parameter array. The `Dump` function is used to print the structure of the AST for debugging purposes. `GenIR`, `GenIRVal`, and `GenIRFParams` are three variants of `GenIR`, used in scenarios with no return value, returning an integer value, and generating IR for formal parameters, respectively. `Eval` is used to evaluate `ConstExp`.

Classes inheriting from `BaseAST` may also have their own unique attributes.

I use a stack of `SymFrame` to manage the symbol table. The LIFO nature of the stack aligns with the nested nature of the symbol table. `SymFrame` is a custom structure representing a scope in the symbol table. Each `SymFrame` uses an `unordered_map` from `string` to `STValue` to map names in SysY code to symbol data structures and includes functions for looking up and inserting symbols. The definition of `STValue` is as follows:
```c++
struct STValue {
  value_t type;
  int const_val;
  char var_start_char;
  int vap_num;
  func_ret_t func_ret_type;
  bool array_is_array;
  int ap_dims;
};
```

I will elaborate on the design considerations of the symbol table below.

In the in-memory form of Koopa IR, the operands of an instruction are represented by a pointer to the instruction that assigns a value to that operand. Meanwhile, all instructions are stored sequentially, and this instruction may have appeared earlier. Therefore, we need a way to record whether an instruction has already been generated into assembly code and where the generated result is stored. I used two `unordered_map`s, `val2name` and `name2offset`. The former maps a `koopa_raw_value_t` to a name, and the latter maps a name to an offset in the stack frame. The reason for this two-step mapping is to accommodate variables into this system: variables can be directly mapped to an offset in the stack frame using their names.


### 2.3 Main Design Considerations and Algorithm Choices

#### 2.3.1 Symbol Table Design Considerations
The data structure of the symbol table has been explained above, so it will not be repeated here. This section focuses on how the symbol table handles different types of symbols.

The symbol table can handle the following types of symbols: local variables, local constants, global variables, global constants, local variable arrays, local constant arrays, global variable arrays, global constant arrays, pointers, and functions.

For constants, the symbol table calculates their values at compile time and stores these values. For variables, the symbol table tracks how many times the original name has appeared and appends a numeric suffix to the original name to distinguish symbols with the same name in different scopes. For functions, the symbol table places all function symbols in the bottom-most scope, which is the global scope. Additionally, since functions are allowed to have the same names as other symbols, the symbol table adds different prefixes to functions and all other symbol types to distinguish them and allow for name collisions.

Except for global variables, global arrays, and functions, which are directly looked up in the bottom-most scope, other symbols are looked up starting from the top-most scope, and if not found, the search proceeds to the next lower scope. When entering and leaving a `Block`, the `SymFrame` stack is `push`ed and `pop`ed respectively to implement nested scopes.

#### 2.3.2 Register Allocation Strategy
Initially, I used a "no register" allocation strategy. Temporary symbols and variables were placed on the stack and accessed using offsets relative to the `sp` pointer.

I also attempted to design and implement a linear scan-based register allocation algorithm. The steps I designed are as follows:
1. Traverse the in-memory form of Koopa IR to build a control flow graph. During this process, estimate the number of times each basic block is traversed, which can be used to decide which symbols to spill.
2. Perform live variable analysis using the control flow graph and the instructions within each basic block.
3. During the generation of assembly code, update the live variable information before generating the assembly code corresponding to a `koopa_raw_value_t`. This includes:
  a. Reclaiming physical registers used by variables whose lifetimes have ended.
  b. Spilling data from all physical registers that will be used by instructions requiring fixed physical registers (e.g., `call`).
  c. Performing further spills if there are not enough free physical registers to execute the next instruction.
4. Within `koopa_raw_value_t`, when referencing another `koopa_raw_value_t`, use a data structure to record whether its information is currently stored in a physical register or a memory address.
Note that I reserved one physical register for loading spilled values.

Unfortunately, due to limited time and the difficulty of implementing this algorithm, it was not fully realized. Some of the code I wrote can be found in the `regalloc.cpp` file in the last commit of the `new` branch on GitLab.

#### 2.3.3 Optimization Strategies Adopted
1. Through testing, I found that not initializing local variable or constant arrays with zero values does not affect the correctness of the program, so I omitted this step.
2. I replaced registers assigned the value zero with `x0` to save on register usage.
3. In binary operations, I folded cases where the operand is zero.

#### 2.3.4 Other Supplementary Design Considerations
In the two-stage compilation process, I used incremental translation, each providing an `ostringstream` to directly output the newly generated code, reducing the complexity of data structures and memory usage.

When the current control branch of Koopa IR has already performed a `return`, no more code should be translated. To achieve this, each `GenIR` function takes a pointer to a boolean value as a parameter, and if its value is true, it stops translating code. To support complex control structures, at control flow branching instructions like `branch`, I create two new boolean pointers and pass them to the two branching `GenIR` functions.

## 3. Implementation of the Compiler

### 3.1 Coding Details of Each Stage

#### Lv1. main Function and Lv2. Initial Target Code Generation
In this part, we only need to use the GenIR function of the AST nodes to generate Koopa IR. During the generation of assembly code, we only need to consider `ret` and `integer`, which is relatively simple.

#### Lv3. Expressions
In this stage of syntax analysis, constructing the syntax to correctly implement the precedence of different operators is a challenge. Fortunately, the syntax rules are provided in the documentation.

Another challenge in the IR generation stage is how to implement logical "and" and "or" operations using bitwise "and" and "or" operations. My implementation method is as follows:

```c++
ir_emit << "\t%" << func_name_ctr << " = ne 0, " << l_and_exp->name << "\n";
ir_emit << "\t%" << func_name_ctr+1 << " = ne 0, " << eq_exp->name << "\n";
ir_emit << "\t%" << func_name_ctr+2 << " = and " << '%' << func_name_ctr << ", " << '%' << func_name_ctr+1 << "\n";
ir_emit << "\tstore %" << func_name_ctr+2 << ", " << ss_var_name << "\n";
```

```c++
ir_emit << "\t%" << func_name_ctr << " = or " << l_or_exp->name << ", " << l_and_exp->name << "\n";
ir_emit << "\t%" << func_name_ctr+1 << " = ne 0, %" << func_name_ctr << "\n";
ir_emit << "\tstore %" << func_name_ctr+1 << ", " << ss_var_name << "\n";
```

#### Lv4. Constants and Variables
To support constants and variables, we need to introduce a symbol table in this chapter. When handling constants, the symbol table evaluates their values at compile time and inserts a mapping from a `string` to an integer. When handling variables, the symbol table inserts a mapping from the variable's name in SysY code to its name in Koopa IR. To support variables with the same name in different scopes, I additionally maintain a mapping from names to integers, where the integer acts as a counter that increments each time a new symbol with that name is added and is used as a suffix.

```c++
void SymFrame::insert_const(std::string name, int value) {
  STValue item = {.type=const_type, 
                  .const_val=value};
  dict[prepend_cvap(name)] = item;
}

void SymFrame::insert_var(std::string name) {
  if (va_name_num.find(name) == va_name_num.end())
    va_name_num[name] = 1;
  STValue item = {.type = var_type, 
                  .var_start_char = '@',
                  .vap_num = va_name_num[name]++};
  dict[prepend_cvap(name)] = item;
}
```

To support variables and temporary symbols, I introduced two `unordered_map`s, `val2name` and `name2offset`, during the compilation of assembly code. These will not be elaborated here.


#### Lv5. Statement Blocks and Scopes
In this chapter, `Stmt` can also be a `Block`, which allows for nested scopes. We just need to add an AST node class:

```c++
class MatchedStmtAST3 : public BaseAST {
public:
  std::unique_ptr<BaseAST> block;

  void Dump() const override;

  void GenIR(bool *skip) override;
};
```

#### Lv6. if Statement
This chapter needs to address two main issues: modifying the syntax to remove the ambiguity of if/else and supporting short-circuit evaluation.

We introduce two non-terminal symbols, `MatchedStmt` and `OpenStmt`. The former represents `stmt` where `if` and `else` are paired, while the latter represents unpaired `stmt`. The corresponding rules are as follows:
```
Stmt
  : MatchedStmt 
  | OpenStmt 
  ;

MatchedStmt
  : LVal '=' Exp ';' 
  | Exp ';' 
  | ';' 
  | Block 
  | IF '(' Exp ')' MatchedStmt ELSE MatchedStmt 
  | RETURN Exp ';' 
  | RETURN ';' 
  ;

OpenStmt
  : IF '(' Exp ')' Stmt
  | IF '(' Exp ')' MatchedStmt ELSE OpenStmt
  ;
```

To support short-circuit evaluation, we introduce a set of labels for all `LAndExp` and `LOrExp` to allow jumps; and introduce a new variable to synthesize the final value obtained from different paths. Taking `LOrExp` as an example:

```c++
void LOrExpAST2::GenIR(bool *skip) {
  std::cout << "LOrExp2\n";

  if (*skip) return;

  auto then_bb_name = new_then_bb_name(branch_name_ctr);
  auto else_bb_name = new_else_bb_name(branch_name_ctr);
  auto end_bb_name = new_if_end_bb_name(branch_name_ctr);
  auto ss_var_name = new_ss_var_name(branch_name_ctr);
  branch_name_ctr++;

  l_or_exp->GenIR(skip);

  ir_emit << '\t' << ss_var_name << " = alloc i32\n";
  ir_emit << "\tbr " << l_or_exp->name << ", " << then_bb_name << ", " << else_bb_name << "\n\n";

  // "then" case: shortcircuited, return 1
  ir_emit << then_bb_name << ":\n"; 
  ir_emit << "\tstore 1, " << ss_var_name << "\n";
  ir_emit << "\tjump " << end_bb_name << "\n\n";

  // "else" case: not shortcircuited
  ir_emit << else_bb_name << ":\n";  
  l_and_exp->GenIR(skip);
  ir_emit << "\t%" << func_name_ctr << " = or " << l_or_exp->name << ", " << l_and_exp->name << "\n";
  ir_emit << "\t%" << func_name_ctr+1 << " = ne 0, %" << func_name_ctr << "\n";
  ir_emit << "\tstore %" << func_name_ctr+1 << ", " << ss_var_name << "\n";
  ir_emit << "\tjump " << end_bb_name << "\n\n";

  ir_emit << end_bb_name << ":\n";
  ir_emit << "\t%" << func_name_ctr+2 << " = load " << ss_var_name << "\n";

  name = '%' + std::to_string(func_name_ctr+2);
  func_name_ctr += 3;  
}
```

#### Lv7. while Statement
For the `while` statement, we similarly generate a set of labels for jumps:
```c++
void MatchedStmtAST8::GenIR(bool *skip) {
  std::cout << "MatchedStmt8\n";

  if (*skip) return;

  std::string entry_bb_name = new_while_entry_bb_name(while_name_ctr);
  std::string body_bb_name = new_while_body_bb_name(while_name_ctr);
  std::string end_bb_name = new_while_end_bb_name(while_name_ctr);
  while_name_ctr++;

  ir_emit << "\tjump " << entry_bb_name << "\n\n";

  while_stack.push(while_name_ctr-1);
  ir_emit << entry_bb_name << ":\n";
  exp->GenIR(skip);
  ir_emit << "\tbr " << exp->name << ", " << body_bb_name << ", " << 
  end_bb_name << "\n\n";

  ir_emit << body_bb_name << ":\n";
  bool* skip1 = new bool;
  *skip1 = false;
  matched_stmt->GenIR(skip1);
  if (!*skip1)
    ir_emit << "\tjump " << entry_bb_name << "\n\n";
  else
    ir_emit << '\n';
  delete skip1;

  while_stack.pop();
  ir_emit << end_bb_name << ":\n";
}
```

As for the `break` and `continue` instructions, we use a stack to maintain the label number of the innermost `while` loop:
```c++
std::stack<int> while_stack;
```

Taking `break` as an example, we first jump to the end basic block of the `while` loop, then print a placeholder to connect the subsequent code and avoid syntax errors:
```c++
void MatchedStmtAST6::GenIR(bool *skip) {
  std::cout << "MatchedStmt6\n";

  if (*skip) return;

  ir_emit << "\tjump " << new_while_end_bb_name(while_stack.top()) << "\n\n";

  ir_emit << new_break_placeholder_name(break_placeholder_ctr) << ":\n";
  break_placeholder_ctr++;
}
```

#### Lv8. Functions and Global Variables
To support function calls, we need to insert code at four points: before the caller calls, when the callee enters, before the callee returns, and after the caller calls.

Before the caller calls: Store the parameters in registers and the stack frame.

When the callee enters: Save the parameters, which are either stored in registers or the stack frame, to the new stack frame positions. Note that the original stack frame offset needs to be increased by the size of this function's stack frame.

Before the callee returns: If the called function's return value is not `void`, store the return value in the `a0` register.

After the caller calls: Store the return value from the `a0` register in the stack frame.

For Koopa runtime functions, we only need to print their declarations as they are when generating IR, and skip functions with zero basic blocks when generating assembly code.

For global variables, we need to add a new type in the symbol table. The calculation of the initial value of global variables is the same as that of global constants.

#### Lv9. Arrays
In this chapter, we need to address three core issues:
1. How to normalize data
2. Handling data types
3. Handling load times

We need to normalize the initial values of global arrays to a level that is easy for subsequent assembly code generation. Here, I used a recursive algorithm, with one of its parameters being a range. If an element of the initial value is a list, the function is called again on a smaller range. This function has several variants, respectively suitable for constant arrays, global variable arrays, and local variable arrays. Taking the variant for constant arrays as an example:
```c++
void pad_const(std::vector<int> &res, const std::vector<int> &cumprod_dims,
               std::unique_ptr<BaseAST> &init_val, // ConstInitValAST
               const int start, const int end) {
  std::cout << "pad_const\n";

  if (init_val->is_init_val_leaf) {
    res[start] = init_val->Eval();
    return;
  }

  int local_curr_len = 0;
  for (auto &civ: 
       static_cast<ConstInitValAST2 *>(init_val.get())->const_init_val_list) {
    // civ is ConstInitVal

    if (civ->is_init_val_leaf) {
      pad_const(res, cumprod_dims,
                civ, 
                start+local_curr_len, start+local_curr_len+1);
      local_curr_len++;
    }

    else {
      bool match = false;

      for (int i = 0; i < cumprod_dims.size(); i++) {
        if (local_curr_len % cumprod_dims[i] == 0) {
          pad_const(res, 
                    std::vector<int>(
                      cumprod_dims.begin()+i+1, 
                      cumprod_dims.end()),
                    civ,
                    start+local_curr_len, 
                    start+local_curr_len+cumprod_dims[i]);
          match = true;
          local_curr_len += cumprod_dims[i];
          break;
        }
      }

      if (!match) {
        std::cerr << "error: invalid const init value for array\n";
        exit(39);
      }
    }
  }

  // Fill the remaining spots until `end` with 0s
  for (int i = start+local_curr_len; i < end; i++)
    res[i] = 0;             
}
```

When generating assembly code, we also need to expand the `aggregate` type into a one-dimensional array for subsequent assignments. I used a recursive algorithm for this:
```c++
void unroll_aggregate(const koopa_raw_aggregate_t &aggregate, 
                      std::vector<int> &res) {
  koopa_raw_value_t item;
  for (int i = 0; i < aggregate.elems.len; i++) {
    item = reinterpret_cast<koopa_raw_value_t>(aggregate.elems.buffer[i]);

    if (item->kind.tag == KOOPA_RVT_INTEGER) {
      res.push_back(Visit(item->kind.data.integer));

    } else if (item->kind.tag == KOOPA_RVT_AGGREGATE) {
      unroll_aggregate(item->kind.data.aggregate, res);

    } else {
      std::cerr << "error: invalid aggregate element" << '\n';
      exit(51);
    }
  }
}
```

To determine the size of elements in `getelemptr` and `getptr`, I maintain a mapping from stack frame offsets to array/pointer types. I use a vector of integers to represent types, where 1 stands for "pointer", 2 stands for "array", and 3 stands for "integer". We can parse the type from the `ty` field in `koopa_raw_value_t`:
```c++
std::vector<int> parse_ptr_type(const koopa_raw_type_kind *ty) {
  if (ty->tag == KOOPA_RTT_INT32) {
    return {3};

  } else if (ty->tag == KOOPA_RTT_ARRAY) {
    auto prev_vec = parse_ptr_type(ty->data.array.base);
    prev_vec.insert(prev_vec.begin(), 2);
    return prev_vec;

  } else if (ty->tag == KOOPA_RTT_POINTER) {
    auto prev_vec = parse_ptr_type(ty->data.pointer.base);
    prev_vec.insert(prev_vec.begin(), 1);
    return prev_vec;
  
  } else {
    std::cerr << "unexpected type in ptr\n";
    exit(56);
  }
}
```

In `getelemptr` and `getptr`, the offset needs to be multiplied by the size of the element. It should be noted that `getelemptr` and `getptr` will change the type, with the former removing the leading 1, while the latter remains unchanged.

In the previous sections, if we have the stack frame offset of a value, we only need to add this amount to the `sp` pointer to get the memory address of this value. However, when dealing with arrays, we might get the memory address of the memory address storing the array. Therefore, we need to maintain a data structure to record when an additional `lw` is needed in the assembly code. `std::unordered_set<int> addi_load_offsets` records when an additional `lw` is needed in the assembly code, and the values obtained by `getelemptr` and `getptr` will be added to it. In functions with pointers as parameters, the first `load` of the parameter does not require an additional `lw`, which is maintained by `std::unordered_set<int> skip_load_addi_load_offsets`.

### 3.2 Tool Software Introduction
1. `Flex/bison`: Used for lexical analysis and syntax analysis
2. `Libkoopa`: Used to generate the in-memory form of Koopa IR and provide runtime functions
3. `Docker`: Used to deploy a unified runtime environment
4. `Git`, `GitLab`: Used for version control and code submission

### 3.3 Testing

During this assignment, I conducted targeted tests on several issues:
1. The number of `lw` operations for arrays and pointers
2. Function names can be the same as other symbol names

For the first issue, I performed permutations and combinations for all situations:
1. Arrays (global/local)
  a. Fully indexed, used as l-value
  b. Fully indexed, used as r-value
  c. Partially indexed, passed as pointer parameter to function

2. Pointers (`*i32`, `*[i32, 2]`, `*[[i32, 2], 2]`)
  a. Fully indexed, used as l-value
  b. Fully indexed, used as r-value
  c. Partially indexed, passed again as pointer parameter to function

For the second issue, I found that segmentation faults occurred only when there were functions and non-function symbols with the same name. By checking the debug information printed by the compiler at runtime, I discovered the problem and solved it by modifying the symbol table.

Meanwhile, I also included the sysy-testsuit-collection repo on GitHub (https://github.com/jokerwyt/sysy-testsuit-collection.git) in the testing scope, which helped identify bugs that local tests could not find.

## 4. Project Summary

### 4.1 Gains and Experiences
I realized the difficulty of designing and implementing a compiler. Even just implementing a functionally (mostly) correct compiler involves many engineering considerations. In the last few days of this assignment, I also tried to implement a linear scan-based register allocation algorithm, but its workload and implementation details far exceeded my expectations. It is hard to imagine how industrial-grade compilers like GDB and LLVM are written.

### 4.2 Difficulties in the Learning Process and Suggestions for the Internship Process and Content
The introduction of arrays means that the stack frame may store addresses of arrays instead of values, possibly requiring an additional `lw`. I personally think this point is difficult to realize and handle correctly. If the documentation could provide more reminders or suggest a better implementation method, it would be very helpful.

Some commands in Koopa IR require additional temporary registers, making it less friendly to linear scan register allocation.

### 4.3 Suggestions for the Content and Method of Teacher's Lectures
I personally hope that the content of the practical class lectures can be more closely related to the lab. Currently, the lecture content overlaps a lot with the theoretical class and does not help much with the lab.
