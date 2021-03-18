#include <nwl_pch.hpp>
#include "io_evt.h"
namespace NW
{
	a_event::a_event(event_types type) :
		type(type), is_handled(false)
	{
	}
}
namespace NW
{
	mouse_event::mouse_event(event_types type, f32 coord_or_scroll_x, f32 coord_or_scroll_y) :
		a_event(type), val_x(coord_or_scroll_x), val_y(coord_or_scroll_y)
	{
	}
	mouse_event::mouse_event(event_types type, mouse_codes code, f32 coord_or_scroll_x, f32 coord_or_scroll_y) :
		a_event(type), code(button_code), val_x(coord_or_scroll_x), val_y(coord_or_scroll_y)
	{
	}
}
namespace NW
{
	keyboard_event::keyboard_event(event_types event_type, keyboard_codes code_or_char) :
		a_event(type), code(code_or_char), nof_repeats(0)
	{
	}
	keyboard_event::keyboard_event(event_types type, keyboard_codes code_or_char, ui32 repeat_count) :
		a_event(type), code(code_or_char), nof_repeats(repeat_count)
	{
	}
}
namespace NW
{
	window_event::window_event(event_types type) :
		a_event(type)
	{
	}
	window_event::window_event(event_types type, si32 width_or_x, si32 height_or_y) :
		a_event(type), val_x(width_or_x), val_y(height_or_y)
	{
	}
}