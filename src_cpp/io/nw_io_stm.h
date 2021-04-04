#ifndef NW_IO_STREAM_H
#define NW_IO_STREAM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	// byte streams
	typedef std::istream              stm_in;
	typedef std::ostream             stm_out;
	typedef std::iostream             stm_io;
	// file streams
	typedef std::ifstream        stm_in_file;
	typedef std::ofstream       stm_out_file;
	// string streams
	typedef std::fstream         stm_io_file;
	typedef std::stringstream    stm_io_str8;
	typedef const stm_io_str8   cstm_io_str8;
	// default streams
	typedef stm_io_str8       stm_io_str;
	typedef const stm_io_str cstm_io_str;
}
namespace NW
{
	template<typename vtype, csize size_x>
	inline stm_out& operator<<(stm_out& stm, const vec_t<vtype, size_x>& vector) { return vector.operator<<(stm); }
	template<typename vtype, csize size_x>
	inline stm_in& operator>>(stm_in& stm, vec_t<vtype, size_x>& vector) { return vector.operator>>(stm); }
	template<typename vtype, csize size_x, csize size_y>
	inline stm_out& operator<<(stm_out& stm, const mat_t<vtype, size_x, size_y>& matrix) { return matrix.operator<<(stm); }
	template<typename vtype, csize size_x, csize size_y>
	inline stm_in& operator>>(stm_in& stm, mat_t<vtype, size_x, size_y>& matrix) { return matrix.operator>>(stm); }
}
#endif	// NW_API
#endif	// NW_IO_STREAM_H
