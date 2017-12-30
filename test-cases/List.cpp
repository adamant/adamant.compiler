#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Main_(::System_::Console_::Console_ *const console_) -> void;

// Class Declarations

// Global Definitions

// Definitions

auto Main_(::System_::Console_::Console_ *const console_) -> void
{
	::System_::Collections_::List_<p_string> *const strings_ = new ::System_::Collections_::List_<p_string>();
	strings_->Add_(p_string("Hello"));
	strings_->Add_(p_string("World!"));
	if (strings_->Length_()->op_NotEqual(p_int(2)).Value)
	{
		console_->WriteLine_(p_string("List length not 2!"));
	}

	console_->WriteLine_(strings_->Get_(p_int(0)));
	for (p_string const s_ : *(strings_))
	{
		console_->Write_(s_);
	}

	console_->WriteLine_();
	::System_::Collections_::List_<::System_::Text_::String_Builder_ *> *const builders_ = new ::System_::Collections_::List_<::System_::Text_::String_Builder_ *>();
	builders_->Add_(new ::System_::Text_::String_Builder_(p_string("sb[0]: ")));
	builders_->Add_(new ::System_::Text_::String_Builder_(p_string("sb[1]: ")));
	for (::System_::Text_::String_Builder_ *const sb_ : *(builders_))
	{
		sb_->Append_(p_string("value"));
	}

	for (::System_::Text_::String_Builder_ const *const sb_ : *(builders_))
	{
		console_->WriteLine_(sb_->ToString_());
	}
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	Main_(new ::System_::Console_::Console_());
	return 0;
}
