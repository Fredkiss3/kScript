#pragma once
#include "headers.h"
#include "Token.h"
#include "Keywords.h"
#include "Operator.h"

namespace KScript {
	class Lexer
	{
	public:
		Lexer(std::string& src) : source(src + '\0' ), line(1), column(1), pos(0), currentChar(src.at(0))
		{
			init();

			advance();
		}


		Lexer(std::string&& src) : Lexer(src) {}

		char& getCurrentChar() { return currentChar; }

		Keyword getKeyWordType(std::string& src) { return keywords[src]; }
		Operator getOperatorType(std::string& src) { return operators[src]; }
		Token getNextToken();

	private:
		void advance();

		void init();

		void skipWhitespace();
		void skipComments();

		std::string collectString(bool singleQuoted);

		std::string collectIdentifier();
		std::string collectNumber();

		bool eof();
		bool isDigit();
		bool isWhitespace();
		bool isString();
		bool isPunctuation();

	private:
		//std::vector<Token> tokens;
		std::unordered_map<std::string, Keyword> keywords;
		std::unordered_map<std::string, Operator> operators;
		
		//Token currentToken{TokenType::UNKNOWN, "" };

		std::string source;

		char currentChar;

		int line;
		int column;
		int pos;
	};

}
