#ifndef NW_INFO_IMAGE_H
#define NW_INFO_IMAGE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../io/nw_io_stm.h"
#	include "../io/nw_io_cmp.h"
#	include "../std/nw_std_cont.h"
#	include "../mem/nw_mem_elem.h"
namespace NW
{
	struct img_bmp_info : public a_io_cmp
	{
	public:
		using pxl_t = mem_elem_t;
		using pxl_tc = mem_elem_tc;
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
		darray<byte_t> pal_idx;
		darray<byte_t> pal_pxl;
		darray<byte_t> img_pxl;
	public:
		// --getters
		inline cv1u get_channels() const { return data_info.nof_pixel_bits / 8; }
		inline cv1u get_count() const   { return NW_MATH_ABS(data_info.width * data_info.height); }
		inline cv1u get_count_x() const { return NW_MATH_ABS(data_info.width); }
		inline cv1u get_count_y() const { return NW_MATH_ABS(data_info.height); }
		inline size_tc get_size() const { return NW_CAST_SIZE(get_count() * get_channels()); }
		inline size_tc get_size_x() const { return NW_CAST_SIZE(get_count_x() * get_channels()); }
		inline size_tc get_size_y() const { return NW_CAST_SIZE(get_count_y() * get_channels()); }
		inline byte_t* get_data(size_tc crd = 0u)   { NW_CHECK(has_pixel(crd), "memory error", return NW_NULL); return &img_pxl[NW_CAST_SIZE(crd)]; }
		inline byte_tc* get_data(size_tc crd) const { NW_CHECK(has_pixel(crd), "memory error", return NW_NULL); return &img_pxl[NW_CAST_SIZE(crd)]; }
		inline byte_t* get_data(size_tc crd_x, size_tc crd_y)        { NW_CHECK(has_pixel(crd_x, crd_y), "memory error", return NW_NULL); return &img_pxl[(crd_y * get_size_x() + crd_y) * get_channels()]; }
		inline byte_tc* get_data(size_tc crd_x, size_tc crd_y) const { NW_CHECK(has_pixel(crd_x, crd_y), "memory error", return NW_NULL); return &img_pxl[(crd_y * get_size_x() + crd_y) * get_channels()]; }
		inline pxl_t get_pixel(cv1u crd)        { NW_CHECK(has_pixel(crd), "memory error", return pxl_t(NW_NULL, 0u)); return pxl_t(get_data(crd), get_channels()); }
		inline pxl_tc get_pixel(cv1u crd) const { NW_CHECK(has_pixel(crd), "memory error", return pxl_t(NW_NULL, 0u)); return pxl_tc(get_data(crd), get_channels()); }
		inline pxl_t get_pixel(cv1u crd_x, cv1u crd_y)        { NW_CHECK(has_pixel(crd_x, crd_y), "memory error", return pxl_t(NW_NULL, NW_NULL)); return pxl_t(get_data(crd_x, crd_y), get_channels()); }
		inline pxl_tc get_pixel(cv1u crd_x, cv1u crd_y) const { NW_CHECK(has_pixel(crd_x, crd_y), "memory error", return pxl_tc(NW_NULL, NW_NULL)); return pxl_tc(get_data(crd_x, crd_y), get_channels()); }
		// --setters
		inline v1nil set_pixel(byte_tc& buffer, cv1u crd)               { memcpy(get_pixel(crd), &buffer, get_channels()); }
		inline v1nil set_pixel(byte_tc& buffer, cv1u crd_x, cv1u crd_y) { memcpy(get_pixel(crd_x, crd_y), &buffer, get_channels()); }
		// --predicates
		inline v1bit has_space(size_tc crd) const                  { return crd < img_pxl.size(); }
		inline v1bit has_space(size_tc crd_x, size_tc crd_y) const { return NW_XY_TO_X(crd_x, crd_y, get_size_x()) < img_pxl.size(); }
		inline v1bit has_pixel(cv1u crd) const               { return has_space(crd * get_channels()); }
		inline v1bit has_pixel(cv1u crd_x, cv1u crd_y) const { return has_space(crd_x * get_channels(), crd_y * get_channels()); }
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	};
}
#endif	// NW_API
#endif	// NW_INFO_IMAGE_H