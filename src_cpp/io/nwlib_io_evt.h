#ifndef NWLIB_IO_EVENT_H
#define NWLIB_IO_EVENT_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "std/nwlib_std_str.h"
#include "nwlib_io_const.h"
namespace NWLIB
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
		v1b is_handled;
		etype type;
	public:
		a_event(etype type);
		// --getters
		inline ecat get_category() const		{ return static_cast<ecat>(type); }
		// --predicates
		inline v1b is_in_category(ecat category) const	{ return (type & category); }
	};
	using event_callback = std::function<void(a_event&)>;
}
namespace NWLIB
{
	/// ms_event struct
	struct NW_API ms_event : public a_event
	{
	public:
		mouse_codes code;
		v1f val_x;
		v1f val_y;
	public:
		// mouse_move_event or mouse_scroll_event
		ms_event(etype type, v1f coord_or_scroll_x, v1f coord_or_scroll_y);
		// mouse_buttevent_proc
		ms_event(etype type, mouse_codes button_code, v1f coord_or_scroll_x = 0.0, v1f coord_or_scroll_y = 0.0);
	};
	/// kbd_event struct
	struct NW_API kbd_event : public a_event
	{
	public:
		union {
			keyboard_codes code;
			union { schar nrow; wchar wide; } character;
		};
		v1u nof_repeats;
	public:
		// release_key_event
		kbd_event(etype type, keyboard_codes code_or_char);
		// press_key_event
		kbd_event(etype type, keyboard_codes code_or_char, v1u repeat_count);
	};
	/// wnd_event struct
	struct NW_API wnd_event : public a_event
	{
	public:
		v1u val_x;
		v1u val_y;
	public:
		// window_close_event or window_focus_event
		wnd_event(etype type);
		// window_resize_event
		wnd_event(etype type, v1s width_or_x, v1s height_or_y);
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
#endif	// NW_API
#endif	//NWLIB_IO_EVENT_H