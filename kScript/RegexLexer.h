#pragma once
#include "Token.h"
#include "Keywords.h"
#include "headers.h"

namespace KScript {
	class RegexLexer
	{
	public:
		RegexLexer(std::string& src) : source(src), currentPosition(0)
		{
			init();
			sourceFromPosition = source.substr(0, source.find('\n'));

			while (currentToken.type != TokenType::EOFL)
			{
				auto token = getNextToken();
				tokens.push_back(token);
			}
		}


		RegexLexer(std::string&& src) : RegexLexer(src) {}
		
		std::vector<Token>& getTokens() { return tokens; }

		Keyword getKeyWordType(std::string& src) { return keywords[src]; }

	private:
		void init();

		
		Token getNextToken();

		bool eof();
		bool hasWhitespace(const std::string& s);
		bool hasComment(const std::string& s);
		bool hasKeyword(const std::string& s);
		
	private:
		std::vector<Token> tokens;
		
		std::unordered_map<std::string, TokenType> vocabulary;
		std::unordered_map<std::string, Keyword> keywords;

		// regexes
		std::regex whiteSpaceRegex;
		std::regex commentRegex;
		std::regex keywordRegex;
		

		std::smatch token_matcher;  

		Token currentToken{ TokenType::UNKNOWN, "" };

		std::string source;
		std::string sourceFromPosition;

		//char currentChar;

		//int line;
		//int column;
		int currentPosition;
	};
}