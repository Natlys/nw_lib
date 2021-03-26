#include <nwl_pch.hpp>
#include "io_err.h"
namespace NW
{
	a_error::a_error(cstr comment, v1ui err_code, cstr location, v1ui line) :
		m_comment(comment), m_location(location), m_code(static_cast<error_codes>(err_code)), m_line(line)
	{
		NW_ERR(get_str());
	}
	// --getters
	inline cstr a_error::get_str() const {
		static stm_io_str stm;
		stm << *this;
		return &stm.str()[0];
	}
	// --operators
	stm_out& a_error::operator<<(stm_out& stm) const {
		return stm <<
			"--==<exception_info>==--" << std::endl <<
			"string: " << get_com() << std::endl <<
			"code: " << get_code() << std::endl <<
			"location: " << get_loc() << std::endl <<
			"line: " << get_line() << std::endl <<
			"--==</exception_info>==--" << std::endl;
	}
	stm_in& a_error::operator>>(stm_in& stm) {
		return stm;
	}
	stm_out& operator<<(stm_out& stm, const a_error& err) { return err.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_error& err) { return err.operator>>(stm); }
}
namespace NW
{

	init_error::init_error(cstr location, v1ui line) : a_error("initialization error", ERC_NO_INIT, location, line) {}

	quit_error::quit_error(cstr location, v1ui line) : a_error("initialization error", ERC_NO_QUIT, location, line) {}

	run_error::run_error(cstr location, v1ui line) : a_error("runtime error", ERC_RUNTIME, location, line) {}
}
namespace NW
{
	load_error::load_error(cstr location, v1ui line) : a_error("loading error", ERC_NO_LOAD, location, line) {}

	save_error::save_error(cstr location, v1ui line) : a_error("saving error", ERC_NO_SAVE, location, line) {}
}
namespace NW
{
	mem_error::mem_error(cstr location, v1ui line) : a_error("memory error", ERC_NO_MEMORY) {}
}