#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#	if (defined NW_API)
#	include "../std/nw_std_cont.h"
namespace NW
{
	/// type_information static class
	class NW_API type_info
	{
	public:
		using info = type_info;
		using cinfo = const info;
		using tab = darray<type_info>;
		using ctab = const tab;
	private:
		type_info(cv1u tid = NW_NULL, cstr tname = NW_NULL, csize tsize = NW_NULL, csize talign = NW_NULL) :
			id(tid),
			name(tname),
			size(tsize),
			align(talign)
		{
			get_tab_static().push_back(*this);
		}
	public:
		cv1u id;
		dstr name;
		csize size;
		csize align;
	public:
#		define NW_INFO_TYPE_DEF(tid, tname) (tid, #tname, sizeof(tname), alignof(tname));
		// --getters
		template <typename tname>
		static inline cinfo& get()         { static type_info inf NW_INFO_TYPE_DEF(get_id_static()++, tname); return inf; }
		static inline cinfo& get(cv1u tid) { return get_tab_static()[tid]; }
		static inline cv1u& get_id()       { return get_id_static(); }
		template <typename tname>
		static inline cv1u get_id()        { return get<tname>().id; }
		// --predicates
		static inline cv1b is_valid(cv1u tid) { return tid < get_tab_static().size(); }
		template<typename tname>
		static inline cv1b is_valid()         { return has_info(get_id<tname>()); }
		// operaotrs
	private:
		static inline v1u& get_id_static()  { static v1u s_curr_id = NW_NULL; return s_curr_id; }
		static inline tab& get_tab_static() { static tab s_table; return s_table; }
#		undef NW_INFO_TYPE_DEF
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
		static inline cv1u get_type_static()          { return type_info::get_id<type>(); }
		virtual inline cv1u get_type() const override { return type_info::get_id<type>(); }
	};
}
#	endif	// NW_API
#endif	// NW_INFO_TYPE_H