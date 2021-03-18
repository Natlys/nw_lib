#ifndef NWL_STRING_H
#define NWL_STRING_H
#include <nwl_core.hpp>
namespace NW
{
	using cstr = const char*;
	using dstr = std::string;
	using stm_io_str = std::stringstream;
	using cstr16 = const wchar_t*;
	using dstr16 = std::wstring;
}
namespace NW
{
	NW_API dstr str_format_var(cstr format, va_list& arg_list);
	NW_API dstr str_format(cstr format, ...);
	NW_API cstr str_part_left(cstr source, schar delim_char, ui32 from_left = 0);
	NW_API cstr str_part_right(cstr source, schar delim_char, ui32 from_right = 0);
	NW_API bit str_is_equal(cstr str0, cstr str1);
}
#endif // NWL_STRING_H