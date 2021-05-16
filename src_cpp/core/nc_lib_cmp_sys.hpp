#ifndef NC_LIB_COMPONENT_SYSTEM_HPP
#	define NC_LIB_COMPONENT_SYSTEM_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "nc_lib_system.hpp"
#		include "nc_lib_cmp.hpp"
/// component_system
/// description:
class nc_cmp_sys : public nc_system_ttr<nc_cmp_sys, nc_cmp_t>
{
public:
public:
	// ctor_dtor //
	nc_cmp_sys();
	~nc_cmp_sys();
	// getters //
	// setters //
	// predicates //
	// commands //
	v1bit_t init();
	v1bit_t quit();
	v1bit_t work();
private:
};
#	endif	// NC_API //
#endif	// NC_LIB_COMPONENT_SYSTEM_HPP //