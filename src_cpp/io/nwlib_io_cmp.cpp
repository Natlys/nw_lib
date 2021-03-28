#include "nwlib_pch.hpp"
#include "nwlib_io_cmp.h"
namespace NWLIB
{
	a_io_cmp::a_io_cmp() { }
	a_io_cmp::~a_io_cmp() { }
	// --setters
	// --operators
	stm_out& operator<<(stm_out& stm, const a_io_cmp& cmp) { return cmp.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_io_cmp& cmp) { return cmp.operator>>(stm); }
	// --==<core_methods>==--
	// --==</core_methods>==--
}