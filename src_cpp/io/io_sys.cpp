#include <nwl_pch.hpp>
#include "io_sys.h"

#include <mem/mem_sys.h>

#include <iomanip>

NW::io_sys::input* NW::io_sys::s_input = nullptr;
NW::io_sys::output* NW::io_sys::s_output = nullptr;

namespace NW
{
	// --setters
	void io_sys::set_stm_out(output& stm) {
		s_output = &stm;
	}
	// --==<core_methods>==--
	void io_sys::on_init()
	{
		if (s_input != nullptr) { return; }
		s_input = new input();
		s_output = &std::cout;
	}
	void io_sys::on_quit()
	{
		if (s_input == nullptr) { return; }
		delete s_input;
		s_input = nullptr;
		s_output = nullptr;
	}
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