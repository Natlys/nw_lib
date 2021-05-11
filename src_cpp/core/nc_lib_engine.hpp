#ifndef NC_LIB_ENGINE_HPP
#	define NC_LIB_ENGINE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "nc_lib_single.hpp"
#		include "nc_lib_flow.hpp"
#		include "nc_lib_array.hpp"
#		include "nc_lib_name.hpp"
#		include "nc_lib_func.hpp"
class nc_engine_state_t : public nc_name_owner_t
{
public:
	using state_t = nc_engine_state_t;
	using state_tc = const state_t;
public:
	// ctor_dtor //
	inline nc_engine_state_t() : nc_name_owner_t() { }
	inline nc_engine_state_t(cstr_t name) : nc_engine_state_t() { set_name(name); }
	virtual inline ~nc_engine_state_t() { }
	// getters //
	// setters //
	// predicates //
	// operators //
	// commands //
	virtual inline v1bit_t init() { return NC_TRUTH; }
	virtual inline v1bit_t quit() { return NC_TRUTH; }
	virtual inline v1bit_t work() { return NC_TRUTH; }
public:
};
/// engine_type
template<class teng, class tstate = nc_engine_state_t>
class nc_engine_t : public std_single_t<teng>, public mem_owner_t
{
public:
	using engine_t = teng;
	using engine_tc = const engine_t;
	using work_proc_t = functor_t<v1nil_t(v1nil_t)>;
	using work_proc_tc = const work_proc_t;
	using work_flow_t = flow_t;
	using work_flow_tc = const flow_t;
	using work_lock_t = v1bit_t;
	using work_lock_tc = const work_lock_t;
	using state_t = tstate;
	using state_tc = const state_t;
	using states_t = array_t<state_t*>;
	using states_tc = const states_t;
public:
	// ctor_dtor //
	inline nc_engine_t() = default;
	inline ~nc_engine_t() = default;
	// getters //
	inline work_flow_t& get_work_flow()        { return m_work_flow; }
	inline work_flow_tc& get_work_flow() const { return m_work_flow; }
	inline work_lock_t& get_work_lock()        { return m_work_lock; }
	inline work_lock_tc& get_work_lock() const { return m_work_lock; }
	inline state_t* get_state(size_tc key)        { NC_CHECK(has_state(key), "not found!", return NC_NULL); return m_states[key]; }
	inline state_tc* get_state(size_tc key) const { NC_CHECK(has_state(key), "not found!", return NC_NULL); return m_states[key]; }
	// setters //
	template<class tname, typename ... args> engine_t& add_state(args&& ... arguments) { m_states.push_back(new tname(std::forward<args>(arguments)...)); return *this; }
	inline engine_t& rmv_state(size_tc key) { NC_CHECK(has_state(key), "key error!", return *this); delete m_states[key]; m_states.erase(m_states.begin() + key); return *this; }
	inline engine_t& rmv_state() { return rmv_state(NC_NULL); }
	// --prediactes
	inline v1bit_t has_work() const  { return m_work_lock; }
	inline v1bit_t has_state() const { return !m_states.empty(); }
	inline v1bit_t has_state(size_tc key) const { return m_states.size() > key; }
	inline v1bit_t has_state(cstr_t key) const { for (auto& istate : m_states) { if (istate->has_name(key)) { return NC_TRUTH; } } return NC_FALSE; }
	// commands //
	inline v1bit_t work_init() { NC_CHECK(!has_work(), "init is already done!", return NC_FALSE); m_work_flow = work_flow_t(m_work_proc); m_work_lock = NC_TRUTH; return NC_TRUTH; }
	inline v1bit_t work_quit() { NC_CHECK(has_work(), "quit is already done!", return NC_FALSE); m_work_lock = NC_FALSE; return NC_TRUTH; }
	virtual inline v1bit_t init() { for (auto& istate : m_states) { NC_CHECK(istate->init(), "init error!", return NC_FALSE); } return NC_TRUTH; }
	virtual inline v1bit_t quit() { for (auto& istate : m_states) { NC_CHECK(istate->quit(), "quit error!", return NC_FALSE); } while (has_state()) { rmv_state(); } m_states.clear(); return NC_TRUTH; }
	virtual inline v1bit_t work() { for (auto& istate : m_states) { NC_CHECK(istate->work(), "work error!", return NC_FALSE); } return NC_TRUTH; }
	// operators //
protected:
	work_flow_t m_work_flow;
	work_lock_t m_work_lock;
	work_proc_t m_work_proc = [this]()->v1nil_t {
		try { NC_CHECK(init(), "init error!", work_quit()); while (has_work()) { NC_CHECK(work(), "update error!", work_quit()); } NC_CHECK(quit(), "quit error!", work_quit()); }
		catch (std::exception exc) { NC_ERROR(exc.what(), work_quit()); }
		catch (...) { NC_ERROR("something went wrong;", work_quit()); }
	};
	states_t m_states;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_ENGINE_HPP //