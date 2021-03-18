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
#endif	// NWL_IO_ERROR_H