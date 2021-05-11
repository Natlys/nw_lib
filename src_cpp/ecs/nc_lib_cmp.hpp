#ifndef NC_LIB_COMPONENT_HPP
#	define NC_LIB_COMPONENT_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "../../nc_mem/src_cpp/core/nc_mem_sys.hpp"
#		include "../std/nc_lib_type_indx.hpp"
// types //
/// component_type
/// description:
class NC_API nc_cmp_t : public nc_type_indx_owner_t
{
public:
public:
	// ctor_dtor //
	constexpr inline nc_cmp_t() : nc_type_indx_owner_t() { }
	virtual inline ~nc_cmp_t() { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
};
/// component_type_template
/// description:
template<class tcmp>
class NC_API nc_cmp_tt : public nc_type_indx_owner_tt<tcmp, nc_cmp_t>
{
public:
public:
	// ctor_dtor //
	constexpr inline nc_cmp_tt() : nc_type_indx_owner_tt() { }
	virtual inline ~nc_cmp_tt() { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_ECS_COMPONENT_HPP //