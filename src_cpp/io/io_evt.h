#ifndef NWL_EVENT_H
#define NWL_EVENT_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
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
		using ecat = event_categories;
		using etype = event_types;
	public:
		bit is_handled;
		etype type;
	public:
		a_event(etype type);
		// --getters
		inline ecat get_category() const		{ return static_cast<ecat>(type); }
		// --predicates
		inline bit is_in_category(ecat category) const	{ return (type & category); }
	};
	using event_callback = std::function<void(a_event&)>;
}
namespace NW
{
	/// ms_event struct
	struct NW_API ms_event : public a_event
	{
	public:
		mouse_codes code = MSC_0;
		f64 val_x = 0.0, val_y = 0.0;
	public:
		// mouse_move_event or mouse_scroll_event
		ms_event(etype type, f32 coord_or_scroll_x, f32 coord_or_scroll_y);
		// mouse_buttevent_proc
		ms_event(etype type, mouse_codes button_code, f32 coord_or_scroll_x = 0.0, f32 coord_or_scroll_y = 0.0);
	};
	/// kbd_event struct
	struct NW_API kbd_event : public a_event
	{
	public:
		union {
			keyboard_codes code = KBC_SPACE;
			union { schar nrow; wchar wide; } character;
		};
		ui32 nof_repeats = 0;
	public:
		// release_key_event
		kbd_event(etype type, keyboard_codes code_or_char);
		// press_key_event
		kbd_event(etype type, keyboard_codes code_or_char, ui32 repeat_count);
	};
	/// wnd_event struct
	struct NW_API wnd_event : public a_event
	{
	public:
		si32 val_x = 0, val_y = 0;
	public:
		// window_close_event or window_focus_event
		wnd_event(etype type);
		// window_resize_event
		wnd_event(etype type, si32 width_or_x, si32 height_or_y);
	};
	/// application event
	struct NW_API app_event : public a_event
	{
	public:
		cstr desc;
	public:
		app_event(etype type, cstr description);
	};
}
#endif	//NWL_EVENT_H