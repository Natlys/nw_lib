#ifndef NWLIB_INFO_H
#define NWLIB_INFO_H
#include "nwlib_core.hpp"
#include <io/nwlib_io_stm.h>
#include "nwlib_std_str.h"
namespace NWLIB
{
	/// abstract info struct
	class NW_API a_info
	{
	public:
		a_info();
		virtual ~a_info() = default;
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
	};
	stm_out& operator<<(stm_out& stm, const a_info& info);
	stm_in& operator>>(stm_in& stm, a_info& info);
}
namespace NWLIB
{
	struct img_bmp_info : a_info
	{
	public:
#pragma pack(push, 1) // add padding 16->14
		struct {
		public:
			v1u16 type_code = 0x4d;	// two encoded letters;usually "bm"
			v1u32 file_size = 54;		// size of the entire file in bytes
			v1u16 reserved1 = 0;		// it is reserved, (can be used by a programmer)
			v1u16 reserved2 = 0;		// so it is always zero
			v1u32 data_offset = 54;	// offset to the pixel data
		} file;	// file information
#pragma pack(pop)
#pragma pack(push, 1)
		struct {
		public:
			v1u32 header_size = 3;     // size of the header in bytes
			v1s32 width = 1;           // bitmap width in pixels
			v1s32 height = 1;          // bitmap height in pixels
			v1u16 nof_planes = 1;      // always 1
			v1u16 nof_pixel_bits = 24; // bpp
			v1u32 compression_type = 0;// 24bpp = 0; 32bpp = 3
			v1u32 image_size = 0;      // 0 for uncompressed
			v1s32 ppm_x = 0;           // don't care
			v1s32 ppm_y = 0;           // don't care
			v1u32 clrs_used = 0;       // indexed pallete count; zero for all available collors;
			v1u32 clrs_need = 0;       // required colors for bitmap
		} data;	// data description
#pragma pack(pop)
	public:
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	};
}
#endif	// NWLIB_INFO_H