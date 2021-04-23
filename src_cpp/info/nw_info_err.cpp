#include "nw_lib_pch.hpp"
#include "nw_info_err.h"
#if (defined NW_API)
namespace NW
{
	a_error::a_error(cstr_t string, cv1u number) :
		m_str(string), m_num(number)
	{
		NW_ERROR(*this, return);
	}
	// --operators
	op_stream_t& a_error::operator<<(op_stream_t& stm) const {
		return stm <<
			"--==<error_info>==--" << std::endl <<
			"string: " << get_str() << std::endl <<
			"number: " << get_num() << std::endl <<
			"--==</erro_info>==--" << std::endl;
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
namespace NW
{
	init_error::init_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
	quit_error::quit_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
	run_error::run_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
namespace NW
{
	load_error::load_error(cstr_t string, cv1u number) : a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
	save_error::save_error(cstr_t string, cv1u number) : a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
namespace NW
{
	mem_error::mem_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
	type_error::type_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
	index_error::index_error(cstr_t string, cv1u number) :
		a_error(string, number)
	{
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
#endif	// NW_API