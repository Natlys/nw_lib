#ifndef NWL_EVENT_H
#define NWL_EVENT_H
#include <nwl_core.hpp>
#include "io_switch.h"
namespace NW
{
	/// abstract event struct
	/// interface:
	/// -> create in the event_proc callback function -> set the event data
	/// -> dispatch to different listeners;
	/// description:
	struct NW_API a_event
	{
	public:
		bit is_handled = false;
		event_types type = EVT_DEFAULT;
	public:
		a_event(event_types type);
		// --predicates
		inline bit is_in_category(event_categories category) { return (type & category); }
	};
	using event_callback = std::function<void(a_event&)>;
}
namespace NW
{
	/// mouse_event struct
	struct NW_API mouse_event : public a_event
	{
	public:
		mouse_codes code = MSC_0;
		f64 val_x = 0.0, val_y = 0.0;
	public:
		// mouse_move_event or mouse_scroll_event
		mouse_event(event_types type, f32 coord_or_scroll_x, f32 coord_or_scroll_y);
		// mouse_buttevent_proc
		mouse_event(event_types type, mouse_codes button_code, f32 coord_or_scroll_x = 0.0, f32 coord_or_scroll_y = 0.0);
	};
	/// keyboard_event struct
	struct NW_API keyboard_event : public a_event
	{
	public:
		union {
			keyboard_codes code = KBC_SPACE;
			union { schar nrow; wchar wide; } character;
		};
		ui32 nof_repeats = 0;
	public:
		// release_key_event
		keyboard_event(event_types type, keyboard_codes code_or_char);
		// press_key_event
		keyboard_event(event_types type, keyboard_codes code_or_char, ui32 repeat_count);
	};
	/// window_event struct
	struct NW_API window_event : public a_event
	{
	public:
		si32 val_x = 0, val_y = 0;
	public:
		// window_close_event or window_focus_event
		window_event(event_types type);
		// window_resize_event
		window_event(event_types type, si32 width_or_x, si32 height_or_y);
	};
}
#endif	//NWL_EVENT_H