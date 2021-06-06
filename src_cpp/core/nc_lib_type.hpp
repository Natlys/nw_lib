#ifndef NC_LIB_TYPE_HPP
#	define NC_LIB_TYPE_HPP
#	include "../nc_lib_core.hpp"
#		if (defined NC_API)
/* includes */
#		include "../std/nc_lib_array.hpp"
/* defines */
/* typedefs */
/// type_information_type
class nc_type_info_t
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
	/* operators */
	nc_type_info_t(type_tc type, cstr_t tname, size_tc tsize, size_tc talig) :
		m_type(type), m_name(tname), m_size(tsize), m_alig(talig) { get_tab_static().push_back(*this); }
	nc_type_info_t(info_tc& copy) : m_type(copy.m_type), m_name(copy.m_name), m_size(copy.m_size), m_alig(copy.m_alig) { }
	nc_type_info_t(info_t&& copy) : m_type(copy.m_type), m_name(copy.m_name), m_size(copy.m_size), m_alig(copy.m_alig) { }
	inline ~nc_type_info_t() { }
	/* getters */
	static inline info_tc& get(type_t type)         { return get_tab_static()[type]; }
	template <typename tname> static info_tc& get() {
		static info_tc s_inf(get_type_static()++, get_name<tname>(), sizeof(tname), alignof(tname));
		return s_inf;
	}
	static inline type_tc get_type()                    { return get_type_static(); }
	template <typename tname> static type_tc get_type() { return get<tname>().m_type; }
	template<typename tname> static cstr_t get_name() {
#		define NC_NAME_FACE "const char *__cdecl" NC_NAMESPACE_STR "::nc_type_info_t::get_name<"
#		define NC_NAME_BACK ">(void)"
#		define NC_NAME_LENGTH sizeof(NC_FUNC_SIGL_STR) - sizeof(NC_NAME_FACE) - sizeof(NC_NAME_BACK)
		static char_t name[NC_NAME_LENGTH] { NC_NULL };
		memcpy(&name[0], &NC_FUNC_SIGL_STR[sizeof(NC_NAME_FACE)], NC_NAME_LENGTH);
#		undef NC_NAME_FACE
#		undef NC_NAME_BACK
#		undef NC_NAME_LENGTH
		return name;
	}
	/* vetters */
	static inline v1bit_t is_valid(type_t type)               { return type < get_tab_static().size(); }
	template<typename tname> static inline v1bit_t is_valid() { return is_valid(get_type<tname>()); }
	/* operators */
	inline info_t& operator=(info_tc& copy) { NC_ERROR("this is entirely constant type!", return *this); return *this; }
	inline info_t& operator=(info_t&& copy) { NC_ERROR("this is entirely constant type!", return *this); return *this; }
	inline nc_ostream_t& operator<<(nc_ostream_t& stm) const {
		return stm << "{"
			<< "type:" << m_type << ";"
			<< "name:" << m_name << ";"
			<< "size:" << m_size << ";"
			<< "alig:" << m_alig << ";"
			<< "}";
	}
private:
	static inline type_t& get_type_static() { static type_t s_type = NC_ZERO; return s_type; }
	static inline tab_t& get_tab_static()   { static tab_t s_table; return s_table; }
};
/// nc_type_owner_type
class nc_type_owner_t
{
public:
	using owner_t = nc_type_owner_t;
	using owner_tc = const owner_t;
	using type_t = v1u_t;
	using type_tc = const type_t;
	using info_t = nc_type_info_t;
	using info_tc = const info_t;
public:
	inline nc_type_owner_t() : m_type(NC_ZERO) { }
	inline nc_type_owner_t(type_tc type) : nc_type_owner_t() { set_type(type); }
	inline nc_type_owner_t(owner_tc& copy) : nc_type_owner_t() { operator=(copy); }
	inline nc_type_owner_t(owner_t&& copy) : nc_type_owner_t() { operator=(copy); }
	virtual ~nc_type_owner_t() = default;
	/* getters */
	inline type_tc get_type() const       { return m_type; }
	inline info_tc& get_type_info() const { return nc_type_info_t::get(m_type); }
	inline cstr_t get_type_name() const   { return &get_type_info().m_name[0]; }
	inline size_t get_type_size() const   { return get_type_info().m_size; }
	/* setters */
	inline owner_t& set_type(type_tc type)       { m_type = type; return *this; }
	template<typename tname> owner_t& set_type() { return set_type(nc_type_info_t::get_type<tname>()); }
	/* vetters */
	inline v1bit_t has_type() const             { return m_type != NC_ZERO; }
	inline v1bit_t has_type(type_tc type) const { return m_type == type; }
	template<typename tname> v1bit_t has_type() const { return has_type(nc_type_info_t::get_type<tname>()); }
	template<typename tname> tname* check_cast() { return has_type<tname>() ? static_cast<tname*>(this) : NC_NULL; }
	template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NC_NULL; }
	/* command */
	/* operators */
	inline owner_t& operator=(owner_tc& copy) { set_type(copy.m_type); return *this; }
	inline owner_t& operator=(owner_t&& copy) { set_type(copy.m_type); return *this; }
	inline v1bit_t operator==(owner_tc& owner) { return has_type(owner.get_type()); }
	inline v1bit_t operator!=(owner_tc& owner) { return !has_type(owner.get_type()); }
	template<typename tname> operator tname* ()             { NC_CHECK(has_type<tname>(), "type error!", NC_VOID); return NC_CAST(this, tname*); }
	template<typename tname> operator const tname* () const { NC_CHECK(has_type<tname>(), "type error!", NC_VOID); return NC_CAST(this, const tname*); }
	template<typename tname> operator tname& ()             { NC_CHECK(has_type<tname>(), "type error!", NC_VOID); return *NC_CAST(this, tname*); }
	template<typename tname> operator const tname& () const { NC_CHECK(has_type<tname>(), "type error!", NC_VOID); return *NC_CAST(this, const tname*); }
protected:
	type_t m_type;
};
/// nc_type_owner_template_type
template<class tprim, class tbase = nc_type_owner_t>
class nc_type_owner_tt : public tbase
{ NC_CHECK_TYPE_BASE(tprim, tbase, "tprim must inherit tbase!");
public:
	using type_t = v1u_t;
	using type_tc = const type_t;
public:
	/* codetor */
	template<typename ... targs> nc_type_owner_tt(targs&& ... args) : tbase(std::forward<targs>(args)...) { set_type(get_type_static()); }
	virtual ~nc_type_owner_tt() = default;
	/* getters */
	static inline type_tc get_type_static() { return nc_type_info_t::get_type<tprim>(); }
	/* vetters */
	template<typename tname> v1bit_t has_type() const { return tbase::has_type(tname::get_type_static()); }
	template<typename tname> tname* check_cast()             { return has_type<tname>() ? static_cast<tname*>(this) : NC_NULL; }
	template<typename tname> const tname* check_cast() const { return has_type<tname>() ? static_cast<const tname*>(this) : NC_NULL; }
	/* command */
	/* operators */
};
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_TYPE_HPP */