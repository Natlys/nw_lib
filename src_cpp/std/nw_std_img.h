#ifndef NW_STD_IMAGE_H
#define NW_STD_IMAGE_H
#include "nw_lib_core.hpp"
#if (defined NW_GAPI)
#include "ecs/nw_ecs_cmp.h"
#include "info/nw_info_img.h"
#include "io/nw_io_cmp.h"
#include "nw_std_cont.h"
namespace NW
{
	/// image class
	class NW_API a_img_cmp : public a_io_cmp
	{
	public:
		using data = darray<ubyte>;
	public:
		a_img_cmp();
		a_img_cmp(const a_img_cmp& cpy);
		a_img_cmp(const a_img_cmp& cpy, v1s offset_x, v1s offset_y, v1s width, v1s height);
		// --getters
		inline v1s get_size_x() const      { return m_size_x; }
		inline v1s get_size_y() const      { return m_size_y; }
		inline v1s get_channels() const    { return m_channels; }
		inline size get_data_size() const  { return static_cast<size>(abs(m_size_x)) * static_cast<size>(abs(m_size_y)) * static_cast<size>(abs(m_channels)); }
		inline size get_pxl_size() const   { return static_cast<size>(abs(m_size_x)) * static_cast<size>(abs(m_size_y)); }
		inline ubyte* get_data()                 { return &m_pxl_data[0]; }
		inline const ubyte* get_data() const     { return &m_pxl_data[0]; }
		inline ubyte* get_data(v1u pxl_x, v1u pxl_y)             { return &m_pxl_data[NW_XY_TO_X(pxl_x * m_channels, pxl_y * m_channels, m_size_x) % get_data_size()]; }
		inline const ubyte* get_data(v1u pxl_x, v1u pxl_y) const { return &m_pxl_data[NW_XY_TO_X(pxl_x * m_channels, pxl_y * m_channels, m_size_x) % get_data_size()]; }
		// --setters
		void set_data(const ubyte* data_ptr);
		void set_data(const a_img_cmp& source);
		void set_data(const a_img_cmp& source, v1s crd_x, v1s crd_y, v1s size_x, v1s size_y);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		data make_region(v1s crd_x, v1s crd_y, v1s size_x, v1s size_y) const;
	protected:
		v1s m_size_x;
		v1s m_size_y;
		v1s m_channels;
		data m_pxl_data;
	};
}
namespace NW
{
	/// img_bmp class
	/// description:
	/// --used for loading of .bmp formatted files
	/// interface:
	/// ->load a bitmap as binary file->read headers "file" and "data"
	/// ->if the image is indexed - load color pallete
	/// ->read pixel data with offset which is defined in "file" header
	/// ->in the case of 24bit and not multiple-of-4 sizes, we need to consider padding
	class NW_API img_bmp : public t_cmp<img_bmp>, public a_img_cmp
	{
	public:
		img_bmp();
		~img_bmp();
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	private:
		img_bmp_info m_info;
	};
}
#endif	// NW_GAPI
#endif	// NW_STD_IMAGE_H
