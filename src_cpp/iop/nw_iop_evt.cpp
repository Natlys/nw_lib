#include "nw_lib_pch.hpp"
#include "nw_iop_evt.h"
#if (defined NW_API)
namespace NW
{
	iop_event_t::iop_event_t(type_tc type) :
		m_type(type), m_is_handled(NW_FALSE)
	{
	}
	v1nil iop_event_t::set_handled(v1bit is_handled) {
		m_is_handled = is_handled;
	}
}
namespace NW
{
	iop_event_cursor_t::iop_event_cursor_t(type_tc type, cv1s coord_or_scroll_x, cv1s coord_or_scroll_y) :
		iop_event_t(type),
		m_val_x(coord_or_scroll_x), m_val_y(coord_or_scroll_y),
		m_code(NW_NULL)
	{
	}
	iop_event_cursor_t::iop_event_cursor_t(type_tc type, code_tc code, cv1s coord_or_scroll_x, cv1s coord_or_scroll_y) :
		iop_event_t(type),
		m_code(code), m_val_x(coord_or_scroll_x), m_val_y(coord_or_scroll_y)
	{
	}
}
namespace NW
{
	iop_event_kbd::iop_event_kbd(type_tc type, code_tc code_or_char) :
		iop_event_t(type),
		m_code(code_or_char), m_nof_repeats(NW_NULL)
	{
	}
	iop_event_kbd::iop_event_kbd(type_tc type, code_tc code_or_char, cv1u repeat_count) :
		iop_event_t(type),
		m_code(code_or_char), m_nof_repeats(repeat_count)
	{
	}
}
namespace NW
{
	iop_event_wnd_t::iop_event_wnd_t(type_tc type, v1bit is_focused_or_closed) :
		iop_event_t(type),
		m_val_x(NW_NULL), m_val_y(NW_NULL),
		m_flag(is_focused_or_closed)
	{
	}
	iop_event_wnd_t::iop_event_wnd_t(type_tc type, cv1s width_or_x, cv1s height_or_y) :
		iop_event_t(type),
		m_val_x(width_or_x), m_val_y(height_or_y),
		m_flag(NW_NULL)
	{
	}
}
namespace NW
{
	iop_event_app_t::iop_event_app_t(type_tc type, cstr_t description) :
		iop_event_t(type),
		m_desc(description)
	{
	}
}
#endif	// NW_API