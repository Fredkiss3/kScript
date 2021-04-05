#pragma once

namespace KScript {
	enum class Operator {
		// assignation & attributes access
		EQUALS, // =
		DOT,	// .

		// math
		MINUS,	// -
		ADD,	// +
		MUL,	// *
		DIV,	// / :
		PERCENT,	// %
		
		// boolean
		LT,		// lt (<)
		GT,		// gt (>)
		LTE,	// lte (<=)
		GTE,	// gte (>=)
		IS,		// is (==) 
		NOT,	// not (!=)
		AND,	// and (&&)
		OR,		// or (||)
	};
}