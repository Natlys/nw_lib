#ifndef NW_DATA_RESOURCE_H
#define NW_DATA_RESOURCE_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <io/io_stm.h>
#include <mem/mem_sys.h>
namespace NW
{
	/// abstract data_resource class
	/// interface:
	/// ->derrive any class you want from the a_data_rsc class
	/// ->implement save() and load() methods
	/// description:
	/// --every object in the engine can be saved in a binary file or some format
	/// --class which is inherit of a_data_rsc can be: saved | loaded
	/// --everything we need - save/load methods implementation for this
	class NW_API a_data_rsc
	{
	protected:
		a_data_rsc(cstr name);
	public:
		virtual ~a_data_rsc();
		// --getters
		inline cstr get_name() const { return &m_name[0]; }
		// --setters
		virtual void set_name(cstr name);
		// --core_methods
		bit save_file(cstr file_path);
		bit load_file(cstr file_path);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const;
		virtual stm_in& operator>>(stm_in& stm);
	protected:
		dstr m_name;
	};
	stm_out& operator<<(stm_out& stm, const a_data_rsc& rsc);
	stm_in& operator>>(stm_in& stm, a_data_rsc& rsc);
}

#endif // NW_DATA_RESOURCE_H