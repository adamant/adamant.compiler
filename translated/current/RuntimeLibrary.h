// On windows this disables warnings about using fopen_s instead of fopen
// It must be defined before including the headers.
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <stdexcept>

// -----------------------------------------------------------------------------
// Logical Operators
// -----------------------------------------------------------------------------
// Use special templates taking closures to support short circuit evaluation

template<typename T, typename F>
T op_and(T const & lhs, F rhs)
{
	return lhs.op_false().value ? lhs : lhs.op_and(rhs());
}

template<typename T, typename F>
T op_or(T const & lhs, F rhs)
{
	return lhs.op_true().value ? lhs : lhs.op_or(rhs());
}

// -----------------------------------------------------------------------------
// Runtime Types
// -----------------------------------------------------------------------------
// Types used to model the language semantics

template<typename T>
struct ref
{
private:
	T *_Nonnull value;

public:
	ref(T *_Nonnull value): value(value) {}
};

template<typename T>
struct var
{
private:
	T value;

public:
	var(T&& value): value(value) {}
};

template<typename T>
struct let
{
private:
	T const value;

public:
	let(T&& value): value(value) {}
};

// -----------------------------------------------------------------------------
// Primitive Types
// -----------------------------------------------------------------------------

struct p_bool
{
public:
	// Runtime Members
	bool value;

	p_bool() = default;
	p_bool(bool value): value(value) {}
	p_bool& operator=(p_bool const& value) = default;

	p_bool *_Nonnull operator->() { return this; }
	p_bool const *_Nonnull operator->() const { return this; }
	p_bool & operator* () { return *this; }
	p_bool const & operator* () const { return *this; }

	// Adamant Members
	static auto construct() -> p_bool { return p_bool(false); }
	p_bool op_not() const { return !this->value; }
	p_bool op_true() const { return this->value; }
	p_bool op_false() const { return !this->value; }
	p_bool op_and(p_bool other) const { return this->value & other.value; }
	p_bool op_or(p_bool other) const { return this->value | other.value; }
};

struct p_uint;

struct p_int
{
public:
	// Runtime Use Members
	std::int32_t value;

	p_int() = default;
	p_int(std::int32_t value): value(value) {}

	p_int *_Nonnull operator->() { return this; }
	p_int const *_Nonnull operator->() const { return this; }
	p_int & operator* () { return *this; }
	p_int const & operator* () const { return *this; }

	// Hack to support conversion of uint to int for now
	p_int(p_uint value);

	// Adamant Members
	static auto construct() -> p_int { return 0; }
	void op_AddAssign(p_int other) { this->value += other.value; }
	void op_SubtractAssign(p_int other) { this->value -= other.value; }
	p_bool op_Equal(p_int other) const { return this->value == other.value; }
	p_bool op_NotEqual(p_int other) const { return this->value != other.value; }
	p_bool op_LessThan(p_int other) const { return this->value < other.value; }
	p_bool op_LessThanOrEqual(p_int other) const { return this->value <= other.value; }
	p_bool op_GreaterThan(p_int other) const { return this->value > other.value; }
	p_bool op_GreaterThanOrEqual(p_int other) const { return this->value >= other.value; }
	p_int op_Add(p_int other) const { return this->value + other.value; }
	p_int op_Subtract(p_int other) const { return this->value - other.value; }
	p_int op_Negate() const { return -this->value; }
	p_int op_Multiply(p_int other) const { return this->value * other.value; }
	p_int op_Divide(p_int other) const { return this->value / other.value; }
	p_int op_Remainder(p_int other) const { return this->value % other.value; }
	p_int op_Magnitude() const { if(this->value==INT32_MIN) throw std::overflow_error("Can't take |int.Min|"); return this->value < 0 ? -this->value : this->value; }

	// Hack because we don't support as correctly yet
	p_uint AsUInt_() const;
};

struct p_uint
{
public:
	// Runtime Use Members
	std::uint32_t value;

	p_uint() = default;
	p_uint(std::uint32_t value): value(value) {}

	p_uint *_Nonnull operator->() { return this; }
	p_uint const *_Nonnull operator->() const { return this; }
	p_uint & operator* () { return *this; }
	p_uint const & operator* () const { return *this; }

	// Hack to support conversion of int to uint for now
	p_uint(p_int value): value(value.value) {}

	// Adamant Members
	static auto construct() -> p_uint { return 0; }
	void op_AddAssign(p_uint other) { this->value += other.value; }
	void op_SubtractAssign(p_uint other) { this->value -= other.value; }
	p_bool op_Equal(p_uint other) const { return this->value == other.value; }
	p_bool op_NotEqual(p_uint other) const { return this->value != other.value; }
	p_bool op_LessThan(p_uint other) const { return this->value < other.value; }
	p_bool op_LessThanOrEqual(p_uint other) const { return this->value <= other.value; }
	p_bool op_GreaterThan(p_uint other) const { return this->value > other.value; }
	p_bool op_GreaterThanOrEqual(p_uint other) const { return this->value >= other.value; }
	p_uint op_Add(p_uint other) const { return this->value + other.value; }
	p_uint op_Subtract(p_uint other) const { return this->value - other.value; }
};

inline p_int::p_int(p_uint value)
	: value(value.value)
{
}

struct p_code_point
{
private:
	std::uint32_t value;

public:
	// Runtime Use Members
	p_code_point() = default;
	p_code_point(char value): value(value) {}
	char CharValue() const;

	p_code_point *_Nonnull operator->() { return this; }
	p_code_point const *_Nonnull operator->() const { return this; }
	p_code_point & operator* () { return *this; }
	p_code_point const & operator* () const { return *this; }

	// Adamant Members
	static auto construct() -> p_code_point { return '\0'; }
	p_bool op_Equal(p_code_point const & other) const { return this->value == other.value; }
	p_bool op_NotEqual(p_code_point const & other) const { return this->value != other.value; }
	// TODO: Not sure code_point should support these operations
	p_bool op_LessThan(p_code_point other) const { return this->value < other.value; }
	p_bool op_LessThanOrEqual(p_code_point other) const { return this->value <= other.value; }
	p_bool op_GreaterThan(p_code_point other) const { return this->value > other.value; }
	p_bool op_GreaterThanOrEqual(p_code_point other) const { return this->value >= other.value; }

};

struct p_string
{
public:
	// Runtime Use Members
	char const *_Nonnull Buffer;
	int Length;

	p_string() = default;
	p_string(char const *_Nonnull s);
	p_string(int length, char const *_Nonnull s);
	char const *_Nonnull cstr() const;
	p_string const *_Nonnull operator->() const { return this; }
	p_string const & operator* () const { return *this; }

	typedef char const *_Nonnull const_iterator;
	const_iterator begin() const { return &Buffer[0]; }
	const_iterator end() const { return &Buffer[Length]; }

	// Hack to support conversion of int and code_point to strings for now
	p_string(p_int other);
	p_string(p_code_point other);

	// Adamant Members
	static auto construct() -> p_string { p_string self; self.Length = 0; self.Buffer = 0; return self; }
	static auto construct(p_string value) -> p_string { return value; }
	static auto construct(p_code_point c, p_int repeat) -> p_string;
	// TODO ByteLength should be a property
	p_int ByteLength_() const { return this->Length; }

	p_string Substring_(p_int start, p_int length) const;
	p_string Substring_(p_int start) const { return Substring_(start, Length-start.value); }
	p_string Replace_(p_string oldValue, p_string newValue) const;
	p_int LastIndexOf_(p_code_point c) const;
	p_int index_of_(p_code_point c) const;

	p_code_point op_Element(p_int const index) const { return Buffer[index.value]; }
	p_string op_Add(p_string const & value) const;
	p_bool op_Equal(p_string const & other) const;
	p_bool op_NotEqual(p_string const & other) const { return !this->op_Equal(other).value; }
	p_bool op_LessThan(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) < 0; }
	p_bool op_LessThanOrEqual(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) <= 0; }
	p_bool op_GreaterThan(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) > 0; }
	p_bool op_GreaterThanOrEqual(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) >= 0; }
};

class None
{
public:
	template<class T>
	operator T*_Nullable() const { return static_cast<T*>(0); }
};
static const None p_none = None();

template<typename T>
struct p_optional
{
private:
	bool hasValue;
	union
    {
        T data;
    };

public:
	p_optional(T const & value) : data(value), hasValue(true) {}
	p_optional(None const none) : hasValue(false) {}
	T & operator->()
	{
		if(!hasValue) throw std::runtime_error("Access to `none` Optional value");
		return data;
	}
	T const & operator->() const
	{
		if(!hasValue) throw std::runtime_error("Access to `none` Optional value");
		return data;
	}
	T & operator* ()
	{
		if(!hasValue) throw std::runtime_error("Access to `none` Optional value");
		return data;
	}
	T const & operator* () const
	{
		if(!hasValue) throw std::runtime_error("Access to `none` Optional value");
		return data;
	}
};

// -----------------------------------------------------------------------------
// Standard Library
// -----------------------------------------------------------------------------
// Parts of the standard library that are currently implemented in the runtime.

// A placeholder function until we get proper exceptions implemented
_Noreturn inline void THROW_EXCEPTION_(const p_string& value)
{
	throw std::runtime_error(value.cstr());
}


inline void assert(const p_bool condition, const p_string code, const p_string message, const p_string file, const std::int32_t line)
{
	if(!condition.value)
		throw std::runtime_error(
			p_string("Assertion failed: ").op_Add(code).op_Add(", ").op_Add(message)
			.op_Add(", file ").op_Add(file).op_Add(", line ").op_Add(p_int(line)).cstr());
}

#define assert_(condition, message) assert(condition, #condition, message, __FILE__, __LINE__)


_Noreturn inline void NOT_IMPLEMENTED(const p_string message, const p_string function, const p_string file, const std::int32_t line)
{
	throw std::runtime_error(
		p_string("Function ").op_Add(function)
		.op_Add(p_string(" not yet implemented, ")).op_Add(message).op_Add(p_string(", ")).op_Add(file).op_Add(p_string(", line ")).op_Add(p_int(line)).cstr());
}

#define NOT_IMPLEMENTED_(message) NOT_IMPLEMENTED(message, __func__, __FILE__, __LINE__)


_Noreturn inline void UNREACHABLE(const p_string function, const p_string file, const std::int32_t line)
{
	throw std::runtime_error(
		p_string("Reached \"UNREACHABLE\" statement in function ").op_Add(function)
		.op_Add(p_string(", ")).op_Add(file).op_Add(p_string(", line ")).op_Add(p_int(line)).cstr());
}

#define UNREACHABLE_() UNREACHABLE(__func__, __FILE__, __LINE__)

class ResourceManager
{
public:
	p_string const & GetString_(p_string resourceName);
	void AddResource(p_string name, p_string value);
};

extern ResourceManager *_Nonnull const resource_manager_;

namespace system_
{
	namespace Collections_
	{
		template<typename T>
		class List_
		{
		private:
			T *_Nonnull values;
			int length;
			int capacity;

		public:
			// Runtime Use Members
			typedef T const *_Nonnull const_iterator;
			const_iterator begin() const { return values; }
			const_iterator end() const { return &values[length]; }

			// Adamant Members
			p_bool op_Equal(List_<T> const *_Nonnull other) const { return this == other; }
			p_bool op_NotEqual(List_<T> const *_Nonnull other) const { return this != other; }

			List_ *_Nonnull construct() { values = 0; length = 0; capacity = 0; return this; }
			void Add_(T value) { add_(value); }
			void Clear_() { clear_(); }
			void add_(T value);
			void clear_() { length = 0; }
			p_int op_Magnitude() const { return length; }
			T const & op_Element(p_int const index) const;
		};

		template<typename T>
		void List_<T>::add_(T value)
		{
			if(length >= capacity)
			{
				int newCapacity = capacity == 0 ? 16 : capacity * 2;
				// Allocate uninitalized buffer (note `sizeof(char) == 1` always)
				// Needed if T is a value type to avoid needing a default constructor
				T* newValues = (T*)new char[newCapacity * sizeof(T)];
				std::memcpy(newValues, values, length * sizeof(T));
				values = newValues;
				capacity = newCapacity;
			}
			values[length] = value;
			length++;
		}

		template<typename T>
		T const & List_<T>::op_Element(p_int const index) const
		{
			if(index.value < 0 || index.value >= length)
				throw std::out_of_range("List index out of bounds");
			return values[index.value];
		}
	}

	namespace Console_
	{
		class Console_
		{
		public:
			void Write_(p_string value);
			void WriteLine_(p_string value);
			void WriteLine_();
		};

		class Arguments_
		{
		private:
			p_string *_Nonnull args;
		public:
			// Runtime Use Members
			typedef p_string const *_Nonnull const_iterator;

			Arguments_(int argc, char const *_Nonnull const *_Nonnull argv);
			const_iterator begin() const { return &args[0]; }
			const_iterator end() const { return &args[Count]; }

			const int Count;

			// Adamant Members
			p_int op_Magnitude() const { return Count; }
			p_string const & Get_(int const index) const { return args[index]; }
		};
	}

	namespace IO_
	{
		class File_Reader_
		{
		private:
			std::FILE *_Nonnull file;

		public:
			File_Reader_ *_Nonnull construct(const p_string& fileName);
			p_string ReadToEndSync_();
			void Close_();
		};

		class File_Writer_
		{
		private:
			std::FILE *_Nonnull file;

		public:
			File_Writer_ *_Nonnull construct(const p_string& fileName);
			void Write_(const p_string& value);
			void Close_();
		};
	}

	namespace Text_
	{
		class String_Builder_
		{
		private:
			p_string buffer;
		public:
			// Runtime Use Members
			String_Builder_() = default;

			// Adamant Members
			p_bool op_Equal(String_Builder_ const *_Nonnull other) const { return this == other; }
			p_bool op_NotEqual(String_Builder_ const *_Nonnull other) const { return this != other; }

			String_Builder_ *_Nonnull construct() { buffer = p_string(""); return this; }
			String_Builder_ *_Nonnull construct(p_string const & value);
			void Append_(p_string const & value);
			void Append_(String_Builder_ const *_Nonnull value);
			void AppendLine_(p_string const& value);
			void AppendLine_();
			void Remove_(p_int start, p_int length);
			void Remove_(p_int start);
			p_string ToString_() const { return buffer; }
		};
	}
}

namespace System_ = system_;
