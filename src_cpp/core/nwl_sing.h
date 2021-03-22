#ifndef NWL_SINGLETON_H
#define NWL_SINGLETON_H
#include <nwl_core.hpp>
namespace NW
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
#endif	// NWL_SINGLETON_H