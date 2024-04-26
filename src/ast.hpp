/*
Generation rules:

CompUnit      ::= FuncDef;

Decl          ::= ConstDecl | VarDecl;
ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
BType         ::= "int";
ConstDef      ::= IDENT "=" ConstInitVal;
ConstInitVal  ::= ConstExp;
VarDecl       ::= BType VarDef {"," VarDef} ";";
VarDef        ::= IDENT | IDENT "=" InitVal;
InitVal       ::= Exp;

FuncDef       ::= FuncType IDENT "(" ")" Block;
FuncType      ::= "int";

Block         ::= "{" {BlockItem} "}";
BlockItem     ::= Decl | Stmt;
Stmt          ::= LVal "=" Exp ";"
                | "return" Exp ";";

Exp           ::= LOrExp;
LVal          ::= IDENT;
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
Number        ::= INT_CONST;
UnaryExp      ::= PrimaryExp | UnaryOp UnaryExp;
UnaryOp       ::= "+" | "-" | "!";
MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp       ::= EqExp | LAndExp "&&" EqExp;
LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
ConstExp      ::= Exp;

*/


#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>


enum unary_op_t {
  positive_op = 1,
  negative_op,
  not_op
};

enum bin_pri_op_t {
  mul_op = 1,
  div_op,
  mod_op
};

enum bin_op_t {
  add_op = 1,
  sub_op
};

enum rel_op_t {
  less_op = 1,
  greater_op,
  less_equal_op,
  greater_equal_op
};

enum eq_op_t {
  equal_op = 1,
  not_equal_op
};


// 所有 AST 的基类
class BaseAST {
public:
  virtual ~BaseAST() = default;

  std::string name;

  virtual void Dump() const = 0;

  virtual int GenIR(int *global_name_ctr, std::ostringstream &oss) = 0;
};

// -----------------------------------------------------------------

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return func_def->GenIR(global_name_ctr, oss);
  }
};

// -----------------------------------------------------------------

class DeclAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_decl;

  void Dump() const override {
    std::cout << "DeclAST { ";
    const_decl->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class ConstDeclAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> b_type;
  std::unique_ptr<BaseAST> const_def;
  std::vector<std::unique_ptr<BaseAST>> const_def_list_vec;

  void Dump() const override {
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

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class ConstDefListAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_def;
  std::unique_ptr<BaseAST> next_list;

  void Dump() const override {
    std::cout << "ConstDefListAST { ";
    const_def->Dump();
    std::cout << ", ";
    next_list->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class BTypeAST : public BaseAST {
public:
  std::string type;

  void Dump() const override {
    std::cout << "BTypeAST { " << type << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class ConstDefAST: public BaseAST {
public:
  std::string ident;
  std::unique_ptr<BaseAST> const_init_val;

  void Dump() const override {
    std::cout << "ConstDefAST { " << ident << ", ";
    const_init_val->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class ConstInitValAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_exp;

  void Dump() const override {
    std::cout << "ConstInitValAST { ";
    const_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};

// -----------------------------------------------------------------

class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  void Dump() const override {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class FuncTypeAST : public BaseAST {
public:
  std::string func_type;

  void Dump() const override {
    std::cout << "FuncTypeAST { " << func_type << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};

// -----------------------------------------------------------------

class BlockAST : public BaseAST {
public:
  std::vector<std::unique_ptr<BaseAST>> block_item_list_vec;

  void Dump() const override {
    std::cout << "BlockAST { ";
    for (auto &block_item : block_item_list_vec) {
      block_item->Dump();
      std::cout << ", ";
    }
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif

    // TODO
    return 0;

    // oss << "\%entry: ";

    // if (stmt->GenIR( global_name_ctr, oss) < 0) {
    //   std::cerr << "error: stmt in BlockAST" << std::endl;
    //   exit(-1);
    // }

    // return 0;
  }
};


class BlockItemListAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> block_item;
  std::unique_ptr<BaseAST> next_list;

  void Dump() const override {
    std::cout << "BlockItemListAST { ";
    block_item->Dump();
    std::cout << ", ";
    next_list->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class BlockItemAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> decl;

  void Dump() const override {
    std::cout << "BlockItemAST1 { ";
    decl->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class BlockItemAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  void Dump() const override {
    std::cout << "BlockItemAST2 { ";
    stmt->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override {
    std::cout << "StmtAST { ";
    exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};

// -----------------------------------------------------------------

class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_or_exp;

  void Dump() const override {
    std::cout << "ExpAST { ";
    l_or_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class LValAST : public BaseAST {
public:
  std::string ident;

  void Dump() const override {
    std::cout << "LValAST { " << ident << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};


class PrimaryExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override {
    std::cout << "PrimaryExpAST1 { ( ";
    exp->Dump();
    std::cout << " ) }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class PrimaryExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> number;

  void Dump() const override {
    std::cout << "PrimaryExpAST2 { ";
    number->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {  
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
};


class PrimaryExpAST3 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_val;

  void Dump() const override {
    std::cout << "PrimaryExpAST3 { ";
    l_val->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {  
    // TODO
    return 0;
  }
};


class NumberAST : public BaseAST {
public:
  int int_const;

  void Dump() const override {
    std::cout << "NumberAST { " << int_const << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    name = std::to_string(int_const);

    return 0;
  }
};


class UnaryExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> primary_exp;

  void Dump() const override {
    std::cout << "UnaryExpAST1 { ";
    primary_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class UnaryExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_op;
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override {
    std::cout << "UnaryExpAST2 { ";
    unary_op->Dump();
    std::cout << ' ';
    unary_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
            std::cerr << "error: undefined unary operator in UnaryExpAST2" << std::endl;
            exit(-1);
        }
      }
    #endif

    switch (ret) {
      case 1:   // positive
        name = unary_exp->name;
        return 0;

      case 2:   // negative
        name = '%' + std::to_string(*global_name_ctr);
        *global_name_ctr += 1;

        oss << name << " = sub 0, " << unary_exp->name << "\n";

        return 0;

      case 3:   // not
        name = '%' + std::to_string(*global_name_ctr);
        *global_name_ctr += 1;

        oss << name << " = eq 0, " << unary_exp->name << "\n";

        return 0;

      default:
        std::cerr << "error: undefined unary operator in UnaryExpAST2" << std::endl;
        exit(-1);
    }
  }
};


class UnaryOpAST : public BaseAST {
public:
  unary_op_t op;

  void Dump() const override {
    std::cout << "UnaryOp { ";
    switch (op) {
      case positive_op: std::cout << '+'; break;
      case negative_op: std::cout << '-'; break;
      case not_op: std::cout << '!'; break;
    }
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return op;
  }
};


class MulExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override {
    std::cout << "MulExpAST1 { ";
    unary_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class MulExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> mul_exp;
  std::unique_ptr<BaseAST> bin_pri_op;
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override {
    std::cout << "MulExpAST2 { ";
    mul_exp->Dump();
    std::cout << ' ';
    bin_pri_op->Dump();
    std::cout << ' ';
    unary_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
      case 1:   // mul
        oss << name << " = mul " << mul_exp->name << ", " << unary_exp->name << "\n";
        return 0;

      case 2:   // div
        oss << name << " = div " << mul_exp->name << ", " << unary_exp->name << "\n";
        return 0;

      case 3:   // mod
        oss << name << " = mod " << mul_exp->name << ", " << unary_exp->name << "\n";
        return 0;

      default:
        std::cerr << "error: undefined operator in MulExpAST2" << std::endl;
        exit(-1);
    }
  }
};


class BinPriOpAST : public BaseAST {
public:
  bin_pri_op_t op;

  void Dump() const override {
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

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return op;
  }
};


class AddExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> mul_exp;

  void Dump() const override {
    std::cout << "AddExpAST1 { ";
    mul_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class AddExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> add_exp;
  std::unique_ptr<BaseAST> bin_op;
  std::unique_ptr<BaseAST> mul_exp;

  void Dump() const override {
    std::cout << "AddExpAST2 { ";
    add_exp->Dump();
    std::cout << ' ';
    bin_op->Dump();
    std::cout << ' ';
    mul_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
      case 1:   // add
        oss << name << " = add " << add_exp->name << ", " << mul_exp->name << "\n";
        return 0;

      case 2:   // sub
        oss << name << " = sub " << add_exp->name << ", " << mul_exp->name << "\n";
        return 0;

      default:
        std::cerr << "error: undefined operator in AddExpAST2" << std::endl;
        exit(-1);
    }
  }
};


class BinOpAST : public BaseAST {
public:
  bin_op_t op;

  void Dump() const override {
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

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return op;
  }
};


class RelExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> add_exp;

  void Dump() const override {
    std::cout << "RelExpAST1 { ";
    add_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class RelExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> rel_exp;
  std::unique_ptr<BaseAST> rel_op;
  std::unique_ptr<BaseAST> add_exp;

  void Dump() const override {
    std::cout << "RelExpAST2 { ";
    rel_exp->Dump();
    std::cout << ' ';
    rel_op->Dump();
    std::cout << ' ';
    add_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
      case 1:   // less
        oss << name << " = lt " << rel_exp->name << ", " << add_exp->name << "\n";
        return 0;

      case 2:   // greater
        oss << name << " = gt " << rel_exp->name << ", " << add_exp->name << "\n";
        return 0;

      case 3:   // less_equal
        oss << name << " = le " << rel_exp->name << ", " << add_exp->name << "\n";
        return 0;
      
      case 4:   // greater_equal
        oss << name << " = ge " << rel_exp->name << ", " << add_exp->name << "\n";
        return 0;

      default:
        std::cerr << "error: undefined operator in RelExpAST2" << std::endl;
        exit(-1);
    }
  }
};


class RelOpAST : public BaseAST {
public:
  rel_op_t op;

  void Dump() const override {
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

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return op;
  }
};


class EqExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> rel_exp;

  void Dump() const override {
    std::cout << "EqExpAST1 { ";
    rel_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class EqExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> eq_exp;
  std::unique_ptr<BaseAST> eq_op;
  std::unique_ptr<BaseAST> rel_exp;

  void Dump() const override {
    std::cout << "EqExpAST2 { ";
    eq_exp->Dump();
    std::cout << ' ';
    eq_op->Dump();
    std::cout << ' ';
    rel_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
      case 1:   // equal
        oss << name << " = eq " << eq_exp->name << ", " << rel_exp->name << "\n";
        return 0;

      case 2:   // not_equal
        oss << name << " = ne " << eq_exp->name << ", " << rel_exp->name << "\n";
        return 0;

      default:
        std::cerr << "error: undefined operator in EqExpAST2" << std::endl;
        exit(-1);
    }
  }
};


class EqOpAST : public BaseAST {
public:
  eq_op_t op;

  void Dump() const override {
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

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    #ifdef PRINT
      std::cout << typeid(*this).name() << std::endl;
    #endif
    return op;
  }
};


class LAndExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> eq_exp;

  void Dump() const override {
    std::cout << "LAndExpAST1 { ";
    eq_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class LAndExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_and_exp;
  std::unique_ptr<BaseAST> eq_exp;

  void Dump() const override {
    std::cout << "LAndExpAST2 { ";
    l_and_exp->Dump();
    std::cout << " && ";
    eq_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
    oss << '%' << *global_name_ctr+1 << " = eq 0, " << '%' << *global_name_ctr << "\n";
    oss << '%' << *global_name_ctr+2 << " = eq 0, " << eq_exp->name << "\n";
    oss << '%' << *global_name_ctr+3 << " = eq 0, " << '%' << *global_name_ctr+2 << "\n";
    oss << '%' << *global_name_ctr+4 << " = and " << '%' << *global_name_ctr+1 
    << ", " << '%' << *global_name_ctr+3 << "\n";

    name = '%' + std::to_string(*global_name_ctr + 4);
    *global_name_ctr += 5;

    return 0;
  }
};


class LOrExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_and_exp;

  void Dump() const override {
    std::cout << "LOrExpAST1 { ";
    l_and_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};


class LOrExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_or_exp;
  std::unique_ptr<BaseAST> l_and_exp;

  void Dump() const override {
    std::cout << "LOrExpAST2 { ";
    l_or_exp->Dump();
    std::cout << " || ";
    l_and_exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
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
};

class ConstExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override {
    std::cout << "ConstExpAST { ";
    exp->Dump();
    std::cout << " }";
  }

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override {
    // TODO
    return 0;
  }
};
