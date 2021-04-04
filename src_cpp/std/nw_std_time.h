#ifndef NW_STD_TIME_H
#define NW_STD_TIME_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// time_state class
	class time_state
	{
		using clock = std::chrono::high_resolution_clock;
		using time_point = std::chrono::time_point<clock>;
		using sec = std::chrono::duration<v1f, std::ratio<1>>;
		using millisec = std::chrono::duration<v1f, std::milli>;
	public:
		time_state() : m_tp_last(clock::now()), m_tp_curr(clock::now()),
			m_curr(0.0), m_last(0.0), m_delta(0.0),
			m_begin(0.0) { }
		// --getters
		inline v1f get_curr(v1f scale = 1.0) const	{ return m_curr * scale; }
		inline v1f get_last(v1f scale = 1.0) const	{ return m_last * scale; }
		inline v1f get_delta(v1f scale = 1.0) const	{ return m_delta * scale; }
		inline v1f get_begin(v1f scale = 1.0) const	{ return m_begin * scale; }
		inline v1f get_ups(v1f scale = 1.0) const	{ return 1.0 / m_delta * scale; }
		// --setters
		inline void update() {
			m_tp_curr = clock::now();
			m_delta = sec(m_tp_curr - m_tp_last).count();
			m_last = m_curr;
			m_curr += m_delta;
			m_tp_last = m_tp_curr;
		}
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
#endif // NW_STD_TIME_H