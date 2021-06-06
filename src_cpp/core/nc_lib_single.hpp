#ifndef NC_LIB_SINGLETON_HPP
#	define NC_LIB_SINGLETON_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
/* defines */
/* typedefs */
/// singleton_type_template
template<class tname>
class nc_single_tt : public nc_mem_owner_t
{
public:
	using sing_t = nc_single_tt<tname>;
	using sing_tc = const sing_t;
	using type_t = tname;
	using type_tc = const type_t;
public:
	/* codetor */
	inline nc_single_tt() = default;
	inline nc_single_tt(type_tc& copy) = delete;
	inline nc_single_tt(type_t&& copy) = delete;
	inline nc_single_tt(sing_tc& copy) = delete;
	inline nc_single_tt(sing_t&& copy) = delete;
	inline ~nc_single_tt() = default;
	/* getters */
	static inline type_t& get() { static type_t s_single; return s_single; }
	/* setters */
	/* vetters */
	/* command */
	/* operators */
	sing_t& operator=(type_tc& copy) = delete;
	sing_t& operator=(type_t&& copy) = delete;
	sing_t& operator=(sing_tc& copy) = delete;
	sing_t& operator=(sing_t&& copy) = delete;
};
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_SINGLETON_HPP */