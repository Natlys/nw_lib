#include "nw_lib_pch.hpp"
#include "nw_std_cam.h"
#if (defined NW_GAPI)
namespace NW
{
	gfx_cam::gfx_cam() :
		m_fov(1.0f), m_ratio(16.0f / 9.0f),
		m_near(0.01f), m_far(100.0f),
		m_crd{ 0.0f, 0.0f, 1.0f }, m_rtn{ 0.0f, 0.0f, 0.0f },
		m_right{ 1.0f, 0.0f, 0.0f }, m_upper{ 0.0f, 1.0f, 0.0f }, m_front{ 0.0f, 0.0f, 1.0f },
		m_mode(NW_CAMERA_2D),
		m_tform(m4f::make_ident()), m_proj(m4f::make_ident()), m_view(m4f::make_ident())
	{
		set_mode(NW_CAMERA_2D);
	}
	// --getters
	void gfx_cam::set_fov(v1f field_of_view) {
		m_fov = field_of_view;
	}
	void gfx_cam::set_ratio(v1f aspect_ratio) {
		m_ratio = aspect_ratio;
	}
	void gfx_cam::set_ratio(v1f size_x, v1f size_y) {
		m_ratio = size_x / size_y;
	}
	void gfx_cam::set_clips(cv1f near_clip, cv1f far_clip) {
		m_near = near_clip;
		m_far = far_clip;
	}
	void gfx_cam::set_clips(cv2f& near_and_far) {
		m_near = near_and_far[0];
		m_far = near_and_far[1];
	}
	void gfx_cam::set_crd(cv3f& coord) {
		m_crd = coord;
	}
	void gfx_cam::set_rtn(cv3f& rotation) {
		m_rtn = rotation;
	}
	void gfx_cam::set_mode(mode mode) {
		m_mode = mode;
		switch (mode) {
		case NW_CAMERA_2D: {
			m_near = -1000.0f;
			m_far = +1000.0f;
			m_fov = 1.0f;
			break;
		}
		case NW_CAMERA_3D: {
			m_near = 0.01f;
			m_far = 100.0f;
			m_fov = 45.0f;
			break;
		}
		}
	}
	// --==<core_methods>==--
	void gfx_cam::update()
	{
		m_ratio = get_max(m_ratio, 0.01f);


		switch (m_mode) {
		case NW_CAMERA_2D: {
			m_proj = make_ortho(m_near, m_far, m_ratio, m_fov);
			m_tform = m4f::make_coord(m_crd) * m4f::make_rotat_z(m_rtn[2]);
			
			m_view = m_tform;

			break;
		}
		case NW_CAMERA_3D: {
			v3f next_front = v3f{
				NW_MATH_SIN(m_rtn[1])* NW_MATH_COS(m_rtn[0]),
				NW_MATH_SIN(m_rtn[0]),
				NW_MATH_COS(m_rtn[1])* NW_MATH_COS(m_rtn[0])
			};
			
			m_front = v3f::make_norm(next_front);
			m_right = v3f::make_norm(v3f::make_cross(m_front, { 0.0f, 1.0f, 0.0f }));
			m_upper = v3f::make_norm(v3f::make_cross(m_right, m_front));

			m_proj = make_persp(m_near, m_far, m_ratio, m_fov);
			m_tform = m4f::make_coord(m_crd) * m4f::make_rotat_xyz(m_rtn);
			
			m_view = make_lookat(-m_crd, m_front - m_crd);
			//m_view = make_lookat(-m_front, m_front);
			//m_view = make_lookat(v3f{0.0f, 0.0f, 0.0f}, m_front);
			//m_view = make_view(m_crd, m_rtn);
			
			break;
		}
		}
	}
	// --==</core_methods>==--
}
namespace NW
{
	gfx_cam_lad::gfx_cam_lad() :
		gfx_cam(),
		zoom_speed(-100.0f), move_speed(-4.0f), rtn_speed(-180.0f),
		rtn_limit{ 89.0f, 180.0f, 180.0f }
	{
	}
	// --==<core_methods>==--
	void gfx_cam_lad::update(const keyboard_state* keyboard, const mouse_state* mouse, const time_state* timer)
	{
		gfx_cam::update();
		if (timer == nullptr) { return; }
		if (keyboard != nullptr) {
			v1f move_delta = timer->get_delta(move_speed);
			// movement
			switch (m_mode) {
			case NW_CAMERA_2D: {
				if (keyboard->is_held(KBC_W)) { m_crd[1] += move_delta; }
				if (keyboard->is_held(KBC_S)) { m_crd[1] -= move_delta; }
				if (keyboard->is_held(KBC_D)) { m_crd[0] += move_delta; }
				if (keyboard->is_held(KBC_A)) { m_crd[0] -= move_delta; }
				break;
			}
			case NW_CAMERA_3D: {
				if (keyboard->is_held(KBC_W)) { m_crd += v3f{ m_front[0], 0.0f, m_front[2] } *move_delta; }
				if (keyboard->is_held(KBC_S)) { m_crd -= v3f{ m_front[0], 0.0f, m_front[2] } *move_delta; }
				if (keyboard->is_held(KBC_D)) { m_crd += m_right * move_delta; }
				if (keyboard->is_held(KBC_A)) { m_crd -= m_right * move_delta; }
				if (keyboard->is_held(KBC_SPACE)) { m_crd[1] += move_delta; }
				if (keyboard->is_held(KBC_LSHIFT)) { m_crd[1] -= move_delta; }
				break;
			}
			}
			// configuration
			if (keyboard->is_held(KBC_C)) {
				if (keyboard->is_pressed(KBC_1)) {
					set_mode(NW_CAMERA_2D);
					m_crd = v3f{ 0.0f, 0.0f, 0.0f };
					m_rtn = v3f{ 0.0f, 0.0f, 0.0f };
				}
				if (keyboard->is_pressed(KBC_2)) { set_mode(NW_CAMERA_2D); }
				if (keyboard->is_pressed(KBC_3)) { set_mode(NW_CAMERA_3D); }
			}
		}
		if (mouse != nullptr) {
			// rotation
			v1f rtn_delta = timer->get_delta(rtn_speed);
			switch (m_mode) {
			case NW_CAMERA_2D: {
				if (m_rtn[2] < -rtn_limit[2]) { m_rtn[2] = +rtn_limit[2]; }
				else if (m_rtn[2] > +rtn_limit[2]) { m_rtn[2] = -rtn_limit[2]; }
				break;
			}
			case NW_CAMERA_3D: {
				if (m_rtn[1] > +rtn_limit[1]) { m_rtn[1] = -rtn_limit[1]; }
				else if (m_rtn[1] < -rtn_limit[1]) { m_rtn[1] = +rtn_limit[1]; }
				m_rtn[1] += mouse->get_move_delta_x() * rtn_delta;
				if (m_rtn[0] > +rtn_limit[0]) { m_rtn[0] = +rtn_limit[0]; }
				else if (m_rtn[0] < -rtn_limit[0]) { m_rtn[0] = -rtn_limit[0]; }
				m_rtn[0] += mouse->get_move_delta_y() * rtn_delta;
				break;
			}
			}
			// zooming
			v1f zoom_delta = timer->get_delta(zoom_speed) * mouse->get_scroll_delta_y();
			switch (m_mode) {
			case NW_CAMERA_2D: {
				m_fov = NW_MATH_CLAMP(0.0f, 1000.0f, m_fov + (m_fov * zoom_delta));
				break;
			}
			case NW_CAMERA_3D: {
				m_fov = NW_MATH_CLAMP(12.5f, 170.0f, m_fov + (m_fov * zoom_delta));
				break;
			}
			}
			// panning
			if (mouse->is_held(MSC_2)) {
				v1f move_delta = timer->get_delta(move_speed);
				m_crd[0] -= mouse->get_move_delta_x() * move_delta * m_fov;
				m_crd[1] += mouse->get_move_delta_y() * move_delta * m_fov;
			}
		}
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI