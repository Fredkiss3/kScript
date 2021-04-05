#pragma once
#include "headers.h"

namespace KScript {
	enum class TokenType {
		EOFL,		// "\0"
		UNKNOWN,	// not in the vocabulary

		KEYWORD,	// the keywords (ex: var, fun, do, etc.)
		IDENTIFIER, // an identifier (variable names, function names, etc.)
		TYPENAME,	// a typename is an identifiers that starts with an uppercase

		OPERATOR,   // = + - * / : %   lt (<) gt (>) lte (<=) gte (>=) is (==) not (!=) and (&&) or (||) 
		
		STRING,		// "string" or 'string'
		NUMBER,		// 12 54.6
		COMMA,		// ,

		// parenthesis
		LPAREN,		// (
		RPAREN,		// )
		LBRACKET,	// [
		RBRACKET	// ]
	};


	struct Token {

		TokenType type;
		std::string value;

		std::string toString() {
			std::string _type = "UNKNOWN";

			switch (type)
			{
			case TokenType::KEYWORD:
				_type = "KEYWORD";
				break;
			case TokenType::IDENTIFIER:
				_type = "IDENTIFIER";
				break;
			//case TokenType::OPERATOR:
			//	_type = "EQUALS";
			//	break;
			case TokenType::STRING:
				_type = "STRING";
				break;
			case TokenType::LPAREN:
				_type = "LEFT PARENTHESIS";
				break;
			case TokenType::RPAREN:
				_type = "RIGHT PARENTHESIS";
				break;
			case TokenType::LBRACKET:
				_type = "LEFT SQUARE BRACKET";
				break;
			case TokenType::RBRACKET:
				_type = "RIGHT SQUARE BRACKET";
				break;
			case TokenType::UNKNOWN:
				_type = "UNKNOWN";
				break;
			case TokenType::EOFL:
				_type = "END OF FILE";
				break;
			case TokenType::NUMBER:
				_type = "NUMBER";
				break;
			case TokenType::OPERATOR:
				_type = "OPERATOR";
				break;
			case TokenType::COMMA:
				_type = "COMMA";
				break;
			case TokenType::TYPENAME:
				_type = "TYPENAME";
				break;
			}

			return  "Token(type="  + _type + ", value=" + "'" + value +  "'" + ")";
		}
	};

}