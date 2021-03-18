#ifndef NW_IO_STREAM_H
#define NW_IO_STREAM_H
#include <nwl_core.hpp>
namespace NW
{
	using stm_in = std::istream;
	using stm_out = std::ostream;
	using stm_io = std::iostream;
	using stm_in_file = std::ifstream;
	using stm_out_file = std::ofstream;
	using stm_io_file = std::fstream;
}
#endif	// NW_IO_STREAM_H