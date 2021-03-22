#ifndef NWL_DATA_SWITCH_H
#define NWL_DATA_SWITCH_H
#include <nwl_core.hpp>
namespace NW
{
	enum data_types : ui32 {
		DT_DEFAULT = 0,
		DT_BOOL = 1,
		DT_VEC2_BOOL, DT_VEC3_BOOL, DT_VEC4_BOOL,
		DT_MAT2_BOOL, DT_MAT3_BOOL, DT_MAT4_BOOL,
		DT_SINT8,
		DT_VEC2_SINT8, DT_VEC3_SINT8, DT_VEC4_SINT8,
		DT_MAT2_SINT8, DT_MAT3_SINT8, DT_MAT4_SINT8,
		DT_UINT8,
		DT_VEC2_UINT8, DT_VEC3_UINT8, DT_VEC4_UINT8,
		DT_MAT2_UINT8, DT_MAT3_UINT8, DT_MAT4_UINT8,
		DT_SINT16,
		DT_VEC2_SINT16, DT_VEC3_SINT16, DT_VEC4_SINT16,
		DT_MAT2_SINT16, DT_MAT3_SINT16, DT_MAT4_SINT16,
		DT_UINT16,
		DT_VEC2_UINT16, DT_VEC3_UINT16, DT_VEC4_UINT16,
		DT_MAT2_UINT16, DT_MAT3_UINT16, DT_MAT4_UINT16,
		DT_SINT32,
		DT_VEC2_SINT32, DT_VEC3_SINT32, DT_VEC4_SINT32,
		DT_MAT2_SINT32, DT_MAT3_SINT32, DT_MAT4_SINT32,
		DT_UINT32,
		DT_VEC2_UINT32, DT_VEC3_UINT32, DT_VEC4_UINT32,
		DT_MAT2_UINT32, DT_MAT3_UINT32, DT_MAT4_UINT32,
		DT_FLOAT32,
		DT_VEC2_FLOAT32, DT_VEC3_FLOAT32, DT_VEC4_FLOAT32,
		DT_MAT2_FLOAT32, DT_MAT3_FLOAT32, DT_MAT4_FLOAT32,
		DT_FLOAT64,
		DT_VEC2_FLOAT64, DT_VEC3_FLOAT64, DT_VEC4_FLOAT64,
		DT_MAT2_FLOAT64, DT_MAT3_FLOAT64, DT_MAT4_FLOAT64,
		DT_SNORM,
		DT_VEC2_SNORM, DT_VEC3_SNORM, DT_VEC4_SNORM,
		DT_MAT2_SNORM, DT_MAT3_SNORM, DT_MAT4_SNORM,
		DT_UNORM,
		DT_VEC2_UNORM, DT_VEC3_UNORM, DT_VEC4_UNORM,
		DT_MAT2_UNORM, DT_MAT3_UNORM, DT_MAT4_UNORM,
		DT_USER_DATA = 99
	};
	enum pixel_formats : ui32 {
		PXF_DEFAULT = 0,
		PXF_R8_SINT8,
		PXF_R8_UINT8,
		PXF_R16_SINT16, PXF_R8G8_SINT16,
		PXF_R16_UINT16, PXF_R8G8_UINT16,
		PXF_R32_SINT32, PXF_R16G16_SINT32, PXF_R8G8B8_SINT32, PXF_R8G8B8A8_SINT32,
		PXF_R32_UINT32, PXF_R16G16_UINT32, PXF_R8G8B8_UINT32, PXF_R8G8B8A8_UINT32,
		PXF_S8_SINT8, PXF_D32_SINT32,
		PXF_S8_UINT8, PXF_D32_UINT32,
		PXF_D24S8_SINT32,
		PXF_D24S8_UINT32,
	};
}
namespace NW
{
	NW_API si32 dt_get_prim_count(data_types data_type);
	NW_API size dt_get_size(data_types data_type, si32 count = 1);
	NW_API size dt_get_aligned_size(data_types data_type, si32 count = 1);

	NW_API pixel_formats pxf_get(ui8 nchannels);
	NW_API ui8 pxf_get(pixel_formats pixel_format);
}
namespace NW
{
	// ENUM CLASS file_type
	enum class file_type {
		none,
		not_found,
		regular,
		directory,
		symlink,

		block, // not used on Windows
		character, // not used in this implementation; theoretically some special files like CON
				   // might qualify, but querying for this is extremely expensive and unlikely
				   // to be useful in practice
		fifo, // not used on Windows (\\.\pipe named pipes don't behave exactly like POSIX fifos)
		socket, // not used on Windows
		unknown,
		junction // implementation-defined value indicating an NT junction
	};
	// ENUM CLASS file_permitionss
	enum class file_perms {
		none = 0,

		owner_read = 0400,
		owner_write = 0200,
		owner_exec = 0100,
		owner_all = 0700,

		group_read = 0040,
		group_write = 0020,
		group_exec = 0010,
		group_all = 0070,

		others_read = 0004,
		others_write = 0002,
		others_exec = 0001,
		others_all = 0007,

		all = 0777, // returned for all files without FILE_ATTRIBUTE_READONLY
		set_uid = 04000,
		set_gid = 02000,
		sticky_bit = 01000,
		mask = 07777,
		unknown = 0xFFFF,

		_All_write = owner_write | group_write | others_write,
		_File_attribute_readonly = all & ~_All_write // returned for files with FILE_ATTRIBUTE_READONLY
	};
	_BITMASK_OPS(file_perms)

	// ENUM CLASS copy_options
	enum class copy_options {
		none = static_cast<int>(__std_fs_copy_options::_None),

		_Existing_mask = static_cast<int>(__std_fs_copy_options::_Existing_mask),
		skip_existing = static_cast<int>(__std_fs_copy_options::_Skip_existing),
		overwrite_existing = static_cast<int>(__std_fs_copy_options::_Overwrite_existing),
		update_existing = static_cast<int>(__std_fs_copy_options::_Update_existing),

		recursive = 0x10,

		_Symlinks_mask = 0xF00,
		copy_symlinks = 0x100,
		skip_symlinks = 0x200,

		_Copy_form_mask = 0xF000,
		directories_only = 0x1000,
		create_symlinks = 0x2000,
		create_hard_links = 0x4000,

		_Unspecified_copy_prevention_tag = 0x10000 // to be removed by LWG-3057
	};
	_BITMASK_OPS(copy_options)
}
#endif	// NWL_DATA_SWITCH_H