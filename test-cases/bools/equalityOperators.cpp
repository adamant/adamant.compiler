#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
BOOL True__0();
void main__0();

// Class Declarations

// Global Definitions

// Definitions

BOOL True__0()
{
	return TRUE;
}

void main__0()
{
	BOOL x__;
	x__ = equal_op(TRUE, FALSE);
	x__ = not_equal_op(TRUE, FALSE);
	x__ = equal_op(True__0(), True__0());
}

// Entry Point Adapter
int32_t main(int argc, char const *const * argv)
{
	main__0();
	return 0;
}
