#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Main() -> int;

// Class Declarations

// Definitions
auto Main() -> int
{
	int const result = 42;
	return result;
}

// Entry Point Adapter
int main(int argc, char const *const * argv)
{
	return Main();
}
