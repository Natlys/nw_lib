#ifndef NW_INFO_IMAGE_H
#define NW_INFO_IMAGE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../iop/nw_iop_stm.h"
#	include "../iop/nw_iop_cmp.h"
#	include "../std/nw_std_array.h"
#	include "../mem/nw_mem_elem.h"
namespace NW
{
	struct img_pal_info
	{
	public:
		t_darray<byte_t> idx_buf;
		t_darray<byte_t> pxl_buf;
	};
	struct img_bmp_info : public a_iop_cmp
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
		} file_info; // file information
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
		} data_info; // data description
#pragma pack(pop)
		img_pal_info palette;
	public:
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
	};
}
#endif	// NW_API
#endif	// NW_INFO_IMAGE_H