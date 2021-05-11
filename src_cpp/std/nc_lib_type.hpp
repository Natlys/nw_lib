#ifndef NC_LIB_TYPE_HPP
#	define NC_LIB_TYPE_HPP
#	include "../nc_lib_core.hpp"
#		if (defined NC_API)
// includes //
#		include "../../nc_iop/src_cpp/cmp/nc_iop_cmp.hpp"
#		include "nc_lib_array.hpp"
// types //
/// type_information_type
class NC_API nc_type_info_t : public nc_op_cmp_t
{
public:
	using info_t = nc_type_info_t;
	using info_tc = const info_t;
	using type_t = v1u_t;
	using type_tc = const type_t;
	using tab_t = nc_array_tt<info_t>;
	using tab_tc = const tab_t;
public:
	type_t m_type;
	cstr_t m_name;
	size_t m_size;
	size_t m_alig;
public:
	// operators //
	nc_type_info_t(type_tc type, cstr_t tname, size_tc tsize, size_tc talig) :
		m_type(type), m_name(tname), m_size(tsize), m_alig(talig) { get_tab_static().push_back(*this); }
	nc_type_info_t(info_tc& copy) : m_type(copy.m_type), m_name(copy.m_name), m_size(copy.m_size), m_alig(copy.m_alig) { }
	nc_type_info_t(info_t&& copy) : m_type(copy.m_type), m_name(copy.m_name), m_size(copy.m_size), m_alig(copy.m_alig) { }
	inline ~nc_type_info_t() { }
	// getters //
	template <typename tname> static info_tc& get() { static info_tc s_inf (get_type_static()++, get_name<tname>(), sizeof(tname), alignof(tname)); return s_inf; }
	static inline info_tc& get(type_t type)         { return get_tab_static()[type]; }
	static inline type_tc get_type()                    { return get_type_static(); }
	template <typename tname> static type_tc get_type() { return get<tname>().m_type; }
	template<typename tname> static cstr_t get_name() {
	define NC_NAME_FRONT "const char *__cdecl" NC_NAMESPACE_STR "::type_info_t::get_name<"
	define NC_NAME_BACK ">(void)"
	define NC_NAME_LENGTH sizeof(__FUNCSIG__) - sizeof(NC_NAME_FRONT) - sizeof(NC_NAME_BACK)
		static char_t name[NC_NAME_LENGTH] { NC_NULL };
		memcpy(&name[0], &__FUNCSIG__[sizeof(NC_NAME_FRONT)], NC_NAME_LENGTH);
	undef NC_NAME_FRONT
	undef NC_NAME_BACK
	undef NC_NAME_LENGTH
		return name;
	}
	// predicates //
	static inline v1bit_t is_valid(type_t type)               { return type < get_tab_static().size(); }
	template<typename tname> static inline v1bit_t is_valid() { return is_valid(get_type<tname>()); }
	// operators //
	inline info_t& operator=(info_tc& copy) { NC_ERROR("this is entirely constant type!", return *this); return *this; }
	inline info_t& operator=(info_t&& copy) { NC_ERROR("this is entirely constant type!", return *this); return *this; }
	inline virtual op_stream_t& operator<<(op_stream_t& stm) const override {
		return stm << "{"
			<< "type:" << m_type << ";"
			<< "name:" << m_name << ";"
			<< "size:" << m_size << ";"
			<< "alig:" << m_alig << ";"
			<< "}";
	}
private:
	static inline type_t& get_type_static() { static type_t s_type = NC_NULL; return s_type; }
	static inline tab_t& get_tab_static()   { static tab_t s_table; return s_table; }
};
/// nc_type_owner_type
class NC_API nc_type_owner_t
{
public:
	using owner_t = nc_type_owner_t;
	using owner_tc = const owner_t;
	using type_t = v1u_t;
	using type_tc = const type_t;
	using info_t = nc_type_info_t;
	using info_tc = const info_t;
public:
	inline nc_type_owner_t() : m_type(NC_NULL) {}
	inline nc_type_owner_t(type_tc type) : nc_type_owner_t() { set_type(type); }
	inline nc_type_owner_t(owner_tc& copy) : nc_type_owner_t() { operator=(copy); }
	inline nc_type_owner_t(owner_t&& copy) : nc_type_owner_t() { operator=(copy); }
	virtual inline ~nc_type_owner_t() { }
	// getters //
	inline type_tc get_type() const       { return m_type; }
	inline info_tc& get_type_info() const { return nc_type_info_t::get(m_type); }
	inline cstr_t get_type_name() const   { return &get_type_info().m_name[0]; }
	inline size_t get_type_size() const   { return get_type_info().m_size; }
	// setters //
	inline v1nil_t set_type(type_tc type)       { m_type = type; }
	template<typename tname> v1nil_t set_type() { set_type(nc_cmp_tt::get_type<tname>()); }
	// predicates //
	inline v1bit_t has_type() const          { return m_type != NC_NULL; }
	inline v1bit_t has_type(type_tc type) const { return m_type == type; }
	template<typename tname> v1bit_t has_type() const { return has_type(type_info_t::get_type<tname>()); }
	template<typename tname> tname* check_cast() { return has_type<tname>() ? static_cast<tname*>(this) : NC_NULL; }
	template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NC_NULL; }
	// commands //
	// operators //
	inline v1nil_t operator=(owner_tc& copy) { set_type(copy.m_type); }
	inline v1nil_t operator=(owner_t&& copy) { set_type(copy.m_type); }
	inline v1bit_t operator==(owner_tc& owner) { return has_type(owner.get_type()); }
	inline v1bit_t operator!=(owner_tc& owner) { return !has_type(owner.get_type()); }
	template<typename tname>
	operator tname* ()             { NC_CHECK(has_type<tname>(), "type error!", return NC_NULL); return static_cast<tname*>(this); }
	template<typename tname>
	operator const tname* () const { NC_CHECK(has_type<tname>(), "type error!", return NC_NULL); return static_cast<const tname*>(this); }
	template<typename tname>
	operator tname& ()             { NC_CHECK(has_type<tname>(), "type error!", return *(tname*)(NC_NULL)); return *static_cast<tname*>(this); }
	template<typename tname>
	operator const tname& () const { NC_CHECK(has_type<tname>(), "type error!", return *(const tname*)(NC_NULL)); return *static_cast<const tname*>(this); }
protected:
	type_t m_type;
};
/// nc_type_owner_template_type
template<class tname, class tbase = nc_type_owner_t>
class nc_type_owner_tt : public tbase
{
public:
	using type_t = v1u_t;
	using type_tc = const type_t;
public:
	// ctor_dtor //
	template<typename ... args> nc_type_owner_tt(args&& ... arguments) : tbase(std::forward<args>(arguments)...) { set_type(get_type_static()); }
	virtual inline ~nc_type_owner_tt() { }
	// getters //
	static inline type_tc get_type_static() { return type_info_t::get_type<tname>(); }
	// predicates //
	template<typename tname> v1bit_t has_type() const { return tbase::has_type(tname::get_type_static()); }
	template<typename tname> tname* check_cast() { return has_type<tname>() ? static_cast<tname*>(this) : NC_NULL; }
	template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NC_NULL; }
	// commands //
	// operators //
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_TYPE_HPP //