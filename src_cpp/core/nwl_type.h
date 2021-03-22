#ifndef NWL_TYPE_H
#define NWL_TYPE_H
#include <nwl_core.hpp>
#include <mem/mem_sys.h>
namespace NW
{
	class NW_API type_indexator
	{
	public:
		template <typename type>
		static const ui32 get_id() { static const ui32 s_type_id{ s_curr_id++ }; return s_type_id; }
		static const ui32 get_id() { return s_curr_id; }
	private:
		static ui32 s_curr_id;
	};
}
#define NW_TYPE_ID(type_name) (type_indexator::get_id<type_name>())
namespace NW
{
	/// abstract type_owner class
	class NW_API a_type_owner
	{
	protected:
		a_type_owner();
	public:
		virtual ~a_type_owner();
		// --getters
		virtual inline ui32 get_type() const = 0;
		// --predicates
		inline bit check_type(ui32 type_id) const		{ return get_type() == type_id; }
		template<typename ct> bit check_type() const	{ return check_type(ct::get_type_static()); }
	};
	/// templated type_owner class
	template<typename type, class atype>
	class NW_API t_type_owner : public atype
	{
	protected:
		template<typename ... args>
		t_type_owner(args ... arguments) :
			atype(std::forward<args>(arguments)...)
		{
		}
	public:
		virtual ~t_type_owner() = default;
		// --getters
		static inline ui32 get_type_static()			{ return type_indexator::get_id<type>(); }
		virtual inline ui32 get_type() const override	{ return type_indexator::get_id<type>(); }
	};
}
#endif	// NWL_TYPE_H