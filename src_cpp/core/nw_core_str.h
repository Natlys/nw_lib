#ifndef NW_CORE_STRING_H
#define NW_CORE_STRING_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	// narrow character set
	typedef char                       schar;
	typedef unsigned char              uchar;
	typedef char*                       sstr;
	typedef const char*                csstr;
	typedef std::string                dstr8;
	typedef const std::string         cdstr8;
	typedef std::string_view       str8_view;
	typedef const str8_view       cstr8_view;
	// wide character set
	typedef wchar_t                    wchar;
	typedef wchar_t*                    wstr;
	typedef const wchar_t*             cwstr;
	typedef std::wstring_view     str16_view;

	typedef std::wstring              dstr16;
	typedef const dstr16             cdstr16;
	typedef const str16_view     cstr16_view;
	typedef std::wstringstream  stm_io_str16;
	typedef const stm_io_str16 cstm_io_str16;
	// default character set
	typedef schar*                   str; // default string type
	typedef const schar*            cstr; // default constant string type
	typedef dstr8                   dstr;
	typedef const dstr             cdstr;
	typedef str8_view           str_view;
	typedef const str_view     cstr_view;
}
#endif	// NW_LIB_CORE_HPP
#endif // NW_CORE_STRING_H