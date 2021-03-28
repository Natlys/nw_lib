#ifndef NWLIB_IO_FILE_LIB_H
#define NWLIB_IO_FILE_LIB_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	namespace flib = std::experimental::filesystem;
	using fdir_entry = flib::directory_entry;
	using fdir_iter = flib::directory_iterator;
	using fdir_iter_recur = flib::recursive_directory_iterator;
	using fspace = flib::space_info;
}
#endif	// NW_API
#endif	// NWLIB_IO_FILE_LIB_H