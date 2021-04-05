#include "headers.h"
//#include "kScript.h"
#include "Lexer.h"
#include "RegexLexer.h"
#include <sstream>
#include <string>

using namespace KScript;

int main(int argc, char* argv[]) {
	std::string val;

	std::string line;
	std::string src;

	if (argc >= 2) {
		auto str = std::string(argv[1]);

		std::ifstream infile(str);

		while (std::getline(infile, line))
		{
			src += line + "\n";
		}
	}
	else {
		src = "cmp Hello do\n" 
				"\t# variable\n"
				"\tInt var = 5\n"
			"endcmp"
			"\n"
			"fun main(String[] args) do\n"
				"\t# console\n"
				"\tprint(this.var)\n"
			"endfun\n"
			"\n"
			;
	}


	// process pair (a,b)
	std::cout << "Src Code : \n#Begin\n" << src << "\n#end" << std::endl;

	auto lex = Lexer(src);
	Token t = lex.getNextToken();

	std::cout << "\nRegular Lexer : " << std::endl;
	while(t.type != TokenType::EOFL && t.type != TokenType::UNKNOWN) {
		std::cout << t.toString() << std::endl;
		t = lex.getNextToken();
	}

	if (t.type == TokenType::UNKNOWN) {
		std::cout << "Unknown token : '" << t.value << "'" << std::endl;
	}


	//while (true) {
	//	std::cout << "kscript> ";

	//	getline(std::cin, val);
	//	if (val == "exit") {
	//		break;
	//	}

	//	auto res = Kscript::run(val);
	//	std::cout << res.toString() << std::endl << std::endl;
	//}

}