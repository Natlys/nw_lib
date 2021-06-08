#ifndef NC_LIB_WAPI_HXX
#   define NC_LIB_WAPI_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* windows platform */
#	    if (NC_WAPI & NC_WAPI_WIN)
/** configs  **/
#		    define NOMINMAX
#           define NOMCX
#           define NOIME
#           define NOSERVICE
#		    define WIN32_LEAN_AND_MEAN
/* includes */
#		    include <windows.h>
#		    include <commdlg.h>
/** support  **/
#		    define NC_DLL_EXPORT  __declspec(dllexport)
#		    define NC_DLL_IMPORT  __declspec(dllexport)
#		    define NC_API_CALL   __stdcall
/* typedefs */
#		    define nc_wapi_thread_t  HANDLE
#		    define nc_wapi_module_t  HMODULE
#		    define nc_wapi_window_t  HWND
#		    define nc_wapi_device_t  HDC
#		    define nc_wapi_context_t HGLRC
/** codes  **/
/*** keyboard  ***/
#	        define NC_CKEY_BACK  8
#	        define NC_CKEY_VTAB  9
#	        define NC_CKEY_HTAB  11
#	        define NC_CKEY_ENTER 13
#	        define NC_CKEY_SHIFT 16
#	        define NC_CKEY_CONTR 18
#	        define NC_CKEY_ALTER 19
#	        define NC_CKEY_PAUSE 20
#	        define NC_CKEY_CAPS  26
#	        define NC_CKEY_ESCP  27
#	        define NC_CKEY_ARROWL 37
#	        define NC_CKEY_ARROWU 38
#	        define NC_CKEY_ARROWR 39
#	        define NC_CKEY_ARROWD 40
#	        define NC_CKEY_INSERT 45
#	        define NC_CKEY_DELETE 46
#	        define NC_CKEY_HOME   47
#	        define NC_CKEY_SPACE   32
#	        define NC_CKEY_EXCLAIM 33
#	        define NC_CKEY_QUOTES  34
#	        define NC_CKEY_HASH    35
#	        define NC_CKEY_DOLLAR  36
#	        define NC_CKEY_PERCENT  37
#	        define NC_CKEY_AMPERSAND  38
#	        define NC_CKEY_APOSTROPH  39
#	        define NC_CKEY_BRACKETL 40
#	        define NC_CKEY_BRACKETR 41
#	        define NC_CKEY_STAR    42
#	        define NC_CKEY_PLUS    43
#	        define NC_CKEY_COMMA   44
#	        define NC_CKEY_MINS    45
#	        define NC_CKEY_POINT   46
#	        define NC_CKEY_SLASH   47
#	        define NC_CKEY_0 48
#	        define NC_CKEY_1 49
#	        define NC_CKEY_2 50
#	        define NC_CKEY_3 51
#	        define NC_CKEY_4 52
#	        define NC_CKEY_5 53
#	        define NC_CKEY_6 54
#	        define NC_CKEY_7 55
#	        define NC_CKEY_8 56
#	        define NC_CKEY_9 57
#	        define NC_CKEY_COLONON 58
#	        define NC_CKEY_SEMICOL 59
#	        define NC_CKEY_LESSR 60
#	        define NC_CKEY_EQUAL 61
#	        define NC_CKEY_GRETR 62
#	        define NC_CKEY_A 65
#	        define NC_CKEY_B 66
#	        define NC_CKEY_C 67
#	        define NC_CKEY_D 68
#	        define NC_CKEY_E 69
#	        define NC_CKEY_F 70
#	        define NC_CKEY_G 71
#	        define NC_CKEY_H 72
#	        define NC_CKEY_I 73
#	        define NC_CKEY_J 74
#	        define NC_CKEY_K 75
#	        define NC_CKEY_L 76
#	        define NC_CKEY_M 77
#	        define NC_CKEY_N 78
#	        define NC_CKEY_O 79
#	        define NC_CKEY_P 80
#	        define NC_CKEY_Q 81
#	        define NC_CKEY_R 82
#	        define NC_CKEY_S 83
#	        define NC_CKEY_T 84
#	        define NC_CKEY_U 85
#	        define NC_CKEY_V 86
#	        define NC_CKEY_W 87
#	        define NC_CKEY_X 88
#	        define NC_CKEY_Y 89
#	        define NC_CKEY_Z 90
#	        define NC_CKEY_a 97
#	        define NC_CKEY_b 98
#	        define NC_CKEY_c 99
#	        define NC_CKEY_d 100
#	        define NC_CKEY_e 101
#	        define NC_CKEY_f 102
#	        define NC_CKEY_g 103
#	        define NC_CKEY_h 104
#	        define NC_CKEY_i 105
#	        define NC_CKEY_j 106
#	        define NC_CKEY_k 107
#	        define NC_CKEY_l 108
#	        define NC_CKEY_m 109
#	        define NC_CKEY_n 110
#	        define NC_CKEY_o 111
#	        define NC_CKEY_p 112
#	        define NC_CKEY_q 113
#	        define NC_CKEY_r 114
#	        define NC_CKEY_s 115
#	        define NC_CKEY_t 116
#	        define NC_CKEY_u 117
#	        define NC_CKEY_v 118
#	        define NC_CKEY_w 119
#	        define NC_CKEY_x 120
#	        define NC_CKEY_y 121
#	        define NC_CKEY_z 122
#	        define NC_CKEY_F1 112
#	        define NC_CKEY_F2 113
#	        define NC_CKEY_F3 114
#	        define NC_CKEY_F4 115
#	        define NC_CKEY_F5 116
#	        define NC_CKEY_F6 117
#	        define NC_CKEY_F7 118
#	        define NC_CKEY_F8 119
#	        define NC_CKEY_F9 120
#	        define NC_CKEY_F10 121
#	        define NC_CKEY_F11 122
#	        define NC_CKEY_F12 123
#	        define NC_CKEY_RECT_DITH 177
#	        define NC_CKEY_RECT_QUAD 254
#	        define NC_CKEY_COUNT     255u
/*** cursor  ***/
#	        define NC_CCUR_0     0
#	        define NC_CCUR_1     1
#	        define NC_CCUR_2     2
#	        define NC_CCUR_3     3
#	        define NC_CCUR_4     4
#	        define NC_CCUR_5     5
#	        define NC_CCUR_6     6
#	        define NC_CCUR_7     7
#	        define NC_CCUR_LEFT  NC_CCUR_0
#	        define NC_CCUR_RIGT  NC_CCUR_1
#	        define NC_CCUR_MIDL  NC_CCUR_2
#	        define NC_CCUR_COUNT 7u
/*** events ***/
#           define NC_CBUT_RAISE ( 1u << 0u )
#           define NC_CBUT_PRESS ( 1u << 1u )
#           define NC_CBUT_FREE  ( 1u << 2u )
#           define NC_CBUT_HELD  ( 1u << 3u )
#	    endif	/* NC_WAPI_WIN */
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* NC_LIB_CORE_HXX */
#	    error "nc_lib_core.hxx must be included before this header"
#   endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif	/* NC_LIB_WAPI_HXX */