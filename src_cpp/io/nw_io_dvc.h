#ifndef NW_IO_DEVICE_H
#define NW_IO_DEVICE_H
#include "nw_lib_core.hpp"
#if (defined NW_WAPI)
#include "nw_io_evt.h"
namespace NW
{
	/// keyboard_button struct
	struct NW_API keyboard_button
	{
		button_states state = BS_FREE;
		v1u nof_repeats = 0;
		union { schar nrow = ' '; wchar wide; } character;
	};
	/// keyboard_state class
	class NW_API keyboard_state
	{
	public:
		using evt = kbd_event;
		using btn = keyboard_button;
		using codes = keyboard_codes;
	public:
		keyboard_state();
		// --getters
		inline v1u get_repeats(codes code) const		{ return m_buttons[code].nof_repeats; }
		// --predicates
		inline v1b is_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline v1b is_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline v1b is_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline v1b is_pressed(codes code) const			{ return m_buttons[code].state == BS_PRESSED; }
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code) const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& kbd_evt);
	private:
		keyboard_button m_buttons[KBC_COUNT];
	};
}
namespace NW
{
	/// mouse_button struct
	struct NW_API mouse_button
	{
	public:
		button_states state = BS_FREE;
		v1f free_coord_x = 0.0, free_coord_y = 0.0;
		v1f free_delta_x = 0.0, free_delta_y = 0.0;
		v1f held_coord_x = 0.0, held_coord_y = 0.0;
		v1f held_delta_x = 0.0, held_delta_y = 0.0;
	};
	/// mouse_state class
	class NW_API mouse_state
	{
	public:
		using evt = ms_event;
		using btn = mouse_button;
		using codes = mouse_codes;
	public:
		mouse_state();
		// --getters
		inline v1f get_free_coord_x(codes code) const	{ return m_buttons[code].free_coord_x; }
		inline v1f get_free_coord_y(codes code) const	{ return m_buttons[code].free_coord_y; }
		inline v1f get_free_delta_x(codes code) const	{ return m_buttons[code].free_delta_x; }
		inline v1f get_free_delta_y(codes code) const	{ return m_buttons[code].free_delta_y; }
		inline v1f get_held_coord_x(codes code) const	{ return m_buttons[code].held_coord_x; }
		inline v2f get_held_coord(codes code) const		{ return v2f{ m_buttons[code].held_coord_x, m_buttons[code].held_coord_y }; }
		inline v1f get_held_coord_y(codes code) const	{ return m_buttons[code].held_coord_y; }
		inline v1f get_held_delta_x(codes code) const	{ return m_buttons[code].held_delta_x; }
		inline v1f get_held_delta_y(codes code) const	{ return m_buttons[code].held_delta_y; }
		inline v2f get_held_delta(codes code) const		{ return v2f{ m_buttons[code].held_delta_x, m_buttons[code].held_delta_y }; }
		inline v1f get_move_coord_x() const				{ return m_move_coord_x; }
		inline v1f get_move_coord_y() const				{ return m_move_coord_y; }
		inline v2f get_move_coord(codes code) const		{ return v2f{ m_move_coord_x, m_move_coord_y }; }
		inline v2f get_move_delta(codes code) const		{ return v2f{ m_move_delta_x, m_move_delta_y }; }
		inline v1f get_move_delta_x() const				{ return m_move_delta_x; }
		inline v1f get_move_delta_y() const				{ return m_move_delta_y; }
		inline v1f get_scroll_delta_x() const			{ return m_scroll_delta_x; }
		inline v1f get_scroll_delta_y() const			{ return m_scroll_delta_y; }
		// --setters
		void set_cursor_enabled(v1b enable_cursor);
		// --predicates
		inline v1b is_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline v1b is_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline v1b is_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline v1b is_pressed(codes code) const			{ return m_buttons[code].state == BS_PRESSED; }
		inline v1b is_cursor_enabled() const			{ return m_is_cursor_enabled; }
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code)const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& ms_evt);
	private:
		btn m_buttons[MSC_COUNT];
		v1f m_move_coord_x, m_move_coord_y;
		v1f m_move_delta_x, m_move_delta_y;
		v1f m_scroll_delta_x, m_scroll_delta_y;
		v1b m_is_cursor_enabled;
	};
}
#endif	// NW_WAPI
#endif	// NW_IO_DEVICE_H
