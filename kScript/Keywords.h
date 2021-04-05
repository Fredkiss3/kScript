#pragma once

namespace KScript {
	enum class Keyword {
		THIS,

		CMP,
		END_CMP,
		
		BEGIN_FUN,
		RETURN,
		END_FUN,
		
		BEGIN_IF,
		END_IF,

		BEGIN_FOR,
		END_FOR,

		BEGIN_WHILE,
		END_WHILE,

		DO,
	};
}