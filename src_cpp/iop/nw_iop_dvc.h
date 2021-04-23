#ifndef NW_IOP_DEVICE_H
#define NW_IOP_DEVICE_H
#include "nw_lib_core.hpp"
#if (defined NW_WAPI)
#	include "nw_iop_evt.h"
namespace NW
{
	/// keyboard_state class
	class NW_API iop_keybod_t
	{
	public:
		using event_t = iop_event_kbd;
		using event_tc = const event_t;
		using button_t = event_t::button_t;
		using button_tc = event_t::button_tc;
		using code_t = button_t::code_t;
		using code_tc = button_tc::code_tc;
	public:
		iop_keybod_t();
		// --getters
		inline button_t& get_button(code_tc code)        { return m_buttons[code]; }
		inline button_tc& get_button(code_tc code) const { return m_buttons[code]; }
		inline cv1u get_repeats(code_tc code) const      { return m_buttons[code].m_nof_repeats; }
		// --setters
		v1nil set_enabled(v1bit enable);
		// --predicates
		inline v1bit is_enabled() const { return m_is_enabled; }
		inline v1bit is_free(code_tc code) const { return m_buttons[code].m_state == NW_BUTTON_FREE; }
		inline v1bit is_held(code_tc code) const { return m_buttons[code].m_state == NW_BUTTON_HELD; }
		inline v1bit is_raise(code_t code) const { return m_buttons[code].m_state == NW_BUTTON_RAISE; }
		inline v1bit is_press(code_t code) const { return m_buttons[code].m_state == NW_BUTTON_PRESS; }
		// --operators
		inline button_t& operator[](code_tc code)        { return get_button(code); }
		inline button_tc& operator[](code_tc code) const { return get_button(code); }
		// --core_methods
		v1nil update();
		v1nil event_proc(event_t& evt);
	private:
		v1bit m_is_enabled;
		button_t m_buttons[NW_KEYCODE_COUNT];
	};
}
namespace NW
{
	/// cursor_type class
	class NW_API iop_cursor_t
	{
	public:
		using event_t = iop_event_cursor_t;
		using event_tc = const event_t;
		using button_t = event_t::button_t;
		using button_tc = event_t::button_tc;
		using code_t = event_t::code_t;
		using code_tc = event_t::code_tc;
	public:
		iop_cursor_t();
		// --getters
		inline button_t& get_button(code_tc code)         { return m_buttons[code]; }
		inline button_tc& get_button(code_tc code) const  { return m_buttons[code]; }
		inline cv1f get_free_coord_x(code_tc code) const  { return m_buttons[code].m_free_coord_x; }
		inline cv1f get_free_coord_y(code_tc code) const  { return m_buttons[code].m_free_coord_y; }
		inline cv2f get_free_coord_xy(code_tc code) const { return { get_free_coord_x(code), get_free_coord_y(code)}; }
		inline cv1f get_free_delta_x(code_tc code) const  { return m_buttons[code].m_free_delta_x; }
		inline cv1f get_free_delta_y(code_tc code) const  { return m_buttons[code].m_free_delta_y; }
		inline cv1f get_held_coord_x(code_tc code) const  { return m_buttons[code].m_held_coord_x; }
		inline cv1f get_held_coord_y(code_tc code) const  { return m_buttons[code].m_held_coord_y; }
		inline cv2f get_held_coord_xy(code_tc code) const { return { get_held_coord_x(code), get_held_coord_y(code) }; }
		inline cv1f get_held_delta_x(code_tc code) const  { return m_buttons[code].m_held_delta_x; }
		inline cv1f get_held_delta_y(code_tc code) const  { return m_buttons[code].m_held_delta_y; }
		inline cv2f get_held_delta_xy(code_tc code) const { return { get_held_delta_x(code), get_held_delta_y(code) }; }
		inline cv1f get_move_coord_x() const  { return m_move_coord_x; }
		inline cv1f get_move_coord_y() const  { return m_move_coord_y; }
		inline cv2f get_move_coord_xy() const { return cv2f{ m_move_coord_x, m_move_coord_y }; }
		inline cv1f get_move_delta_x() const  { return m_move_delta_x; }
		inline cv1f get_move_delta_y() const  { return m_move_delta_y; }
		inline cv2f get_move_delta_xy() const { return cv2f{ m_move_delta_x, m_move_delta_y }; }
		inline cv1f get_scroll_delta_x() const  { return m_scroll_delta_x; }
		inline cv1f get_scroll_delta_y() const  { return m_scroll_delta_y; }
		inline cv2f get_scroll_delta_xy() const { return cv2f{ m_scroll_delta_x, m_scroll_delta_y }; }
		// --setters
		v1nil set_enabled(v1bit enable);
		// --predicates
		inline v1bit is_enabled() const { return m_is_enabled; }
		inline v1bit is_free(code_tc code) const { return m_buttons[code].m_state == NW_BUTTON_FREE; }
		inline v1bit is_held(code_tc code) const { return m_buttons[code].m_state == NW_BUTTON_HELD; }
		inline v1bit is_raise(code_tc code) const { return m_buttons[code].m_state== NW_BUTTON_RAISE; }
		inline v1bit is_press(code_tc code) const { return m_buttons[code].m_state == NW_BUTTON_PRESS; }
		// --operators
		inline button_t& operator[](code_tc code)        { return get_button(code); }
		inline button_tc& operator[](code_tc code) const { return get_button(code); }
		// --core_methods
		v1nil update();
		v1nil event_proc(event_t& evt);
	private:
		v1bit m_is_enabled;
		button_t m_buttons[NW_CURCODE_COUNT];
		v1f m_move_coord_x, m_move_coord_y;
		v1f m_move_delta_x, m_move_delta_y;
		v1f m_scroll_delta_x, m_scroll_delta_y;
	};
}
#endif	// NW_WAPI
#endif	// NW_IOP_DEVICE_H
