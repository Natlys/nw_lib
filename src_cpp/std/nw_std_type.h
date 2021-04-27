#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#	if (defined NW_API)
#	include "../std/nw_std_array.h"
#	include "../iop/nw_iop_cmp.h"
namespace NW
{
	/// type_information static class
	class NW_API type_info : public a_op_cmp
	{
	public:
		using info_t = type_info;
		using info_tc = const info_t;
		using type_t = v1u;
		using type_tc = const type_t;
		using tab_t = darray_t<type_info>;
		using tab_tc = const tab_t;
	public:
		type_t type;
		cstr_t name;
		size_t size;
		size_t alig;
	public:
		// --operators
		type_info(type_tc type, cstr_t tname, size_tc tsize, size_tc talig) :
			type(type), name(tname), size(tsize), alig(talig) { get_tab_static().push_back(*this); }
		type_info(info_tc& copy) : type(copy.type), name(copy.name), size(copy.size), alig(copy.alig) { }
		type_info(info_t&& copy) : type(copy.type), name(copy.name), size(copy.size), alig(copy.alig) { }
		virtual ~type_info() = default;
		// --getters
		template <typename tname>
		static info_tc& get()                   { static info_tc s_inf (get_type_static()++, get_name<tname>(), sizeof(tname), alignof(tname)); return s_inf; }
		static inline info_tc& get(type_t type) { return get_tab_static()[type]; }
		static inline type_tc get_type()        { return get_type_static(); }
		template <typename tname>
		static inline type_tc get_type()        { return get<tname>().type; }
		template<typename tname>
		static inline cstr_t get_name() {
#		define NW_NAME_FRONT "const char *__cdecl" NW_NAMESPACE_STR "::type_info::get_name<"
#		define NW_NAME_BACK ">(void)"
#		define NW_NAME_LENGTH sizeof(__FUNCSIG__) - sizeof(NW_NAME_FRONT) - sizeof(NW_NAME_BACK)
			static char_t name[NW_NAME_LENGTH] { NW_NULL };
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
		virtual op_stream_t& operator<<(op_stream_t& stm) const override {
			return stm << "{"
				<< "type:" << type << ";"
				<< "name:" << name << ";"
				<< "size:" << size << ";"
				<< "alig:" << alig << ";"
				<< "}";
		}
	private:
		static inline type_t& get_type_static() { static type_t s_type = NW_NULL; return s_type; }
		static inline tab_t& get_tab_static()   { static tab_t s_table; return s_table; }
	};
}
namespace NW
{
	/// a_type_owner class
	class NW_API a_type_owner
	{
	public:
		using owner_t = a_type_owner;
		using owner_tc = const owner_t;
		using type_t = v1u;
		using type_tc = const type_t;
		using info_t = type_info;
		using info_tc = const info_t;
	public:
		inline a_type_owner() : m_type(NW_NULL) {}
		inline a_type_owner(type_tc type) : a_type_owner() { set_type(type); }
		inline a_type_owner(owner_tc& copy) : a_type_owner() { operator=(copy); }
		inline a_type_owner(owner_t&& copy) : a_type_owner() { operator=(copy); }
		virtual ~a_type_owner() { }
		// --getters
		inline type_tc get_type() const       { return m_type; }
		inline info_tc& get_type_info() const { return type_info::get(m_type); }
		inline cstr_t get_type_name() const   { return &get_type_info().name[0]; }
		inline size_t get_type_size() const   { return get_type_info().size; }
		// --setters
		inline v1nil set_type(type_tc type)       { m_type = type; }
		template<typename tname> v1nil set_type() { set_type(type_info::get_type<tname>()); }
		// --predicates
		inline v1bit has_type() const          { return m_type != NW_NULL; }
		inline v1bit has_type(type_tc type) const { return m_type == type; }
		template<typename tname> v1bit has_type() const { return has_type(type_info::get_type<tname>()); }
		template<typename tname> tname* check_cast() { return has_type<tname>() ? static_cast<tname*>(this) : NW_NULL; }
		template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NW_NULL; }
		// --operators
		inline v1nil operator=(owner_tc& copy) { set_type(copy.m_type); }
		inline v1nil operator=(owner_t&& copy) { set_type(copy.m_type); }
		inline v1bit operator==(owner_tc& owner) { return has_type(owner.get_type()); }
		inline v1bit operator!=(owner_tc& owner) { return !has_type(owner.get_type()); }
		template<typename tname>
		operator tname* ()             { NW_CHECK(has_type<tname>(), "type error!", return NW_NULL); return static_cast<tname*>(this); }
		template<typename tname>
		operator const tname* () const { NW_CHECK(has_type<tname>(), "type error!", return NW_NULL); return static_cast<const tname*>(this); }
		template<typename tname>
		operator tname& ()             { NW_CHECK(has_type<tname>(), "type error!", return *(tname*)(NW_NULL)); return *static_cast<tname*>(this); }
		template<typename tname>
		operator const tname& () const { NW_CHECK(has_type<tname>(), "type error!", return *(const tname*)(NW_NULL)); return *static_cast<const tname*>(this); }
	protected:
		type_t m_type;
	};
	/// typed_type_owner class
	template<class tname, class tbase = a_type_owner>
	class t_type_owner : public tbase
	{
	public:
		using type_t = v1u;
		using type_tc = const type_t;
	protected:
		template<typename ... args>
		t_type_owner(args&& ... arguments) : tbase(std::forward<args>(arguments)...) { set_type(get_type_static()); }
	public:
		virtual ~t_type_owner() = default;
		// --getters
		static inline type_tc get_type_static() { return type_info::get_type<tname>(); }
		// --predicates
		template<typename tname> v1bit has_type() const { return tbase::has_type(tname::get_type_static()); }
		template<typename tname> tname* check_cast() { return has_type<tname>() ? static_cast<tname*>(this) : NW_NULL; }
		template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NW_NULL; }
	};
}
#	endif	// NW_API
#endif	// NW_INFO_TYPE_H