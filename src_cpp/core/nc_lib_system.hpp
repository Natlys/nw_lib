#ifndef NC_LIB_SYSTEM_HPP
#	define NC_LIB_SYSTEM_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
#		include "../std/nc_lib_table.hpp"
#		include "nc_lib_single.hpp"
/* defines */
/* typedefs */
/// system_type_template
template<class tsys>
class nc_system_tt : public nc_single_tt<tsys>
{
public:
	using sys_t = tsys;
	using sys_tc = const sys_t;
public:
	/* codetor */
	inline nc_system_tt() = default;
	inline ~nc_system_tt() = default;
	/* getters */
	/* setters */
	/* vetters */
	/* command */
	inline v1bit_t init() { return NC_TRUTH; }
	inline v1bit_t quit() { return NC_TRUTH; }
	inline v1bit_t work() { return NC_TRUTH; }
	/* operators */
protected:
};
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_SYSTEM_HPP */