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
#include <sstream>
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

  virtual int eval() { return 0; }
};

// -----------------------------------------------------------------

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};

// -----------------------------------------------------------------

class DeclAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_decl;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class ConstDeclAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> b_type;
  std::unique_ptr<BaseAST> const_def;
  std::vector<std::unique_ptr<BaseAST>> const_def_list_vec;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class ConstDefListAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_def;
  std::unique_ptr<BaseAST> next_list;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class BTypeAST : public BaseAST {
public:
  std::string type;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class ConstDefAST: public BaseAST {
public:
  std::string ident;
  std::unique_ptr<BaseAST> const_init_val;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class ConstInitValAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> const_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};

// -----------------------------------------------------------------

class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class FuncTypeAST : public BaseAST {
public:
  std::string func_type;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};

// -----------------------------------------------------------------

class BlockAST : public BaseAST {
public:
  std::vector<std::unique_ptr<BaseAST>> block_item_list_vec;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class BlockItemListAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> block_item;
  std::unique_ptr<BaseAST> next_list;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class BlockItemAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> decl;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class BlockItemAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};

// -----------------------------------------------------------------

class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_or_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class LValAST : public BaseAST {
public:
  std::string ident;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class PrimaryExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class PrimaryExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> number;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class PrimaryExpAST3 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_val;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class NumberAST : public BaseAST {
public:
  int int_const;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class UnaryExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> primary_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class UnaryExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_op;
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class UnaryOpAST : public BaseAST {
public:
  unary_op_t op;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class MulExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class MulExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> mul_exp;
  std::unique_ptr<BaseAST> bin_pri_op;
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class BinPriOpAST : public BaseAST {
public:
  bin_pri_op_t op;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class AddExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> mul_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class AddExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> add_exp;
  std::unique_ptr<BaseAST> bin_op;
  std::unique_ptr<BaseAST> mul_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class BinOpAST : public BaseAST {
public:
  bin_op_t op;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class RelExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> add_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class RelExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> rel_exp;
  std::unique_ptr<BaseAST> rel_op;
  std::unique_ptr<BaseAST> add_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class RelOpAST : public BaseAST {
public:
  rel_op_t op;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class EqExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> rel_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class EqExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> eq_exp;
  std::unique_ptr<BaseAST> eq_op;
  std::unique_ptr<BaseAST> rel_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class EqOpAST : public BaseAST {
public:
  eq_op_t op;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;
};


class LAndExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> eq_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class LAndExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_and_exp;
  std::unique_ptr<BaseAST> eq_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class LOrExpAST1 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_and_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class LOrExpAST2 : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_or_exp;
  std::unique_ptr<BaseAST> l_and_exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};


class ConstExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  void Dump() const override;

  int GenIR(int *global_name_ctr, std::ostringstream &oss) override;

  int eval() override;
};
