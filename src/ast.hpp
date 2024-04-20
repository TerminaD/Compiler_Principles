#pragma once

#include <memory>
#include <string>
#include <iostream>


// 一元运算符的种类
enum unary_op_t {
  positive_op,
  negative_op,
  not_op
};


// 所有 AST 的基类
class BaseAST {
public:
  virtual ~BaseAST() = default;

  virtual void Dump() const = 0;

  virtual int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const = 0;
};


class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return func_def->GenIR(ir, reg_ctr);
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    auto ir1 = std::make_shared<std::string>();
    if (func_type->GenIR(ir1, reg_ctr) < 0) {
      std::cerr << "error: func_type in FuncDefAST" << std::endl;
      exit(-1);
    }

    auto ir2 = std::make_shared<std::string>();
    if (block->GenIR(ir2, reg_ctr) < 0) {
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    auto ir1 = std::make_shared<std::string>();
    if (stmt->GenIR(ir1, reg_ctr) < 0) {
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return exp->GenIR(ir, reg_ctr);
  }
};


class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_exp;

  void Dump() const override {
    std::cout << "ExpAST { ";
    unary_exp->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return unary_exp->GenIR(ir, reg_ctr);
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return exp->GenIR(ir, reg_ctr);
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return number->GenIR(ir, reg_ctr);
  }
};


class NumberAST : public BaseAST {
public:
  int int_const;

  void Dump() const override {
    std::cout << "NumberAST { " << int_const << " }";
  }

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    return primary_exp->GenIR(ir, reg_ctr);
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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
    auto ir1 = std::make_shared<std::string>();
    int ret = unary_op->GenIR(ir1, reg_ctr);
    if (ret < 0) {
      std::cerr << "error: unary_op in UnaryExpAST2" << std::endl;
      exit(-1);
    }

    auto ir2 = std::make_shared<std::string>();
    if (unary_exp->GenIR(ir2, reg_ctr) < 0) {
      std::cerr << "error: unary_exp in UnaryExpAST2" << std::endl;
      exit(-1);
    }

    if (*reg_ctr != 0)
      *ir = *ir2;
    
    *ir += ("%" + std::to_string(*reg_ctr) + " = ");

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

    if (*reg_ctr == 0) {
      *ir += *ir2;
      *ir += "\n";
    } else {
      *ir += ("%" + std::to_string(*reg_ctr-1) + "\n");
    }
      
    (*reg_ctr) += 1;

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

  int GenIR(std::shared_ptr<std::string> ir, size_t *reg_ctr) const override {
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
