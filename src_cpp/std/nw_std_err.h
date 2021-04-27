#ifndef NW_STD_ERROR_H
#define NW_STD_ERROR_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../iop/nw_iop_cmp.h"
namespace NW
{
	/// abstract_error class
	class NW_API a_error : public a_op_cmp
	{
	public:
		a_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		inline cstr_t get_str() const { return m_str; }
		inline cv1u get_num() const { return m_num; }
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		// --core_methods
	private:
		cstr_t m_str;
		cv1u m_num;
	};
}
namespace NW
{
	/// init_error class
	class NW_API init_error : public a_error
	{
	public:
		init_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// quit_error class
	class NW_API quit_error : public a_error
	{
	public:
		quit_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// runtime_error class
	class NW_API run_error : public a_error
	{
	public:
		run_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
}
namespace NW
{
	class NW_API load_error : public a_error
	{
	public:
		load_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	class NW_API save_error : public a_error
	{
	public:
		save_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// memory_error class
	class NW_API mem_error : public a_error
	{
	public:
		mem_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// type_error class
	class NW_API type_error : public a_error
	{
	public:
		type_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// index_error class
	class NW_API index_error : public a_error
	{
	public:
		index_error(cstr_t string = NW_NULL, cv1u number = NW_NULL);
		// --getters
		// --setters
		// --operators
	private:
	};
}
#endif	// NW_API
#endif	// NW_STD_ERROR_H