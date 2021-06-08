#ifndef NC_LIB_STRING_HXX
#	define NC_LIB_STRING_HXX
#	include "../nc_lib_pch.hxx"
#	if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* includes */
#   	include <string.h>
#   	include <ctype.h>
#   	include <wchar.h>
#   	include <uchar.h>
/* defines */
/** constants **/
#		define NC_STR_DIRL "\\"
#		define NC_STR_ENDL "\n"
#		define NC_STR_TABL "\t"
#		define NC_STR_SEPL ";"
#		define NC_STR_SIGL "?"
#   	define NC_GREETING "hello_native_world" NC_STR_SEPL NC_STR_ENDL
#   	define NC_VOID_STR "default"
#   	define NC_NAME_FULL_STR "nati_code"
#   	define NC_NAME_ILOG_STR "nc_ilog"
#   	define NC_NAME_OLOG_STR "nc_olog"
#   	define NC_NAME_ELOG_STR "nc_elog"
#   	define NC_NAMESPACE_STR "NC"
#   	define NC_FILE_STR __FILE__
#   	define NC_FUNC_STR __func__
#   	define NC_DATE_STR __DATE__
#   	define NC_TIME_STR __TIME__
#		if (!(defined(NC_USE_SIZE_NAME)))
#			define NC_MIN_SIZE_NAME ( 1u << 1u ) /* 2 bytes */
#			define NC_MID_SIZE_NAME ( 1u << 6u ) /* 64 bytes */
#			define NC_MAX_SIZE_NAME ( 1u << 8u ) /* 256 bytes */
#			define NC_USE_SIZE_NAME NC_MID_SIZE_NAME
#		endif /* NC_USE_SIZE_NAME */
#		if (!(defined(NC_USE_SIZE_TEXT)))
#			define NC_MIN_SIZE_TEXT ( 1u << 6u ) /* 64 bytes */
#			define NC_MID_SIZE_TEXT ( 1u << 10u ) /* 1024 bytes */
#			define NC_MAX_SIZE_TEXT ( 1u << 13u ) /* 8096 bytes */
#			define NC_USE_SIZE_TEXT NC_MID_SIZE_TEXT
#		endif /* NC_USE_SIZE_TEXT */
#		if (!(defined(NC_USE_SIZE_PATH)))
#			define NC_MIN_SIZE_PATH ( 1u << 6u ) /* 64 bytes */
#			define NC_MID_SIZE_PATH ( 1u << 7u ) /* 128 bytes */
#			define NC_MAX_SIZE_PATH ( 1u << 8u ) /* 256 bytes */
#			define NC_USE_SIZE_PATH NC_MID_SIZE_PATH
#		endif /* NC_USE_SIZE_PATH */
/** functions **/
#		define NC_STR_TEXT(code)       ( #code )
#		define NC_STR_LESS(str0, str1) ( strcmp(str0, str1) <  NC_ZERO ) /* less than */
#		define NC_STR_MORE(str0, str1) ( strcmp(str0, str1) >  NC_ZERO ) /* more than */
#		define NC_STR_TEQU(str0, str1) ( strcmp(str0, str1) == NC_ZERO ) /* truth equal to */
#		define NC_STR_FEQU(str0, str1) ( strcmp(str0, str1) != NC_ZERO ) /* false equal to */
#		define NC_STR_LEQU(str0, str1) ( strcmp(str0, str1) <= NC_ZERO ) /* less than or equal to */
#		define NC_STR_MEQU(str0, str1) ( strcmp(str0, str1) >= NC_ZERO ) /* more than or equal to */
#       define NC_STR_HASH(str, buf) ({ \
            buf = NC_ZERO;              \
            size_t len = strlen(str);   \
            size_t itr = NC_ZERO;       \
			char_t* chr = (char_t*)str; \
			while(itr < len) {          \
				buf = buf + *chr;       \
				itr = itr + 1u;         \
				chr = chr + 1u;         \
			}                           \
			buf = NC_NUM_FABS(buf);      \
		})
/* typedefs */
/* default character set */
typedef char                           char_t;
typedef const char_t                  char_tc;
typedef char_t*                         str_t;
typedef const str_t                    str_tc;
typedef const char_t*                  cstr_t;
typedef const cstr_t*                 cstr_tc;
/* signed character set */
typedef signed char                     schar_t;
typedef const schar_t                  schar_tc;
typedef schar_t*                         sstr_t;
typedef const sstr_t                    sstr_tc;
typedef const schar_t*                  csstr_t;
typedef const csstr_t*                 csstr_tc;
/* unsigned character set */
typedef unsigned char                   uchar_t;
typedef const uchar_t                  uchar_tc;
typedef uchar_t*                         ustr_t;
typedef const ustr_t                    ustr_tc;
typedef const uchar_t*                  custr_t;
typedef const custr_t*                 custr_tc;
/* wide character set */
// typedef wchar_t                      wchar_t;
typedef const wchar_t                  wchar_tc;
typedef wchar_t*                         wstr_t;
typedef const wstr_t                    wstr_tc;
typedef const wchar_t*                  cwstr_t;
typedef const cwstr_t*                 cwstr_tc;
/* chararter_type
 * description:
 * ->contains union for all types of characters;
*/
typedef struct nc_char_t {
	union {
		schar_t snar;
		uchar_t unar;
		wchar_t wide;
	};
} nc_char_t;
typedef const nc_char_t nc_char_tc;
/* dynamic_string_iterator_type
 * description:
*/
#		define nc_dstr_iter_t(tname) nc_dstr_iter##_##tname
#		define NC_TYPEDEF_DSTR_ITER(tname) \
			typedef struct                 \
				nc_dstr_iter_t(tname)      \
				nc_dstr_iter_t(tname);     \
			typedef struct                 \
				nc_dstr_iter_t(tname) {    \
					tname data;            \
				} nc_dstr_iter_t(tname);   \
/** type is defined **/
/* dynamic_string_main_type
 * description:
*/
#		define nc_dstr_main_t(tname) nc_dstr_main##_##tname
#		define NC_TYPEDEF_DSTR_MAIN(tname)       \
			typedef struct                       \
				nc_dstr_main_t(tname)            \
				nc_dstr_main_t(tname);           \
			typedef struct                       \
				nc_dstr_main_t(tname) {          \
					nc_dstr_iter_t(tname)* head; \
					nc_dstr_iter_t(tname)* back; \
					size_t numb;                 \
				} nc_dstr_main_t(tname);         \
/** type is defined **/
/** codetor **/
#		define nc_dstr_ctor(tname, ref) ({ \
			ref.head = NC_NULL;            \
			ref.back = NC_NULL;            \
			ref.numb = NC_ZERO;            \
})
#		define nc_dstr_dtor(tname, ref) ({         \
			nc_dstr_set_numb(tname, ref, NC_ZERO); \
			ref.head = NC_NULL;                    \
			ref.back = NC_NULL;                    \
			ref.numb = NC_ZERO;                    \
})
/** getters **/
#		define nc_dstr_get_iter(tname, ref, indx, iter) ({ \
			iter = ref.head + indx;                        \
})
#		define nc_dstr_get_elem(tname, ref, indx, elem) ({ \
			memcpy(&elem, ref.head + indx, sizeof(tname)); \
})
#		define nc_dstr_get_data(tname, ref, data) ({ \
			memcpy(data, ref.head, ref.numb);        \
})
#		define nc_dstr_get_part(tname, ref, indx, leng, part) ({ \
			memcpy(part, ref.head + indx, sizeof(tname) * leng); \
})
/** setters **/
#		define nc_dstr_set_numb(tname, ref, numb) ({  \
			size_t sz_old = sizeof(tname) * ref.numb; \
			size_t sz_new = sizeof(tname) * numb;     \
			NC_MEM_EDIT(ref.head, sz_old, sz_new);    \
			ref.numb = numb;                          \
			ref.back = ref.head + numb;               \
			*ref.back = NC_ZERO;                      \
})
#		define nc_dstr_set_elem(tname, ref, indx, elem) ({ \
			ref.head[indx] = elem;                         \
})
#		define nc_dstr_set_data(tname, ref, data) ({     \
			size_tc size = sizeof(tname) * strlen(data); \
			memcpy(ref.head, data, size);                \
})
#		define nc_dstr_set_part(tname, ref, indx, leng, part) ({ \
			memcpy(ref.head + indx, part, sizeof(tname) * leng); \
})
/** vetters **/
/** command **/
/** other names **/
#		define nc_dstr_t(tname) nc_dstr_main_t(tname)
#		define NC_TYPEDEF_DSTR(tname)    \
			NC_TYPEDEF_DSTR_ITER(tname); \
			NC_TYPEDEF_DSTR_MAIN(tname); \
/** type is defined **/
NC_TYPEDEF_DSTR(char_t);
NC_TYPEDEF_DSTR(schar_t);
NC_TYPEDEF_DSTR(uchar_t);
NC_TYPEDEF_DSTR(wchar_t);
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* nc_lib_str.hxx is included without nc_lib_core.hxx */
#	    error "nc_lib_core.hxx must be included before this header"
#	endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif /* NC_LIB_STRING_HXX */