#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto Main_(::System_::Console_::Console_ *_Nonnull const console_) -> void;

// Class Declarations

// Global Definitions

// Definitions

auto Main_(::System_::Console_::Console_ *_Nonnull const console_) -> void
{
	p_int x_ = p_int(1);
	for (;;)
	{
		if (cond(equal_op(x_.op_remainder(p_int(3)), p_int(0))))
		{
			if (cond(equal_op(x_.op_remainder(p_int(5)), p_int(0))))
			{
				console_->WriteLine_(p_string("FizzBuzz"));
			}
			else
			{
				console_->WriteLine_(p_string("Fizz"));
			}
		}
		else if (cond(equal_op(x_.op_remainder(p_int(5)), p_int(0))))
		{
			console_->WriteLine_(p_string("Buzz"));
		}
		else
		{
			console_->WriteLine_(x_);
		}

		x_.op_add_assign(p_int(1));
		if (cond(x_.op_greater_than(p_int(100))))
		{
			break;
		}
	}
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		Main_(new ::System_::Console_::Console_());
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
