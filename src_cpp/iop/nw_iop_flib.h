#ifndef NW_IOP_FILE_LIB_H
#define NW_IOP_FILE_LIB_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	namespace flib = std::experimental::filesystem;
	using fdir_entry = flib::directory_entry;
	using fdir_iter = flib::directory_iterator;
	using fdir_iter_recur = flib::recursive_directory_iterator;
	using fspace = flib::space_info;
}
#endif	// NW_API
#endif	// NW_IOP_FILE_LIB_H
