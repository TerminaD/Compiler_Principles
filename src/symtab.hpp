//! TODO: lookup after insert results in nonsense names, so for now, we simply append an '@' to the start of a variable's name in source as its name in IR

#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum type_t { const_type, var_type };

struct Value {
  type_t type;
  int const_val;
  const char *var_ir_name;
};

class SymFrame {
private:
  std::unordered_map<std::string, Value> dict;

public:
  int lookup_const(std::string name) { //! Does not check if the name exists
    auto res = dict[name];
    if (res.type == const_type)
      return res.const_val;
    else
      assert(false);
  }

  auto lookup_var(std::string name) {
    auto res = dict[name];
    if (res.type == var_type) {
      std::cout << "lookup var: " << name << " with ir_name: " << res.var_ir_name << std::endl;
      return res.var_ir_name;
    }
    else
      assert(false);
  }

  void insert_const(std::string name, int value) {
    Value item = Value();
    item.type = const_type;
    item.const_val = value;
    dict[name] = item;
    std::cout << "inserted const: " << name << " with value: " << value << std::endl;
  }

  void insert_var(std::string name, const char *ir_name) {
    Value item = Value();
    item.type = var_type;
    item.var_ir_name = ir_name;
    dict[name] = item;
    std::cout << "inserted var: " << name << " with ir_name: " << ir_name << std::endl;
  }

  bool exists_const(std::string name) {
    return dict.find(name) != dict.end() && dict[name].type == const_type;
  }

  bool exists_var(std::string name) {
    return dict.find(name) != dict.end() && dict[name].type == var_type;
  }
};

class SymTab {
private:
  std::vector<std::unique_ptr<SymFrame>> frame_stack;

public:
  SymTab() { frame_stack.push_back(std::make_unique<SymFrame>()); }

  void insert_const(std::string name, int value) {
    frame_stack.back()->insert_const(name, value);
  }

  void insert_var(std::string name, const char *ir_name) {
    frame_stack.back()->insert_var(name, ir_name);
  }

  bool exists_const(std::string name) {
    for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
      if ((*it)->exists_const(name))
        return true;
    }
    return false;
  }

  bool exists_var(std::string name) {
    for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
      if ((*it)->exists_var(name))
        return true;
    }
    return false;
  }

  // If finds const, return 1; if var, return 2, if none, return 3
  int exists(std::string name) {
    if (exists_const(name))
      return 1;
    else if (exists_var(name))
      return 2;
    else
      return 3;
  }

  int lookup_const(std::string name) {
    for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
      if ((*it)->exists_const(name))
        return (*it)->lookup_const(name);
    }
    assert(false);
  }

  auto lookup_var(std::string name) {
    for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
      if ((*it)->exists_var(name))
        return (*it)->lookup_var(name);
    }
    assert(false);
  }

  void push_frame() { frame_stack.push_back(std::make_unique<SymFrame>()); }

  void pop_frame() { frame_stack.pop_back(); }
};

extern SymTab sym_tab;
