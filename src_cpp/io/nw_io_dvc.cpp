#include "nw_lib_pch.hpp"
#include "nw_io_dvc.h"
#if (defined NW_WAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
	keyboard_state::keyboard_state() :
		m_buttons()
	{
	}
	// --core_methods
	void keyboard_state::update()
	{
		for (auto& ibtn : m_buttons) {
			switch (ibtn.state) {
			case BS_FREE:
				ibtn.nof_repeats = 0;
				break;
			case BS_HELD:
				ibtn.nof_repeats += 1;
				break;
			case BS_PRESSED:
				ibtn.nof_repeats = 0;
				ibtn.state = BS_HELD;
				break;
			case BS_RELEASED:
				ibtn.nof_repeats = 0;
				ibtn.state = BS_FREE;
				break;
			}
		}
	}
	void keyboard_state::event_proc(evt& kbd_evt)
	{
		auto& rbtn = m_buttons[kbd_evt.code];
		switch (kbd_evt.type) {
		case EVT_KBD_PRESSED:
			rbtn.state = BS_PRESSED;
			break;
		case EVT_KBD_RELEASED:
			rbtn.state = BS_RELEASED;
			break;
		case EVT_KBD_CHAR:
			rbtn.character.wide = kbd_evt.character.wide;
			rbtn.character.nrow = kbd_evt.character.nrow;
			break;
		}
	}
}
namespace NW
{
	mouse_state::mouse_state() :
		m_buttons(),
		m_move_coord_x(0.0f), m_move_coord_y(0.0f),
		m_move_delta_x(0.0f), m_move_delta_y(0.0f),
		m_scroll_delta_x(0.0f), m_scroll_delta_y(0.0f),
		m_is_cursor_enabled(false)
	{
	}
	// --setters
	void mouse_state::set_cursor_enabled(v1b enable_cursor) {
		m_is_cursor_enabled = enable_cursor;
		if (enable_cursor == true) {
			while (::ShowCursor(TRUE) < 0) { }
			::ReleaseCapture();
			::ClipCursor(NULL);
		}
		if (enable_cursor == false) {
			while (::ShowCursor(FALSE) >= 0) { }
			HWND wnd_handle = ::GetFocus();
			RECT wnd_rect = { 0, 0, 0, 0 };
			::GetWindowRect(wnd_handle, &wnd_rect);
			//::MapWindowPoints(wnd_handle, NULL, reinterpret_cast<POINT*>(&wnd_rect), 2);
			::SetCapture(wnd_handle);
			wnd_rect.left += 10;
			wnd_rect.right -= 10;
			wnd_rect.top += 50;
			wnd_rect.bottom -= 10;
			::ClipCursor(&wnd_rect);
		}
	}
	// --core_methods
	void mouse_state::update()
	{
		m_move_delta_x = 0.0f;
		m_move_delta_y = 0.0f;
		m_scroll_delta_x = 0.0f;
		m_scroll_delta_y = 0.0f;
	}
	void mouse_state::event_proc(evt& ms_evt)
	{
		switch (ms_evt.type) {
		case EVT_MS_MOVE:
			m_move_delta_x = ms_evt.val_x;
			m_move_delta_y = ms_evt.val_y;
			for (auto& ibtn : m_buttons) {
				switch (ibtn.state) {
				case BS_RELEASED:
					ibtn.state = BS_FREE;
					ibtn.free_coord_x = m_move_coord_x;
					ibtn.free_coord_y = m_move_coord_y;
					break;
				case BS_PRESSED:
					ibtn.state = BS_HELD;
					ibtn.held_coord_x = m_move_coord_x;
					ibtn.held_coord_y = m_move_coord_y;
					break;
				}
			}
			break;
		case EVT_MS_COORD:
			m_move_coord_x = ms_evt.val_x;
			m_move_coord_y = ms_evt.val_y;
			for (auto& ibtn : m_buttons) {
				switch (ibtn.state) {
				case BS_FREE:
					ibtn.free_delta_x = ms_evt.val_x;
					ibtn.free_delta_y = ms_evt.val_y;
					break;
				case BS_HELD:
					ibtn.held_delta_x = ms_evt.val_x;
					ibtn.held_delta_y = ms_evt.val_y;
					break;
				case BS_RELEASED:
					ibtn.state = BS_FREE;
					ibtn.held_delta_x = 0.0f;
					ibtn.held_delta_y = 0.0f;
					break;
				case BS_PRESSED:
					ibtn.state = BS_HELD;
					ibtn.free_delta_x = 0.0f;
					ibtn.free_delta_y = 0.0f;
					break;
				}
			}
			break;
		case EVT_MS_SCROLL:
			m_scroll_delta_x += ms_evt.val_x;
			m_scroll_delta_y += ms_evt.val_y;
			break;
		case EVT_MS_PRESSED:
			m_buttons[ms_evt.code].state = BS_PRESSED;
			break;
		case EVT_MS_RELEASED:
			m_buttons[ms_evt.code].state = BS_RELEASED;
			break;
		}
	}
}
#	endif	// WAPI_WIN
#endif	// NW_WAPI