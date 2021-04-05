#pragma once
#include "headers.h"

class Result {
private:
	std::string _input;
public:
	Result(std::string& in): _input(in) {}

	std::string toString() {
		return "result : " + _input;
	}
};

class Error {
public: 
	std::string toString() {
		return "Error";
	}
};

class Kscript {
public:
	static Result run(std::string input) {
		return Result(input);
	}
};