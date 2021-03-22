#ifndef NWL_DATA_LIB_H
#define NWL_DATA_LIB_H
#include <nwl_core.hpp>
namespace NW
{
	using data_dir_entry = std::experimental::filesystem::directory_entry;
	using data_dir_iter = std::experimental::filesystem::directory_iterator;
	using data_dir_iter_recur = std::experimental::filesystem::recursive_directory_iterator;
	using data_space_info = std::experimental::filesystem::space_info;
}
#endif	// NWL_DATA_LIB_H