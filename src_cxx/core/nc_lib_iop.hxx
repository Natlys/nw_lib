#ifndef NC_LIB_IOPUT_HXX
#   define NC_LIB_IOPUT_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
/* defines */
/** constants **/
#       define NC_NAME_ILOG nc_ilog
#       define NC_NAME_OLOG nc_olog
#       define NC_NAME_ELOG nc_elog
/** functions **/
/*** input_output ***/
#       define NC_IPUT(args...) fscanf(stdin, args);
#       define NC_OPUT(args...) fprintf(stdout, args);
#       define NC_EPUT(args...) fprintf(stderr, args);
/*** logging ***/
#       if !(defined NC_ILOG)
#           define NC_ILOG(mesg, args...) ({          \
                NC_IPUT(                              \
                    "from: " NC_NAME_ILOG_STR " | "   \
                    "file: " NC_FILE_STR " | "        \
                    "line: " "%d" " | "               \
	    			"mesg: " NC_ENDL "" mesg "" NC_ENDL \
                    , __LINE__, ##args)               \
            })
#       endif  /* NC_ILOG */
#       if !(defined NC_OLOG)
#           define NC_OLOG(mesg, args...) ({          \
                NC_OPUT(                              \
                    "from: " NC_NAME_OLOG_STR " | "   \
                    "file: " NC_FILE_STR " | "        \
                    "line: " "%d" " | "               \
	    			"mesg: " NC_ENDL "" mesg "" NC_ENDL \
                    , __LINE__, ##args)               \
            })
#       endif   /* NC_OLOG */
#       if !(defined NC_ELOG)
#           define NC_ELOG(mesg, args...) ({          \
                NC_EPUT(                              \
                    "from: " NC_NAME_ELOG_STR " | "   \
                    "file: " NC_FILE_STR " | "        \
                    "line: " "%d" " | "               \
	    			"mesg: " NC_ENDL "" mesg "" NC_ENDL \
                    , __LINE__, ##args)               \
            })
#       endif   /* NC_ELOG */
/* typedefs */
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_IOPUT_HXX */