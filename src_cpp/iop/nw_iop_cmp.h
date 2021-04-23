#ifndef NW_IOP_COMPONENT_H
#define NW_IOP_COMPONENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_iop_flib.h"
#	include "nw_iop_stm.h"
namespace NW
{
	/// input_component class
	class NW_API a_ip_cmp
	{
	public:
		a_ip_cmp() = default;
		a_ip_cmp(const a_ip_cmp& copy) = default;
		a_ip_cmp(a_ip_cmp&& copy) = default;
		virtual ~a_ip_cmp() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
		virtual ip_stream_t& operator>>(ip_stream_t& stm) = 0;
		// --core_methods
	};
	inline NW_API ip_stream_t& operator>>(ip_stream_t& stm, a_ip_cmp& cmp) { return cmp.operator>>(stm); }
	/// output_component class
	class NW_API a_op_cmp
	{
	public:
		a_op_cmp() = default;
		a_op_cmp(const a_op_cmp& copy) = default;
		a_op_cmp(a_op_cmp&& copy) = default;
		virtual ~a_op_cmp() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const = 0;
		// --core_methods
	};
	inline NW_API op_stream_t& operator<<(op_stream_t& stm, const a_op_cmp& cmp) { return cmp.operator<<(stm); }
	/// input_output_component class
	class NW_API a_iop_cmp : public a_ip_cmp, public a_op_cmp
	{
	public:
		a_iop_cmp() = default;
		a_iop_cmp(const a_iop_cmp& copy) = default;
		a_iop_cmp(a_iop_cmp&& copy) = default;
		virtual ~a_iop_cmp() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const = 0;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) = 0;
		// --core_methods
	};
}
#endif	// NW_API
#endif	// NW_IOP_COMPONENT_H
