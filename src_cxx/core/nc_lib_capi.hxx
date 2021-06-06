#ifndef NC_LIB_CAPI_HXX
#   define NC_LIB_CAPI_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined NC_LIB_CORE_HXX)
/** constants **/
#       define NC_FILE_STR __FILE__
#       define NC_DATE_STR __DATE__
#       define NC_TIME_STR __TIME__
#	    if (NC_CAPI & NC_CAPI_MVS)
/** constants **/
/** functions **/
#	        define NC_BREAK() ( __debugbreak(); )
/** warnings  **/
#	    	=pragma warning(disable : 4002) /* too many arguments for macro */
#	    	=pragma warning(disable : 4005)
#	    	=pragma warning(disable : 4081)
#	    	=pragma warning(disable : 4099)
#	    	=pragma warning(disable : 4102)
#	    	=pragma warning(disable : 4244)
#	    	=pragma warning(disable : 4251)
#	    	=pragma warning(disable : 4267)
#	    	=pragma warning(disable : 4273)
#	    	=pragma warning(disable : 4275)
#	    	=pragma warning(disable : 4551)
#	    	=pragma warning(disable : 4552)
#	    	=pragma warning(disable : 4996) /* unsafe functions */
#	    	=pragma warning(disable : 4172) /* returning of local variable */
#	    	ifndef _CRT_SECURE_NO_WARNINGS
#	    		define _CRT_SECURE_NO_WARNINGS
#	    	endif	/* _CRT_SECURE_NO_WARNINGS */
#	    endif	/* NC_CAPI_MVS */
#	    if (NC_CAPI & NC_CAPI_GNU)
/** constants **/
#           define NC_FUNC_NAME_STR __FUNCTION__
#           define NC_FUNC_SIGL_STR __PRETTY_FUNCTION__
/** functions **/
#           define NC_CSTACK_PTR() ( __builtin_frame_address(NC_ZERO) )
#           if (defined SIGINT)
#	            define NC_BREAK() ({ raise(SIGINT); })
#           else
#               define NC_BREAK() ({ NC_OPUT("\a"); system("pause"); })
#           endif   /* SIGINT */
/** warnings  **/
#           pragma GCC diagnostic push
#           pragma GCC diagnostic ignored "-Wpragmas"          // warning: unknown option after '#pragma GCC diagnostic' kind
#           pragma GCC diagnostic ignored "-Wunused-function"  // warning: 'xxxx' defined but not used
#           pragma GCC diagnostic ignored "-Wdouble-promotion" // warning: implicit conversion from 'float' to 'double' when passing argument to function
#           pragma GCC diagnostic ignored "-Wconversion"       // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#           pragma GCC diagnostic ignored "-Wstack-protector"  // warning: stack protector not protecting local variables: variable length buffer
#           pragma GCC diagnostic ignored "-Wclass-memaccess"  // warning: 'memset/memcpy' clearing/writing an object of type 'xxxx' with no trivial copy-assignment
#           pragma GCC diagnostic ignored "-Wimplicit-function-declaration" // warning: incompatible implicit declaration of built-in function 'xxxx'
#           pragma GCC diagnostic pop
#	    endif	/* NC_CAPI_GNU */
#       if (NC_CAPI & NC_CAPI_CLG)
/** constants **/
/** functions **/
/** warnings  **/
#           pragma clang diagnostic ignored "-Wunknown-pragmas"                // warning: unknown warning group 'xxx'
#           pragma clang diagnostic ignored "-Wold-style-cast"                 // warning: use of old-style cast
#           pragma clang diagnostic ignored "-Wfloat-equal"                    // warning: comparing floating point with == or != is unsafe
#           pragma clang diagnostic ignored "-Wsign-conversion"                // warning: implicit conversion changes signedness
#           pragma clang diagnostic ignored "-Wcomma"                          // warning: possible misuse of comma operator here
#           pragma clang diagnostic ignored "-Wdouble-promotion"               // warning: implicit argument conversion from 'float' to 'double'
#           pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning: zero as null pointer constant
#           pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"  // warning: implicit conversion from 'xxx' to 'float' may lose precision
#	    endif	/* NC_CAPI_CLG */
#   else
#	    error "nc_lib_core.hxx must be included before this header"
#   endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif	/* NC_LIB_CAPI_HXX */