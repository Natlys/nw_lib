#ifndef NC_LIB_DEBUG_HXX
#   define NC_LIB_DEBUG_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
#       include "nc_lib_iop.hxx"
/* defines */
#   define NC_WORK
//#   define NC_GAME
#   if (defined(NC_WORK))
#       define NC_ERROR(mesg, actn)       ({ NC_ELOG(mesg); NC_BREAK(); ({ nc_code_err = NC_UNIT; actn; }); })
#       define NC_CHECK(expr, mesg, actn) ({ if ((expr) == NC_FALSE) { NC_ERROR(mesg, actn); } })
#       define NC_PCALL(code, mesg, actn) ({ code; NC_CHECK( nc_code_err == NC_ZERO, mesg, ({ actn; nc_code_err = NC_ZERO; }) ); })
#   endif	/* NC_WORK */
#   if (defined(NC_GAME))
#	    define NC_ERROR(mesg, actn)       ({ actn })
#	    define NC_CHECK(expr, mesg, actn) ({ if ((expr) == NC_FALSE) { NC_ERROR(mesg, actn); } })
#       define NC_PCALL(code, mesg, actn) ({ code; NC_CHECK( nc_code_err == NC_ZERO, mesg, ({ actn; nc_code_err = NC_ZERO; }) ); })
#   endif	/* NC_GAME */
/* typedefs */
/* data */
NC_API indx_t nc_code_err; /* last set errno value */
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_DEBUG_HXX */