#ifndef NC_LIB_TABLE_HPP
#	define NC_LIB_TABLE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
/* defines */
// types //
/// table_iterator_type_template
class nc_table_iter_tt
{
public:
    // ctor_dtor //
    /* getters */
    /* setters */
    /* predicates */
    /* commands */
    /* operators */
private:
};
/// table_main_type_template
class nc_table_main_tt
{
public:
    // ctor_dtor //
    /* getters */
    /* setters */
    /* predicates */
    /* commands */
    /* operators */
private:
};
// other_names //
template<typename tname> using nc_table_t = nc_table_main_t<tname>;
template<typename tname> using nc_table_tc = const nc_table_t<tname>;
#	endif	/* NC_API */
/* end_of_file */
#endif	// NC_LIB_TABLE_HPP //