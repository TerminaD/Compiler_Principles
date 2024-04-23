#pragma once

#include <cstddef>
#include <fstream>
#include <cassert>

#include "koopa.h"


// Allocates a register
class AsmRegAlloc {
public:
	size_t ctr;

	std::string gen_reg() {
		switch (ctr) {
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
		ctr = (ctr+1) % 15;
	}
};


int generate_asm(const char *irp, std::ofstream &out);

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

// Visit a binary instruction
void Visit(const koopa_raw_binary_t &bin, std::ofstream &out);
