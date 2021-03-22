#ifndef NWL_IO_ERROR_H
#define NWL_IO_ERROR_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include "io_switch.h"
#include "io_stm.h"
namespace NW
{
	/// abstract error class
	class NW_API a_error
	{
	public:
		using code = error_codes;
	public:
		a_error(cstr comment = "default", ui32 err_code = ERC_DEFAULT, cstr location = "default", ui32 line = -1);
		// --getters
		inline cstr get_str() const;
		inline code get_code() const	{ return m_code; }
		inline cstr get_com() const		{ return &m_comment[0]; }
		inline cstr get_loc() const		{ return &m_location[0]; }
		inline ui32 get_line() const	{ return m_line; }
		// --operators
		stm_out& operator<<(stm_out& stm) const;
		stm_in& operator>>(stm_in& stm);
	private:
		dstr m_comment;
		error_codes m_code;
		dstr m_location;
		ui32 m_line;
	};
	stm_out& operator<<(stm_out& stm, const a_error& err);
	stm_in& operator>>(stm_in& stm, a_error& err);
}
namespace NW
{
	/// init_error class
	class NW_API init_error : public a_error
	{
	public:
		init_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// quit_error class
	class NW_API quit_error : public a_error
	{
	public:
		quit_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// runtime_error class
	class NW_API run_error : public a_error
	{
	public:
		run_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// memory_error class
}
namespace NW
{
	class NW_API load_error : public a_error
	{
	public:
		load_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	class NW_API save_error : public a_error
	{
	public:
		save_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
}
namespace NW
{
	class NW_API mem_error : public a_error
	{
	public:
		mem_error(cstr location = "default", ui32 line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
}
namespace NW
{
	// errors
	// We would really love to use the proper way of building std::error_code by specializing
	// is_error_code_enum and make_error_code for __std_win_error, but because:
	//   1. We would like to keep the definition of __std_win_error in xfilesystem_abi.h
	//   2. and xfilesystem_abi.h cannot include <std::system_error>
	//   3. and specialization of is_error_code_enum and overload of make_error_code
	//      need to be kept together with the enum (see limerick in N4810 [temp.expl.spec]/7)
	// we resort to using this make_err_code helper.
	// --make an std::error_code
	inline std::error_code make_err_code(__std_win_error err_no) noexcept { return { static_cast<int>(err_no), std::system_category() }; }

	inline void throw_sys_err_from_std_win_err(const __std_win_error err_no) { throw std::system_error{ make_err_code(err_no) }; }

	inline int check_convert_result(const __std_fs_convert_result res) {
		if (res._Err != __std_win_error::_Success) { throw_sys_err_from_std_win_err(res._Err); }
		return res._Len;
	}
}
#endif	// NWL_IO_ERROR_H