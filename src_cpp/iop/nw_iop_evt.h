#ifndef NW_IOP_EVENT_H
#define NW_IOP_EVENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "std/nw_std_func.h"
#	include "num/nw_num_vec.h"
#	include "nw_iop_code.h"
#	ifndef NW_IOP_EVDEF_H
#	define NW_IOP_EVDEF_H
	// event types
	// // cursor
#	define NW_EVTYPE_CURSOR_MOVED   1 << 1
#	define NW_EVTYPE_CURSOR_COORD   1 << 2
#	define NW_EVTYPE_CURSOR_SCROL   1 << 3
#	define NW_EVTYPE_CURSOR_RAISE   1 << 4
#	define NW_EVTYPE_CURSOR_PRESS   1 << 5
	// // keyboard
#	define NW_EVTYPE_KEYBOD_RAISE   1 << 8
#	define NW_EVTYPE_KEYBOD_PRESS   1 << 9
#	define NW_EVTYPE_KEYBOD_CHART   1 << 10
	// // window
#	define NW_EVTYPE_WINDOW_CLOSE   1 << 12
#	define NW_EVTYPE_WINDOW_FOCUS   1 << 15
#	define NW_EVTYPE_WINDOW_SIZED   1 << 13
#	define NW_EVTYPE_WINDOW_MOVED   1 << 14
#	define NW_EVTYPE_WINDOW_ACTIV   1 << 16
	// // application
#	define NW_EVTYPE_APPLIC_DROPF   1 << 20
	// event categories
#	define NW_EVSORT_CURSOR    NW_NULL \
	| NW_EVTYPE_CURSOR_MOVED | NW_EVTYPE_CURSOR_COORD | NW_EVTYPE_CURSOR_SCROL \
	| NW_EVTYPE_CURSOR_PRESS | NW_EVTYPE_CURSOR_RAISE \
	// // keyboard
#	define NW_EVSORT_KEYBOD    NW_NULL \
	| NW_EVTYPE_KEYBOD_PRESS | NW_EVTYPE_KEYBOD_RAISE | NW_EVTYPE_KEYBOD_CHART \
	// // window
#	define NW_EVSORT_WINDOW    NW_NULL \
	| NW_EVTYPE_WINDOW_CLOSE | NW_EVTYPE_WINDOW_SIZED | NW_EVTYPE_WINDOW_MOVED \
	| NW_EVTYPE_WINDOW_FOCUS | NW_EVTYPE_WINDOW_ACTIV
	// // application
#	define NW_EVSORT_APPLIC    NW_NULL \
	| NW_EVTYPE_APPLIC_DROPF
#	endif	// NW_IOP_EVDEF_H
namespace NW
{
	/// abstract event struct
	/// interface:
	/// -> create in the event_proc callback function -> set the event data;
	/// -> dispatch to different listeners;
	/// description:
	struct NW_API iop_event_t
	{
	public:
		using type_t = v1u64;
		using type_tc = const type_t;
		using sort_t = v1u64;
		using sort_tc = const sort_t;
	public:
		iop_event_t(type_tc type);
		// --getters
		inline type_tc get_type() const { return m_type; }
		inline sort_tc get_sort() const { return m_type; }
		// --setters
		v1nil set_handled(v1bit is_handled);
		// --predicates
		inline v1bit has_type(type_tc type) const { return (m_type & type); }
		inline v1bit has_sort(sort_tc sort) const { return (m_type & sort); }
		inline v1bit is_handled() const { return m_is_handled; }
		// --operators
		template<class tevent>
		operator tevent& ()             { return *static_cast<tevent*>(this); }
		template<class tevent>
		operator const tevent& () const { return *static_cast<const tevent*>(this); }
	protected:
		type_tc m_type;
		v1bit m_is_handled;
	};
	using event_callback = std::function<void(iop_event_t&)>;
}
namespace NW
{
	/// iop_event_cursor_t struct
	struct NW_API iop_event_cursor_t : public iop_event_t
	{
	public:
		using button_t = iop_button_crs;
		using button_tc = const button_t;
		using code_t = button_t::code_t;
		using code_tc = button_t::code_tc;
	public:
		// cursor_moved_event or cursor_scroll_event
		iop_event_cursor_t(type_tc type, cv1s coord_or_scroll_x, cv1s coord_or_scroll_y);
		// iop_button_crs_event
		iop_event_cursor_t(type_tc type, code_tc code, cv1s coord_or_scroll_x = NW_NULL, cv1s coord_or_scroll_y = NW_NULL);
		// --getters
		inline code_tc get_code() const { return m_code; }
		inline cv1s get_val_x(cv1s scale = 1) const  { return v1s{ m_val_x } * scale; }
		inline cv1s get_val_y(cv1s scale = 1) const  { return v1s{ m_val_y } * scale; }
		inline cv2s get_val_xy(cv1s scale = 1) const { return v2s{ m_val_x, m_val_y } * scale; }
		// --predicates
		inline v1bit has_code(code_tc code) const { return m_code == code; }
		inline v1bit has_val_x(cv1u val_x) const { return m_val_x == val_x; }
		inline v1bit has_val_y(cv1u val_y) const { return m_val_y == val_y; }
		inline v1bit has_val_xy(cv1u val_x, cv1u val_y) const { return m_val_x == val_x && m_val_y == val_y; }
	private:
		code_tc m_code;
		cv1s m_val_x;
		cv1s m_val_y;
	};
	/// keboard_event struct
	struct NW_API iop_event_kbd : public iop_event_t
	{
	public:
		using button_t = iop_button_kbd;
		using button_tc = const button_t;
		using code_t = button_t::code_t;
		using code_tc = button_t::code_tc;
	public:
		// raise_key_event
		iop_event_kbd(type_tc type, code_tc code_or_char);
		// press_key_event
		iop_event_kbd(type_tc type, code_tc code_or_char, cv1u repeat_count);
		// --getters
		inline code_tc get_code() const   { return m_code; }
		inline nwchar_tc get_char() const { return m_char; }
		inline schar_t get_schar() const { return m_char.snar; }
		inline uchar_t get_uchar() const { return m_char.unar; }
		inline wchar_t get_wchar() const { return m_char.wide; }
		// --predicates
	private:
		union {
			code_tc m_code;
			nwchar_tc m_char;
		};
		cv1u m_nof_repeats;
	};
	/// iop_event_wnd_t struct
	struct NW_API iop_event_wnd_t : public iop_event_t
	{
	public:
		// close or focus event
		iop_event_wnd_t(type_tc type, v1bit is_focused_or_closed);
		// resize event
		iop_event_wnd_t(type_tc type, cv1s width_or_x, cv1s height_or_y);
		// --getters
		inline cv1u get_val_x(cv1u scale = 1) const { return v1u{ m_val_x } * scale; }
		inline cv1u get_val_y(cv1u scale = 1) const { return v1u{ m_val_y } * scale; }
		inline cv2u get_val_xy(cv1u scale = 1) const { return cv2u{ m_val_x, m_val_y } * scale; }
		// --predicates
		inline v1bit is_activ() const { return has_type(NW_EVTYPE_WINDOW_ACTIV) && m_flag; }
		inline v1bit is_focus() const { return has_type(NW_EVTYPE_WINDOW_FOCUS) && m_flag; }
		inline v1bit is_close() const { return has_type(NW_EVTYPE_WINDOW_CLOSE) && m_flag; }
	private:
		v1u m_val_x;
		v1u m_val_y;
		v1bit m_flag;
	};
	/// application_event struct
	struct NW_API iop_event_app_t : public iop_event_t
	{
	public:
		iop_event_app_t(type_tc type, cstr_t description);
		// --getters
		inline cstr_t get_desc() const { return &m_desc[0]; }
	private:
		cstr_t m_desc;
	};
}
#endif	// NW_API
#endif	//NW_IOP_EVENT_H
