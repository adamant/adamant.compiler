#include "runtime.h"

// Declarations
int Main();

// Class Declarations

// Definitions
int Main()
{
	int const result = 42;
	return result;
}

// Entry Point Adapter
int main(int argc, char const *const * argv)
{
	return Main();
}
