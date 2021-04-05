#include "headers.h"
#include "Lexer.h"


namespace KScript {
	void Lexer::advance()
	{
		if (pos < source.size())
		{
			char c = source.at(pos);
			currentChar = c;
		} 
		else
		{
			currentChar = '\0';
		}

		pos++;
	}

	void Lexer::init()
	{
		keywords["this"] = Keyword::THIS;
		keywords["cmp"] = Keyword::CMP;
		keywords["endcmp"] = Keyword::END_CMP;
		keywords["do"] = Keyword::DO;
		keywords["fun"] = Keyword::BEGIN_FUN;
		keywords["endfun"] = Keyword::END_FUN;
		keywords["if"] = Keyword::BEGIN_IF;
		keywords["endif"] = Keyword::END_IF;
		keywords["for"] = Keyword::BEGIN_FOR;
		keywords["endfor"] = Keyword::END_FOR;
		keywords["return"] = Keyword::RETURN;

		operators["lt"] = Operator::LT;
		operators["lte"] = Operator::LTE;
		operators["gt"] = Operator::GT;
		operators["gte"] = Operator::GTE;
		operators["is"] = Operator::IS;
		operators["not"] = Operator::NOT;
		operators["and"] = Operator::AND;
		operators["or"] = Operator::OR;

		operators["."] = Operator::DOT;
		operators["="] = Operator::EQUALS;

		operators[":"] = Operator::DIV;
		operators["/"] = Operator::DIV;
		operators["-"] = Operator::MINUS;
		operators["+"] = Operator::ADD;
		operators["*"] = Operator::MUL;
		operators["%"] = Operator::PERCENT;
	}


	void Lexer::skipWhitespace()
	{
		while (isWhitespace())
		{
			advance();
		}
	}

	void Lexer::skipComments()
	{
		while (currentChar != '\n' && currentChar != '\r' && !eof())
		{
			advance();
		}
		advance();
	}
	
	Token Lexer::getNextToken()
	{
		TokenType t = TokenType::UNKNOWN;
		std::string value;

		if (pos < source.length())
		{
			while (isWhitespace() || currentChar == '#') {
				if (isWhitespace())
				{
					skipWhitespace();
				}

				if (currentChar == '#') {
					skipComments();
				}
			}

			value = std::string(1, currentChar);

			switch (currentChar) {
			case '\0':
				t = TokenType::EOFL;
				value = std::string(1, '\0');
				break;
			case '=': 
				t = TokenType::OPERATOR; 
				advance();
				break;
			case ':': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '/': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '-': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '+': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '.': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '*': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '%': 
				t = TokenType::OPERATOR;
				advance(); 
				break;
			case '(': 
				t = TokenType::LPAREN; 
				advance();
				break;
			case ',': 
				t = TokenType::COMMA; 
				advance();
				break;
			case ')': 
				t = TokenType::RPAREN; 
				advance();
				break;
			case '[': 
				t = TokenType::LBRACKET; 
				advance();
				break;
			case ']': 
				t = TokenType::RBRACKET; 
				advance();
				break;
			case '"': 
				t = TokenType::STRING; 
				value = collectString(false); 
				break;
			case '\'': 
				t = TokenType::STRING; 
				value = collectString(true); 
				break;
			default:
				if (isalpha(currentChar)) {
					value = collectIdentifier();

					if (operators.find(value) != operators.end()) {
						t = TokenType::OPERATOR;
					}
					else {
						if (isupper(value.at(0))) {
							t = TokenType::TYPENAME;
						}
						else if (keywords.find(value) != keywords.end()) {
							t = TokenType::KEYWORD;
						}
						else {
							t = TokenType::IDENTIFIER;
						}
					}
				}
				else if (isdigit(currentChar)) {
					value = collectNumber();
					t = TokenType::NUMBER;
				}
				break;
			}

			//advance();

		}
		else {
			t = TokenType::EOFL;
			value = std::string(1, '\0');
		}


		//currentToken = 
		return Token{ t, value };
	}

	std::string Lexer::collectString(bool singleQuoted)
	{
		std::string s;
		auto closing = singleQuoted ? '\'' : '"';

		advance();
		while (currentChar != closing && !eof())
		{
			s += currentChar;
			advance();
		}

		advance();
		return s;
	}

	std::string Lexer::collectIdentifier()
	{
		// initialize string
		std::string s = std::string(1, currentChar);

		advance();
		while (isString() && !isPunctuation() && !eof())
		{
			s += currentChar;
			advance();
		}

		return s;
	}

	std::string Lexer::collectNumber()
	{
		// initialize string
		std::string s = std::string(1, currentChar);

		advance();
		while ((isDigit() || currentChar == '.') && !isWhitespace() && !eof())
		{
			s += currentChar;
			advance();
		}

		return s;
	}
	
	bool Lexer::eof()
	{
		return currentChar == '\0' || pos >= source.size();
	}

	bool Lexer::isDigit()
	{
		return isdigit(currentChar);
	}

	bool Lexer::isWhitespace()
	{
		return (currentChar == ' '
			|| currentChar == '\n'
			|| currentChar == '\r'
			|| currentChar == '\t'
			)
			//&& !isPunctuation()
			&& !eof();
	}


	bool Lexer::isString()
	{
		return isalnum(currentChar) && !isWhitespace() && !isPunctuation();
	}

	bool Lexer::isPunctuation()
	{
		return currentChar == ')' 
			|| currentChar == '(' 
			|| currentChar == ':' 
			;
	}
}

