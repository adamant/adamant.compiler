#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Main_() -> void;

// Class Declarations

// Global Definitions

// Definitions

auto Main_() -> void
{
	p_int x_ = p_int(1)->op_Plus(p_int(2));
	x_ = p_int(1)->op_Minus(p_int(2));
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	Main_();
	return 0;
}
