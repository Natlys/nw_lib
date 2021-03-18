#ifndef NWL_TIME_H
#define NWL_TIME_H
#include <nwl_core.hpp>
namespace NW
{
	/// time_state class
	class NW_API time_state
	{
		using clock = std::chrono::high_resolution_clock;
		using time_point = std::chrono::time_point<clock>;
		using sec = std::chrono::duration<f32, std::ratio<1>>;
		using millisec = std::chrono::duration<f32, std::milli>;
	public:
		time_state();
		// --getters
		inline f32 get_curr(f32 scale = 1.0) const	{ return m_curr * scale; }
		inline f32 get_last(f32 scale = 1.0) const	{ return m_last * scale; }
		inline f32 get_delta(f32 scale = 1.0) const	{ return m_delta * scale; }
		inline f32 get_begin(f32 scale = 1.0) const	{ return m_begin * scale; }
		inline f32 get_ups(f32 scale = 1.0) const	{ return 1.0 / m_delta * scale; }
		// --setters
		void update();
		// --core_methods
	private:
		time_point m_tp_curr;
		time_point m_tp_last;
		f32 m_curr;
		f32 m_last;
		f32 m_delta;
		f32 m_begin;
	};
}
#endif // NWL_TIME_H