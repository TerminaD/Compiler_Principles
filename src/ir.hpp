#pragma once

#include <fstream>

#include "koopa.h"


int generate_mem_ir(const char *irp, std::ofstream &out);

// Visit a program
void Visit(const koopa_raw_program_t &program, std::ofstream &out);

// Visit a slice
void Visit(const koopa_raw_slice_t &slice, std::ofstream &out);

// Visit a function
void Visit(const koopa_raw_function_t &func, std::ofstream &out);

// Visit a basic block
void Visit(const koopa_raw_basic_block_t &bb, std::ofstream &out);

// Visit a value/instruction
void Visit(const koopa_raw_value_t &value, std::ofstream &out);

// Visit a return instruction
void Visit(const koopa_raw_return_t &ret, std::ofstream &out);

// Visit an integer
void Visit(const koopa_raw_integer_t &ret, std::ofstream &out);
