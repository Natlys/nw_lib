#ifndef NW_CORE_STRING_H
#define NW_CORE_STRING_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
#	define NW_MAX_NAME   1 << 6
#	define NW_STR_EQUAL(str0, str1) ( strcmp(str0, str1) == 0 )
namespace NW
{
	// default character set
	typedef char                           char_t;
	typedef const char_t                  char_tc;
	typedef char_t*                         str_t;
	typedef const str_t                    str_tc;
	typedef const char_t*                  cstr_t;
	typedef const cstr_t*                 cstr_tc;
	typedef std::basic_string<char_t>      dstr_t;
	typedef const dstr_t                  dstr_tc;
	typedef std::basic_string_view<char_t> vstr_t;
	typedef const vstr_t                  vstr_tc;
	// signed character set
	typedef signed char                     schar_t;
	typedef const schar_t                  schar_tc;
	typedef schar_t*                         sstr_t;
	typedef const sstr_t                    sstr_tc;
	typedef const schar_t*                  csstr_t;
	typedef const csstr_t*                 csstr_tc;
	typedef std::basic_string<schar_t>      dsstr_t;
	typedef const dsstr_t                  dsstr_tc;
	typedef std::basic_string_view<schar_t> vsstr_t;
	typedef const vsstr_t                  vsstr_tc;
	// unsigned character set
	typedef unsigned char                   uchar_t;
	typedef const uchar_t                  uchar_tc;
	typedef uchar_t*                         ustr_t;
	typedef const ustr_t                    ustr_tc;
	typedef const uchar_t*                  custr_t;
	typedef const custr_t*                 custr_tc;
	typedef std::basic_string<uchar_t>      dustr_t;
	typedef const dustr_t                  dustr_tc;
	typedef std::basic_string_view<uchar_t> vustr_t;
	typedef const vustr_t                  vustr_tc;
	// wide character set
	// typedef wchar_t                      wchar_t;
	typedef const wchar_t                  wchar_tc;
	typedef wchar_t*                         wstr_t;
	typedef const wstr_t                    wstr_tc;
	typedef const wchar_t*                  cwstr_t;
	typedef const cwstr_t*                 cwstr_tc;
	typedef std::basic_string<wchar_t>      dwstr_t;
	typedef const dwstr_t                  dwstr_tc;
	typedef std::basic_string_view<wchar_t> vwstr_t;
	typedef const vwstr_t                   vwtr_tc;

	struct nwchar_t
	{
		union { schar_t snar; uchar_t unar; wchar_t wide; };
		inline operator schar_t& () { return snar; }
		inline operator uchar_t& () { return unar; }
		inline operator wchar_t& () { return wide; }
	};
	typedef const nwchar_t  nwchar_tc;
}
#endif	// NW_LIB_CORE_HPP
#endif // NW_CORE_STRING_H