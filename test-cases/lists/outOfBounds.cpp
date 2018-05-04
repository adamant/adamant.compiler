#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto main_() -> i32;

// Class Declarations

// Global Definitions

// Definitions

auto main_() -> i32
{
	::System_::Collections_::List_<i32> const *_Nonnull const values_ = (new ::System_::Collections_::List_<i32>())->construct();
	return values_->op_Element(i32(0));
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
