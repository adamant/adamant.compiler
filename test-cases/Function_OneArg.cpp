#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Identity_(p_int const value_) -> p_int;
auto Main_() -> p_int;

// Class Declarations

// Global Definitions

// Definitions

auto Identity_(p_int const value_) -> p_int
{
	return value_;
}

auto Main_() -> p_int
{
	return Identity_(p_int(42));
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	return Main_().Value;
}
