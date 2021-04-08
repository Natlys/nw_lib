#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#	if (defined NW_API)
namespace NW
{
	/// type_indexator static class
	class NW_API type_indexator
	{
	public:
		template <typename tn>
		static inline cv1u get_id()            { static cv1u s_type_id{ get_id()++ }; return s_type_id; }
	private:
		static inline v1u& get_id()   { static v1u s_curr_id; return s_curr_id; }
	};
}
namespace NW
{
	/// type_owner abstract class
	class NW_API a_type_owner
	{
	protected:
		a_type_owner() = default;
	public:
		virtual ~a_type_owner() = default;
		// --getters
		virtual inline cv1u get_type() const = 0;
		// --predicates
		inline cv1b check_type(v1u type_id) const     { return get_type() == type_id; }
		template<typename ct> cv1b check_type() const { return check_type(ct::get_type_static()); }
		template<typename ct> ct* check_cast()        { return check_type<ct>() ? static_cast<ct*>(this) : nullptr; }
	};
	/// type_owner template class
	template<typename type, class atype>
	class NW_API t_type_owner : public atype
	{
	protected:
		template<typename ... args>
		t_type_owner(args ... arguments) : atype(std::forward<args>(arguments)...) { }
	public:
		virtual ~t_type_owner() = default;
		// --getters
		static inline cv1u get_type_static()          { return type_indexator::get_id<type>(); }
		virtual inline cv1u get_type() const override { return type_indexator::get_id<type>(); }
	};
}
#	endif	// NW_API
#endif	// NW_INFO_TYPE_H