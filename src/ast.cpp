#include <cassert>
#include <csignal>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdatomic.h>
#include <string>
#include <typeinfo>
#include <vector>

#include "ast.hpp"
#include "symtab.hpp"

SymTab sym_tab = SymTab();
bool var_decl;

// -----------------------------------------------------------------

void CompUnitAST::Dump() const {
  std::cout << "CompUnitAST { ";
  func_def->Dump();
  std::cout << " }";
}

int CompUnitAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return func_def->GenIR(global_name_ctr, oss);
}

// -----------------------------------------------------------------

void DeclAST1::Dump() const {
  std::cout << "DeclAST { ";
  const_decl->Dump();
  std::cout << " }";
}

int DeclAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return const_decl->GenIR(global_name_ctr, oss);
}

void DeclAST2::Dump() const {
  std::cout << "DeclAST { ";
  var_decl->Dump();
  std::cout << " }";
}

int DeclAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return var_decl->GenIR(global_name_ctr, oss);
}

void ConstDeclAST::Dump() const {
  std::cout << "ConstDeclAST { ";
  b_type->Dump();
  std::cout << ", ";
  const_def->Dump();
  std::cout << ", ";
  for (int i = 0; i < const_def_list_vec.size(); ++i) {
    const_def_list_vec[i]->Dump();
    std::cout << ", ";
  }
  std::cout << " }";
}

int ConstDeclAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif

  if (b_type->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: b_type in ConstDeclAST" << std::endl;
    exit(-1);
  }

  if (const_def->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: const_def in ConstDeclAST" << std::endl;
    exit(-1);
  }

  for (int i = 0; i < const_def_list_vec.size(); ++i) {
    if (const_def_list_vec[i]->GenIR(global_name_ctr, oss) < 0) {
      std::cerr << "error: const_def_list in ConstDeclAST" << std::endl;
      exit(-1);
    }
  }

  return 0;
}

void ConstDefListAST::Dump() const {}

int ConstDefListAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return 0;
}

void BTypeAST::Dump() const { std::cout << "BTypeAST { " << type << " }"; }

int BTypeAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return 0;
}

void ConstDefAST::Dump() const {
  std::cout << "ConstDefAST { " << ident << ", ";
  const_init_val->Dump();
  std::cout << " }";
}

int ConstDefAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  int val = const_init_val->eval();
  sym_tab.insert_const(ident, val);
  return 0;
}

void ConstInitValAST::Dump() const {
  std::cout << "ConstInitValAST { ";
  const_exp->Dump();
  std::cout << " }";
}

int ConstInitValAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (const_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: const_exp in ConstInitValAST" << std::endl;
    exit(-1);
  }
  name = const_exp->name;
  return 0;
}

int ConstInitValAST::eval() { return const_exp->eval(); }

void VarDeclAST::Dump() const {
  std::cout << "VarDeclAST { ";
  b_type->Dump();
  std::cout << ", ";
  var_def->Dump();
  std::cout << ", ";
  for (int i = 0; i < var_def_list_vec.size(); ++i) {
    var_def_list_vec[i]->Dump();
    std::cout << ", ";
  }
  std::cout << " }";
}

int VarDeclAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  if (var_def->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: var_def in VarDeclAST" << std::endl;
    exit(-1);
  }
  for (auto &var_def_item : var_def_list_vec) {
    if (var_def_item->GenIR(global_name_ctr, oss) < 0) {
      std::cerr << "error: var_def_list in VarDeclAST" << std::endl;
      exit(-1);
    }
  }
  var_decl = true;
  return 0;
}

void VarDefListAST::Dump() const {}

int VarDefListAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  return 0;
}

void VarDefAST::Dump() const {
  std::cout << "VarDefAST { " << ident << ", ";
  init_val->Dump();
  std::cout << " }";
}

int VarDefAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  sym_tab.insert_var(ident, (std::string("@") + ident).c_str());
  oss << '@' << ident << " = alloc i32\n";
  if (init_val != nullptr) {
    if (init_val->GenIR(global_name_ctr, oss) < 0) {
      std::cerr << "error: init_val in VarDefAST" << std::endl;
      exit(-1);
    }
    oss << "store " << init_val->name << ", @" << ident << "\n";
  }
  return 0;
}

void InitValAST::Dump() const {
  std::cout << "InitValAST { ";
  exp->Dump();
  std::cout << " }";
}

int InitValAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in InitValAST" << std::endl;
    exit(-1);
  }
  name = exp->name;
  return 0;
}

// -----------------------------------------------------------------

void FuncDefAST::Dump() const {
  std::cout << "FuncDefAST { ";
  func_type->Dump();
  std::cout << ", " << ident << ", ";
  block->Dump();
  std::cout << " }";
}

int FuncDefAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  oss << "fun @" << ident << "(): ";

  if (func_type->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: func_type in FuncDefAST" << std::endl;
    exit(-1);
  }

  oss << " { ";

  if (block->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: block in FuncDefAST" << std::endl;
    exit(-1);
  }

  oss << " } ";

  return 0;
}

void FuncTypeAST::Dump() const {
  std::cout << "FuncTypeAST { " << func_type << " }";
}

int FuncTypeAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (func_type == "int")
    oss << "i32";
  else {
    std::cerr << "error: non-int data type not supported" << std::endl;
    exit(-1);
  }
  return 0;
}

// -----------------------------------------------------------------

void BlockAST::Dump() const {
  std::cout << "BlockAST { ";
  for (auto &block_item : block_item_list_vec) {
    block_item->Dump();
    std::cout << ", ";
  }
  std::cout << " }";
}

int BlockAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif

  oss << "\%entry: ";

  for (auto &block_item : block_item_list_vec) {
    if (block_item->GenIR(global_name_ctr, oss) < 0) {
      std::cerr << "error: block_item in BlockAST" << std::endl;
      exit(-1);
    }
  }

  return 0;
}

void BlockItemListAST::Dump() const {}

int BlockItemListAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return 0;
}

void BlockItemAST1::Dump() const {
  std::cout << "BlockItemAST1 { ";
  decl->Dump();
  std::cout << " }";
}

int BlockItemAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (decl->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: decl in BlockItemAST1" << std::endl;
    exit(-1);
  }
  return 0;
}

void BlockItemAST2::Dump() const {
  std::cout << "BlockItemAST2 { ";
  stmt->Dump();
  std::cout << " }";
}

int BlockItemAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (stmt->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: stmt in BlockItemAST2" << std::endl;
    exit(-1);
  }
  return 0;
}

void StmtAST1::Dump() const {
  std::cout << "StmtAST1 { ";
  exp->Dump();
  std::cout << " }";
}

int StmtAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in StmtAST" << std::endl;
    exit(-1);
  }

  oss << "ret " << exp->name << "\n";

  var_decl = false;
  return 0;
}

void StmtAST2::Dump() const {
  std::cout << "StmtAST2 { ";
  l_val->Dump();
  std::cout << ", ";
  exp->Dump();
  std::cout << " }";
}

int StmtAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  if (l_val->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_val in StmtAST2" << std::endl;
    exit(-1);
  }
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in StmtAST2" << std::endl;
    exit(-1);
  }
  auto l_val_ident = static_cast<LValAST *>(l_val.get())->ident;
  if (sym_tab.exists_var(l_val_ident)) {
    oss << "store " << exp->name << ", " << '@' << l_val_ident << "\n";
  } else {
    std::cerr << "error: variable not found in StmtAST2" << std::endl;
    exit(-1);
  }
  return 0;
}

// -----------------------------------------------------------------

void ExpAST::Dump() const {
  std::cout << "ExpAST { ";
  l_or_exp->Dump();
  std::cout << " }";
}

int ExpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (l_or_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_or_exp in ExpAST" << std::endl;
    exit(-1);
  }

  name = l_or_exp->name;

  return 0;
}

int ExpAST::eval() { return l_or_exp->eval(); }

void LValAST::Dump() const { std::cout << "LValAST { " << ident << " }"; }

int LValAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif

  switch (sym_tab.exists(ident)) {
    case 1:   // const
      name = std::to_string(sym_tab.lookup_const(ident));
      return 0;

    case 2:   // var
      //! Cause an additional variable load
      oss << '%' << *global_name_ctr << " = load " << '@' << ident << "\n";
      name = '%' + std::to_string(*global_name_ctr);
      *global_name_ctr += 1;
      
      return 0;

    default:  // LVal does not exist or unexpected behavior
      std::cerr << "error: in LValAST" << std::endl;
      exit(-1);
  }
}

int LValAST::eval() {
  if (sym_tab.exists(ident) == 1)
    return sym_tab.lookup_const(ident);
  else {
    std::cerr << "error: cannot evaluate variable or undefined" << std::endl;
    exit(-1);
  }
}

void PrimaryExpAST1::Dump() const {
  std::cout << "PrimaryExpAST1 { ( ";
  exp->Dump();
  std::cout << " ) }";
}

int PrimaryExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in PrimaryExpAST1" << std::endl;
    exit(-1);
  }

  name = exp->name;

  return 0;
}

int PrimaryExpAST1::eval() { return exp->eval(); }

void PrimaryExpAST2::Dump() const {
  std::cout << "PrimaryExpAST2 { ";
  number->Dump();
  std::cout << " }";
}

int PrimaryExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (number->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: number in PrimaryExpAST2" << std::endl;
    exit(-1);
  }

  name = number->name;

  return 0;
}

int PrimaryExpAST2::eval() { return number->eval(); }

void PrimaryExpAST3::Dump() const {
  std::cout << "PrimaryExpAST3 { ";
  l_val->Dump();
  std::cout << " }";
}

int PrimaryExpAST3::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (l_val->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_val in PrimaryExpAST3" << std::endl;
    exit(-1);
  }

  name = l_val->name;

  return 0;
}

int PrimaryExpAST3::eval() { return l_val->eval(); }

void NumberAST::Dump() const {
  std::cout << "NumberAST { " << int_const << " }";
}

int NumberAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  name = std::to_string(int_const);

  return 0;
}

int NumberAST::eval() { return int_const; }

void UnaryExpAST1::Dump() const {
  std::cout << "UnaryExpAST1 { ";
  primary_exp->Dump();
  std::cout << " }";
}

int UnaryExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (primary_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: primary_exp in UnaryExpAST1" << std::endl;
    exit(-1);
  }

  name = primary_exp->name;

  return 0;
}

int UnaryExpAST1::eval() { return primary_exp->eval(); }

void UnaryExpAST2::Dump() const {
  std::cout << "UnaryExpAST2 { ";
  unary_op->Dump();
  std::cout << ' ';
  unary_exp->Dump();
  std::cout << " }";
}

int UnaryExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  int ret;
  if ((ret = unary_op->GenIR(global_name_ctr, oss)) < 0) {
    std::cerr << "error: unary_op in UnaryExpAST2" << std::endl;
    exit(-1);
  }

  if (unary_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: unary_exp in UnaryExpAST2" << std::endl;
    exit(-1);
  }

// If operand can be calculated at compile-time
#ifndef NOFOLD
  if (unary_exp->name[0] != '%') {
    switch (ret) {
    case 1:
      name = unary_exp->name;
      return 0;

    case 2:
      name = std::to_string(-std::stoi(unary_exp->name));
      return 0;

    case 3:
      name = std::to_string(!std::stoi(unary_exp->name));
      return 0;

    default:
      std::cerr << "error: undefined unary operator in UnaryExpAST2"
                << std::endl;
      exit(-1);
    }
  }
#endif

  switch (ret) {
  case 1: // positive
    name = unary_exp->name;
    return 0;

  case 2: // negative
    name = '%' + std::to_string(*global_name_ctr);
    *global_name_ctr += 1;

    oss << name << " = sub 0, " << unary_exp->name << "\n";

    return 0;

  case 3: // not
    name = '%' + std::to_string(*global_name_ctr);
    *global_name_ctr += 1;

    oss << name << " = eq 0, " << unary_exp->name << "\n";

    return 0;

  default:
    std::cerr << "error: undefined unary operator in UnaryExpAST2" << std::endl;
    exit(-1);
  }
}

int UnaryExpAST2::eval() {
  int val = unary_exp->eval();

  switch (static_cast<UnaryOpAST *>(unary_op.get())->op) {
  case positive_op:
    return val;

  case negative_op:
    return -val;

  case not_op:
    return !val;

  default:
    std::cerr << "error: undefined unary operator in UnaryExpAST2" << std::endl;
    exit(-1);
  }
}

void UnaryOpAST::Dump() const {
  std::cout << "UnaryOp { ";
  switch (op) {
  case positive_op:
    std::cout << '+';
    break;
  case negative_op:
    std::cout << '-';
    break;
  case not_op:
    std::cout << '!';
    break;
  }
  std::cout << " }";
}

int UnaryOpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return op;
}

void MulExpAST1::Dump() const {
  std::cout << "MulExpAST1 { ";
  unary_exp->Dump();
  std::cout << " }";
}

int MulExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (unary_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error" << std::endl;
    exit(-1);
  }

  name = unary_exp->name;

  return 0;
}

int MulExpAST1::eval() { return unary_exp->eval(); }

void MulExpAST2::Dump() const {
  std::cout << "MulExpAST2 { ";
  mul_exp->Dump();
  std::cout << ' ';
  bin_pri_op->Dump();
  std::cout << ' ';
  unary_exp->Dump();
  std::cout << " }";
}

int MulExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (mul_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: mul_exp in MulExpAST2" << std::endl;
    exit(-1);
  }

  int ret;
  if ((ret = bin_pri_op->GenIR(global_name_ctr, oss)) < 0) {
    std::cerr << "error: unary_op in MulExpAST2" << std::endl;
    exit(-1);
  }

  if (unary_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: unary_exp in MulExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (mul_exp->name[0] != '%' && unary_exp->name[0] != '%') {
    int val1 = std::stoi(mul_exp->name);
    int val2 = std::stoi(unary_exp->name);

    switch (ret) {
    case 1:
      name = std::to_string(val1 * val2);
      return 0;

    case 2:
      name = std::to_string(val1 / val2);
      return 0;

    case 3:
      name = std::to_string(val1 % val2);
      return 0;

    default:
      std::cerr << "error: undefined operator in MulExpAST2" << std::endl;
      exit(-1);
    }
  }
#endif

  name = '%' + std::to_string(*global_name_ctr);
  *global_name_ctr += 1;

  switch (ret) {
  case 1: // mul
    oss << name << " = mul " << mul_exp->name << ", " << unary_exp->name
        << "\n";
    return 0;

  case 2: // div
    oss << name << " = div " << mul_exp->name << ", " << unary_exp->name
        << "\n";
    return 0;

  case 3: // mod
    oss << name << " = mod " << mul_exp->name << ", " << unary_exp->name
        << "\n";
    return 0;

  default:
    std::cerr << "error: undefined operator in MulExpAST2" << std::endl;
    exit(-1);
  }
}

int MulExpAST2::eval() {
  int val1 = mul_exp->eval();
  int val2 = unary_exp->eval();

  switch (static_cast<BinPriOpAST *>(bin_pri_op.get())->op) {
  case mul_op:
    return val1 * val2;

  case div_op:
    return val1 / val2;

  case mod_op:
    return val1 % val2;

  default:
    std::cerr << "error: undefined operator in MulExpAST2" << std::endl;
    exit(-1);
  }
}

void BinPriOpAST::Dump() const {
  std::cout << "BinPriOpAST { ";
  switch (op) {
  case mul_op:
    std::cout << '*';
    break;
  case div_op:
    std::cout << '/';
    break;
  case mod_op:
    std::cout << '%';
    break;
  }
  std::cout << " }";
}

int BinPriOpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return op;
}

void AddExpAST1::Dump() const {
  std::cout << "AddExpAST1 { ";
  mul_exp->Dump();
  std::cout << " }";
}

int AddExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (mul_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error" << std::endl;
    exit(-1);
  }

  name = mul_exp->name;

  return 0;
}

int AddExpAST1::eval() { return mul_exp->eval(); }

void AddExpAST2::Dump() const {
  std::cout << "AddExpAST2 { ";
  add_exp->Dump();
  std::cout << ' ';
  bin_op->Dump();
  std::cout << ' ';
  mul_exp->Dump();
  std::cout << " }";
}

int AddExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (add_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: add_exp in AddExpAST2" << std::endl;
    exit(-1);
  }

  int ret;
  if ((ret = bin_op->GenIR(global_name_ctr, oss)) < 0) {
    std::cerr << "error: bin_op in AddExpAST2" << std::endl;
    exit(-1);
  }

  if (mul_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: mul_exp in AddExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (add_exp->name[0] != '%' && mul_exp->name[0] != '%') {
    int val1 = std::stoi(add_exp->name);
    int val2 = std::stoi(mul_exp->name);

    switch (ret) {
    case 1:
      name = std::to_string(val1 + val2);
      return 0;

    case 2:
      name = std::to_string(val1 - val2);
      return 0;

    default:
      std::cerr << "error: undefined operator in AddExpAST2" << std::endl;
      exit(-1);
    }
  }
#endif

  name = '%' + std::to_string(*global_name_ctr);
  *global_name_ctr += 1;

  switch (ret) {
  case 1: // add
    oss << name << " = add " << add_exp->name << ", " << mul_exp->name << "\n";
    return 0;

  case 2: // sub
    oss << name << " = sub " << add_exp->name << ", " << mul_exp->name << "\n";
    return 0;

  default:
    std::cerr << "error: undefined operator in AddExpAST2" << std::endl;
    exit(-1);
  }
}

int AddExpAST2::eval() {
  int val1 = add_exp->eval();
  int val2 = mul_exp->eval();

  switch (static_cast<BinOpAST *>(bin_op.get())->op) {
  case add_op:
    return val1 + val2;

  case sub_op:
    return val1 - val2;

  default:
    std::cerr << "error: undefined operator in AddExpAST2" << std::endl;
    exit(-1);
  }
}

void BinOpAST::Dump() const {
  std::cout << "BinOpAST { ";
  switch (op) {
  case add_op:
    std::cout << '+';
    break;
  case sub_op:
    std::cout << '-';
    break;
  }
  std::cout << " }";
}

int BinOpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return op;
}

void RelExpAST1::Dump() const {
  std::cout << "RelExpAST1 { ";
  add_exp->Dump();
  std::cout << " }";
}

int RelExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (add_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error in RelExpAST1" << std::endl;
    exit(-1);
  }

  name = add_exp->name;

  return 0;
}

int RelExpAST1::eval() { return add_exp->eval(); }

void RelExpAST2::Dump() const {
  std::cout << "RelExpAST2 { ";
  rel_exp->Dump();
  std::cout << ' ';
  rel_op->Dump();
  std::cout << ' ';
  add_exp->Dump();
  std::cout << " }";
}

int RelExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (rel_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: rel_exp in RelExpAST2" << std::endl;
    exit(-1);
  }

  int ret;
  if ((ret = rel_op->GenIR(global_name_ctr, oss)) < 0) {
    std::cerr << "error: rel_op in RelExpAST2" << std::endl;
    exit(-1);
  }

  if (add_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: add_exp in RelExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (rel_exp->name[0] != '%' && add_exp->name[0] != '%') {
    int val1 = std::stoi(rel_exp->name);
    int val2 = std::stoi(add_exp->name);

    switch (ret) {
    case 1:
      name = std::to_string(val1 < val2);
      return 0;

    case 2:
      name = std::to_string(val1 > val2);
      return 0;

    case 3:
      name = std::to_string(val1 <= val2);
      return 0;

    case 4:
      name = std::to_string(val1 >= val2);
      return 0;

    default:
      std::cerr << "error: undefined operator in RelExpAST2" << std::endl;
      exit(-1);
    }
  }
#endif

  name = '%' + std::to_string(*global_name_ctr);
  *global_name_ctr += 1;

  switch (ret) {
  case 1: // less
    oss << name << " = lt " << rel_exp->name << ", " << add_exp->name << "\n";
    return 0;

  case 2: // greater
    oss << name << " = gt " << rel_exp->name << ", " << add_exp->name << "\n";
    return 0;

  case 3: // less_equal
    oss << name << " = le " << rel_exp->name << ", " << add_exp->name << "\n";
    return 0;

  case 4: // greater_equal
    oss << name << " = ge " << rel_exp->name << ", " << add_exp->name << "\n";
    return 0;

  default:
    std::cerr << "error: undefined operator in RelExpAST2" << std::endl;
    exit(-1);
  }
}

int RelExpAST2::eval() {
  int val1 = rel_exp->eval();
  int val2 = add_exp->eval();

  switch (static_cast<RelOpAST *>(rel_op.get())->op) {
  case less_op:
    return val1 < val2;

  case greater_op:
    return val1 > val2;

  case less_equal_op:
    return val1 <= val2;

  case greater_equal_op:
    return val1 >= val2;

  default:
    std::cerr << "error: undefined operator in RelExpAST2" << std::endl;
    exit(-1);
  }
}

void RelOpAST::Dump() const {
  std::cout << "RelOpAST { ";
  switch (op) {
  case less_op:
    std::cout << '<';
    break;
  case greater_op:
    std::cout << '>';
    break;
  case less_equal_op:
    std::cout << "<=";
    break;
  case greater_equal_op:
    std::cout << ">=";
    break;
  }
  std::cout << " }";
}

int RelOpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return op;
}

void EqExpAST1::Dump() const {
  std::cout << "EqExpAST1 { ";
  rel_exp->Dump();
  std::cout << " }";
}

int EqExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (rel_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error in EqExpAST1" << std::endl;
    exit(-1);
  }

  name = rel_exp->name;

  return 0;
}

int EqExpAST1::eval() { return rel_exp->eval(); }

void EqExpAST2::Dump() const {
  std::cout << "EqExpAST2 { ";
  eq_exp->Dump();
  std::cout << ' ';
  eq_op->Dump();
  std::cout << ' ';
  rel_exp->Dump();
  std::cout << " }";
}

int EqExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (eq_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: eq_exp in EqExpAST2" << std::endl;
    exit(-1);
  }

  int ret;
  if ((ret = eq_op->GenIR(global_name_ctr, oss)) < 0) {
    std::cerr << "error: eq_op in EqExpAST2" << std::endl;
    exit(-1);
  }

  if (rel_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: rel_exp in EqExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (eq_exp->name[0] != '%' && rel_exp->name[0] != '%') {
    int val1 = std::stoi(eq_exp->name);
    int val2 = std::stoi(rel_exp->name);

    switch (ret) {
    case 1:
      name = std::to_string(val1 == val2);
      return 0;

    case 2:
      name = std::to_string(val1 != val2);
      return 0;

    default:
      std::cerr << "error: undefined operator in EqExpAST2" << std::endl;
      exit(-1);
    }
  }
#endif

  name = '%' + std::to_string(*global_name_ctr);
  *global_name_ctr += 1;

  switch (ret) {
  case 1: // equal
    oss << name << " = eq " << eq_exp->name << ", " << rel_exp->name << "\n";
    return 0;

  case 2: // not_equal
    oss << name << " = ne " << eq_exp->name << ", " << rel_exp->name << "\n";
    return 0;

  default:
    std::cerr << "error: undefined operator in EqExpAST2" << std::endl;
    exit(-1);
  }
}

int EqExpAST2::eval() {
  int val1 = eq_exp->eval();
  int val2 = rel_exp->eval();

  switch (static_cast<EqOpAST *>(eq_op.get())->op) {
  case equal_op:
    return val1 == val2;
  case not_equal_op:
    return val1 != val2;
  default:
    std::cerr << "error: undefined operator in EqExpAST2" << std::endl;
    exit(-1);
  }
}

void EqOpAST::Dump() const {
  std::cout << "EqOpAST { ";
  switch (op) {
  case equal_op:
    std::cout << "==";
    break;
  case not_equal_op:
    std::cout << "!=";
    break;
  }
  std::cout << " }";
}

int EqOpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return op;
}

void LAndExpAST1::Dump() const {
  std::cout << "LAndExpAST1 { ";
  eq_exp->Dump();
  std::cout << " }";
}

int LAndExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (eq_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error in LAndExpAST1" << std::endl;
    exit(-1);
  }

  name = eq_exp->name;

  return 0;
}

int LAndExpAST1::eval() { return eq_exp->eval(); }

void LAndExpAST2::Dump() const {
  std::cout << "LAndExpAST2 { ";
  l_and_exp->Dump();
  std::cout << " && ";
  eq_exp->Dump();
  std::cout << " }";
}

int LAndExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (l_and_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_and_exp in LAndExpAST2" << std::endl;
    exit(-1);
  }

  if (eq_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: eq_exp in LAndExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (l_and_exp->name[0] != '%' && eq_exp->name[0] != '%') {
    int val1 = std::stoi(l_and_exp->name);
    int val2 = std::stoi(eq_exp->name);

    name = std::to_string(val1 && val2);

    return 0;
  }
#endif

  // a && b <==> !!a && !!b
  oss << '%' << *global_name_ctr << " = ne 0, " << l_and_exp->name << "\n";
  oss << '%' << *global_name_ctr + 1 << " = ne 0, " << eq_exp->name << "\n";
  oss << '%' << *global_name_ctr + 2 << " = and " << '%' << *global_name_ctr << ", " << '%' << *global_name_ctr + 1 << "\n";

  name = '%' + std::to_string(*global_name_ctr + 2);
  *global_name_ctr += 3;

  return 0;
}

int LAndExpAST2::eval() {
  int val1 = l_and_exp->eval();
  int val2 = eq_exp->eval();

  return val1 && val2;
}

void LOrExpAST1::Dump() const {
  std::cout << "LOrExpAST1 { ";
  l_and_exp->Dump();
  std::cout << " }";
}

int LOrExpAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (l_and_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error in LOrExpAST1" << std::endl;
    exit(-1);
  }

  name = l_and_exp->name;

  return 0;
}

int LOrExpAST1::eval() { return l_and_exp->eval(); }

void LOrExpAST2::Dump() const {
  std::cout << "LOrExpAST2 { ";
  l_or_exp->Dump();
  std::cout << " || ";
  l_and_exp->Dump();
  std::cout << " }";
}

int LOrExpAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (l_or_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_or_exp in LOrExpAST2" << std::endl;
    exit(-1);
  }

  if (l_and_exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: l_and_exp in LOrExpAST2" << std::endl;
    exit(-1);
  }

#ifndef NOFOLD
  if (l_or_exp->name[0] != '%' && l_and_exp->name[0] != '%') {
    int val1 = std::stoi(l_or_exp->name);
    int val2 = std::stoi(l_and_exp->name);

    name = std::to_string(val1 || val2);

    return 0;
  }
#endif

  auto name1 = '%' + std::to_string(*global_name_ctr);
  name = '%' + std::to_string(*global_name_ctr + 1);
  *global_name_ctr += 2;

  // a || b <==> (a | b) != 0
  oss << name1 << " = or " << l_or_exp->name << ", " << l_and_exp->name << "\n";
  oss << name << " = ne 0, " << name1 << "\n";

  return 0;
}

int LOrExpAST2::eval() {
  int val1 = l_or_exp->eval();
  int val2 = l_and_exp->eval();

  return val1 || val2;
}

void ConstExpAST::Dump() const {
  std::cout << "ConstExpAST { ";
  exp->Dump();
  std::cout << " }";
}

int ConstExpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in ConstExpAST" << std::endl;
    exit(-1);
  }

  name = exp->name;

  return 0;
}

int ConstExpAST::eval() { return exp->eval(); }
