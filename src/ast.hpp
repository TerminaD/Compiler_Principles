#pragma once

#include <memory>
#include <string>
#include <iostream>


// 所有 AST 的基类
class BaseAST {
public:
  virtual ~BaseAST() = default;

  virtual void Dump() const = 0;

  virtual int GenIR(std::shared_ptr<std::string> irp) const = 0;
};


class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> irp) const override {
    return func_def->GenIR(irp);
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

  int GenIR(std::shared_ptr<std::string> irp) const override {
    // if (ident != "main") {
    //   std::cerr << "error: name of function is not \"main\"" << std::endl;
    //   exit(-1);
    // }

    auto irp1 = std::make_shared<std::string>();
    if (func_type->GenIR(irp1) < 0) {
      std::cerr << "error: in generating IR" << std::endl;
      exit(-1);
    }

    auto irp2 = std::make_shared<std::string>();
    if (block->GenIR(irp2) < 0) {
      std::cerr << "error: in generating IR" << std::endl;
      exit(-1);
    }

    *irp = "fun @" + ident + "(): " + *irp1 + " { " + *irp2 + " }";
    return 0;
  }
};


class FuncTypeAST : public BaseAST {
public:
  std::string func_type;

  void Dump() const override {
    std::cout << "FuncTypeAST { " << func_type << " }";
  }

  int GenIR(std::shared_ptr<std::string> irp) const override {
    *irp = "i32";
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

  int GenIR(std::shared_ptr<std::string> irp) const override {
    auto irp1 = std::make_shared<std::string>();

    if (stmt->GenIR(irp1) < 0) {
      std::cerr << "error: in generating IR" << std::endl;
      exit(-1);
    }

    *irp = "\%entry: " + *irp1;
    return 0;
  }
};


class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> number;

  void Dump() const override {
    std::cout << "StmtAST { ";
    number->Dump();
    std::cout << " }";
  }

  int GenIR(std::shared_ptr<std::string> irp) const override {
    auto irp1 = std::make_shared<std::string>();

    if (number->GenIR(irp1) < 0) {
      std::cerr << "error: in generating IR" << std::endl;
      exit(-1);
    }

    *irp = "ret " + *irp1;
    return 0;
  }
};


class NumberAST : public BaseAST {
public:
  int int_const;

  void Dump() const override {
    std::cout << "NumberAST { " << int_const << " }";
  }

  int GenIR(std::shared_ptr<std::string> irp) const override {
    *irp = std::to_string(int_const);
    return 0;
  }
};
