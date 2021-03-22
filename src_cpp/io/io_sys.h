#ifndef NWL_IO_SYSTEM_H
#define NWL_IO_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_sing.h>
#include <core/nwl_str.h>
#include "io_switch.h"
#include "io_stm.h"
namespace NW
{
	/// input_output_system static class
	class NW_API io_sys : public t_singleton<io_sys>
	{
		friend class t_singleton<io_sys>;
	public:
		using input = stm_io_str;
		using output = stm_out;
	private:
		io_sys();
	public:
		~io_sys();
		// --getters
		inline input& get_input() { return *m_input; }
		inline output& get_output() { return *m_output; }
		// --setters
		void set_stm_out(output& out);
		// --core_methods
		void update();
		// --logging
		void write_info(cstr format, ...);
		void write_warn(cstr format, ...);
		void write_error(error_codes err_code, cstr format, ...);
	private:
		input* m_input;
		output* m_output;
	};
}
#endif // NWL_IO_SYSTEM_H