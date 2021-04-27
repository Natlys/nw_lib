#ifndef NW_CORE_TYPE_IDX_H
#define NW_CORE_TYPE_IDX_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_std_type.h"
#	include "nw_std_idx.h"
namespace NW
{
	/// abstract type_id class
	class NW_API a_type_idx_owner : public a_type_owner, public a_idx_owner
	{
	protected:
		a_type_idx_owner() : a_type_owner(), a_idx_owner() { }
	public:
		virtual ~a_type_idx_owner() = default;
		// --getters
		virtual inline cv1u get_idx() const = 0;
	};
	/// templated type_id class
	template<class type, class atype = a_type_idx_owner>
	class NW_API t_type_idx_owner : public t_type_owner<type, atype>, public t_idx_owner<type> 
	{
	protected:
		t_type_idx_owner() : t_type_owner(), t_idx_owner() { }
	public:
		virtual ~t_type_idx_owner() = default;
		// --getters
		virtual inline cv1u get_idx() const override { return m_idx; }
	};
}
#endif	// NW_API
#endif	// NW_CORE_TYPE_IDX_H