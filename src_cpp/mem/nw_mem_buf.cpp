#include "nw_lib_pch.hpp"
#include "nw_mem_buf.h"
#if (defined NW_API)
#	include "nw_mem_sys.h"
namespace NW
{
	mem_buf::mem_buf() : m_layt(layt_t()), m_count(NW_NULL), m_data(NW_NULL) { }
	mem_buf::mem_buf(layt_tc& layout, cv1u count, ptr_tc data) : mem_buf() { NW_CHECK(remake(layout, count, data), "failed to remake!", return); }
	mem_buf::mem_buf(buf_tc& copy) : mem_buf() { operator=(copy); }
	mem_buf::mem_buf(buf_t&& copy) : mem_buf() { operator=(copy); }
	mem_buf::~mem_buf() { set_count(NW_NULL); }
	// --setters
	mem_buf::buf_t& mem_buf::set_layt(layt_tc& layout) {
		size_tc old_space = m_count * m_layt.get_space();
		size_tc new_space = m_count * layout.get_space();
		if (old_space != new_space) {
			size_tc cpy_space = NW_MATH_MIN(old_space, new_space);
			byte_t* old_data = m_data;
			byte_t* new_data = NW_NULL;
			if (new_space > 0u) {
				new_data = mem_sys::get().new_arr<byte_t>(new_space);
				if (cpy_space > 0u) { memmove(new_data, old_data, cpy_space); }
			}
			if (old_space > 0u) { mem_sys::get().del_arr<byte_t>(old_data, old_space); }
			m_data = new_data;
		}
		m_layt = layout;
		return *this;
	}
	mem_buf::buf_t& mem_buf::set_count(cv1u count) {
		size_tc old_space = get_stride() * m_count;
		size_tc new_space = get_stride() * count;
		if (old_space != new_space) {
			size_tc cpy_space = NW_MATH_MIN(old_space, new_space);
			byte_t* old_data = m_data;
			byte_t* new_data = NW_NULL;
			if (new_space > 0u) {
				new_data = mem_sys::get().new_arr<byte_t>(new_space);
				if (cpy_space > 0u) { memmove(new_data, old_data, cpy_space); }
			}
			if (old_space > 0u) { mem_sys::get().del_arr<byte_t>(old_data, old_space); }
			m_data = new_data;
		}
		m_count = count;
		return *this;
	}
	mem_buf::buf_t& mem_buf::set_data(cv1u key, ptr_tc data, cv1u count) {
		NW_CHECK(has_count(key + count), "memory error!", return *this);
		if (data != NW_NULL) { memcpy(get_data(get_stride() * key), data, get_stride() * count); }
		else { memcpy(get_data(get_stride() * key), get_data(get_stride() * key), get_stride() * count); }
		return *this;
	}
	// --operators
	op_stream_t& mem_buf::operator<<(op_stream_t& stm) const {
		stm << "{" NW_STR_EOL;
		stm << "layout:" << get_layt() << NW_STR_EOL;
		stm << "count:" << get_count() << ";" NW_STR_EOL;
		stm << "data:";
		stm.write(reinterpret_cast<byte_tc*>(get_data()), get_space());
		stm << ";" NW_STR_EOL;
		stm << "};" NW_STR_EOL;
		return stm;
	}
	ip_stream_t& mem_buf::operator>>(ip_stream_t& stm) {
		byte_t temp[256u]{ NW_NULL };
		layt_t layout;
		v1u count;
		byte_t* data;
		stm.getline(temp, 256u, '\n');
		stm.getline(temp, 256u, ':');
		stm >> layout;
		stm.getline(temp, 256u, '\n');
		stm.getline(temp, 256u, ':');
		stm >> count;
		stm.getline(temp, 256u, '\n');
		stm.getline(temp, 256u, ':');
		if ((layout.get_space() * count) > 0u) {
			data = mem_sys::get().new_arr<byte_t>(count * layout.get_space());
			stm.read(data, count * layout.get_space());
			mem_sys::get().del_arr<byte_t>(data, count * layout.get_space());
		}
		stm.getline(temp, 256u, '\n');
		return stm;
	}
	// --==<core_methods>==--
	v1bit mem_buf::remake()
	{
		NW_CHECK(get_layt().remake(), "remake error!", return NW_FALSE);
		NW_CHECK(has_space(), "no size!", return NW_FALSE);
		NW_CHECK(has_data(), "no data!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API