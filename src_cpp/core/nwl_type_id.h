#ifndef NWL_TYPE_ID_H
#define NWL_TYPE_ID_H
#include "nwl_type.h"
#include "nwl_id.h"
namespace NW
{
	/// abstract type_id class
	class NW_API a_type_id_owner : public a_type_owner, public a_id_owner
	{
	protected:
		a_type_id_owner() : a_type_owner(), a_id_owner() { }
	public:
		virtual ~a_type_id_owner() = default;
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
		virtual inline ui32 get_type() const override { return type_indexator::get_id<type>(); }
		virtual inline ui32 get_id() const override { return m_id; }
	};
}
#endif	// NWL_TYPE_ID_H