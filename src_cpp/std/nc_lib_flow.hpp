#ifndef NC_LIB_FLOW_HPP
#	define NC_LIB_FLOW_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#       include <thread>
#       include <mutex>
// defines //
#		define NC_FLOWS_MULTIP 1 << 0
#		define NC_FLOWS_SINGLE 1 << 1
#		define NC_FLOWS        NC_FLOWS_SINGLE
// types //
using flow_t = std::thread;
using flow_tc = const flow_t;
using flow_lock_t = std::mutex;
using flow_lock_tc = const flow_lock_t;
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_FLOW_HPP //