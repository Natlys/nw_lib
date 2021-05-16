#ifndef NC_LIB_ENTITY_SYSTEM_HPP
#	define NC_LIB_ENTITY_SYSTEM_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "nc_lib_system.hpp"
#		include "nc_lib_ent.hpp"
/// entity_system
/// description:
/// --manager for all entity_type instances
class nc_ent_sys : public nc_system_ttr<nc_ent_sys, nc_ent_t>
{
public:
public:
	nc_ent_sys();
	~nc_ent_sys();
	// commands //
	v1bit_t init();
	v1bit_t quit();
	v1bit_t work();
private:
};
#	endif	// NC_API //
#endif // NC_LIB_ENTITY_SYSTEM_HPP //