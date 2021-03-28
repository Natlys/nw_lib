#ifndef NWLIB_STD_TREE_H
#define NWLIB_STD_TREE_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	class NW_API a_tree_node
	{
	protected:
		a_tree_node();
	public:
		virtual ~a_tree_node();
	protected:
	};
}
#endif	// NW_API
#endif // NWLIB_STD_TREE_H