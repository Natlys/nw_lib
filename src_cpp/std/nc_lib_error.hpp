#ifndef NC_LIB_ERROR_H
#	define NC_LIB_ERROR_H
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "../../nc_iop/src_cpp/cmp/nc_iop_cmp.hpp"
// types //
/// error_type
class NC_API nc_error_t : public nc_op_cmp_t
{
public:
	using err_t = nc_error_t;
	using err_tc = const err_t;
public:
	// ctor_dtor //
	nc_error_t(cstr_t string, v1u_tc number) : m_str(string), m_num(number) { NC_ERROR(*this, return); }
	// getters //
	inline cstr_t get_str() const { return m_str; }
	inline v1u_tc get_num() const { return m_num; }
	// setters //
	// predicates //
	// commands //
	// operators //
	virtual op_stream_t& operator<<(op_stream_t& stm) const override { return stm << "{" << "string: " << m_str << "number: " << m_num << "};"; }
protected:
	cstr_t m_str;
	v1u_tc m_num;
};
/// init_error_type
class NC_API nc_init_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_init_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// predicates //
	// getters //
	// setters //
	// commands //
	// operators //
private:
};
/// quit_error_type
class NC_API nc_quit_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_quit_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// worktime_error_type
class NC_API nc_work_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_work_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// load_error_type
class NC_API nc_load_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_load_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// save_error_type
class NC_API nc_save_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_save_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// memory_error_type
class NC_API nc_mem_error_t : public nc_error_t
{
public:
	nc_mem_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// type_error_type
class NC_API nc_type_error_t : public nc_error_t
{
public:
	nc_type_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
/// index_error_type
class NC_API nc_indx_error_t : public nc_error_t
{
public:
	// ctor_dtor //
	nc_indx_error_t(cstr_t string = NC_NULL, v1u_tc number = NC_NULL) : nc_error_t(string, number) { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_ERROR_HPP //