#include <nwl_pch.hpp>
#include "io_evt.h"
namespace NW
{
	a_event::a_event(etype type) :
		type(type), is_handled(false)
	{
	}
}
namespace NW
{
	ms_event::ms_event(etype type, v1f coord_or_scroll_x, v1f coord_or_scroll_y) :
		a_event(type),
		val_x(coord_or_scroll_x), val_y(coord_or_scroll_y),
		code(MSC_0)
	{
	}
	ms_event::ms_event(etype type, mouse_codes code, v1f coord_or_scroll_x, v1f coord_or_scroll_y) :
		a_event(type),
		code(code), val_x(coord_or_scroll_x), val_y(coord_or_scroll_y)
	{
	}
}
namespace NW
{
	kbd_event::kbd_event(etype type, keyboard_codes code_or_char) :
		a_event(type),
		code(code_or_char), nof_repeats(0)
	{
	}
	kbd_event::kbd_event(etype type, keyboard_codes code_or_char, v1ui repeat_count) :
		a_event(type),
		code(code_or_char), nof_repeats(repeat_count)
	{
	}
}
namespace NW
{
	wnd_event::wnd_event(etype type) :
		a_event(type),
		val_x(0), val_y(0)
	{
	}
	wnd_event::wnd_event(etype type, v1si width_or_x, v1si height_or_y) :
		a_event(type),
		val_x(width_or_x), val_y(height_or_y)
	{
	}
}
namespace NW
{
	app_event::app_event(etype type, cstr description) :
		a_event(type),
		desc(description)
	{
	}
}