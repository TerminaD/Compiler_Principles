#pragma once

#include <fstream>

#include "koopa.h"


int generate_asm(const char *irp, std::ofstream &out);

// Visit a program
void Visit(const koopa_raw_program_t &program, 
           std::ofstream &out, 
           int *global_reg_ctr);

// Visit a slice
void Visit(const koopa_raw_slice_t &slice, 
           std::ofstream &out, 
           int *global_reg_ctr);

// Visit a function
void Visit(const koopa_raw_function_t &func, 
           std::ofstream &out, 
           int *global_reg_ctr);

// Visit a basic block
void Visit(const koopa_raw_basic_block_t &bb, 
           std::ofstream &out, 
           int *global_reg_ctr);

// Visit a value/instruction
void Visit(const koopa_raw_value_t &value, 
           std::ofstream &out, 
           int *global_reg_ctr,
           int *reg_ctr);

// Visit a return instruction
void Visit(const koopa_raw_return_t &ret, 
           std::ofstream &out, 
           int *global_reg_ctr);

// Visit an integer
void Visit(const koopa_raw_integer_t &ret, 
           std::ofstream &out, 
           int *global_reg_ctr,
           int *reg_ctr);

// Visit a binary instruction
void Visit(const koopa_raw_binary_t &bin, 
           std::ofstream &out, 
           int *global_reg_ctr,
           int *reg_ctr);
