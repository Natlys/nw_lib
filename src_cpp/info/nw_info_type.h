#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#	if (defined NW_API)
#	include "../std/nw_std_cont.h"
#	include "../io/nw_io_cmp.h"
namespace NW
{
	/// type_information static class
	class NW_API type_info : public a_io_cmp
	{
	public:
		using info = type_info;
		using cinfo = const info;
		using tab = darray<type_info>;
		using ctab = const tab;
	private:
		type_info(cv1u tid = NW_NULL, cstr tname = NW_NULL, csize tsize = NW_NULL, csize talign = NW_NULL);
	public:
		cv1u id;
		cstr name;
		csize size;
		csize align;
	public:
		// --getters
		template <typename tname>
		static cinfo& get()                { static info s_inf (get_id_static()++, get_name<tname>(), sizeof(tname), alignof(tname)); return s_inf; }
		static inline cinfo& get(cv1u tid) { return get_tab_static()[tid]; }
		static inline cv1u& get_id()       { return get_id_static(); }
		template <typename tname>
		static inline cv1u get_id()        { return get<tname>().id; }
		template<typename tname>
		static inline cstr get_name() {
#		define NW_NAME_FRONT "const char *__cdecl" NW_NAMESPACE_STR "::type_info::get_name<"
#		define NW_NAME_BACK ">(void)"
#		define NW_NAME_LENGTH sizeof(__FUNCSIG__) - sizeof(NW_NAME_FRONT) - sizeof(NW_NAME_BACK)
			static schar name[NW_NAME_LENGTH] { NW_NULL };
			memcpy(&name[0], &__FUNCSIG__[sizeof(NW_NAME_FRONT)], NW_NAME_LENGTH);
#		undef NW_NAME_FRONT
#		undef NW_NAME_BACK
#		undef NW_NAME_LENGTH
			return name;
		}
		// --predicates
		static inline cv1b is_valid(cv1u tid) { return tid < get_tab_static().size(); }
		template<typename tname>
		static inline cv1b is_valid()         { return is_valid(get_id<tname>()); }
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override { return stm; }
	private:
		static inline v1u& get_id_static()  { static v1u s_curr_id = NW_NULL; return s_curr_id; }
		static inline tab& get_tab_static() { static tab s_table; return s_table; }
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