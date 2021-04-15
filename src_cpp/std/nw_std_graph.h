#ifndef NW_STD_GRAPH_H
#define NW_STD_GRAPH_H
#include "nw_lib_core.hpp"
#if(defined NW_API)
#include "nw_std_cont.h"
namespace NW
{
	/// graph_node typed class
	template<typename tnode, typename tkey = dstr>
	class NW_API t_graph_cmp
	{
	public:
		using node_t = tnode;
		using node_tc = const node_t;
		using key_t = tkey;
		using key_tc = const key_t;
	public:
		t_graph_cmp() {}
		virtual ~t_graph_cmp() = default;
		// --getters
		// --setters
		// --operators
	protected:
	};
}
#endif	// NW_API
#endif	// NW_STD_GRAPH_H