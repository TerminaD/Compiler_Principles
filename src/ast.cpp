#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "ast.hpp"
#include "symtab.hpp"

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

void DeclAST::Dump() const {
  std::cout << "DeclAST { ";
  const_decl->Dump();
  std::cout << " }";
}

int DeclAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  return const_decl->GenIR(global_name_ctr, oss);
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


void BTypeAST::Dump() const { std::cout << "BTypeAST { " << type << " }"; }

int BTypeAST::GenIR(int *global_name_ctr, std::ostringstream &oss) { return 0; }


void ConstDefAST::Dump() const {
  std::cout << "ConstDefAST { " << ident << ", ";
  const_init_val->Dump();
  std::cout << " }";
}

int ConstDefAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  int val = const_init_val->eval();
}


void ConstInitValAST::Dump() const {
  std::cout << "ConstInitValAST { ";
  const_exp->Dump();
  std::cout << " }";
}

int ConstInitValAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  // TODO
  return 0;
}

int ConstInitValAST::eval() { return const_exp->eval(); }

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

  // TODO
  // return 0;

  oss << "\%entry: ";

  //! Temporary
  assert(block_item_list_vec.size() == 1);

  if ((block_item_list_vec[0])->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: stmt in BlockAST" << std::endl;
    exit(-1);
  }

  return 0;
}


void BlockItemListAST::Dump() const {
  std::cout << "BlockItemListAST { ";
  block_item->Dump();
  std::cout << ", ";
  next_list->Dump();
  std::cout << " }";
}

int BlockItemListAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  // TODO
  return 0;
}


void BlockItemAST1::Dump() const {
  std::cout << "BlockItemAST1 { ";
  decl->Dump();
  std::cout << " }";
}

int BlockItemAST1::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  // TODO
  return 0;
}


void BlockItemAST2::Dump() const {
  std::cout << "BlockItemAST2 { ";
  stmt->Dump();
  std::cout << " }";
}

int BlockItemAST2::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  // TODO
  return 0;
}


void StmtAST::Dump() const {
  std::cout << "StmtAST { ";
  exp->Dump();
  std::cout << " }";
}

int StmtAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
#ifdef PRINT
  std::cout << typeid(*this).name() << std::endl;
#endif
  if (exp->GenIR(global_name_ctr, oss) < 0) {
    std::cerr << "error: exp in StmtAST" << std::endl;
    exit(-1);
  }

  oss << "ret " << exp->name << "\n";

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
  // TODO
  return 0;
}

int LValAST::eval() {
  if (sym_tab.exists(ident)) {
    return sym_tab.lookup(ident);
  } else {
    std::cerr << "error: variable not found in LValAST" << std::endl;
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
  // TODO
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
  oss << '%' << *global_name_ctr << " = eq 0, " << l_and_exp->name << "\n";
  oss << '%' << *global_name_ctr + 1 << " = eq 0, " << '%' << *global_name_ctr
      << "\n";
  oss << '%' << *global_name_ctr + 2 << " = eq 0, " << eq_exp->name << "\n";
  oss << '%' << *global_name_ctr + 3 << " = eq 0, " << '%'
      << *global_name_ctr + 2 << "\n";
  oss << '%' << *global_name_ctr + 4 << " = and " << '%' << *global_name_ctr + 1
      << ", " << '%' << *global_name_ctr + 3 << "\n";

  name = '%' + std::to_string(*global_name_ctr + 4);
  *global_name_ctr += 5;

  return 0;
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


void ConstExpAST::Dump() const {
  std::cout << "ConstExpAST { ";
  exp->Dump();
  std::cout << " }";
}

int ConstExpAST::GenIR(int *global_name_ctr, std::ostringstream &oss) {
  // TODO
  return 0;
}

int ConstExpAST::eval() { return exp->eval(); }
