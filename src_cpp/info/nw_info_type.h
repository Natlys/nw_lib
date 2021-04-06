#ifndef NW_INFO_TYPE_H
#define NW_INFO_TYPE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)

#	ifndef NW_APPLY
#	if(NW_FALSE)
#		define NW_TYPE_APPLY_ALL   \
\
		NW_APPLY(v1b,   NW_V1_BIT) \
		NW_APPLY(v2b,   NW_V2_BIT) \
		NW_APPLY(v3b,   NW_V3_BIT) \
		NW_APPLY(v4b,   NW_V4_BIT) \
\
		NW_APPLY(v1s8,  NW_V1_S08) \
		NW_APPLY(v2s8,  NW_V2_S08) \
		NW_APPLY(v3s8,  NW_V3_S08) \
		NW_APPLY(v4s8,  NW_V4_S08) \
\
		NW_APPLY(v1u8,  NW_V1_U08) \
		NW_APPLY(v2u8,  NW_V2_U08) \
		NW_APPLY(v3u8,  NW_V3_U08) \
		NW_APPLY(v4u8,  NW_V4_U08) \
\
		NW_APPLY(v1s16, NW_V1_S16) \
		NW_APPLY(v2s16, NW_V2_S16) \
		NW_APPLY(v3s16, NW_V3_S16) \
		NW_APPLY(v4s16, NW_V4_S16) \
\
		NW_APPLY(v1u16, NW_V1_U16) \
		NW_APPLY(v2u16, NW_V2_U16) \
		NW_APPLY(v3u16, NW_V3_U16) \
		NW_APPLY(v4u16, NW_V4_U16) \
\
		NW_APPLY(v1s32, NW_V1_S32) \
		NW_APPLY(v2s32, NW_V2_S32) \
		NW_APPLY(v3s32, NW_V3_S32) \
		NW_APPLY(v4s32, NW_V4_S32) \
\
		NW_APPLY(v1u32, NW_V1_U32) \
		NW_APPLY(v2u32, NW_V2_U32) \
		NW_APPLY(v3u32, NW_V3_U32) \
		NW_APPLY(v4u32, NW_V4_U32) \
\
		NW_APPLY(v1s64, NW_V1_S64) \
		NW_APPLY(v2s64, NW_V2_S64) \
		NW_APPLY(v3s64, NW_V3_S64) \
		NW_APPLY(v4s64, NW_V4_S64) \
\
		NW_APPLY(v1u64, NW_V1_U64) \
		NW_APPLY(v2u64, NW_V2_U64) \
		NW_APPLY(v3u64, NW_V3_U64) \
		NW_APPLY(v4u64, NW_V4_U64) \
\
		NW_APPLY(v1f32, NW_V1_F32) \
		NW_APPLY(v2f32, NW_V2_F32) \
		NW_APPLY(v3f32, NW_V3_F32) \
		NW_APPLY(v4f32, NW_V4_F32) \
\
		NW_APPLY(v1f64, NW_V1_F64) \
		NW_APPLY(v2f64, NW_V2_F64) \
		NW_APPLY(v3f64, NW_V3_F64) \
		NW_APPLY(v4f64, NW_V4_F64) \
		NW_APPLY(ptr,   NW_VARRAY) \
		NW_APPLY(ptr*,  NW_STRUCT)
\
// it is done
#	elif(NW_TRUE)
#		define NW_TYPE_APPLY_ALL   \
\
		NW_APPLY(v1s32, NW_V1_S32) \
		NW_APPLY(v2s32, NW_V2_S32) \
		NW_APPLY(v3s32, NW_V3_S32) \
		NW_APPLY(v4s32, NW_V4_S32) \
\
		NW_APPLY(v1u32, NW_V1_U32) \
		NW_APPLY(v2u32, NW_V2_U32) \
		NW_APPLY(v3u32, NW_V3_U32) \
		NW_APPLY(v4u32, NW_V4_U32) \
\
		NW_APPLY(v1f32, NW_V1_F32) \
		NW_APPLY(v2f32, NW_V2_F32) \
		NW_APPLY(v3f32, NW_V3_F32) \
		NW_APPLY(v4f32, NW_V4_F32) \
\
// it is done
#	endif
#		define NW_APPLY(tname, tenum) NW_DEFAULT
#		undef NW_APPLY
#	else
#		error "NW_APPLY must not be defined here"
#	endif	// NW_APPLY

namespace NW
{
	struct info_type
	{
	public:
		info_type(cstr tname) :
			type_name(tname)
		{
		}
	public:
		cstr type_name;
		csize val_size;
		csize val_count;
		cenum_id type_cpp;
		cenum_id type_gfx;
	};
	/// info_type enumeration struct
	template<cenum_id tenum> struct info_type_e;
	/// info_type unsigned 32 bit
	template<> struct info_type_e<NW_V1_S32>
	{
		using type = v1s32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v1s32);
		static constexpr csize val_count    = 1u;
		static constexpr cstr type_name     = "v1s32";
		static constexpr cenum_id type_enum = NW_V1_S32;
		static constexpr cenum_id type_gapi = 0x1404; // GL_INT
	};
	template<> struct info_type_e<NW_V2_S32>
	{
		using type = v2s32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v2s32);
		static constexpr csize val_count    = 2u;
		static constexpr cstr type_name     = "v2s32";
		static constexpr cenum_id type_enum = NW_V2_S32;
		static constexpr cenum_id type_gapi = 0x1404; // GL_INT
	};
	template<> struct info_type_e<NW_V3_S32>
	{
		using type                          = v3s32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v3s32);
		static constexpr csize val_count    = 3u;
		static constexpr cstr type_name     = "v3s32";
		static constexpr cenum_id type_enum = NW_V3_S32;
		static constexpr cenum_id type_gapi = 0x1404; // GL_INT
	};
	template<> struct info_type_e<NW_V4_S32>
	{
		using type                          = v4s32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v4s32);
		static constexpr csize val_count    = 4u;
		static constexpr cstr type_name     = "v4s32";
		static constexpr cenum_id type_enum = NW_V4_S32;
		static constexpr cenum_id type_gapi = 0x1404; // GL_INT
	};
	/// info_type unsigned 32 bit
	template<> struct info_type_e<NW_V1_U32>
	{
		using type                          = v1u32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v1u32);
		static constexpr csize val_count    = 1u;
		static constexpr cstr type_name     = "v1u32";
		static constexpr cenum_id type_enum = NW_V1_U32;
		static constexpr cenum_id type_gapi = 0x1405; // GL_UNSIGNED_INT
	};
	template<> struct info_type_e<NW_V2_U32>
	{
		using type                          = v2u32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v2u32);
		static constexpr csize val_count    = 2u;
		static constexpr cstr type_name     = "v2u32";
		static constexpr cenum_id type_enum = NW_V2_U32;
		static constexpr cenum_id type_gapi = 0x1405; // GL_UNSIGNED_INT
	};
	template<> struct info_type_e<NW_V3_U32>
	{
		using type                          = v3u32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v3u32);
		static constexpr csize val_count    = 3u;
		static constexpr cstr type_name     = "v3u32";
		static constexpr cenum_id type_enum = NW_V3_U32;
		static constexpr cenum_id type_gapi = 0x1405; // GL_UNSIGNED_INT
	};
	template<> struct info_type_e<NW_V4_U32>
	{
		using type                          = v4u32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v4u32);
		static constexpr csize val_count    = 4u;
		static constexpr cstr type_name     = "v4u32";
		static constexpr cenum_id type_enum = NW_V4_U32;
		static constexpr cenum_id type_gapi = 0x1405; // GL_UNSIGNED_INT
	};
	/// info_type float 32 bit
	template<> struct info_type_e<NW_V1_F32>
	{
		using type                          = v1f32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v1f32);
		static constexpr csize val_count    = 1u;
		static constexpr cstr type_name     = "v1f32";
		static constexpr cenum_id type_enum = NW_V1_F32;
		static constexpr cenum_id type_gapi = 0x1406; // GL_FLOAT
	};
	template<> struct info_type_e<NW_V2_F32>
	{
		using type                          = v2f32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v2f32);
		static constexpr csize val_count    = 2u;
		static constexpr cstr type_name     = "v2f32";
		static constexpr cenum_id type_enum = NW_V2_F32;
		static constexpr cenum_id type_gapi = 0x1406; // GL_FLOAT
	};
	template<> struct info_type_e<NW_V3_F32>
	{
		using type                          = v3f32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v3f32);
		static constexpr csize val_count    = 3u;
		static constexpr cstr type_name     = "v3f32";
		static constexpr cenum_id type_enum = NW_V3_F32;
		static constexpr cenum_id type_gapi = 0x1406; // GL_FLOAT
	};
	template<> struct info_type_e<NW_V4_F32>
	{
		using type                          = v4f32;
		static constexpr cv1b is_valid      = NW_TRUE;
		static constexpr csize val_size     = sizeof(v4f32);
		static constexpr csize val_count    = 4u;
		static constexpr cstr type_name     = "v4f32";
		static constexpr cenum_id type_enum = NW_V4_F32;
		static constexpr cenum_id type_gapi = 0x1406; // GL_FLOAT
	};
#ifndef NW_APPLY
#	define NW_APPLY(tname, tenum)       \
		static_assert(                  \
		info_type_e<tenum>::is_valid,   \
		"undefined enumeration types" );
	NW_TYPE_APPLY_ALL
#	undef NW_APPLY
#else
#	error "NW_APPLY macro has to be free here"
#endif	// NW_APPLY
	/// type_info typed struct
	template<typename tname> struct info_type_t;
#ifndef NW_APPLY
#	define NW_APPLY(tname, tenum)         \
	template<> struct info_type_t<tname>  \
		: public info_type_e<tenum> { };
	NW_TYPE_APPLY_ALL
#	undef NW_APPLY
#else
#	error "NW_APPLY macro has to be free here"
#endif	// NW_APPLY
}
namespace NW
{
	/// type_indexator static class
	class NW_API type_indexator
	{
	public:
		template<cenum_id te>
		using infoe = info_type_e<te>;
		template<cenum_id te>
		using cinfoe = const infoe<te>;
		template<typename tn>
		using infot = info_type_t<tn>;
		template<typename tn>
		using cinfot = const infot<tn>;
	public:
		template <typename tn>
		static inline cv1u get_id()            { static cv1u s_type_id{ get_id()++ }; return s_type_id; }
		template<typename tn>
		static inline cinfot<tn>& get_info()   { static cinfot<tn> inf; return inf; }
		template<cenum_id te>
		static inline cinfoe<te>& get_info()   { static cinfoe<te> inf; return inf; }
		template <typename tn>
		static inline csize get_info_size()    { return get_info<tn>().val_size; }
		template <typename tn>
		static inline csize get_info_count()   { return get_info<tn>().val_count; }
		template <typename tn>
		static inline cstr get_info_name()     { return get_info<tn>().type_name; }
		template <typename tn>
		static inline cenum_id get_info_enum() { return get_info<tn>().type_enum; }
		template <typename tn>
		static inline cenum_id get_info_gapi() { return get_info<tn>().type_gapi; }
#	ifndef NW_APPLY
#		define NW_APPLY(tname, tenum) case tenum: return get_info<tenum>().val_size;
		static inline csize get_info_size(cenum_id type) {
			switch (type) { NW_TYPE_APPLY_ALL }
			return NW_DEFAULT_VAL;
		}
#		undef NW_APPLY
#		define NW_APPLY(tname, tenum) case tenum: return get_info<tenum>().val_count;
		static inline csize get_info_count(cenum_id type) {
			switch (type) { NW_TYPE_APPLY_ALL }
			return NW_DEFAULT_VAL;
	}
#		define NW_APPLY(tname, tenum) case tenum: return get_info<tenum>().type_name;
		static inline cstr get_info_name(cenum_id type) {
			switch (type) { NW_TYPE_APPLY_ALL }
			return NW_DEFAULT_STR;
		}
#		undef NW_APPLY
#		define NW_APPLY(tname, tenum) case tenum: return get_info<tenum>().type_enum;
		static inline cenum_id get_info_enum(cenum_id type) {
			switch (type) { NW_TYPE_APPLY_ALL }
			return NW_DEFAULT_VAL;
		}
#		undef NW_APPLY
#		define NW_APPLY(tname, tenum) case tenum: return get_info<tenum>().type_gapi;
		static inline cenum_id get_info_gapi(cenum_id type) {
			switch (type) { NW_TYPE_APPLY_ALL }
			return NW_DEFAULT_VAL;
	}
#		undef NW_APPLY
#	else
#		error "NW_APPLY macro must not be defined here"
#	endif	// NW_APPLY
#	define NW_GET_TYPE_ID(type_name)  ( type_indexator::get_id<type_name>() )
		// static macro getters
#	define NW_GET_TYPE_NAME_S(index)  ( type_indexator::get_info_name<index>()  )
#	define NW_GET_TYPE_SIZE_S(index)  ( type_indexator::get_info_size<index>()  )
#	define NW_GET_TYPE_COUNT_S(index) ( type_indexator::get_info_count<index>() )
#	define NW_GET_TYPE_ENUM_S(index)  ( type_indexator::get_info_enum<index>()  )
#	define NW_GET_TYPE_GAPI_S(index)  ( type_indexator::get_info_gapi<index>()  )
		// dynamic macro getters
#	define NW_GET_TYPE_NAME_D(index)  ( type_indexator::get_info_name(index)  )
#	define NW_GET_TYPE_SIZE_D(index)  ( type_indexator::get_info_size(index)  )
#	define NW_GET_TYPE_COUNT_D(index) ( type_indexator::get_info_count(index) )
#	define NW_GET_TYPE_ENUM_D(index)  ( type_indexator::get_info_enum(index)  )
#	define NW_GET_TYPE_GAPI_D(index)  ( type_indexator::get_info_gapi(index)  )
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
#endif	// NW_API
#endif	// NW_INFO_TYPE_H