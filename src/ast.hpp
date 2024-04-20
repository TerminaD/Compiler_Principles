#pragma once

#include <memory>
#include <string>
#include <iostream>


enum unary_op_t {
  positive_op,
  negative_op,
  not_op
};

enum bin_pri_op_t {
  mul_op,
  div_op,
  mod_op
};

enum bin_op_t {
  add_op,
  sub_op
};

enum rel_op_t {
  less_op,
  greater_op,
  less_equal_op,
  greater_equal_op
};

enum eq_op_t {
  equal_op,
  not_equal_op
};


// 所有 AST 的基类
class BaseAST {
public:
  virtual ~BaseAST() = default;

  virtual void Dump() const = 0;

  virtual int GenIR(std::shared_ptr<std::string> ir, int *gic) = 0;

  int ident_ctr;
};


class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    return func_def->GenIR(ir, gic);
  }
};


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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (func_type->GenIR(ir1, gic) < 0) {
      std::cerr << "error: func_type in FuncDefAST" << std::endl;
      exit(-1);
    }

    auto ir2 = std::make_shared<std::string>();
    if (block->GenIR(ir2, gic) < 0) {
      std::cerr << "error: block in FuncDefAST" << std::endl;
      exit(-1);
    }

    *ir = "fun @" + ident + "(): " + *ir1 + " { " + *ir2 + " }";
    return 0;
  }
};


class FuncTypeAST : public BaseAST {
public:
  std::string func_type;

  void Dump() const override {
    std::cout << "FuncTypeAST { " << func_type << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    if (func_type == "int")
      *ir = "i32";
    else {
      std::cerr << "error: non-int data type not supported" << std::endl;
      exit(-1);
    }
    return 0;
  }
};


class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  void Dump() const override {
    std::cout << "BlockAST { ";
    stmt->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (stmt->GenIR(ir1, gic) < 0) {
      std::cerr << "error: stmt in BlockAST" << std::endl;
      exit(-1);
    }

    *ir = "\%entry: " + *ir1;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = exp->GenIR(ir, gic);

    if (exp->ident_ctr == -1) 
      *ir = "ret " + *ir + "\n";
    else {
      *ir += ("ret %" + std::to_string(exp->ident_ctr) + "\n");
    }

    return ret;
  }
};


class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> l_or_exp;

  void Dump() const override {
    std::cout << "ExpAST { ";
    l_or_exp->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = l_or_exp->GenIR(ir, gic);
    ident_ctr = l_or_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = exp->GenIR(ir, gic);
    ident_ctr = exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = number->GenIR(ir, gic);
    ident_ctr = -1;
    return ret;
  }
};


class NumberAST : public BaseAST {
public:
  int int_const;

  void Dump() const override {
    std::cout << "NumberAST { " << int_const << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    *ir = std::to_string(int_const);
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = primary_exp->GenIR(ir, gic);
    ident_ctr = primary_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    int ret = unary_op->GenIR(ir1, gic);
    if (ret < 0) {
      std::cerr << "error: unary_op in UnaryExpAST2" << std::endl;
      exit(-1);
    }

    auto ir2 = std::make_shared<std::string>();
    if (unary_exp->GenIR(ir2, gic) < 0) {
      std::cerr << "error: unary_exp in UnaryExpAST2" << std::endl;
      exit(-1);
    }

    if (unary_exp->ident_ctr != -1)
      *ir = *ir2;
    
    *ir += ("%" + std::to_string(*gic) + " = ");

    switch (ret) {
      case 1:
        *ir += "add 0, ";
        break;

      case 2:
        *ir += "sub 0, ";
        break;

      case 3:
        *ir += "eq 0, ";
        break;

      default:
        std::cerr << "error: undefined unary operator in UnaryExpAST2" << std::endl;
        exit(-1);
    }

    if (unary_exp->ident_ctr == -1) {
      *ir += *ir2;
      *ir += "\n";
    } else {
      *ir += ("%" + std::to_string(unary_exp->ident_ctr) + "\n");
    }
    
    ident_ctr = *gic;
    *gic += 1;

    // std::cout << *ir << std::endl;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    switch (op) {
      case positive_op:
        return 1;
        break;
      case negative_op:
        return 2;
        break;
      case not_op:
        return 3;
        break;
      default:
        std::cerr << "error: undefined unary operator" << std::endl;
        exit(-1);
    }
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = unary_exp->GenIR(ir, gic);
    ident_ctr = unary_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (mul_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = mul_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    int ret = bin_pri_op->GenIR(ir2, gic);
    if (ret < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    auto ir3 = std::make_shared<std::string>();
    if (unary_exp->GenIR(ir3, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr3 = unary_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr3 != -1)
      *ir += *ir3;

    *ir += ("%" + std::to_string(*gic) + " = ");

    switch (ret) {
      case 1:   // Mul
        *ir += "mul ";
        break;
      case 2:   // Div
        *ir += "div ";
        break;
      case 3:   // Mod
        *ir += "mod ";
        break;
      default:
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (mul_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(mul_exp->ident_ctr));

    *ir += ", ";

    if (unary_exp->ident_ctr == -1)
      *ir += *ir3;
    else
      *ir += ("%" + std::to_string(unary_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = mul_exp->GenIR(ir, gic);
    ident_ctr = mul_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (add_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = add_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    int ret = bin_op->GenIR(ir2, gic);
    if (ret < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    auto ir3 = std::make_shared<std::string>();
    if (mul_exp->GenIR(ir3, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr3 = mul_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr3 != -1)
      *ir += *ir3;

    *ir += ("%" + std::to_string(*gic) + " = ");

    switch (ret) {
      case 1:   // add
        *ir += "add ";
        break;
      case 2:   // sub
        *ir += "sub ";
        break;
      default:
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (add_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(add_exp->ident_ctr));

    *ir += ", ";

    if (mul_exp->ident_ctr == -1)
      *ir += *ir3;
    else
      *ir += ("%" + std::to_string(mul_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = add_exp->GenIR(ir, gic);
    ident_ctr = add_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (rel_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = rel_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    int ret = rel_op->GenIR(ir2, gic);
    if (ret < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    auto ir3 = std::make_shared<std::string>();
    if (add_exp->GenIR(ir3, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr3 = add_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr3 != -1)
      *ir += *ir3;

    *ir += ("%" + std::to_string(*gic) + " = ");

    switch (ret) {
      case 1:   // <
        *ir += "lt ";
        break;
      case 2:   // >
        *ir += "gt ";
        break;
      case 3:   // <=
        *ir += "le ";
        break;
      case 4:   // >=
        *ir += "ge ";
        break;
      default:
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (rel_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(rel_exp->ident_ctr));

    *ir += ", ";

    if (add_exp->ident_ctr == -1)
      *ir += *ir3;
    else
      *ir += ("%" + std::to_string(add_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = rel_exp->GenIR(ir, gic);
    ident_ctr = rel_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (eq_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = eq_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    int ret = eq_op->GenIR(ir2, gic);
    if (ret < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    auto ir3 = std::make_shared<std::string>();
    if (rel_exp->GenIR(ir3, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr3 = rel_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr3 != -1)
      *ir += *ir3;

    *ir += ("%" + std::to_string(*gic) + " = ");

    switch (ret) {
      case 1:   // ==
        *ir += "eq ";
        break;
      case 2:   // !=
        *ir += "ne ";
        break;
      default:
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (eq_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(eq_exp->ident_ctr));

    *ir += ", ";

    if (rel_exp->ident_ctr == -1)
      *ir += *ir3;
    else
      *ir += ("%" + std::to_string(rel_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = eq_exp->GenIR(ir, gic);
    ident_ctr = eq_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (l_and_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = l_and_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    if (eq_exp->GenIR(ir2, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr2 = eq_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr2 != -1)
      *ir += *ir2;

    *ir += ("%" + std::to_string(*gic) + " = and ");

    if (l_and_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(l_and_exp->ident_ctr));

    *ir += ", ";

    if (eq_exp->ident_ctr == -1)
      *ir += *ir2;
    else
      *ir += ("%" + std::to_string(eq_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    int ret = l_and_exp->GenIR(ir, gic);
    ident_ctr = l_and_exp->ident_ctr;
    return ret;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    auto ir1 = std::make_shared<std::string>();
    if (l_or_exp->GenIR(ir1, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr1 = l_or_exp->ident_ctr;

    auto ir2 = std::make_shared<std::string>();
    if (l_and_exp->GenIR(ir2, gic) < 0) {
      std::cerr << "error" << std::endl;
      exit(-1);
    }
    int ident_ctr2 = l_and_exp->ident_ctr;

    *ir = "";
    if (ident_ctr1 != -1)
      *ir += *ir1;
    if (ident_ctr2 != -1)
      *ir += *ir2;

    *ir += ("%" + std::to_string(*gic) + " = or ");

    if (l_or_exp->ident_ctr == -1)
      *ir += *ir1;
    else
      *ir += ("%" + std::to_string(l_or_exp->ident_ctr));

    *ir += ", ";

    if (l_and_exp->ident_ctr == -1)
      *ir += *ir2;
    else
      *ir += ("%" + std::to_string(l_and_exp->ident_ctr));

    *ir += "\n";

    ident_ctr = *gic;
    *gic += 1;

    return 0;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    switch (op) {
      case mul_op:
        return 1;
        break;
      case div_op:
        return 2;
        break;
      case mod_op:
        return 3;
        break;
      default:
        std::cerr << "error: undefined binary priority operator" << std::endl;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    switch (op) {
      case add_op:
        return 1;
        break;
      case sub_op:
        return 2;
        break;
      default:
        std::cerr << "error: undefined binary operator" << std::endl;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    switch (op) {
      case less_op:
        return 1;
        break;
      case greater_op:
        return 2;
        break;
      case less_equal_op:
        return 3;
        break;
      case greater_equal_op:
        return 4;
        break;
      default:
        std::cerr << "error: undefined relational operator" << std::endl;
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

  int GenIR(std::shared_ptr<std::string> ir, int *gic) override {
    switch (op) {
      case equal_op:
        return 1;
        break;
      case not_equal_op:
        return 2;
        break;
      default:
        std::cerr << "error: undefined equality operator" << std::endl;
        exit(-1);
    }
  }
};

