#include "headers.h"
#include "RegexLexer.h"



namespace KScript {
	
	void RegexLexer::init()
	{
		// initialize keywords
		keywords["this"] = KeywordType::THIS;
		keywords["do"] = KeywordType::DO;
		keywords["fun"] = KeywordType::BEGIN_FUN;
		keywords["endfun"] = KeywordType::END_FUN;
		keywords["if"] = KeywordType::BEGIN_IF;
		keywords["endif"] = KeywordType::END_IF;
		keywords["for"] = KeywordType::BEGIN_FOR;
		keywords["endfor"] = KeywordType::END_FOR;
		keywords["return"] = KeywordType::RETURN;

		std::string kregex = "^(";
		for (auto& p : keywords) {
			kregex += p.first + "|";
		}
		// remove the last '|'
		kregex = kregex.substr(0, kregex.length() - 1);
		kregex += R"()\s(.*\n?)*)";
		keywordRegex = std::regex(kregex);

		// initialize vocabulary
		vocabulary[R"(^(:)(.*\n?)*)"] = TokenType::COLON;
		vocabulary[R"(^(=)(.*\n?)*)"] = TokenType::EQUALS;
		vocabulary[R"(^(\()(.*\n?)*)"] = TokenType::LPAREN;
		vocabulary[R"(^(\))(.*\n?)*)"] = TokenType::RPAREN;
		vocabulary[R"(^([0-9]+(\.[0-9]+)*)[^a-zA-Z_](.*\n?)*)"] = TokenType::NUMBER;
		vocabulary[R"(^(\"[^\"]*\"|\'[^\']*\')(.*\n?)*)"] = TokenType::STRING;
		vocabulary[R"(^([a-zA-Z_][\w]*)(.*\n?)*)"] = TokenType::IDENTIFIER;

		// add whitespace & comments
		whiteSpaceRegex = std::regex(
				R"(^(\s+).*)"
		);
		commentRegex = std::regex(
					R"(^(#.*\n?))"
				);
	}


	Token RegexLexer::getNextToken()
	{
		if (eof()) {
			currentToken = Token{ TokenType::EOFL, "\0" };
			return currentToken;
		} 
		
		TokenType tokenType = TokenType::UNKNOWN;
		std::string value = "\0";
		sourceFromPosition = source.substr(currentPosition);

		while (hasWhitespace(sourceFromPosition))
		{
			value = token_matcher[1].str();

			currentPosition += value.length();
			sourceFromPosition = source.substr(currentPosition);
		}
		
		while (hasComment(sourceFromPosition))
		{
			value = token_matcher[1].str();

			currentPosition += value.length();
			sourceFromPosition = source.substr(currentPosition);
		}

		bool found = false;


		if (sourceFromPosition.empty()) {
			currentToken = Token{ TokenType::EOFL, "\0" };
			return currentToken;
		}

		if (hasKeyword(sourceFromPosition)) {
			tokenType = TokenType::KEYWORD;
			
			value = token_matcher[1].str();
			currentPosition += value.length();
			found = true;
		}

		if (!found) {
			for (auto& p : vocabulary) {
				auto regex = std::regex(p.first);
				if (std::regex_match(sourceFromPosition, token_matcher, regex)) {
					// the token type
					tokenType = p.second;

					// the first matching group
					value = token_matcher[1].str();
					
					if (tokenType == TokenType::STRING) {
						// skip the surrounding quotes
						value = value.substr(1, value.length() - 2);
						currentPosition += value.length() + 2;
					}
					else {
						currentPosition += value.length();
					}
					break;
				}
			}
		}
	
		currentToken = Token{ tokenType, value };
		return currentToken;
	}

	bool RegexLexer::eof()
	{
		return currentPosition >= source.size();
	}

	bool RegexLexer::hasWhitespace(const std::string & s)
	{
		return std::regex_match(s, token_matcher, whiteSpaceRegex);
	}
	
	bool RegexLexer::hasComment(const std::string & s)
	{
		return std::regex_match(s, token_matcher, commentRegex);
	}
	
	bool RegexLexer::hasKeyword(const std::string & s)
	{
		return std::regex_match(s, token_matcher, keywordRegex);
	}

}

