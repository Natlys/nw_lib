#ifndef NC_LIB_TIME_HPP
#	define NC_LIB_TIME_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
#   	include <chrono>
/* typedefs */
/// timer_type
class nc_timer_t
{
public:
	using timer_t = nc_timer_t;
	using timer_tc = const timer_t;
	using val_t = v1f_t;
	using val_tc = const val_t;
	using clock_t = std::chrono::high_resolution_clock;
	using point_t = std::chrono::time_point<clock_t>;
	using sec_t = std::chrono::duration<val_t, std::ratio<1>>;
	using millisec_t = std::chrono::duration<val_t, std::milli>;
public:
	/* codetor */
	inline nc_timer_t() : m_tp_last(point_t()), m_tp_curr(point_t()), m_curr(NC_ZERO), m_last(NC_ZERO), m_delta(NC_ZERO), m_begin(NC_ZERO) { }
	inline ~nc_timer_t() { }
	/* getters */
	inline val_tc get_curr(val_tc scale = 1.0) const  { return m_curr * scale; }
	inline val_tc get_last(val_tc scale = 1.0) const  { return m_last * scale; }
	inline val_tc get_delta(val_tc scale = 1.0) const { return m_delta * scale; }
	inline val_tc get_begin(val_tc scale = 1.0) const { return m_begin * scale; }
	inline val_tc get_ups(val_tc scale = 1.0) const	  { return 1.0 / m_delta * scale; }
	/* setters */
	inline v1bit_t update() {
		m_tp_curr = clock_t::now();
		m_delta = sec_t(m_tp_curr - m_tp_last).count();
		m_last = m_curr;
		m_curr += m_delta;
		m_tp_last = m_tp_curr;
		return NC_TRUTH;
	}
	/* vetters */
	/* command */
	/* operators */
private:
	point_t m_tp_curr;
	point_t m_tp_last;
	val_t m_curr;
	val_t m_last;
	val_t m_delta;
	val_t m_begin;
};
#	endif	/* NC_API */
/* end_of_file */
#endif /* NC_LIB_TIME_HPP */