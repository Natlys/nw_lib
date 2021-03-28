#ifndef NWLIB_STD_STRING_H
#define NWLIB_STD_STRING_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	// narrow string
	using dstr8 = std::string;
	using cdstr8 = const std::string;
	using str8_view = std::string_view;
	using cstr8_view = const str8_view;
	using stm_io_str8 = std::stringstream;
	using cstm_io_str8 = const stm_io_str8;
	// wide string
	using dstr16 = std::wstring;
	using cdstr16 = const dstr16;
	using str16_view = std::wstring_view;
	using cstr16_view = const str16_view;
	using stm_io_str16 = std::wstringstream;
	using cstm_io_str16 = const stm_io_str16;
	// default string
	using dstr = dstr8;
	using cdstr = const dstr;
	using str_view = str8_view;
	using cstr_view = const str_view;
	using stm_io_str = stm_io_str8;
	using cstm_io_str = const stm_io_str;
}
namespace NWLIB
{
	NW_API void str_format_var(str buffer, cstr format, va_list& arg_list);
	NW_API dstr str_format_var(cstr format, va_list& arg_list);
	NW_API dstr str_format(cstr format, ...);
	NW_API cstr str_part_left(cstr source, schar delim_char, size from_left = 0);
	NW_API cstr str_part_right(cstr source, schar delim_char, size from_right = 0);
	NW_API cstr str_sub_left(cstr source, size nof_chars, size offset = 0);
	NW_API cstr str_sub_right(cstr source, size nof_chars, size offset = 0);
	NW_API v1b str_is_equal(cstr str0, cstr str1);
}
#endif	// NW_API
#endif // NWLIB_STD_STRING_H