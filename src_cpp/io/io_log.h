#ifndef NWL_IO_LOG_SYSTEM_H
#define NWL_IO_LOG_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include "io_switch.h"
#include "io_stm.h"
namespace NW
{
	/// input_output_system static class
	class NW_API io_sys
	{
	public:
		using input = stm_io_str;
		using output = stm_out;
	public:
		// --getters
		static inline input& get_input() { return *s_input; }
		static inline output& get_output() { return *s_output; }
		// --setters
		static void on_init();
		static void on_quit();
		static void update();
		static void set_stm_out(stm_out& out);
		// --core_methods
		static void write_info(cstr format, ...);
		static void write_error(error_codes err_code, cstr format, ...);
		static void write_warn(cstr format, ...);
	private:
		static input* s_input;
		static output* s_output;
	};
}
#endif // NWL_IO_LOG_SYSTEM_H