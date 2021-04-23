#include "nw_lib_pch.hpp"
#include "nw_mem_buf.h"
#if (defined NW_API)
#	include "nw_mem_sys.h"
namespace NW
{
	mem_buf::mem_buf() :
		m_layt(layt_t()),
		m_count(NW_NULL),
		m_count_used(NW_NULL),
		m_data(NW_NULL)
	{
	}
	mem_buf::mem_buf(layt_tc& layout, cv1u count, ptr_tc data) :
		mem_buf()
	{
		NW_CHECK(remake(layout, count, data), "failed to remake!", return);
	}
	mem_buf::mem_buf(buf_tc& copy) :
		a_mem_cmp(copy),
		m_layt(layt_t()),
		m_count(NW_NULL),
		m_count_used(NW_NULL),
		m_data(NW_NULL)
	{
		NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "failed to remake!", return);
	}
	mem_buf::mem_buf(buf_t&& copy) :
		a_mem_cmp(copy),
		m_layt(layt_t()),
		m_count(NW_NULL),
		m_count_used(NW_NULL),
		m_data(NW_NULL)
	{
		NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "failed to remake!", return);
	}
	mem_buf::~mem_buf()
	{
		if (m_data != NW_NULL) { mem_sys::get().del_arr<byte_t>(m_data, get_space()); }
	}
	// --setters
	v1nil mem_buf::set_layt(layt_tc& layout) {
		m_layt = layout;
	}
	v1nil mem_buf::set_count(cv1u count) {
		if (has_count()) { mem_sys::get().del_arr<byte_t>(m_data, get_space()); m_data = NW_NULL; }
		m_count = count;
		if (has_count()) { m_data = mem_sys::get().new_arr<byte_t>(get_space()); }
	}
	v1nil mem_buf::set_data(cv1u key, ptr_tc data, cv1u count) {
		NW_CHECK(has_count(key + count), "memory error!", return);
		if (data != NW_NULL) { memcpy(get_data(get_stride() * key), data, get_stride() * count); }
		else { memcpy(get_data(get_stride() * key), get_data(get_stride() * key), get_stride() * count); }
	}
	// --operators
	v1nil mem_buf::operator=(buf_tc& copy) {
		NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "failed to remake!", return);
	}
	v1nil mem_buf::operator=(buf_t&& copy) {
		NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "failed to remake!", return);
	}
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
		NW_CHECK(get_layt().remake(), "failed remake!", return NW_FALSE);
		NW_CHECK(has_space(), "no size!", return NW_FALSE);
		NW_CHECK(has_data(), "no data!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API