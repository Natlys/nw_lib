#include <nwl_pch.hpp>
#include "io_log.h"

#include <mem/mem_sys.h>

#include <iomanip>

NW::io_sys::input* NW::io_sys::s_input = nullptr;
NW::io_sys::output* NW::io_sys::s_output = nullptr;

namespace NW
{
	// --==<core_methods>==--
	void io_sys::on_init()
	{
		if (s_input != nullptr) { return; }
		s_input = new input();
		s_output = &std::cout;

		// format flags;
		// use "flags" method to get them;
		// or "setf"/"unsetf" for individual setting;
		std::ios_base::fmtflags input_flags =
			std::ios_base::internal |		// central padding
			std::ios_base::boolalpha |		// true/false
			std::ios_base::oct |			// octodecimal
			std::ios_base::hex |			// hexadecimal
			std::ios_base::showbase |		// 0 or x before oct/hex
			std::ios_base::showpoint |		// no matter zeros;
			std::ios_base::uppercase;		//
		std::ios_base::fmtflags flag_fields =
			std::ios_base::basefield |		//
			std::ios_base::adjustfield |	// 
			std::ios_base::floatfield;		//
		std::cout.exceptions(std::ios_base::failbit | std::ios_base::badbit);
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
	}
	void io_sys::write_info(cstr format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_info>==--" << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_info>==--" << std::endl;
		va_end(valArgs);
	}
	void io_sys::write_warn(cstr format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_warning>==--" << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(valArgs);
		NW_BREAK();
	}
	void io_sys::write_error(error_codes err_code, cstr format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_a_err>==--" << std::endl <<
			"code:" << err_code << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_a_err>==--" << std::endl;
		va_end(valArgs);
		NW_BREAK();
	}
	// --==</core_methods>==--
}