#ifndef NWL_DATA_ENTITY_H
#define NWL_DATA_ENTITY_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <ecs/ecs_ent.h>
#include "data_cmp.h"
#include "data_path.h"
namespace NW
{
	/// data_entity class
	/// description:
	/// --handles some data resource
	/// --requires a file path
	/// if something was found - uses that file
	/// else creates new one
	class NW_API a_data_ent : public data_path
	{
	public:
		a_data_ent(cstr fpath);
		virtual ~a_data_ent();
		// --getters
		// --setters
		// --predicates
		// --core_methods
		virtual bit save(ui8 idx) = 0;
		virtual bit load(ui8 idx) = 0;
	protected:
	};
}
#endif // NW_DATA_ENTITY_H