#ifndef NW_IO_ERROR_H
#define NW_IO_ERROR_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "nw_io_stm.h"
namespace NW
{
	enum error_codes : v1u {
		ERC_DEFAULT = 0,
		ERC_NO_INIT = 1, ERC_NO_QUIT = 2,
		ERC_NO_SUPPORT, ERC_NO_STATE,
		ERC_NO_MEMORY,
		ERC_NO_LOAD, ERC_NO_SAVE,
		ERC_RUNTIME,
		ERC_DATA_BAD, ERC_DATA_LOSS, ERC_DATA_OVERFLOW, ERC_DATA_UNDERFLOW,
		ERC_UNKNOWN_ID, ERC_UNKNOWN_NAME,
		ERC_INVALID_FORMAT, ERC_INVALID_SYNTAX, ERC_INVALID_TYPE, ERC_INVALID_ENUM,
		ERC_COMPILLATION, ERC_LINKAGE
	};
}
namespace NW
{
	/// abstract error class
	class NW_API a_error
	{
	public:
		using code = error_codes;
	public:
		a_error(cstr comment = "default", v1u err_code = ERC_DEFAULT, cstr location = "default", v1u line = -1);
		// --getters
		inline cstr get_str() const;
		inline code get_code() const { return m_code; }
		inline cstr get_com() const  { return &m_comment[0]; }
		inline cstr get_loc() const  { return &m_location[0]; }
		inline v1u get_line() const  { return m_line; }
		// --operators
		stm_out& operator<<(stm_out& stm) const;
		stm_in& operator>>(stm_in& stm);
	private:
		dstr m_comment;
		error_codes m_code;
		dstr m_location;
		v1u m_line;
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
		init_error(cstr location = "default", v1u line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// quit_error class
	class NW_API quit_error : public a_error
	{
	public:
		quit_error(cstr location = "default", v1u line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	/// runtime_error class
	class NW_API run_error : public a_error
	{
	public:
		run_error(cstr location = "default", v1u line = -1);
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
		load_error(cstr location = "default", v1u line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
	class NW_API save_error : public a_error
	{
	public:
		save_error(cstr location = "default", v1u line = -1);
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
		mem_error(cstr location = "default", v1u line = -1);
		// --getters
		// --setters
		// --operators
	private:
	};
}
#endif	// NW_API
#endif	// NW_IO_ERROR_H
