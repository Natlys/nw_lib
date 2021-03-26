#ifndef NWL_TYPE_H
#define NWL_TYPE_H
#include <nwl_core.hpp>
#include "nwl_const.h"
namespace NW
{
	class NW_API type_indexator
	{
	public:
		template <typename type>
		static const v1ui get_id() { static const v1ui s_type_id{ get_id()++ }; return s_type_id; }
	private:
		static v1ui& get_id()      { static v1ui s_curr_id; return s_curr_id; }
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
		virtual inline v1ui get_type() const = 0;
		// --predicates
		inline bit check_type(v1ui type_id) const		{ return get_type() == type_id; }
		template<typename ct> bit check_type() const	{ return check_type(ct::get_type_static()); }
	};
	/// templated type_owner class
	template<typename type, class atype>
	class NW_API t_type_owner : public atype
	{
	protected:
		template<typename ... args>
		t_type_owner(args ... arguments) : atype(std::forward<args>(arguments)...) { }
	public:
		virtual ~t_type_owner() = default;
		// --getters
		static inline v1ui get_type_static()			{ return type_indexator::get_id<type>(); }
		virtual inline v1ui get_type() const override	{ return type_indexator::get_id<type>(); }
	};
}
namespace NW
{
	/// templated native_type_info class
	template<typename type>
	struct NW_API t_ntp_info
	{
		static inline const bool is_valid = false;
		static inline const char* string_name = "void";
		static inline const native_types enum_type = NTP_DEFAULT;
		static inline const size size_in_bytes = 0u;
	};
	/// templated native_type_info_enumeration
	template<native_types enum_type>
	struct NW_API t_ntp_info_enum { };
#define NW_DEF_NATIVE_TYPE_INFO(type, enumeration) \
	template<> struct NW_API t_ntp_info<type> { \
		static inline const bool is_valid = true; \
		static inline const char* string_name = NW_STR_TXT(type); \
		static inline const native_types enum_type = enumeration; \
		static inline const size size_in_bytes = sizeof(type); \
	}; \
	template<> struct NW_API t_ntp_info_enum<enumeration> : public t_ntp_info<type> { };
	NW_DEF_NATIVE_TYPE_INFO(bit, NTP_BIT)
	NW_DEF_NATIVE_TYPE_INFO(v1si8, NTP_SINT8)
	NW_DEF_NATIVE_TYPE_INFO(v1ui8, NTP_UINT8)
	NW_DEF_NATIVE_TYPE_INFO(v1si16, NTP_SINT16)
	NW_DEF_NATIVE_TYPE_INFO(v1ui16, NTP_UINT16)
	NW_DEF_NATIVE_TYPE_INFO(v1si32, NTP_SINT32)
	NW_DEF_NATIVE_TYPE_INFO(v1ui32, NTP_UINT32)
	NW_DEF_NATIVE_TYPE_INFO(v1si64, NTP_SINT64)
	NW_DEF_NATIVE_TYPE_INFO(v1ui64, NTP_UINT64)
	NW_DEF_NATIVE_TYPE_INFO(v1f32, NTP_FLOAT32)
	NW_DEF_NATIVE_TYPE_INFO(v1f64, NTP_FLOAT64)
	NW_DEF_NATIVE_TYPE_INFO(a_type_owner, NTP_STRUCT)
}
#endif	// NWL_TYPE_H