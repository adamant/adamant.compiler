#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto main_() -> i32;
auto Func_() -> i32;

// Class Declarations

// Global Definitions

// Definitions

auto main_() -> i32
{
	return Func_();
}

auto Func_() -> i32
{
	return i32(42);
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		return main_().value;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
