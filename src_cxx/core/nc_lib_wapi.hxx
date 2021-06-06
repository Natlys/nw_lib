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
#	        define NC_KEYCODE_BACK  8
#	        define NC_KEYCODE_VTAB  9
#	        define NC_KEYCODE_HTAB  11
#	        define NC_KEYCODE_ENTER 13
#	        define NC_KEYCODE_SHIFT 16
#	        define NC_KEYCODE_CONTR 18
#	        define NC_KEYCODE_ALTER 19
#	        define NC_KEYCODE_PAUSE 20
#	        define NC_KEYCODE_CAPS  26
#	        define NC_KEYCODE_ESCP  27
#	        define NC_KEYCODE_ARROWL 37
#	        define NC_KEYCODE_ARROWU 38
#	        define NC_KEYCODE_ARROWR 39
#	        define NC_KEYCODE_ARROWD 40
#	        define NC_KEYCODE_INSERT 45
#	        define NC_KEYCODE_DELETE 46
#	        define NC_KEYCODE_HOME   47
#	        define NC_KEYCODE_SPACE   32
#	        define NC_KEYCODE_EXCLAIM 33
#	        define NC_KEYCODE_QUOTES  34
#	        define NC_KEYCODE_HASH    35
#	        define NC_KEYCODE_DOLLAR  36
#	        define NC_KEYCODE_PERCENT  37
#	        define NC_KEYCODE_AMPERSAND  38
#	        define NC_KEYCODE_APOSTROPH  39
#	        define NC_KEYCODE_BRACKETL 40
#	        define NC_KEYCODE_BRACKETR 41
#	        define NC_KEYCODE_STAR    42
#	        define NC_KEYCODE_PLUS    43
#	        define NC_KEYCODE_COMMA   44
#	        define NC_KEYCODE_MINS    45
#	        define NC_KEYCODE_POINT   46
#	        define NC_KEYCODE_SLASH   47
#	        define NC_KEYCODE_0 48
#	        define NC_KEYCODE_1 49
#	        define NC_KEYCODE_2 50
#	        define NC_KEYCODE_3 51
#	        define NC_KEYCODE_4 52
#	        define NC_KEYCODE_5 53
#	        define NC_KEYCODE_6 54
#	        define NC_KEYCODE_7 55
#	        define NC_KEYCODE_8 56
#	        define NC_KEYCODE_9 57
#	        define NC_KEYCODE_COLONON 58
#	        define NC_KEYCODE_SEMICOL 59
#	        define NC_KEYCODE_LESSR 60
#	        define NC_KEYCODE_EQUAL 61
#	        define NC_KEYCODE_GRETR 62
#	        define NC_KEYCODE_A 65
#	        define NC_KEYCODE_B 66
#	        define NC_KEYCODE_C 67
#	        define NC_KEYCODE_D 68
#	        define NC_KEYCODE_E 69
#	        define NC_KEYCODE_F 70
#	        define NC_KEYCODE_G 71
#	        define NC_KEYCODE_H 72
#	        define NC_KEYCODE_I 73
#	        define NC_KEYCODE_J 74
#	        define NC_KEYCODE_K 75
#	        define NC_KEYCODE_L 76
#	        define NC_KEYCODE_M 77
#	        define NC_KEYCODE_N 78
#	        define NC_KEYCODE_O 79
#	        define NC_KEYCODE_P 80
#	        define NC_KEYCODE_Q 81
#	        define NC_KEYCODE_R 82
#	        define NC_KEYCODE_S 83
#	        define NC_KEYCODE_T 84
#	        define NC_KEYCODE_U 85
#	        define NC_KEYCODE_V 86
#	        define NC_KEYCODE_W 87
#	        define NC_KEYCODE_X 88
#	        define NC_KEYCODE_Y 89
#	        define NC_KEYCODE_Z 90
#	        define NC_KEYCODE_a 97
#	        define NC_KEYCODE_b 98
#	        define NC_KEYCODE_c 99
#	        define NC_KEYCODE_d 100
#	        define NC_KEYCODE_e 101
#	        define NC_KEYCODE_f 102
#	        define NC_KEYCODE_g 103
#	        define NC_KEYCODE_h 104
#	        define NC_KEYCODE_i 105
#	        define NC_KEYCODE_j 106
#	        define NC_KEYCODE_k 107
#	        define NC_KEYCODE_l 108
#	        define NC_KEYCODE_m 109
#	        define NC_KEYCODE_n 110
#	        define NC_KEYCODE_o 111
#	        define NC_KEYCODE_p 112
#	        define NC_KEYCODE_q 113
#	        define NC_KEYCODE_r 114
#	        define NC_KEYCODE_s 115
#	        define NC_KEYCODE_t 116
#	        define NC_KEYCODE_u 117
#	        define NC_KEYCODE_v 118
#	        define NC_KEYCODE_w 119
#	        define NC_KEYCODE_x 120
#	        define NC_KEYCODE_y 121
#	        define NC_KEYCODE_z 122
#	        define NC_KEYCODE_F1 112
#	        define NC_KEYCODE_F2 113
#	        define NC_KEYCODE_F3 114
#	        define NC_KEYCODE_F4 115
#	        define NC_KEYCODE_F5 116
#	        define NC_KEYCODE_F6 117
#	        define NC_KEYCODE_F7 118
#	        define NC_KEYCODE_F8 119
#	        define NC_KEYCODE_F9 120
#	        define NC_KEYCODE_F10 121
#	        define NC_KEYCODE_F11 122
#	        define NC_KEYCODE_F12 123
#	        define NC_KEYCODE_RECT_DITH 177
#	        define NC_KEYCODE_RECT_QUAD 254
#	        define NC_KEYCODE_COUNT     255u
/*** cursor  ***/
#	        define NC_CURCODE_0     0
#	        define NC_CURCODE_1     1
#	        define NC_CURCODE_2     2
#	        define NC_CURCODE_3     3
#	        define NC_CURCODE_4     4
#	        define NC_CURCODE_5     5
#	        define NC_CURCODE_6     6
#	        define NC_CURCODE_7     7
#	        define NC_CURCODE_LEFT  NC_CURCODE_0
#	        define NC_CURCODE_RIGT  NC_CURCODE_1
#	        define NC_CURCODE_MIDL  NC_CURCODE_2
#	        define NC_CURCODE_COUNT 7u
/*** events ***/
#           define NC_EVTCODE_FREE 0u
#           define NC_EVTCODE_HELD 1u
#	    endif	/* NC_WAPI_WIN */
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* NC_LIB_CORE_HXX */
#	    error "nc_lib_core.hxx must be included before this header"
#   endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif	/* NC_LIB_WAPI_HXX */