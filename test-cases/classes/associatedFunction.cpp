#include "RuntimeLibrary.h"

// Type Declarations
class C_;

// Function Declarations
auto Main_() -> void;

// Class Declarations

class C_
{
public:
	p_bool op_equal(C_ const * other) const { return this == other; }
	p_bool op_not_equal(C_ const * other) const { return this != other; }
	auto method_() const -> p_string;
	static auto function_() -> p_string;
	auto construct() -> ::C_* { return this; }
};

// Global Definitions

// Definitions

auto ::C_::method_() const -> p_string
{
	auto self = this;
	return function_();
}

auto ::C_::function_() -> p_string
{
	return p_string("hello");
}

auto Main_() -> void
{
	::C_ const *_Nonnull const c_ = (new ::C_())->construct();
	c_->method_();
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		Main_();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
