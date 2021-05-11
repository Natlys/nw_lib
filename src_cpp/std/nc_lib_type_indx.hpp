#ifndef NC_LIB_TYPE_INDEX_HPP
#	define NC_LIB_TYPE_INDEX_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "nc_lib_type.hpp"
#		include "nc_lib_indx.hpp"
// types //
/// type_index_owner_type
class NC_API nc_type_indx_owner_t : public nc_nc_type_owner_t, public nc_nc_indx_owner_t
{
public:
public:
	// ctor_dtor //
	inline nc_type_indx_owner_t() : nc_nc_type_owner_t(), nc_nc_indx_owner_t() { }
	virtual ~nc_type_indx_owner_t() { }
	// getters //
	virtual inline indx_tc get_indx() const = 0;
	// setters //
	// predicates //
	// commands //
	// operators //
};
/// typed_type_index_owner_type
template<class tname, class tbase = nc_type_indx_owner_t>
class nc_type_indx_owner_tt : public nc_type_owner_t<tname, tbase>, public nc_indx_owner_t<tname> 
{
public:
	inline nc_type_indx_owner_tt() : nc_type_owner_t(), nc_indx_owner_t() { }
	virtual ~nc_type_indx_owner_tt() { }
	// getters //
	virtual inline indx_tc get_indx() const override { return m_indx; }
	// setters //
	// predicates //
	// commands //
	// operators //
};
#endif	// NC_API
#endif	// NC_CORE_TYPE_IDX_HPP