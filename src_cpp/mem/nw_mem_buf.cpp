#include "nw_lib_pch.hpp"
#include "nw_mem_buf.h"
#if (defined NW_API)
#	include "nw_mem_sys.h"
namespace NW
{
	mem_buf::mem_buf() : m_layt(layt_t()), m_count(NW_NULL), m_data(NW_NULL) { }
	mem_buf::mem_buf(layt_tc& layout, size_t space) : mem_buf() { NW_CHECK(remake(layout, space), "remake error!", return); }
	mem_buf::mem_buf(layt_tc& layout, size_t space, ptr_tc data) : mem_buf() { NW_CHECK(remake(layout, space, data), "remake error!", return); }
	mem_buf::mem_buf(buf_tc& copy) : mem_buf() { operator=(copy); }
	mem_buf::mem_buf(buf_t&& copy) : mem_buf() { operator=(copy); }
	mem_buf::~mem_buf() { set_count(NW_NULL); }
	// --setters
	mem_buf::buf_t& mem_buf::set_layt(layt_tc& layout) { m_layt = layout; return set_space(get_space()); }
	mem_buf::buf_t& mem_buf::set_count(size_t count) { return set_space(count * m_layt.get_space()); }
	mem_buf::buf_t& mem_buf::set_space(size_t space) {
		NW_CHECK(has_stride(), "no stride!", return *this);
		size_tc old_space = get_space();
		size_tc new_space = space + (space % get_stride());
		if (get_space() == new_space) { return *this; }
		size_tc cpy_space = NW_NUM_MIN(old_space, new_space);
		byte_t* old_data = get_data();
		byte_t* new_data = NW_NULL;
		if (new_space) { new_data = mem_sys::get().new_arr<byte_t>(new_space); if (cpy_space && old_data) { memmove(new_data, old_data, cpy_space); } }
		if (old_space) { mem_sys::get().del_arr<byte_t>(old_data, old_space); }
		m_data = new_data;
		m_count = new_space / get_stride();
		return *this;
	}
	mem_buf::buf_t& mem_buf::set_data(size_t key, ptr_tc data, size_t count) {
		NW_CHECK(data != NW_NULL, "no data!", return *this);
		memcpy(get_data(key * get_stride()), data, count * get_stride());
		return *this;
	}
	// --operators
	op_stream_t& mem_buf::operator<<(op_stream_t& stm) const {
		stm << "{" NW_STR_EOL;
		stm << "layout:" << get_layt() << NW_STR_EOL;
		stm << "count:" << get_count() << ";" NW_STR_EOL;
		stm << "space:" << get_space() << ";" NW_STR_EOL;
		(stm << "data:").write(reinterpret_cast<byte_tc*>(get_data()), get_space()) << ";" NW_STR_EOL;
		stm << "};" NW_STR_EOL;
		return stm;
	}
	ip_stream_t& mem_buf::operator>>(ip_stream_t& stm) { return stm; }
	// --==<core_methods>==--
	v1bit mem_buf::remake()
	{
		NW_CHECK(m_layt.remake(), "remake error!", return NW_FALSE);
		NW_CHECK(has_stride(), "no stride!", return NW_FALSE);
		NW_CHECK(has_count(), "no count!", return NW_FALSE);
		NW_CHECK(has_space(), "no space!", return NW_FALSE);
		NW_CHECK(has_data(), "no data!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API