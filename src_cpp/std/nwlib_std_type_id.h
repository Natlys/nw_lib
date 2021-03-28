#ifndef NWLIB_STD_TYPE_ID_H
#define NWLIB_STD_TYPE_ID_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "nwlib_std_type.h"
#include "nwlib_std_id.h"
namespace NWLIB
{
	/// abstract type_id class
	class NW_API a_type_id_owner : public a_type_owner, public a_id_owner
	{
	protected:
		a_type_id_owner() : a_type_owner(), a_id_owner() { }
	public:
		virtual ~a_type_id_owner() = default;
		// --getters
		virtual inline cv1u get_type() const override = 0;
		virtual inline cv1u get_id() const = 0;
	};
	/// templated type_id class
	template<class type, class atype = a_type_id_owner>
	class NW_API t_type_id_owner : public t_type_owner<type, atype>, public t_id_owner<type> 
	{
	protected:
		t_type_id_owner() : t_type_owner(), t_id_owner() { }
	public:
		virtual ~t_type_id_owner() = default;
		// --getters
		virtual inline cv1u get_type() const override { return type_indexator::get_id<type>(); }
		virtual inline cv1u get_id() const override { return m_id; }
	};
}
#endif	// NW_API
#endif	// NWLIB_STD_YPE_ID_H