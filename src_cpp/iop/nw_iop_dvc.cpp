#include "nw_lib_pch.hpp"
#include "nw_iop_dvc.h"
#if (defined NW_WAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
	iop_keybod_t::iop_keybod_t() :
		m_buttons()
	{
	}
	iop_keybod_t::~iop_keybod_t() { }
	// --setters
	iop_keybod_t::kbd_t& iop_keybod_t::set_enabled(v1bit enable)
	{
		if (is_enabled() == enable) { return *this; }
		m_is_enabled = enable;
		if (enable) {
			//
		}
		else {
			//
		}
		return *this;
	}
	// --==<core_methods>==--
	v1nil iop_keybod_t::update()
	{
		for (auto& ibtn : m_buttons) {
			switch (ibtn.m_state) {
			case NW_BUTTON_FREE:
				ibtn.m_nof_repeats = 0;
				break;
			case NW_BUTTON_HELD:
				ibtn.m_nof_repeats += 1;
				break;
			case NW_BUTTON_PRESS:
				ibtn.m_nof_repeats = 0;
				ibtn.m_state = NW_BUTTON_HELD;
				break;
			case NW_BUTTON_RAISE:
				ibtn.m_nof_repeats = 0;
				ibtn.m_state = NW_BUTTON_FREE;
				break;
			}
		}
	}
	v1nil iop_keybod_t::event_proc(event_t& evt)
	{
		switch (evt.get_type()) {
		case NW_EVTYPE_KEYBOD_PRESS:
			m_buttons[evt.get_code()].m_state = NW_BUTTON_PRESS;
			break;
		case NW_EVTYPE_KEYBOD_RAISE:
			m_buttons[evt.get_code()].m_state = NW_BUTTON_RAISE;
			break;
		case NW_EVTYPE_KEYBOD_CHART:
			m_buttons[evt.get_code()].m_state = NW_BUTTON_PRESS;
			break;
		}
	}
	// --==</core_methods>==--
}
namespace NW
{
	iop_cursor_t::iop_cursor_t() :
		m_bounds{ 0, 0, 0, 0 },
		m_buttons(),
		m_is_enabled(NW_FALSE),
		m_move_coord_x(NW_NULL), m_move_coord_y(NW_NULL),
		m_move_delta_x(NW_NULL), m_move_delta_y(NW_NULL),
		m_scroll_delta_x(NW_NULL), m_scroll_delta_y(NW_NULL)
	{
	}
	iop_cursor_t::~iop_cursor_t() { }
	// --setters
	iop_cursor_t::crs_t& iop_cursor_t::set_enabled(v1bit enable) {
		if (is_enabled() == enable) { return *this; }
		m_is_enabled = enable;
		if (enable) {
			while (::ShowCursor(NW_TRUE) < 0) { }
			::ReleaseCapture();
			//::ClipCursor(NW_NULL);
		}
		else {
			while (::ShowCursor(NW_FALSE) >= 0) { }
			::HWND wnd_handle = ::GetFocus();
			//::RECT clip_rect = { 0, 0, 0, 0 };
			//::GetWindowRect(wnd_handle, &clip_rect);
			//::MapWindowPoints(wnd_handle, NULL, reinterpret_cast<POINT*>(&clip_rect), 2);
			::SetCapture(wnd_handle);
			//clip_rect.left += 10;
			//clip_rect.right -= 10;
			//clip_rect.top += 50;
			//clip_rect.bottom -= 10;
			//::ClipCursor(&clip_rect);
		}
		return *this;
	}
	iop_cursor_t::crs_t& iop_cursor_t::set_bounds(cv4s& bounds) {
		m_bounds = bounds;
		if (bounds == 0) { ::ClipCursor(NW_NULL); }
		else { RECT clip_rect = { m_bounds[0], m_bounds[1], m_bounds[2], m_bounds[3] }; ::ClipCursor(&clip_rect); }
		return *this;
	}
	// --==<core_methods>==--
	v1nil iop_cursor_t::update()
	{
		m_move_delta_x = NW_NULL;
		m_move_delta_y = NW_NULL;
		m_scroll_delta_x = NW_NULL;
		m_scroll_delta_y = NW_NULL;
	}
	v1nil iop_cursor_t::event_proc(event_t& evt)
	{
		switch (evt.get_type()) {
		case NW_EVTYPE_CURSOR_MOVED:
			m_move_delta_x = evt.get_val_x();
			m_move_delta_y = evt.get_val_y();
			for (auto& ibtn : m_buttons) {
				switch (ibtn.m_state) {
				case NW_BUTTON_RAISE:
					ibtn.m_state = NW_BUTTON_FREE;
					ibtn.m_free_coord_x = m_move_coord_x;
					ibtn.m_free_coord_y = m_move_coord_y;
					break;
				case NW_BUTTON_PRESS:
					ibtn.m_state = NW_BUTTON_HELD;
					ibtn.m_held_coord_x = m_move_coord_x;
					ibtn.m_held_coord_y = m_move_coord_y;
					break;
				}
			}
			break;
		case NW_EVTYPE_CURSOR_COORD:
			m_move_coord_x = evt.get_val_x();
			m_move_coord_y = evt.get_val_y();
			for (auto& ibtn : m_buttons) {
				switch (ibtn.m_state) {
				case NW_BUTTON_FREE:
					ibtn.m_free_delta_x = evt.get_val_x();
					ibtn.m_free_delta_y = evt.get_val_y();
					break;
				case NW_BUTTON_HELD:
					ibtn.m_held_delta_x = evt.get_val_x();
					ibtn.m_held_delta_y = evt.get_val_y();
					break;
				case NW_BUTTON_RAISE:
					ibtn.m_state = NW_BUTTON_FREE;
					ibtn.m_held_delta_x = NW_NULL;
					ibtn.m_held_delta_y = NW_NULL;
					break;
				case NW_BUTTON_PRESS:
					ibtn.m_state = NW_BUTTON_HELD;
					ibtn.m_free_delta_x = NW_NULL;
					ibtn.m_free_delta_y = NW_NULL;
					break;
				}
			}
			break;
		case NW_EVTYPE_CURSOR_SCROL:
			m_scroll_delta_x += evt.get_val_x();
			m_scroll_delta_y += evt.get_val_y();
			break;
		case NW_EVTYPE_CURSOR_PRESS:
			m_buttons[evt.get_code()].m_state = NW_BUTTON_PRESS;
			break;
		case NW_EVTYPE_CURSOR_RAISE:
			m_buttons[evt.get_code()].m_state = NW_BUTTON_RAISE;
			break;
		}
	}
	// --==</core_methods>==--
}
#	endif	// WAPI_WIN
#endif	// NW_WAPI