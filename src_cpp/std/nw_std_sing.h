#ifndef NW_STD_SINGLETON_H
#define NW_STD_SINGLETON_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// singleton template class
	template<class type>
	class singleton_t
	{
	protected:
		singleton_t() = default;
		singleton_t(const singleton_t& cpy) = delete;
	public:
		virtual ~singleton_t() = default;
		// --getters
		static inline type& get()	{ static type s_single; return s_single; }
		// --operators
		void operator=(const singleton_t& cpy) = delete;
	};
}
#endif	// NW_API
#endif	// NW_STD_SINGLETON_H