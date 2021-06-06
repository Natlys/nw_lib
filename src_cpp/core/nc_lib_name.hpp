#ifndef NC_LIB_NAME_HPP
#	define NC_LIB_NAME_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
/* defines */
/* typedefs */
/// name_owner_type
/// description:
class nc_name_owner_t
{
public:
	using name_t = dstr_t;
	using name_tc = const name_t;
	using owner_t = nc_name_owner_t;
	using owner_tc = const owner_t;
public:
	inline nc_name_owner_t() : m_name(NC_VOID_STR) { }
	inline nc_name_owner_t(cstr_t name) : nc_name_owner_t() { set_name(name); }
	inline nc_name_owner_t(name_tc& name) : nc_name_owner_t() { set_name(name); }
	inline nc_name_owner_t(owner_tc& copy) : nc_name_owner_t() { operator=(copy); }
	inline nc_name_owner_t(owner_t&& copy) : nc_name_owner_t() { operator=(copy); }
	virtual ~nc_name_owner_t() = default;
	/* getters */
	inline cstr_t get_name() const { return &m_name[0]; }
	/* setters */
	inline owner_t& set_name(cstr_t name)   { m_name = name; return *this; }
	inline owner_t& set_name(name_tc& name) { m_name = name; return *this; }
	/* vetters */
	inline v1bit_t has_name() const              { return m_name != ""; }
	inline v1bit_t has_name(cstr_t name) const   { return m_name == name; }
	inline v1bit_t has_name(name_tc& name) const { return m_name == name; }
	/* operators */
	inline owner_t operator=(owner_tc& copy) { return set_name(copy.get_name()); }
	inline owner_t operator=(owner_t&& copy) { return set_name(copy.get_name()); }
	/* command */
protected:
	name_t m_name;
};
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_NAME_HPP */