#ifndef NC_LIB_ENTITY_SYSTEM_HPP
#	define NC_LIB_ENTITY_SYSTEM_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "../core/nc_lib_system_ref.hpp"
#		include "nc_lib_ent.hpp"
/// entity_system
/// description:
/// --manager for all entity_type instances
class NC_API nc_ent_sys : public ref_sys_tt<nc_ent_sys, nc_ent_t>
{
public:
public:
	nc_ent_sys();
	~nc_ent_sys();
	// commands //
	v1bit_t init() { NC_CHECK(ref_sys_t::init(), "failed init!", return NC_FALSE); return NC_TRUTH; }
	v1bit_t quit() { NC_CHECK(ref_sys_t::quit(), "failed quit!", return NC_FALSE); return NC_TRUTH; }
private:
};
#	endif	// NC_API //
#endif // NC_LIB_ENTITY_SYSTEM_HPP //