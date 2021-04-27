#ifndef NW_CORE_VALUE_H
#define NW_CORE_VALUE_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	typedef void         v1nil;
	typedef const void  cv1nil;
	typedef void*        v1ptr;
	typedef const void* cv1ptr;
}
namespace NW
{
	/// typed_number struct
	template <typename tval>
	struct t_num
	{
	public:
		using num_t = t_num<tval>;
		using num_tc = const num_t;
		using val_t = tval;
		using val_tc = const val_t;
	public:
		// --constructor_destructor
#	if (NW_TRUE)
		constexpr inline t_num() : m_value(static_cast<val_t>(NW_NULL)) { }
		constexpr inline t_num(val_tc value) : m_value(value) { }
		constexpr inline t_num(num_tc& copy) : m_value(copy.m_value) { }
		constexpr inline t_num(num_t&& copy) : m_value(std::move(copy.m_value)) { }
		~t_num() = default;
#	endif	// constructor_destructor
		// --getters
#	if (NW_TRUE)
#	endif	// getters
		// --setters
#	if (NW_TRUE)
#	endif	// setters
		// --predicates
#	if (NW_TRUE)
#	endif	// predicates
		// --operators
#	if (NW_TRUE)
		// // --math
#		if (NW_TRUE)
#		endif	// math
		// // --assignment
#		if (NW_TRUE)
		inline t_num& operator=(num_tc& copy) { m_value = copy.m_value; return *this; }
		inline t_num& operator=(num_t&& copy) { m_value = std::move(copy.m_value); return *this; }
#		endif	// assignment
		// // --convertion
#		if (NW_TRUE)
		inline operator val_t& ()        { return m_value; }
		inline operator val_tc& () const { return m_value; }
		inline operator val_t* ()        { return &m_value; }
		inline operator val_tc* () const { return &m_value; }
#		endif	// convertion
		// // --logic
#		if (NW_TRUE)
#		endif	// logic
		// // --input_output
#		if (NW_TRUE)
#		endif	// input_output
#	endif	// operators
		// --core_methods
	public:
		val_t m_value;
	};
}
#	if (!defined NW_FOREACH && !defined NW_INVOKER && !defined NW_ITERATOR)
#	define NW_FOREACH(INVOKER, ITERATOR)   \
	INVOKER(bit, bool, ITERATOR)           \
	INVOKER(s08, signed char, ITERATOR)    \
	INVOKER(u08, unsigned char, ITERATOR)  \
	INVOKER(s16, signed short, ITERATOR)   \
	INVOKER(u16, unsigned short, ITERATOR) \
	INVOKER(s32, signed int, ITERATOR)     \
	INVOKER(u32, unsigned int, ITERATOR)   \
	INVOKER(s64, signed long, ITERATOR)    \
	INVOKER(u64, unsigned long, ITERATOR)  \
	INVOKER(f32, float, ITERATOR)          \
	INVOKER(f64, double, ITERATOR)         \
	INVOKER(b, bool, ITERATOR)         \
	INVOKER(s, signed int, ITERATOR)   \
	INVOKER(u, unsigned int, ITERATOR) \
	INVOKER(f, float, ITERATOR)        \
	INVOKER(n, double, ITERATOR)       \
// that's it
#	define NW_INVOKER(tname, vtype, ITERATOR) \
		ITERATOR(v1##tname, vtype)            \
// that's it
#		if (NW_FALSE)
#	define NW_ITERATOR(tname, vtype) \
	typedef t_num<vtype> tname;      \
	typedef const tname  c##tname;   \
// that's it
namespace NW { NW_FOREACH(NW_INVOKER, NW_ITERATOR); }
#		endif
#		if (NW_TRUE)
#	define NW_ITERATOR(tname, vtype) \
		typedef vtype          tname; \
		typedef const tname c##tname; \
// that's it
namespace NW { NW_FOREACH(NW_INVOKER, NW_ITERATOR); }
#		endif
#	undef NW_ITERATOR
#	undef NW_INVOKER
#	undef NW_FOREACH
#	else
#		error "macroses named above must not be defined here"
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
#else
#	error "nw_lib_core.hpp must be included before this file"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_VALUE_H