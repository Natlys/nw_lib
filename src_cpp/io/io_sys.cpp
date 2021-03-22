#include <nwl_pch.hpp>
#include "io_sys.h"

#include <mem/mem_sys.h>

#include <iomanip>

namespace NW
{
	io_sys::io_sys() :
		m_input(nullptr)
	{
		if (m_input != nullptr) { return; }
		m_input = new input();
		m_output = &std::cout;
	}
	io_sys::~io_sys()
	{
		if (m_input == nullptr) { return; }
		delete m_input;
		m_input = nullptr;
		m_output = nullptr;
	}
	// --setters
	void io_sys::set_stm_out(output& stm) {
		m_output = &stm;
	}
	// --==<core_methods>==--
	void io_sys::update()
	{
		get_output() << get_input().str();
		get_input().str("");
	}
	// --==</core_methods>==--
	// --==<logging>==--
	void io_sys::write_info(cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_information>==--" << std::endl <<
			"::message:" << str_format_var(format, arguments) << std::endl <<
			"--==</log_information>==--" << std::endl;
		va_end(arguments);
	}
	void io_sys::write_warn(cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_warning>==--" << std::endl <<
			"::message:" << str_format_var(format, arguments) << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(arguments);
		NW_BREAK();
	}
	void io_sys::write_error(error_codes err_code, cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_error>==--" << std::endl <<
			"code:" << err_code << std::endl <<
			"::message:" << &str_format_var(format, arguments)[0] << std::endl <<
			"--==</log_error>==--" << std::endl;
		va_end(arguments);
		NW_BREAK();
	}
	// --==</logging>==--
}