#ifndef NC_LIB_FLOW_HPP
#   define NC_LIB_FLOW_HPP
//#   include "../nc_lib_core.hpp"
#   include "../nc_cfg_core.hpp"
#   if (defined NC_API)
#       include <functional>
#       define NC_FLOW_FLAG_LIVE ( 1u << 0u )
#       define NC_FLOW_FLAG_WAIT ( 1u << 1u )
#       if !(defined NC_DEFAULT_FLOW_SIZE)
#           define NC_MINIMAL_FLOW_SIZE 1 << 10u // 1 kb //
#           define NC_AVERAGE_FLOW_SIZE 1 << 15u // 32 kb //
#           define NC_MAXIMAL_FLOW_SIZE 1 << 20u // 1024 kb //
#           define NC_DEFAULT_FLOW_SIZE NC_AVERAGE_FLOW_SIZE
#       endif   // NC_DEFAULT_FLOW_SIZE //
/// flow_type
/// description:
/// interface:
class nc_flow_t
{
public:
    using flow_t = nc_flow_t;
    using flow_tc = const flow_t;
    using mark_t = nc_wapi_thread_t;
    using mark_tc = const mark_t;
    using func_t = std::function<v1bit_t(ptr_t iput, ptr_t oput)>;
    using func_tc = const func_t;
public:
    // ctor_dtor //
    inline nc_flow_t() : m_mark(NC_NULL), m_indx(NC_ZERO), m_func(NC_NULL), m_size(NC_DEFAULT_FLOW_SIZE), m_flag(NC_FALSE) { }
    inline nc_flow_t(func_tc func) : nc_flow_t() { NC_CHECK(init(func), "init error!", return); }
    inline nc_flow_t(func_tc func, size_tc size) : nc_flow_t() { NC_CHECK(init(func, size), "init error!", return); }
    inline nc_flow_t(flow_tc& copy) : nc_flow_t() { operator=(copy); }
    inline nc_flow_t(flow_t&& copy) : nc_flow_t() { operator=(copy); }
    inline ~nc_flow_t() { if (has_work()) { NC_CHECK(quit(), "quit error!", return); } }
    // getters //
    inline mark_tc get_mark() const { return m_mark; }
    inline indx_tc get_indx() const { return m_indx; }
    inline func_tc get_func() const { return m_func; }
    inline size_tc get_size() const { return m_size; }
    inline flag_tc get_flag() const { return m_flag; }
    // setters //
    inline flow_t& set_func(func_tc func) {
        NC_CHECK(!has_work(), "this is a working flow!", return *this);
        //
        m_func = func;
        return *this;
    }
    inline flow_t& set_size(size_tc size) {
        NC_CHECK(!has_work(), "this is a working flow!", return *this);
        NC_CHECK(size >= NC_MINIMAL_FLOW_SIZE, "very small flow size!", return *this);
        NC_CHECK(size <= NC_MAXIMAL_FLOW_SIZE, "very large flow size!", return *this);
        m_size = size;
        return *this;
    }
    inline flow_t& set_flag(flag_tc flag) {
        if (m_flag == flag) { return *this; }
        else { m_flag = flag; }
        if (m_mark == NC_NULL) { return *this; }
        if (has_flag(NC_FLOW_FLAG_WAIT) == NC_FALSE) { NC_CHECK(::ResumeThread(m_mark) != -1, "flow error!", return *this); }
        if (has_flag(NC_FLOW_FLAG_WAIT) == NC_TRUTH) { NC_CHECK(::SuspendThread(m_mark) != -1, "flow error!", return *this); }
        return *this;
    }
    inline flow_t& add_flag(flag_tc flag) {
        if (has_flag(flag)) { return *this; }
        else { m_flag |= flag; }
        if (m_mark == NC_NULL) { return *this; }
        if (flag != NC_FLOW_FLAG_WAIT) { NC_CHECK(::ResumeThread(m_mark) != -1, "flow error!", return *this); }
        if (flag == NC_FLOW_FLAG_WAIT) { NC_CHECK(::SuspendThread(m_mark) != -1, "flow error!", return *this); }
        return *this;
    }
    inline flow_t& rmv_flag(flag_tc flag) {
        if (has_flag(flag)) { return *this; }
        else { m_flag &= ~flag; }
        if (m_mark == NC_NULL) { return *this; }
        if (flag != NC_FLOW_FLAG_WAIT) { NC_CHECK(::ResumeThread(m_mark) != -1, "flow error!", return *this); }
        if (flag == NC_FLOW_FLAG_WAIT) { NC_CHECK(::SuspendThread(m_mark) != -1, "flow error!", return *this); }
        return *this;
    }
    // predicates //
    inline v1bit_t has_mark() const             { return m_mark != NC_NULL; }
    inline v1bit_t has_mark(mark_tc mark) const { return m_mark == mark; }
    inline v1bit_t has_indx() const             { return m_indx != NC_ZERO; }
    inline v1bit_t has_indx(indx_tc indx) const { return m_indx == indx; }
    inline v1bit_t has_func() const             { return m_func != NC_NULL; }
    inline v1bit_t has_func(func_tc func) const { return &m_func == &func; }
    inline v1bit_t has_size() const             { return m_size != NC_ZERO; }
    inline v1bit_t has_size(size_tc size) const { return m_size >= size; }
    inline v1bit_t has_flag() const             { return m_flag != NC_ZERO; }
    inline v1bit_t has_flag(flag_tc flag) const { return m_flag & flag; }
    inline v1bit_t has_work() const { return has_mark() && has_indx() && has_func() && has_size(); }
    // commands //
    inline v1bit_t init(func_tc func)               { return set_func(func).init(); }
    inline v1bit_t init(size_tc size)               { return set_size(size).init(); }
    inline v1bit_t init(func_tc func, size_tc size) { return set_func(func).set_size(size).init(); }
    inline v1bit_t init()
    {
        NC_PCALL({ // checking //
            NC_CHECK(has_work() == NC_FALSE, "this is a working flow!", return NC_FALSE);
        }, "init error!", return NC_FALSE);
        NC_PCALL({ // action //
            static LPTHREAD_START_ROUTINE routine = [](LPVOID iput)->DWORD {
                flow_t* this_flow = reinterpret_cast<flow_t*>(iput);
                NC_CHECK(this_flow->work(this_flow, NC_NULL), "work error!", return NC_FALSE);
                return NC_TRUTH;
            };
            NC_CHECK(
                (m_mark = ::CreateThread(
                    NC_ZERO, // NULL = no security attributes and handle is not inherited //
                    m_size,  // ZERO = default stack size of an executable //
                    routine, // function to execute //
                    this,    // pass the current instance to use that in the routine //
                    has_flag(NC_FLOW_FLAG_WAIT) ?
                        CREATE_SUSPENDED // CREATE_SUSPENDED = ResumeThread //
                        : NC_ZERO,       // ZERO = launch it right now! //
                    &m_indx  // where the index will be written //
                )
            ) != NC_NULL, "windows cannot create a thread!", return NC_FALSE);
        }, "init error!", return NC_FALSE);
        NC_PCALL({ // logging //
            NC_CHECK(olog(), "olog error!", return NC_FALSE);
        }, "init error!", return NC_FALSE);
        // result //
        return NC_TRUTH;
    }
    inline v1bit_t quit()
    {
        NC_PCALL({ // logging //
            NC_CHECK(olog(), "olog error!", return NC_FALSE);
        }, "init error!", return NC_FALSE);
        NC_PCALL({ // checking //
            NC_CHECK(has_work() == NC_TRUTH, "this is not a working flow!", return NC_FALSE);
        }, "quit error!", return NC_FALSE);
        NC_PCALL({ // action //
            NC_CHECK(::CloseHandle(m_mark), "windows cannot close a thread", return NC_FALSE);
            m_mark = NC_DEFAULT_PTR;
            m_indx = NC_DEFAULT_VAL;
        }, "quit error!", return NC_FALSE);
        // result //
        return NC_TRUTH;
    }
    inline v1bit_t work(ptr_t iput, ptr_t oput) {
        // checking //
        NC_CHECK(has_work(), "work error!", return NC_FALSE);
        // action //
        add_flag(NC_FLOW_FLAG_LIVE);
        NC_CHECK(m_func(iput, oput), "work error!", return NC_FALSE);
        rmv_flag(NC_FLOW_FLAG_LIVE);
        // result //
        return NC_TRUTH;
    }
    inline v1bit_t olog() {
        // checking //
        // action //
        NC_PCALL({ // logging //
            NC_OLOG("flow_olog:{" NC_STR_EOL
                "   mark: %d;" NC_STR_EOL
                "   indx: %d;" NC_STR_EOL
                "   func: %d;" NC_STR_EOL
                "   size: %d;" NC_STR_EOL
                "   flag: %d;" NC_STR_EOL
                "}",
                (size_t)get_mark(),
                (size_t)get_indx(),
                (size_t)&get_func(),
                (size_t)get_size(),
                (size_t)get_flag()
            );
        }, "olog error!", return NC_FALSE);
        // result //
        return NC_TRUTH;
    }
    // operators //
    inline flow_t& operator=(flow_tc& copy) { NC_CHECK(set_flag(copy.m_flag).init(copy.m_func), "init error!", return *this); return *this; }
    inline flow_t& operator=(flow_t&& copy) { memmove(this, &copy, sizeof(flow_t)); return *this; }
private:
    mark_t m_mark;
    indx_t m_indx;
    func_t m_func;
    size_t m_size;
    flag_t m_flag;
};
#   endif // NC_API //
// end_of_file //
#endif  // NC_LIB_FLOW_HPP //