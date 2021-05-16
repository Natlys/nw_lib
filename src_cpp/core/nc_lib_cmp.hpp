#ifndef NC_LIB_COMPONENT_HPP
#	define NC_LIB_COMPONENT_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "../../nc_mem/src_cpp/core/nc_mem_sys.hpp"
#		include "nc_lib_type.hpp"
#		include "nc_lib_indx.hpp"
// defines //
// types //
/// component_type
/// description:
class nc_cmp_t : public nc_type_owner_t, public nc_indx_owner_t
{
public:
public:
	// ctor_dtor //
	inline nc_cmp_t() = default;
	virtual ~nc_cmp_t() = default;
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
};
/// component_type_template
/// description:
template<class tcmp>
class nc_cmp_tt : public nc_type_owner_tt<tcmp, nc_cmp_t>, public nc_indx_owner_tt<tcmp>
{
public:
public:
	// ctor_dtor //
	inline nc_cmp_tt() = default;
	virtual ~nc_cmp_tt() = default;
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_ECS_COMPONENT_HPP //