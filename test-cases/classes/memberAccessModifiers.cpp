#include "RuntimeLibrary.hpp"

// Type Declarations
typedef struct C C;

// Function Declarations
C *_Nonnull C__new__1(C *_Nonnull self, string const name_);
inline C *_Nonnull new_C(string const name_);
auto main_() -> void;

// Class Declarations

struct C
{
	string name_;
	auto method_() const -> string;
	auto double_name_() const -> string;
};

// Global Definitions

// Definitions

C *_Nonnull C__new__1(C *_Nonnull self, string const name_)
{
	self->name_ = name_;
	return self;
}

inline C *_Nonnull new_C(string const name_)
{
	return C__new__1(new C(), name_);
}

auto ::C::method_() const -> string
{
	auto self = this;
	return double_name_();
}

auto ::C::double_name_() const -> string
{
	auto self = this;
	return name_.op__add(name_);
}

auto main_() -> void
{
	C const *_Nonnull const c_ = new_C(string("Bob"));
	c_->method_();
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		main_();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
