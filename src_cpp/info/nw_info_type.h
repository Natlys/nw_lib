#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#	if (defined NW_API)
#	include "../std/nw_std_cont.h"
#	include "../io/nw_io_cmp.h"
namespace NW
{
	/// type_information static class
	class NW_API type_info : public a_io_cmp
	{
	public:
		using info_t = type_info;
		using info_tc = const info_t;
		using type_t = v1u;
		using type_tc = const type_t;
		using tab_t = darray<type_info>;
		using tab_tc = const tab_t;
	public:
		type_tc type;
		cstr name;
		size_t size;
		size_t align;
	public:
		type_info(type_tc type = NW_NULL, cstr tname = NW_NULL, size_tc tsize = NW_NULL, size_tc talign = NW_NULL);
		type_info(info_tc& copy) : type(copy.type), name(copy.name), size(copy.size), align(copy.align) { }
		type_info(info_t&& copy) : type(copy.type), name(copy.name), size(copy.size), align(copy.align) { }
		virtual ~type_info() = default;
		// --getters
		template <typename tname>
		static info_tc& get()                   { static info_tc s_inf (get_type_static()++, get_name<tname>(), sizeof(tname), alignof(tname)); return s_inf; }
		static inline info_tc& get(type_t type) { return get_tab_static()[type]; }
		static inline type_tc get_type()        { return get_type_static(); }
		template <typename tname>
		static inline type_tc get_type()        { return get<tname>().type; }
		template<typename tname>
		static inline cstr get_name() {
#		define NW_NAME_FRONT "const char *__cdecl" NW_NAMESPACE_STR "::type_info::get_name<"
#		define NW_NAME_BACK ">(void)"
#		define NW_NAME_LENGTH sizeof(__FUNCSIG__) - sizeof(NW_NAME_FRONT) - sizeof(NW_NAME_BACK)
			static schar name[NW_NAME_LENGTH] { NW_NULL };
			memcpy(&name[0], &__FUNCSIG__[sizeof(NW_NAME_FRONT)], NW_NAME_LENGTH);
#		undef NW_NAME_FRONT
#		undef NW_NAME_BACK
#		undef NW_NAME_LENGTH
			return name;
		}
		// --predicates
		static inline v1bit is_valid(type_t type)               { return type < get_tab_static().size(); }
		template<typename tname> static inline v1bit is_valid() { return is_valid(get_type<tname>()); }
		// --operators
		inline v1nil operator=(info_tc& copy) { NW_ERROR("this is entirely constant type!", return); }
		inline v1nil operator=(info_t&& copy) { NW_ERROR("this is entirely constant type!", return); }
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	private:
		static inline type_t& get_type_static() { static type_t s_type = NW_NULL; return s_type; }
		static inline tab_t& get_tab_static()   { static tab_t s_table; return s_table; }
	};
}
namespace NW
{
	/// type_owner abstract class
	class NW_API a_type_owner
	{
	public:
		using type_t = v1u;
		using type_tc = const type_t;
		using info_t = type_info;
		using info_tc = const info_t;
	protected:
		a_type_owner() = default;
	public:
		virtual ~a_type_owner() = default;
		// --getters
		virtual inline type_tc get_type() const = 0;
		inline info_tc& get_type_info() const { return type_info::get(get_type()); }
		// --predicates
		inline v1bit has_type(type_tc type) const       { return get_type() == type; }
		template<typename tname> v1bit has_type() const { return has_type(tname::get_type_static()); }
		template<typename tname> tname* check_cast()             { return has_type<tname>() ? static_cast<tname*>(this) : NW_NULL; }
		template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<tname*>(this) : NW_NULL; }
	};
	/// type_owner template class
	template<class tname, class tbase = a_type_owner>
	class t_type_owner : public tbase
	{
	public:
		using type_t = v1u;
		using type_tc = const type_t;
	protected:
		template<typename ... args>
		t_type_owner(args&& ... arguments) : tbase(std::forward<args>(arguments)...) { }
	public:
		virtual ~t_type_owner() = default;
		// --getters
		virtual inline type_tc get_type() const override { return type_info::get_type<tname>(); }
		static inline type_tc get_type_static()          { return type_info::get_type<tname>(); }
	};
	/// value_type_owner class
	class NW_API v_type_owner
	{
	public:
		using vtype_t = v1u;
		using vtype_tc = const vtype_t;
		using vinfo_t = type_info;
		using vinfo_tc = const vinfo_t;
		using owner_t = v_type_owner;
		using owner_tc = const owner_t;
	public:
		v_type_owner();
		v_type_owner(vtype_tc type);
		v_type_owner(owner_tc& copy);
		v_type_owner(owner_t&& copy);
		virtual ~v_type_owner() = default;
		// --getters
		inline vtype_tc get_vtype() const       { return m_vtype; }
		inline vinfo_tc& get_vtype_info() const { return type_info::get(m_vtype); }
		inline cstr get_vtype_name() const      { return &get_vtype_info().name[0]; }
		inline size_t get_vtype_size() const    { return get_vtype_info().size; }
		// --setters
		inline v1nil set_vtype(vtype_tc type);
		// --predicates
		inline v1bit has_vtype(cv1u type) const          { return m_vtype == type; }
		template<typename tname> v1bit has_vtype() const { return has_vtype(type_info::get_type<tname>()); }
		// --operators
		inline v1nil operator=(owner_tc& copy) { m_vtype = copy.m_vtype; }
		inline v1nil operator=(owner_t&& copy) { m_vtype = copy.m_vtype; }
		template<typename tname>
		operator tname* ()             { NW_CHECK(has_vtype<tname>(), "type error!", return NW_NULL); return static_cast<tname*>(this); }
		template<typename tname>
		operator const tname* () const { NW_CHECK(has_vtype<tname>(), "type error!", return NW_NULL); return static_cast<const tname*>(this); }
		template<typename tname>
		operator tname& ()             { NW_CHECK(has_vtype<tname>(), "type error!", return *(tname*)(NW_NULL)); return *static_cast<tname*>(this); }
		template<typename tname>
		operator const tname& () const { NW_CHECK(has_vtype<tname>(), "type error!", return *(const tname*)(NW_NULL)); return *static_cast<const tname*>(this); }
	protected:
		vtype_t m_vtype;
	};
}
#	endif	// NW_API
#endif	// NW_INFO_TYPE_H