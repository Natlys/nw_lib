#ifndef NW_STD_LIST_H
#define NW_STD_LIST_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
#	if (NW_FALSE)
	template <typename tval>
	class list2_t
	{
	public:
		using list2_tc = const list2_t<tval>;
		using list_t = std::list<tval>;
		using list_tc = const list_t;
		using val_t = tval;
		using val_tc = const val_t;
	public:
		inline list2_t() : m_list(list_t()) { }
		inline list2_t(list_t& copy) : m_list(list_t()) { }
		inline ~list2_t() { }
		// --getters
		// --setters
		// --predicates
		// --operators
		// --core_methods
	private:
		list_t m_list;
	};
	template <typename tval>
	using list2_tc = const list2_t<tval>;
#	endif
	template <typename tval>
	using list2_t = std::list<tval>;
	template <typename tval>
	using list2_tc = const list2_t<tval>;
}
#endif	// NW_API
#endif // NW_STD_LIST_H