#ifndef NW_STD_CAMERA_H
#define NW_STD_CAMERA_H
#include "nw_lib_core.hpp"
#if (defined NW_GAPI)
#define NW_CAMERA_2D  1 << 1
#define NW_CAMERA_3D  0 << 2
#define NW_CAMERA     1 << 0
namespace NW
{
	/// graphics_camera class
	/// description:
	/// --makes all relevant rotation and movement calculations
	/// --makes projection and view-lookAt matricies
	/// interface:
	/// ->config Frustrum, tarGet, 
	/// ->set coordinates and rotation
	/// ->get transform matricies: proj and view
	class NW_API gfx_cam
	{
	public:
		using mode = enum_id;
	public:
		gfx_cam();
		// --getters
		inline v1f get_fov() const   { return m_fov; }
		inline v1f get_ratio() const { return m_ratio; }
		inline v1f get_near() const  { return m_near; }
		inline v1f get_far() const   { return m_far; }
		inline v3f get_crd() const   { return m_crd; }
		inline v3f get_rtn() const   { return m_rtn; }
		inline v3f get_right_dir(v1f scalar = 1.0f) const { return v3f{ -m_right[0], +m_right[1], -m_right[2] } * scalar; }
		inline v3f get_upper_dir(v1f scalar = 1.0f) const { return v3f{ -m_upper[0], +m_upper[1], -m_upper[2] } * scalar; }
		inline v3f get_front_dir(v1f scalar = 1.0f) const { return v3f{ -m_front[0], +m_front[1], -m_front[2] } * scalar; }
		inline v3f get_right_crd(v1f scalar = 1.0f) const { return m_right * -scalar + m_crd; }
		inline v3f get_upper_crd(v1f scalar = 1.0f) const { return m_upper * -scalar + m_crd; }
		inline v3f get_front_crd(v1f scalar = 1.0f) const { return get_front_dir(scalar) + m_crd; }
		inline const m4f& get_proj() const  { return m_proj; }
		inline const m4f& get_view() const  { return m_view; }
		inline const m4f& get_tform() const { return m_tform; }
		inline const mode& get_mode() const { return m_mode; }
		static inline cm4f make_ortho(cv1f znear, cv1f zfar, cv1f ratio, cv1f fov) {
			v1f lft = -fov * ratio / 2.0f;
			v1f rht = +fov * ratio / 2.0f;
			v1f bot = -fov / 2.0f;
			v1f top = +fov / 2.0f;
			m4f result(0.0f);
			result[0][0] = 2.0f / (rht - lft);
			result[1][1] = 2.0f / (top - bot);
			result[0][3] = -(rht + lft) / (rht - lft);
			result[1][3] = -(top + bot) / (top - bot);
			result[2][2] = -2.0f / (zfar - znear);
			result[2][3] = -(zfar + znear) / (zfar - znear);
			result[3][3] = 1.0f;
			return result;
		}
		static inline cm4f make_persp(cv1f znear, cv1f zfar, cv1f ratio, cv1f fov) {
			m4f result(0.0f);
			v1f fov_tan = NW_MATH_TANG(fov / 2.0f);
			result[0][0] = 1.0f / (fov_tan * ratio);
			result[1][1] = 1.0f / (fov_tan);
			result[2][2] = -(zfar + znear) / (zfar - znear);
			result[2][3] = -1.0f;
			result[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
			return result;
		}
		static inline cm4f make_lookat(cv3f& view_crd, cv3f& dest_crd = v3f{ 0.0f, 0.0f, 0.0f }, cv3f upper_dir = v3f{ 0.0f, 1.0f, 0.0f }) {
			v3f axis_z = v3f::make_norm(dest_crd - view_crd);
			v3f axis_x = v3f::make_norm(v3f::make_cross(axis_z, upper_dir));
			v3f axis_y = v3f::make_norm(v3f::make_cross(axis_x, axis_z));

			axis_z = -axis_z;
			m4f result;
#	if (0)
			result[0] = v4f{ axis_x[0], axis_x[1], axis_x[2], -v3f::get_dot(axis_x, view_crd) };
			result[1] = v4f{ axis_y[0], axis_y[1], axis_y[2], -v3f::get_dot(axis_y, view_crd) };
			result[2] = v4f{ axis_z[0], axis_z[1], axis_z[2], -v3f::get_dot(axis_z, view_crd) };
			result[3] = v4f{ 0.0f, 0.0f, 0.0f, 1.0f };
#	elif (1)
			result[0] = v4f{ axis_x[0], axis_y[0], axis_z[0], 0.0f };
			result[1] = v4f{ axis_x[1], axis_y[1], axis_z[1], 0.0f };
			result[2] = v4f{ axis_x[2], axis_y[2], axis_z[2], 0.0f };
			result[3] = v4f{ -view_crd.get_dot(axis_x), -view_crd.get_dot(axis_y) , -view_crd.get_dot(axis_z), 1.0f };
#	endif
			
			return result;
		}
		static inline cm4f make_view(cv3f& view_crd, cv3f& view_rtn) {
			return m4f::make_coord(v3f{ -view_crd[0], +view_crd[1], -view_crd[2] }) * m4f::make_rotat_xyz(view_rtn);
		}
		// --setters
		void set_fov(v1f field_of_view);
		void set_ratio(v1f size_x, v1f size_y);
		void set_ratio(v1f aspect_ratio);
		void set_clips(cv1f near_clip, cv1f far_clip);
		void set_clips(cv2f& near_and_far);
		void set_crd(cv3f& coord);
		void set_rtn(cv3f& rotation);
		void set_mode(mode mode);
		// --core_methods
		void update();
	protected:
		v1f m_fov;
		v1f m_ratio;
		v1f m_near, m_far;
		v3f m_crd, m_rtn;
		v3f m_right, m_upper, m_front;
		m4f m_tform, m_view, m_proj;
		mode m_mode;
	};
}
#include "io/nw_io_dvc.h"
#include "nw_std_time.h"
namespace NW
{
	/// graphics_camera_lad class
	class NW_API gfx_cam_lad : public gfx_cam
	{
	public:
		v1f rtn_speed;
		v1f move_speed;
		v1f zoom_speed;
		v3f rtn_limit;
	public:
		gfx_cam_lad();
		// --core_methods
		void update(const keyboard_state* keyboard, const mouse_state* mouse, const time_state* timer);
	};
}
#endif	// NW_GAPI
#endif // NW_STD_CAMERA_H