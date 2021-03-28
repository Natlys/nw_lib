#ifndef NWLIB_IO_STREAM_H
#define NWLIB_IO_STREAM_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	using stm_in = std::istream;
	using stm_out = std::ostream;
	using stm_io = std::iostream;
	using stm_in_file = std::ifstream;
	using stm_out_file = std::ofstream;
	using stm_io_file = std::fstream;
}
#endif	// NW_API
#endif	// NWLIB_IO_STREAM_H