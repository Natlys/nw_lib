#ifndef NW_STD_SINGLETON_H
#define NW_STD_SINGLETON_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_singleton class
	template<class tname>
	class t_singleton
	{
	public:
		using sing_t = t_singleton<tname>;
		using sing_tc = const sing_t;
	protected:
		t_singleton() = default;
		t_singleton(const tname& copy) = delete;
		t_singleton(tname&& copy) = delete;
		t_singleton(const t_singleton& copy) = delete;
		t_singleton(t_singleton&& copy) = delete;
	public:
		virtual ~t_singleton() = default;
		// --getters
		static inline tname& get() { static tname s_single; return s_single; }
		// --operators
		void operator=(const tname& copy) = delete;
		void operator=(tname&& copy) = delete;
		void operator=(const t_singleton& copy) = delete;
		void operator=(t_singleton&& copy) = delete;
	};
}
#endif	// NW_API
#endif	// NW_STD_SINGLETON_H