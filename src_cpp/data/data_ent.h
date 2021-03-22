#ifndef NW_DATA_ENTITY_H
#define NW_DATA_ENTITY_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <core/nwl_cln.h>
#include <io/io_stm.h>
#include <mem/mem_ref.h>
#include <ecs/ecs_ent.h>
#include "data_rsc.h"
#include "data_path.h"
namespace NW
{
	/// data_entity class
	/// description:
	/// --handles some data resource
	/// --requires a file path
	/// if something was found - uses that file
	/// else creates new one
	class NW_API data_ent : public t_ent<a_ent, a_ent, a_data_rsc>
	{
	protected:
		data_ent(cstr name);
		data_ent(cstr path, cstr name);
	public:
		virtual ~data_ent();
		// --getters
		inline cstr get_name() const		{ return &m_path.fname().string()[0]; }
		inline data_path get_path() const	{ return m_path; }
		// --setters
		// --core_methods
		virtual bit save_file(cstr file_path);
		virtual bit load_file(cstr file_path);
		// --operators
	private:
		data_path m_path;
	};
}
#endif // NW_DATA_ENTITY_H