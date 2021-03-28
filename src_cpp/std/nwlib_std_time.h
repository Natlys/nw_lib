#ifndef NWLIB_STD_TIME_H
#define NWLIB_STD_TIME_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	/// time_state class
	class NW_API time_state
	{
		using clock = std::chrono::high_resolution_clock;
		using time_point = std::chrono::time_point<clock>;
		using sec = std::chrono::duration<v1f, std::ratio<1>>;
		using millisec = std::chrono::duration<v1f, std::milli>;
	public:
		time_state();
		// --getters
		inline v1f get_curr(v1f scale = 1.0) const	{ return m_curr * scale; }
		inline v1f get_last(v1f scale = 1.0) const	{ return m_last * scale; }
		inline v1f get_delta(v1f scale = 1.0) const	{ return m_delta * scale; }
		inline v1f get_begin(v1f scale = 1.0) const	{ return m_begin * scale; }
		inline v1f get_ups(v1f scale = 1.0) const	{ return 1.0 / m_delta * scale; }
		// --setters
		void update();
		// --core_methods
	private:
		time_point m_tp_curr;
		time_point m_tp_last;
		v1f m_curr;
		v1f m_last;
		v1f m_delta;
		v1f m_begin;
	};
}
#endif	// NW_API
#endif // NWLIB_STD_TIME_H