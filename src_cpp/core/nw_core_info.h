#ifndef NW_CORE_INFO_H
#define NW_CORE_INFO_H
#include "nw_lib_pch.hpp"
#ifndef NW_LIB_CORE_HPP_H
#	if (defined NW_FOREACH) || (defined NW_INVOKER) || (defined NW_ITERATOR)
#		error "macroses named above must not be defined here"
#	else
#	define NW_FOREACH(INVOKER, ITERATOR) \
	INVOKER(bit, BIT, ITERATOR) \
	INVOKER(s08, S08, ITERATOR) \
	INVOKER(u08, U08, ITERATOR) \
	INVOKER(s16, S16, ITERATOR) \
	INVOKER(u16, U16, ITERATOR) \
	INVOKER(s32, S32, ITERATOR) \
	INVOKER(u32, U32, ITERATOR) \
	INVOKER(s64, S64, ITERATOR) \
	INVOKER(u64, U64, ITERATOR) \
	INVOKER(f32, F32, ITERATOR) \
	INVOKER(f64, F64, ITERATOR) \
// apply to every system type
#	define NW_INVOKER(tname, tenum, ITERATOR)   \
	ITERATOR(v1##tname, NW_TYPE_V1##tenum, 1u)  \
	ITERATOR(v2##tname, NW_TYPE_V2##tenum, 2u)  \
	ITERATOR(v3##tname, NW_TYPE_V3##tenum, 3u)  \
	ITERATOR(v4##tname, NW_TYPE_V4##tenum, 4u)  \
	ITERATOR(m2##tname, NW_TYPE_M2##tenum, 4u)  \
	ITERATOR(m3##tname, NW_TYPE_M3##tenum, 9u)  \
	ITERATOR(m4##tname, NW_TYPE_M4##tenum, 16u) \
// apply every type of matrix and vector to every value type
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
namespace NW
{
#	define NW_ITERATOR(tname, tenum) tenum,
	enum value_types_ : venum {
		NW_TYPE_DEFAULT = NW_NULL,
		NW_FOREACH(NW_INVOKER, NW_ITERATOR)
	};
	typedef venum value_types;
#	undef NW_ITERATOR
	/// info_type enumed struct
	template<cvenum tenum> struct e_info_type;
	/// info_type typed struct
	template<typename tname> struct t_info_type;
	/// info_type struct
	struct info_type
	{
		using type = value_types;
		using ctype = const type;
	public:
		info_type(cstr tname, ctype tenum, csize esize, csize ecount = 1u) :
			type_name(tname),
			type_enum(tenum),
			elem_size(esize),
			elem_count(ecount)
		{
		}
		// --core_methods
		template<typename tname>
		static inline t_info_type<tname>& get() { static t_info_type<tname> inf; return inf; }
		template<ctype tenum>
		static inline e_info_type<tenum>& get() { static e_info_type<tenum> inf; return inf; }
		static inline info_type& get(ctype tenum);
	public:
		cstr type_name;
		ctype type_enum;
		csize elem_size;
		csize elem_count;
	};
	/// basic value type instances (tname and tenum must be defined)
#	define NW_ITERATOR(tname, tenum, vcount)         \
	template<>                                       \
	struct e_info_type<tenum> : public info_type {   \
		using sys_type = tname;                      \
		e_info_type() : info_type(                   \
		#tname, tenum,                               \
		sizeof(tname), vcount) { } };                \
	template<>                                       \
	struct t_info_type<tname> : public info_type {   \
		using sys_type = tname;                      \
		t_info_type() : info_type(                   \
		#tname, tenum,                               \
		sizeof(tname), vcount) { } };                \
// that's it
	NW_FOREACH(NW_INVOKER, NW_ITERATOR);
	template<> struct e_info_type<NW_TYPE_DEFAULT> : public info_type {
		using sys_type = void;
		e_info_type() : info_type(NW_DEFAULT_STR, NW_TYPE_DEFAULT, 0u) { }
	};
	template<> struct t_info_type<void> : public info_type {
		using sys_type = void;
		t_info_type() : info_type(NW_DEFAULT_STR, NW_TYPE_DEFAULT, 0u) { }
	};
#	undef NW_ITERATOR
		// dynamic-static bridge for info getter
#	define NW_ITERATOR(tname, tenum) case tenum: return get<tname>();
		inline info_type& info_type::get(ctype tenum) {
		switch (tenum) {
			NW_FOREACH(NW_INVOKER, NW_ITERATOR);
		}
		return get<NW_TYPE_DEFAULT>();
	}
#	undef NW_ITERATOR
}
#	undef NW_INVOKER
#	undef NW_FOREACH
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP_H
#endif	// NW_CORE_INFO_H