#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>


class SymFrame {
private:
	std::unordered_map<std::string, int> dict;

public:
	int lookup(std::string name) {	//! Does not check if the name exists
		return dict[name];
	}

	void insert(std::string name, int value) {
		dict[name] = value;
	}

	bool exists(std::string name) {
		return dict.find(name) != dict.end();
	}
};


class SymTab {
private:
	std::vector<std::unique_ptr<SymFrame>> frame_stack;

public:
	void insert(std::string name, int value) {
		frame_stack.back()->insert(name, value);
	}

	bool exists(std::string name) {
		for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
			if (it->get()->exists(name))
				return true;
		}
		return false;
	}

	int lookup(std::string name) {	//! Does not check if the name exists
		for (auto it = frame_stack.rbegin(); it != frame_stack.rend(); ++it) {
			if (it->get()->exists(name))
				return it->get()->lookup(name);
		}
		assert(false);	// Name not found, throw error
	}

	void push_frame() {
		frame_stack.push_back(std::make_unique<SymFrame>());
	}

	void pop_frame() {
		frame_stack.pop_back();
	}
};


extern SymTab sym_tab;
