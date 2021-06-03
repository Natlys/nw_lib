#include "../nc_lib_pch.hxx"
#include "nc_lib_flow.hxx"
#if (defined NC_API)
/* ctor_dtor */
v1bit_t nc_flow_ctor(nc_flow_t* flow) {
    /* init */
    NC_PCALL({
        NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
    }, "ctor error!", return NC_FALSE);
    /* work */
    flow->mark = NC_VOID_PTR;
    flow->indx = NC_VOID_VAL;
    //flow->proc = NC_VOID_PTR;
    flow->size = NC_VOID_FLOW_SIZE;
    flow->flag = NC_VOID_VAL;
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_flow_dtor(nc_flow_t* flow) {
    /* init */
    NC_PCALL({
        NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
    }, "dtor error!", return NC_FALSE);
    /* work */
    if (nc_flow_has_work(flow)) { NC_CHECK(nc_flow_quit(flow), "dtor error!", return NC_FALSE); }
    flow->mark = NC_VOID_PTR;
    flow->indx = NC_VOID_VAL;
    //flow->proc= NC_VOID_PTR;
    flow->size = NC_VOID_FLOW_SIZE;
    flow->flag = NC_VOID_VAL;
    /* quit */
    return NC_TRUTH;
}
/* getters */
/* setters */
v1bit_t nc_flow_set_size(nc_flow_t* flow, size_t size) {
    /* init */
    NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
    NC_CHECK(size >= NC_MINIMAL_FLOW_SIZE, "flow size is too small!", return NC_FALSE);
    NC_CHECK(size <= NC_MAXIMAL_FLOW_SIZE, "flow size is too large!", return NC_FALSE);
    /* work */
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_flow_set_flag(nc_flow_t* flow, flag_t flag) {
    /* init */
    NC_CHECK(flow != NC_NULL, "set error!", return NC_FALSE);
    /* work */
    if (flow->flag == flag) { return NC_TRUTH; }
    flow->flag = flag;
    if (flow->mark == NC_NULL) { return NC_TRUTH; }
    if (flag & NC_FLOW_FLAG_WAIT == NC_FALSE) { NC_CHECK(ResumeThread(flow->mark) != -1, "flow error!", return NC_FALSE); }
    if (flag & NC_FLOW_FLAG_WAIT == NC_TRUTH) { NC_CHECK(SuspendThread(flow->mark) != -1, "flow error!", return NC_FALSE); }
    /* quit */
    return NC_TRUTH;
}
/* preicates */
/* commands */
v1bit_t nc_flow_init(nc_flow_t* flow) {
    /* init */
    NC_PCALL({
        NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
        NC_CHECK(nc_flow_has_work(flow) == NC_FALSE, "there must not be any work!", return NC_FALSE);
    }, "quit error!", return NC_FALSE);
    /* olog */
    NC_PCALL({
        nc_flow_olog(flow);
    }, "init error!", return NC_FALSE);
    /* work */
    NC_PCALL({
        nc_flow_add_flag(flow, NC_FLOW_FLAG_LIVE);
        NC_CHECK(
            (flow->mark = CreateThread(
                NC_ZERO,             /* NULL = no security attributes and handle is not inherited */
                flow->size,          /* ZERO = default stack size of an executable */
                nc_flow_wapi_proc,   /* function to execute */
                flow,                /* pass the current instance to use that in the routine */
                nc_flow_has_flag(flow, NC_FLOW_FLAG_WAIT) ?
                    CREATE_SUSPENDED /* CREATE_SUSPENDED = ResumeThread */
                    : NC_ZERO,       /* ZERO = launch it right now! */
                &flow->indx          /* where the index will be written */
            )
        ) != NC_NULL, "windows cannot create a thread!", return NC_FALSE);
    }, "init error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_flow_quit(nc_flow_t* flow) {
    /* olog */
    NC_PCALL({
        nc_flow_olog(flow);
    }, "quit error!", return NC_FALSE);
    /* init */
    NC_PCALL({
        NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
        NC_CHECK(nc_flow_has_work(flow) == NC_TRUTH, "there must be a work!", return NC_FALSE);
    }, "quit error!", return NC_FALSE);
    /* work */
    NC_PCALL({
            NC_CHECK(CloseHandle(flow->mark), "windows cannot close a thread", return NC_FALSE);
            flow->mark = NC_NULL;
            flow->indx = NC_ZERO;
    }, "quit error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_flow_work(nc_flow_t* flow, ptr_t iput, ptr_t oput) {
    /* init */
    NC_PCALL({
        NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
        NC_CHECK(nc_flow_has_work(flow) == NC_TRUTH, "there must be a work!", return NC_FALSE);
    }, "work error!", return NC_FALSE);
    /* work */
    NC_PCALL({
        nc_flow_add_flag(flow, NC_FLOW_FLAG_LIVE);
        NC_CHECK(flow->proc(iput, oput), "flow error!", return NC_FALSE);
        nc_flow_rmv_flag(flow, NC_FLOW_FLAG_LIVE);
    }, "work error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_flow_olog(nc_flow_t* flow) {
    /* init */
    NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
    /* work */
    NC_PCALL({
        NC_OLOG("flow_olog:");
        NC_OPUT("{" NC_ENDL);
        NC_OPUT(NC_HTAB "mark: %d;" NC_ENDL, flow->mark);
        NC_OPUT(NC_HTAB "indx: %d;" NC_ENDL, flow->indx);
        NC_OPUT(NC_HTAB "proc: %d;" NC_ENDL, flow->proc);
        NC_OPUT(NC_HTAB "size: %d;" NC_ENDL, flow->size);
        NC_OPUT(NC_HTAB "flag: %d;" NC_ENDL, flow->flag);
        NC_OPUT("}" NC_ENDL);
    }, "olog error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
/** system  **/
DWORD nc_flow_wapi_proc(LPVOID iput) {
    nc_flow_t* flow = NC_CAST(iput, nc_flow_t*);
    NC_CHECK(nc_flow_work(flow, flow, NC_NULL), "work error!", return NC_FALSE);
    return NC_TRUTH;
}
/** testing  **/
v1bit_t nc_flow_test_proc(ptr_t iput, ptr_t oput) {
    static size_t counter = 0u;
    nc_flow_t* flow = NC_CAST(iput, nc_flow_t*);
    while ((counter += 1u) < 10000u) {
        for (size_t itr = 0u; itr < 1000000u; itr += 1u) { }
        if (counter % 1000u == NC_ZERO) {
            NC_OLOG("counter: %d; flow_indx: %d;", counter, flow->indx);
        }
    }
    return NC_TRUTH;
}
#endif  /* NC_API */
/* end_of_file */