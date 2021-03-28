#ifndef NWLIB_STD_TYPE_H
#define NWLIB_STD_TYPE_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "nwlib_std_str.h"
#include "nwlib_std_val.h"
namespace NWLIB
{
	/// value_types enumeration
	enum value_types : v1u {
		VTYPE_DEFAULT = 0,
		// boolean 8 bit
		VTYPE_V1_BIT, VTYPE_V2_BIT, VTYPE_V3_BIT, VTYPE_V4_BIT,
		// integer 8 bit
		VTYPE_V1_S8, VTYPE_V2_S8, VTYPE_V3_S8, VTYPE_V4_S8,
		VTYPE_V1_U8, VTYPE_V2_U8, VTYPE_V3_U8, VTYPE_V4_U8,
		// integer 16 bit
		VTYPE_V1_S16, VTYPE_V2_S16, VTYPE_V3_S16, VTYPE_V4_S16,
		VTYPE_V1_U16, VTYPE_V2_U16, VTYPE_V3_U16, VTYPE_V4_U16,
		// integer 32 bit
		VTYPE_V1_S32, VTYPE_V2_S32, VTYPE_V3_S32, VTYPE_V4_S32,
		VTYPE_V1_U32, VTYPE_V2_U32, VTYPE_V3_U32, VTYPE_V4_U32,
		// integer 64 bit
		VTYPE_V1_S64, VTYPE_V2_S64, VTYPE_V3_S64, VTYPE_V4_S64,
		VTYPE_V1_U64, VTYPE_V2_U64, VTYPE_V3_U64, VTYPE_V4_U64,
		// float 32 bit
		VTYPE_V1_F32, VTYPE_V2_F32, VTYPE_V3_F32, VTYPE_V4_F32,
		// float 64 bit
		VTYPE_V1_F64, VTYPE_V2_F64, VTYPE_V3_F64, VTYPE_V4_F64,
	};
	/// value_type_info struct
	struct NW_API vtype_info
	{
		using vtype = value_types;
		using cvtype = const vtype;
	public:
		vtype_info(v1b is_valid_type, cstr name_of_type, value_types type_enum, size tsize) :
			is_valid(is_valid_type),
			type_name(name_of_type),
			type_enum(type_enum),
			type_size(tsize)
		{
		}
	public:
		cv1b is_valid;
		csstr type_name;
		cvtype type_enum;
		csize type_size;
	};
	/// typed native_type_info class
	template<typename type>
	struct NW_API t_vtype_info : public vtype_info
	{
		t_vtype_info() : vtype_info(false, "void", VTYPE_DEFAULT, 0u) { }
	};
	/// enumerated value_type_info
	template<value_types enum_type>
	struct NW_API e_vtype_info
	{
		e_vtype_info() { }
	};
	/// value_type_info definition macro
#define NW_DEF_VTYPE_INFO(tname, tenum)  \
	template<>                          \
	struct NW_API t_vtype_info<tname> : \
        public vtype_info {             \
			t_vtype_info() :            \
			vtype_info(                 \
				true,                   \
				NW_STR_TXT(tname),      \
				tenum,                  \
				sizeof(tname)) { } };   \
	template<>                          \
	struct NW_API e_vtype_info<tenum> : \
		public t_vtype_info<tname> { };
	// definitions
	NW_DEF_VTYPE_INFO(void*, VTYPE_DEFAULT)
		// boolean 8 bit
		NW_DEF_VTYPE_INFO(v1b, VTYPE_V1_BIT)
		NW_DEF_VTYPE_INFO(v2b, VTYPE_V2_BIT)
		NW_DEF_VTYPE_INFO(v3b, VTYPE_V3_BIT)
		NW_DEF_VTYPE_INFO(v4b, VTYPE_V4_BIT)
		// signed integer 8 bit
		NW_DEF_VTYPE_INFO(v1s8, VTYPE_V1_S8)
		NW_DEF_VTYPE_INFO(v2s8, VTYPE_V2_S8)
		NW_DEF_VTYPE_INFO(v3s8, VTYPE_V3_S8)
		NW_DEF_VTYPE_INFO(v4s8, VTYPE_V4_S8)
		// unsigned integer 8 bit
		NW_DEF_VTYPE_INFO(v1u8, VTYPE_V1_U8)
		NW_DEF_VTYPE_INFO(v2u8, VTYPE_V2_U8)
		NW_DEF_VTYPE_INFO(v3u8, VTYPE_V3_U8)
		NW_DEF_VTYPE_INFO(v4u8, VTYPE_V4_U8)
		// signed integer 16 bit
		NW_DEF_VTYPE_INFO(v1s16, VTYPE_V1_S16)
		NW_DEF_VTYPE_INFO(v2s16, VTYPE_V2_S16)
		NW_DEF_VTYPE_INFO(v3s16, VTYPE_V3_S16)
		NW_DEF_VTYPE_INFO(v4s16, VTYPE_V4_S16)
		// unsigned integer 16 bit
		NW_DEF_VTYPE_INFO(v1u16, VTYPE_V1_U16)
		NW_DEF_VTYPE_INFO(v2u16, VTYPE_V2_U16)
		NW_DEF_VTYPE_INFO(v3u16, VTYPE_V3_U16)
		NW_DEF_VTYPE_INFO(v4u16, VTYPE_V4_U16)
		// signed integer 32 bit
		NW_DEF_VTYPE_INFO(v1s32, VTYPE_V1_S32)
		NW_DEF_VTYPE_INFO(v2s32, VTYPE_V2_S32)
		NW_DEF_VTYPE_INFO(v3s32, VTYPE_V3_S32)
		NW_DEF_VTYPE_INFO(v4s32, VTYPE_V4_S32)
		// unsigned integer 32 bit
		NW_DEF_VTYPE_INFO(v1u32, VTYPE_V1_U32)
		NW_DEF_VTYPE_INFO(v2u32, VTYPE_V2_U32)
		NW_DEF_VTYPE_INFO(v3u32, VTYPE_V3_U32)
		NW_DEF_VTYPE_INFO(v4u32, VTYPE_V4_U32)
		// signed integer 64 bit
		NW_DEF_VTYPE_INFO(v1s64, VTYPE_V1_S64)
		NW_DEF_VTYPE_INFO(v2s64, VTYPE_V2_S64)
		NW_DEF_VTYPE_INFO(v3s64, VTYPE_V3_S64)
		NW_DEF_VTYPE_INFO(v4s64, VTYPE_V4_S64)
		// unsigned integer 64 bit
		NW_DEF_VTYPE_INFO(v1u64, VTYPE_V1_U64)
		NW_DEF_VTYPE_INFO(v2u64, VTYPE_V2_U64)
		NW_DEF_VTYPE_INFO(v3u64, VTYPE_V3_U64)
		NW_DEF_VTYPE_INFO(v4u64, VTYPE_V4_U64)
		// float 32 bit
		NW_DEF_VTYPE_INFO(v1f32, VTYPE_V1_F32)
		NW_DEF_VTYPE_INFO(v2f32, VTYPE_V2_F32)
		NW_DEF_VTYPE_INFO(v3f32, VTYPE_V3_F32)
		NW_DEF_VTYPE_INFO(v4f32, VTYPE_V4_F32)
		// float 64 bit
		NW_DEF_VTYPE_INFO(v1f64, VTYPE_V1_F64)
		NW_DEF_VTYPE_INFO(v2f64, VTYPE_V2_F64)
		NW_DEF_VTYPE_INFO(v3f64, VTYPE_V3_F64)
		NW_DEF_VTYPE_INFO(v4f64, VTYPE_V4_F64)
}
namespace NWLIB
{
	/// type_indexator static class
	class NW_API type_indexator
	{
	public:
		using vtype = value_types;
		using vinfo = vtype_info;
		using cvinfo = const vinfo;
		template<typename tname>
		using t_vinfo = t_vtype_info<tname>;
		template<vtype tenum>
		using e_vinfo = e_vtype_info<tenum>;
	public:
		template <typename t>
		static inline cv1u get_id()       { static const v1u s_type_id{ get_id()++ }; return s_type_id; }
#	define NW_GET_TYPE_ID(type_name)      (type_indexator::get_id<type_name>())
		template<typename t>
		static inline cvinfo& get_vinfo() { static const t_vinfo<t> inf; return inf; }
		template<value_types e>
		static inline cvinfo& get_vinfo() { static const e_vinfo<e> inf; return inf; }
		static inline cvinfo& get_vinfo(vtype type) {
			switch (type) {
				// boolean 
			case VTYPE_V1_BIT: return get_vinfo(VTYPE_V1_BIT);
			case VTYPE_V2_BIT: return get_vinfo(VTYPE_V2_BIT);
			case VTYPE_V3_BIT: return get_vinfo(VTYPE_V3_BIT);
			case VTYPE_V4_BIT: return get_vinfo(VTYPE_V4_BIT);
				// signed integer 8 bit
			case VTYPE_V1_S8: return get_vinfo<VTYPE_V1_S8>();
			case VTYPE_V2_S8: return get_vinfo<VTYPE_V2_S8>();
			case VTYPE_V3_S8: return get_vinfo<VTYPE_V3_S8>();
			case VTYPE_V4_S8: return get_vinfo<VTYPE_V4_S8>();
				// unsigned integer 8 bit
			case VTYPE_V1_U8: return get_vinfo<VTYPE_V1_U8>();
			case VTYPE_V2_U8: return get_vinfo<VTYPE_V2_U8>();
			case VTYPE_V3_U8: return get_vinfo<VTYPE_V3_U8>();
			case VTYPE_V4_U8: return get_vinfo<VTYPE_V4_U8>();
				// signed integer 16 bit
			case VTYPE_V1_S16: return get_vinfo<VTYPE_V1_S16>();
			case VTYPE_V2_S16: return get_vinfo<VTYPE_V2_S16>();
			case VTYPE_V3_S16: return get_vinfo<VTYPE_V3_S16>();
			case VTYPE_V4_S16: return get_vinfo<VTYPE_V4_S16>();
				// unsigned integer 16 bit
			case VTYPE_V1_U16: return get_vinfo<VTYPE_V1_U16>();
			case VTYPE_V2_U16: return get_vinfo<VTYPE_V2_U16>();
			case VTYPE_V3_U16: return get_vinfo<VTYPE_V3_U16>();
			case VTYPE_V4_U16: return get_vinfo<VTYPE_V4_U16>();
				// signed integer 32 bit
			case VTYPE_V1_S32: return get_vinfo<VTYPE_V1_S32>();
			case VTYPE_V2_S32: return get_vinfo<VTYPE_V2_S32>();
			case VTYPE_V3_S32: return get_vinfo<VTYPE_V3_S32>();
			case VTYPE_V4_S32: return get_vinfo<VTYPE_V4_S32>();
				// unsigned integer 32 bit
			case VTYPE_V1_U32: return get_vinfo<VTYPE_V1_U32>();
			case VTYPE_V2_U32: return get_vinfo<VTYPE_V2_U32>();
			case VTYPE_V3_U32: return get_vinfo<VTYPE_V3_U32>();
			case VTYPE_V4_U32: return get_vinfo<VTYPE_V4_U32>();
				// signed integer 64 bit
			case VTYPE_V1_S64: return get_vinfo<VTYPE_V1_S64>();
			case VTYPE_V2_S64: return get_vinfo<VTYPE_V2_S64>();
			case VTYPE_V3_S64: return get_vinfo<VTYPE_V3_S64>();
			case VTYPE_V4_S64: return get_vinfo<VTYPE_V4_S64>();
				// unsigned integer 64 bit
			case VTYPE_V1_U64: return get_vinfo<VTYPE_V1_U64>();
			case VTYPE_V2_U64: return get_vinfo<VTYPE_V2_U64>();
			case VTYPE_V3_U64: return get_vinfo<VTYPE_V3_U64>();
			case VTYPE_V4_U64: return get_vinfo<VTYPE_V4_U64>();
				// float 32 bit
			case VTYPE_V1_F32: return get_vinfo<VTYPE_V1_F32>();
			case VTYPE_V2_F32: return get_vinfo<VTYPE_V2_F32>();
			case VTYPE_V3_F32: return get_vinfo<VTYPE_V3_F32>();
			case VTYPE_V4_F32: return get_vinfo<VTYPE_V4_F32>();
				// float 64 bit
			case VTYPE_V1_F64: return get_vinfo<VTYPE_V1_F64>();
			case VTYPE_V2_F64: return get_vinfo<VTYPE_V2_F64>();
			case VTYPE_V3_F64: return get_vinfo<VTYPE_V3_F64>();
			case VTYPE_V4_F64: return get_vinfo<VTYPE_V4_F64>();
			default: break;
			}
			return get_vinfo<VTYPE_DEFAULT>();
		}
		// static macro getters
#	define NW_GET_VTYPE_INFO_S(index)  (type_indexator::get_vinfo<index>())
#	define NW_GET_VTYPE_ENUM_S(index)  (type_indexator::get_vinfo<index>().type_enum)
#	define NW_GET_VTYPE_SIZE_S(index)  (type_indexator::get_vinfo<index>().type_size)
		// dynamic macro getters
#	define NW_GET_VTYPE_INFO_D(index)  (type_indexator::get_vinfo(index))
#	define NW_GET_VTYPE_ENUM_D(index)  (type_indexator::get_vinfo(index).type_enum)
#	define NW_GET_VTYPE_SIZE_D(index)  (type_indexator::get_vinfo(index).type_size)
	private:
		static v1u& get_id()         { static v1u s_curr_id; return s_curr_id; }
	};
}
namespace NWLIB
{
	/// abstract type_owner class
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
		static inline cv1u get_type_static()          { return type_indexator::get_id<type>(); }
		virtual inline cv1u get_type() const override { return type_indexator::get_id<type>(); }
	};
}
#endif	// NW_API
#endif	// NWLIB_STD_TYPE_H