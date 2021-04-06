#include "nw_lib_pch.hpp"
#include "nw_std_img.h"
#if (defined NW_GAPI)
#include "io/nw_io_err.h"
namespace NW
{
	a_img_cmp::a_img_cmp() :
		a_io_cmp(),
		m_size_x(1), m_size_y(1),
		m_channels(4),
		m_pxl_data{ data{ 255u, 255u, 255u, 255u } }
	{
	}
	a_img_cmp::a_img_cmp(const a_img_cmp& cpy) :
		a_io_cmp(cpy),
		m_size_x(cpy.m_size_x), m_size_y(cpy.m_size_y),
		m_channels(cpy.m_channels),
		m_pxl_data(cpy.m_pxl_data)
	{
	}
	a_img_cmp::a_img_cmp(const a_img_cmp& cpy, v1s offset_x, v1s offset_y, v1s width, v1s height) :
		a_io_cmp(cpy),
		m_size_x(width), m_size_y(height)
	{
		set_data(cpy, offset_x, offset_y, width, height);
	}
	// --setters
	void a_img_cmp::set_data(const ubyte* data_ptr) {
		if (data_ptr == nullptr || m_size_x == 0 || m_size_y == 0 || m_channels == 0) { m_pxl_data.clear(); return; }
		else {
			m_pxl_data.resize(get_data_size());
			memcpy(&m_pxl_data[0], &data_ptr[0], get_data_size());
		}
	}
	void a_img_cmp::set_data(const a_img_cmp& source) {
		m_size_x = source.get_size_x();
		m_size_y = source.get_size_y();
		m_channels = source.get_channels();
		set_data(source.get_data());
	}
	void a_img_cmp::set_data(const a_img_cmp& source, v1s crd_x, v1s crd_y, v1s size_x, v1s size_y) {
		m_size_x = size_x;
		m_size_y = size_y;
		if (m_size_x == 0 || m_size_y == 0 || m_channels == 0) { m_pxl_data.clear(); return; }
		else { m_pxl_data.resize(get_data_size()); }
		v1s beg_x = crd_x, beg_y = crd_y;
		v1s end_x = beg_x, end_y = beg_y;
		v1s dir_x = +1, dir_y = +1;
		if (size_x < 0) {
			beg_x += m_size_x - 1;
			end_x -= 1;
			dir_x = -1;
		}
		else {
			beg_x += +0;
			end_x += m_size_x;
			dir_x = +1;
		}
		if (size_y < 0) {
			beg_y += m_size_y - 1;
			end_y -= 1;
			dir_y = -1;
		}
		else {
			beg_y += 0;
			end_y += m_size_y;
			dir_y = +1;
		}
		beg_x *= m_channels; beg_y *= m_channels;
		end_x *= m_channels; end_y *= m_channels;
		dir_x *= m_channels; dir_y *= m_channels;
		for (v1s iy = beg_y; iy != end_y; iy += dir_y) {
			for (v1s ix = beg_x; ix != end_x; ix += dir_x) {
				memcpy(&m_pxl_data[NW_XY_TO_X(iy, ix, m_size_x)], &source.get_data()[NW_XY_TO_X(iy, ix, m_size_x)], m_channels);
			}
		}
	}
	// --operators
	// --==<core_methods>==--
	a_img_cmp::data a_img_cmp::make_region(v1s crd_x, v1s crd_y, v1s size_x, v1s size_y) const {
		data region;
		if (size_x == 0 || size_y == 0) { throw run_error(__FILE__, __LINE__); return region; }
		region.resize(std::abs(size_x) * std::abs(size_y) * m_channels);
		v1s beg_x = crd_x, beg_y = crd_y;
		v1s end_x = beg_x, end_y = beg_y;
		v1s dir_x = +1, dir_y = +1;
		if (size_x < 0) {
			beg_x += size_x - 1;
			end_x -= 1;
			dir_x = -1;
		}
		else {
			beg_x += +0;
			end_x += size_x;
			dir_x = +1;
		}
		if (size_y < 0) {
			beg_y += size_y - 1;
			end_y -= 1;
			dir_y = -1;
		}
		else {
			beg_y += 0;
			end_y += size_y;
			dir_y = +1;
		}
		beg_x *= m_channels; beg_y *= m_channels;
		end_x *= m_channels; end_y *= m_channels;
		dir_x *= m_channels; dir_y *= m_channels;
		for (v1s iy = beg_y; iy != end_y; iy += dir_y) {
			for (v1s ix = beg_x; ix != end_x; ix += dir_x) {
				memcpy(&region[NW_XY_TO_X(ix - beg_x, iy - beg_y, size_x)], &m_pxl_data[NW_XY_TO_X(ix, iy, m_size_x)], m_channels);
			}
		}
		return region;
	// --==</core_methods>==--
	}
}
namespace NW
{
	img_bmp::img_bmp() :
		t_cmp(), a_img_cmp()
	{
	}
	img_bmp::~img_bmp() { }
	// --operators
	stm_out& img_bmp::operator<<(stm_out& stm) const {
		stm << m_info;
		stm.write(reinterpret_cast<const sbyte*>(&m_pxl_data[0]), get_data_size());
		return stm;
	}
	stm_in& img_bmp::operator>>(stm_in& stm) {
		stm >> m_info;
		if (m_info.data.nof_pixel_bits != 8 && m_info.data.nof_pixel_bits != 16 &&
			m_info.data.nof_pixel_bits != 24 && m_info.data.nof_pixel_bits != 32) {
			throw load_error(__FILE__, __LINE__);
			return stm;
		}

		m_size_x = get_abs(m_info.data.width);
		m_size_y = get_abs(m_info.data.height);

		if (m_info.data.nof_pixel_bits <= 16) {
			m_channels = 4;
			m_pxl_data.resize(m_info.data.image_size * m_channels);
			darray<ubyte> colors(m_info.data.clrs_used * m_channels, 0u);
			darray<ubyte> indices(m_info.data.image_size, 0u);
			stm.read(reinterpret_cast<sbyte*>(&colors[0]), colors.size());
			stm.read(reinterpret_cast<sbyte*>(&indices[0]), indices.size());
			for (v1s idx = 0; idx < indices.size(); idx++) {
				memcpy(&m_pxl_data[idx * m_channels], &colors[indices[idx] * m_channels], m_channels);
			}
		}
		else {
			m_channels = m_info.data.nof_pixel_bits / 8;
			m_pxl_data.resize(get_data_size());
			v1s pad = ((m_size_x * m_channels) % 4) % 4;
			v1s beg_x, beg_y;
			v1s end_x, end_y;
			v1s dir_x, dir_y;
			if (m_info.data.width < 0) {
				beg_y = m_size_y - 1;
				end_y = -1;
				dir_y = -1;
			}
			else {
				beg_y = +0;
				end_y = +m_size_y;
				dir_y = +1;
			}
			if (m_info.data.height < 0) {
				beg_x = +m_size_x - 1;
				end_x = -1;
				dir_x = -1;
			}
			else {
				beg_x = +0;
				end_x = +m_size_x;
				dir_x = +1;
			}
			stm.seekg(m_info.file.data_offset, stm.beg);
			for (v1s iy = beg_y; iy != end_y; iy += dir_y) {
				for (v1s ix = beg_x; ix != end_x; ix += dir_x) {
					v1s get_pos = (iy * m_size_x + ix) * m_channels;
					for (v1s ich = 0; ich < m_channels; ich++, get_pos++) {
						m_pxl_data[get_pos + ich] = stm.get();
					}
				}
				stm.seekg(pad, stm.cur);
			}
		}
		return stm;
	}

}
#endif	// NW_GAPI