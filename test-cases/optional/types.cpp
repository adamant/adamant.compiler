#include "RuntimeLibrary.hpp"

// Type Declarations
struct t_Test;

// Function Declarations
t_Test *_Nonnull c_t_Test(t_Test *_Nonnull self);
inline t_Test *_Nonnull new_t_Test();
auto Func_(p_optional<str> const x_, p_optional<u32> const y_) -> p_optional<i32>;
auto main_(t_system__console__Console *_Nonnull const console_) -> void;

// Class Declarations

struct t_Test
{
};

// Global Definitions

// Definitions

t_Test *_Nonnull c_t_Test(t_Test *_Nonnull self) { return self; }

inline t_Test *_Nonnull new_t_Test()
{
	return c_t_Test(new t_Test());
}

auto Func_(p_optional<str> const x_, p_optional<u32> const y_) -> p_optional<i32>
{
	p_optional<i32> const z_ = none;
	t_Test const *_Nullable const t_ = none;
	t_system__text__String_Builder *_Nullable const sb_ = none;
	t_system__collections__List<p_optional<i32>> const *_Nonnull const l_ = new_t_system__collections__List<p_optional<i32>>();
	t_Test *_Nullable const m_ = none;
	p_optional<p_optional<i32>> const d_ = none;
	return none;
}

auto main_(t_system__console__Console *_Nonnull const console_) -> void
{
	Func_(none, none);
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		main_(new t_system__console__Console());
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
