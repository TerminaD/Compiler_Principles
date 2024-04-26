#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "ast.hpp"


class SymFrame: {
private:
	std::unordered_map<std::string, int> dict;

public:
	int lookup(std::string name) {
		return dict[name];
	}
};



class SymTab: {
private:
	std::vector<std::unique_ptr<SymFrame>> frame_stack;

public:
	
};