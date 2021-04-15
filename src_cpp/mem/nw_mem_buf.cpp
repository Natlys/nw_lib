#include "nw_lib_pch.hpp"
#include "nw_mem_buf.h"
#if (defined NW_API)
#	include "nw_mem_sys.h"
namespace NW
{
	mem_buf::mem_buf(cv1u stride, cv1u count, ptr_tc data) :
		a_mem_cmp(),
		m_bytes(NW_NULL),
		m_stride(NW_NULL),
		m_count(NW_NULL)
	{
		NW_CHECK(remake(stride, count, data), "failed to remake!", return);
	}
	mem_buf::mem_buf(buf_tc& copy) :
		a_mem_cmp(copy),
		m_bytes(NW_NULL),
		m_stride(NW_NULL),
		m_count(NW_NULL)
	{
		NW_CHECK(remake(copy.get_stride(), copy.get_count(), copy.get_bytes()), "failed to remake!", return);
	}
	mem_buf::mem_buf(buf_t&& copy) :
		a_mem_cmp(copy),
		m_bytes(NW_NULL),
		m_stride(NW_NULL),
		m_count(NW_NULL)
	{
		NW_CHECK(remake(copy.get_stride(), copy.get_count(), copy.get_bytes()), "failed to remake!", return);
	}
	mem_buf::~mem_buf()
	{
		remake(NW_NULL, NW_NULL, NW_NULL);
	}
	// --setters
	v1nil mem_buf::set_data(cv1u count, ptr_tc data, cv1u offset) {
		NW_CHECK(has_count(count + offset), "memory error!", return);
		NW_CHECK(count != NW_NULL, "no difference!", return);
		if (data != NW_NULL) {
			memcpy(get_byte(get_stride() * offset), data, get_stride() * count);
		}
		else {
			memcpy(get_byte(get_stride() * offset), get_byte(get_stride() * offset), get_stride() * count);
		}
	}
	// --operators
	v1nil mem_buf::operator=(buf_tc& copy) {
		NW_CHECK(remake(copy.get_stride(), copy.get_count(), copy.get_bytes()), "failed to remake!", return);
	}
	v1nil mem_buf::operator=(buf_t&& copy) {
		NW_CHECK(remake(copy.get_stride(), copy.get_count(), copy.get_bytes()), "failed to remake!", return);
	}
	// --==<core_methods>==--
	v1bit mem_buf::remake(cv1u stride, cv1u count, ptr_tc data)
	{
		if (m_bytes != NW_NULL) { mem_sys::get().del_arr<byte_t>(m_bytes, get_space()); m_bytes = NW_NULL; }
		if (stride != NW_NULL && count != NW_NULL) { m_bytes = mem_sys::get().new_arr<byte_t>(stride * count); }
		if (stride != NW_NULL && count != NW_NULL && data != NW_NULL) { memcpy(m_bytes, data, m_stride * m_count); }
		m_count = count;
		m_stride = stride;
		return NW_TRUE;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_arr::mem_arr(layt_tc& layout, cv1u count, ptr_tc data) :
		mem_buf(layout.get_size(), count, data),
		m_layt(layout)
	{
	}
	mem_arr::mem_arr(arr_tc& copy) :
		mem_buf(copy),
		m_layt(copy.m_layt)
	{
	}
	mem_arr::mem_arr(arr_t&& copy) :
		mem_buf(copy),
		m_layt(copy.m_layt)
	{
	}
	mem_arr::~mem_arr()
	{
	}
	// --setters
	v1nil mem_arr::set_layt(layt_tc& layout) {
		m_layt = layout;
	}
	// --operators
	v1nil mem_arr::operator=(arr_tc& copy) {
		mem_buf::operator=(copy);
		m_layt = copy.m_layt;
	}
	v1nil mem_arr::operator=(arr_t&& copy) {
		mem_buf::operator=(copy);
		m_layt = copy.m_layt;
	}
	// --==<core_methods>==--
	v1bit mem_arr::remake(cv1u stride, cv1u count, ptr_tc data) {
		NW_CHECK(m_layt.remake(NW_NULL, NW_NULL), "failed remake!", return NW_FALSE);
		NW_CHECK(m_layt.get_size() == stride, "stride has to be equal to the layout size!", return NW_FALSE);
		NW_CHECK(mem_buf::remake(stride, count, data), "failed remake!", return NW_FALSE);
		NW_CHECK(m_layt.remake(mem_buf::get_bytes(), NW_NULL), "failed remake!", return NW_FALSE);
		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API