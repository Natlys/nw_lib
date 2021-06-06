#include "../nc_lib_pch.hxx"
#include "nc_lib_flow.hxx"
#if (defined(NC_API))
/* system  */
NC_API_CALL DWORD nc_flow_wapi_proc(LPVOID iput) {
    nc_flow_t* flow = NC_CAST(iput, nc_flow_t*);
    NC_CHECK(nc_flow_work(flow, flow, NC_NULL), "work error!", return NC_FALSE);
    return NC_TRUTH;
}
/* typedefs */
typedef struct nc_flow_t {
    ptr_t hand;
    nc_flow_proc_f proc;
    indx_t indx;
    flag_t flag;
    size_t size;
} nc_flow_t;
/* codetor */
NC_API_CALL v1bit_t nc_flow_ctor(nc_flow_t** ref) {
    /* init */
    NC_CHECK(
        ref != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    NC_CHECK(
        nc_lib_sys_mset(ref, NC_ZERO, sizeof(nc_flow_t)),
        "failed to create flow!",
        return NC_FALSE
    );
    nc_flow_t* flow = *ref;
    flow->hand = NC_VOID_PTR;
    flow->indx = NC_VOID_VAL;
    flow->proc = NC_VOID_PTR;
    flow->flag = NC_VOID_VAL;
    flow->size = NC_USE_FLOW_SIZE;
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_dtor(nc_flow_t** ref) {
    /* init */
    NC_CHECK(
        ref != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    NC_CHECK(
        nc_flow_vet_work(*ref),
        "quit is required!",
        return NC_FALSE
    );
    /* work */
    nc_flow_t* flow = *ref;
    flow->hand = NC_VOID_PTR;
    flow->indx = NC_VOID_VAL;
    flow->proc = NC_VOID_PTR;
    flow->flag = NC_VOID_VAL;
    flow->size = NC_VOID_VAL;
    NC_CHECK(
        nc_lib_sys_mset(ref, sizeof(nc_flow_t), NC_ZERO),
        "failed to create flow!",
        return NC_FALSE
    );
    /* quit */
    return NC_TRUTH;
}
/* getters */
/* setters */
NC_API_CALL v1bit_t nc_flow_set_size(nc_flow_t* flow, size_t size) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    NC_CHECK(
        NC_NUM_ISIDE(size, NC_MIN_FLOW_SIZE, NC_MAX_FLOW_SIZE),
        "size error!",
        return NC_FALSE
    );
    /* work */
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_set_flag(nc_flow_t* flow, flag_t flag) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    if (flow->flag == flag) { return NC_TRUTH; }
    flow->flag = flag;
    if (flow->hand == NC_NULL) { return NC_TRUTH; }
    if ((flag & NC_FLOW_FLAG_WAIT) == NC_FALSE) {
        NC_CHECK(
            ResumeThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    if ((flag & NC_FLOW_FLAG_WAIT) == NC_TRUTH) {
        NC_CHECK(
            SuspendThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_add_flag(nc_flow_t* flow, flag_t flag) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    if (nc_flow_vet_flag(flow, flag) == NC_TRUTH) { return NC_TRUTH; }
    flow->flag = flow->flag | flag;
    if (nc_flow_vet_work(flow) == NC_FALSE) { return NC_TRUTH; }
    if (flag != NC_FLOW_FLAG_WAIT) {
        NC_CHECK(
            ResumeThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    if (flag == NC_FLOW_FLAG_WAIT) {
        NC_CHECK(
            SuspendThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_rmv_flag(nc_flow_t* flow, flag_t flag) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    if (nc_flow_vet_flag(flow, flag) == NC_FALSE) { return NC_TRUTH; }
    flow->flag = flow->flag & ~flag;
    if (nc_flow_vet_work(flow) == NC_FALSE) { return NC_TRUTH; }
    if (flag == NC_FLOW_FLAG_WAIT) {
        NC_CHECK(
            ResumeThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    if (flag != NC_FLOW_FLAG_WAIT) {
        NC_CHECK(
            SuspendThread(flow->hand) != -1,
            "flow error!",
            return NC_FALSE
        );
    }
    /* quit */
    return NC_TRUTH;
}
/* vetters */
NC_API_CALL v1bit_t nc_flow_vet_work(nc_flow_t* flow) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    /* quit */
    return flow->hand != NC_NULL && flow->proc != NC_NULL;
}
NC_API_CALL v1bit_t nc_flow_vet_flag(nc_flow_t* flow, flag_t flag) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    /* quit */
    return flow->flag & flag;
}
NC_API_CALL v1bit_t nc_flow_vet_live(nc_flow_t* flow) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    /* quit */
    return flow->flag & NC_FLOW_FLAG_LIVE;
}
NC_API_CALL v1bit_t nc_flow_vet_wait(nc_flow_t* flow) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    /* quit */
    return flow->flag & NC_FLOW_FLAG_WAIT;
}
/* command */
NC_API_CALL v1bit_t nc_flow_init(nc_flow_t* flow) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    NC_CHECK(
        nc_flow_vet_work(flow) == NC_FALSE,
        "there must not be any work!",
        return NC_FALSE
    );
    /* work */
    nc_flow_add_flag(flow, NC_FLOW_FLAG_LIVE);
    NC_CHECK(
        (flow->hand = CreateThread(
            NC_ZERO,             /* NULL = no security attributes and handle is not inherited */
            flow->size,          /* ZERO = default stack size of an executable */
            nc_flow_wapi_proc,   /* function to execute */
            flow,                /* pass the current instance to use that in the routine */
            nc_flow_vet_flag(flow, NC_FLOW_FLAG_WAIT) ?
                CREATE_SUSPENDED /* CREATE_SUSPENDED = ResumeThread */
                : NC_ZERO,       /* ZERO = launch it right now! */
            &flow->indx          /* where the index will be written */
        )) != NC_NULL,
        "windows cannot create a thread!",
        return NC_FALSE
    );
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_quit(nc_flow_t* flow) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    NC_CHECK(
        nc_flow_vet_work(flow) == NC_TRUTH,
        "there must be a work!",
        return NC_FALSE
    );
    /* work */
    NC_CHECK(
        CloseHandle(flow->hand),
        "windows cannot close a thread",
        return NC_FALSE
    );
    flow->hand = NC_NULL;
    flow->indx = NC_ZERO;
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_work(nc_flow_t* flow, ptr_t iput, ptr_t oput) {
    /* init */
    NC_CHECK(
        flow != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    NC_CHECK(
        nc_flow_vet_work(flow) == NC_TRUTH,
        "there must be a work!",
        return NC_FALSE
    );
    /* work */
    nc_flow_add_flag(flow, NC_FLOW_FLAG_LIVE);
    NC_CHECK(flow->proc(iput, oput), "flow error!", return NC_FALSE);
    nc_flow_rmv_flag(flow, NC_FLOW_FLAG_LIVE);
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_flow_olog(nc_flow_t* flow) {
    /* init */
    NC_CHECK(flow != NC_NULL, "null error!", return NC_FALSE);
    /* work */
    NC_OLOG("flow_olog:");
    NC_OPUT("{" NC_ENDL);
    NC_OPUT(NC_TABL "hand: %d;" NC_ENDL, flow->hand);
    NC_OPUT(NC_TABL "indx: %d;" NC_ENDL, flow->indx);
    NC_OPUT(NC_TABL "proc: %d;" NC_ENDL, flow->proc);
    NC_OPUT(NC_TABL "size: %d;" NC_ENDL, flow->size);
    NC_OPUT(NC_TABL "flag: %d;" NC_ENDL, flow->flag);
    NC_OPUT("}" NC_ENDL);
    /* quit */
    return NC_TRUTH;
}
#endif  /* NC_API */
/* end_of_file */