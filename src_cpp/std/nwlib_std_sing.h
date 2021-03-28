#ifndef NWLIB_STD_SINGLETON_H
#define NWLIB_STD_SINGLETON_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	/// templated singleton class
	template<class type>
	class NW_API t_singleton
	{
	protected:
		t_singleton() = default;
		t_singleton(const t_singleton& cpy) = delete;
	public:
		virtual ~t_singleton() = default;
		// --getters
		static inline type& get()	{ static type s_single; return s_single; }
		// --operators
		void operator=(const t_singleton& cpy) = delete;
	};
}
#endif	// NW_API
#endif	// NWLIB_STD_SINGLETON_H