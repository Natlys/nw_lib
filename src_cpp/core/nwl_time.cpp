#include <nwl_pch.hpp>
#include "nwl_time.h"
namespace NW
{
	time_state::time_state() :
		m_tp_last(clock::now()), m_tp_curr(clock::now()),
		m_curr(0.0), m_last(0.0), m_delta(0.0),
		m_begin(0.0)
	{
		m_begin = sec(m_tp_curr - m_tp_last).count();
	}
	// --core_methods
	void time_state::update() {
		m_tp_curr = clock::now();
		m_delta = sec(m_tp_curr - m_tp_last).count();
		m_last = m_curr;
		m_curr += m_delta;
		m_tp_last = m_tp_curr;
	}
}