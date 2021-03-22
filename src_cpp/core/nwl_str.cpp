#include <nwl_pch.hpp>
#include "nwl_str.h"

#include <io/io_err.h>
#include <mem/mem_sys.h>

namespace NW
{
	void str_format_var(str buffer, cstr format, va_list& arg_list) {
		schar ccurr = format[0];
		size ncurr = 0;
		size nend = 0;
		size nlen = strlen(format);

		while (ncurr < nlen) {
			ccurr = format[ncurr++];
			switch (ccurr) {
			case '%': {
				switch (ccurr = format[++ncurr]) {
					// nothing special; simple percent
				case '%':
					buffer[nend++] = ccurr; break;
					// signed number
				case 's':
					switch (ccurr = format[++ncurr]) {
					case 'b': _itoa(va_arg(arg_list, si8), &buffer[nend++], 10); break;
					case 's': _itoa(va_arg(arg_list, si16), &buffer[nend++], 10); break;
					case 'i': _itoa(va_arg(arg_list, si32), &buffer[nend++], 10); break;
					case 'l': _itoa(va_arg(arg_list, si64), &buffer[nend++], 10); break;
					default:throw run_error(__FILE__, __LINE__); return; break;
					} break;
					// unsigned number
				case 'u':
					switch (ccurr = format[++ncurr]) {
					case 'b': _itoa(va_arg(arg_list, ui8), &buffer[nend++], 10); break;
					case 's': _itoa(va_arg(arg_list, ui16), &buffer[nend++], 10); break;
					case 'i': _itoa(va_arg(arg_list, ui32), &buffer[nend++], 10); break;
					case 'l': _itoa(va_arg(arg_list, ui64), &buffer[nend++], 10); break;
					default: throw run_error(__FILE__, __LINE__); return; break;
					} break;
					// floating point number
				case 'f':
					switch (ccurr = format[++ncurr]) {
					case 'f': strcpy(&buffer[nend++], &std::to_string(va_arg(arg_list, f32))[0]); break;
					case 'd': strcpy(&buffer[nend++], &std::to_string(va_arg(arg_list, f64))[0]);  break;
					default: throw run_error(__FILE__, __LINE__); return; break;
					} break;
					// bytes
				case 'c':
					switch (ccurr = format[++ncurr]) {
					case 's': strcpy(&buffer[nend++], va_arg(arg_list, sbyte*)); break;
					default: throw run_error(__FILE__, __LINE__); return; break;
					} break;
				default: throw run_error(__FILE__, __LINE__); return; break;
				} break;
			}
			}
		}
	}
	dstr str_format_var(cstr format, va_list& arg_list) {
		schar ccurr = format[0];
		size ncurr = 0;
		size nlen = strlen(format);
		dstr result;

		while (ncurr < nlen) {
			ccurr = format[ncurr++];
			switch (ccurr) {
			case '%': {
				switch (ccurr = format[ncurr++]) {
					// nothing special; simple percent
				case '%':
					result.push_back(ccurr); break;
					// signed number
				case 's':
					switch (ccurr = format[ncurr++]) {
					case 'b': _itoa_s(va_arg(arg_list, si8), &result.back(), result.size(), 10); break;
					case 's': _itoa_s(va_arg(arg_list, si16), &result.back(), result.size(), 10); break;
					case 'i': _itoa_s(va_arg(arg_list, si32), &result.back(), result.size(), 10); break;
					case 'l': _itoa_s(va_arg(arg_list, si64), &result.back(), result.size(), 10); break;
					default:throw run_error(__FILE__, __LINE__); return result; break;
					} break;
					// unsigned number
				case 'u':
					switch (ccurr = format[ncurr++]) {
					case 'b': _itoa_s(va_arg(arg_list, ui8), &result.back(), result.size(), 10); break;
					case 's': _itoa_s(va_arg(arg_list, ui16), &result.back(), result.size(), 10); break;
					case 'i': _itoa_s(va_arg(arg_list, ui32), &result.back(), result.size(), 10); break;
					case 'l': _itoa_s(va_arg(arg_list, ui64), &result.back(), result.size(), 10); break;
					default: throw run_error(__FILE__, __LINE__); return result; break;
					} break;
					// floating point number
				case 'f':
					switch (ccurr = format[++ncurr]) {
					case 'f': result += std::to_string(va_arg(arg_list, f32)); break;
					case 'd': result += std::to_string(va_arg(arg_list, f64));  break;
					default: throw run_error(__FILE__, __LINE__); return result; break;
					} break;
					// characters
				case 'c':
					switch (ccurr = format[ncurr++]) {
					case 's': result += va_arg(arg_list, sbyte*); break;
					default: throw run_error(__FILE__, __LINE__); return result; break;
					} break;
				default: throw run_error(__FILE__, __LINE__); return result; break;
				} break;
			}
			default: result.push_back(ccurr); break;
			}
		}
		result.push_back('\0');
		return result;
	}
	dstr str_format(cstr format, ...) {
		va_list arg_list;
		va_start(arg_list, format);
		dstr result = str_format_var(format, arg_list);
		va_end(arg_list);
		return result;
	}
	cstr str_part_left(cstr source, schar delim_char, ui32 offset_from_left) {
		size length = strlen(source);
		if (length == 0) { return ""; }
		size ncurr = offset_from_left % length;
		while (source[ncurr] != delim_char && ncurr <= length) { ncurr += 1; }
		return &source[ncurr];
	}
	cstr str_part_right(cstr source, schar delim_char, ui32 offset_from_right) {
		size length = strlen(source);
		if (length == 0) { return ""; }
		size ncurr= length - (offset_from_right % length);
		while (source[ncurr] != delim_char && ncurr <= length) { ncurr -= 1; }
		return &source[ncurr];
	}
	cstr str_sub_left(cstr source, ui32 nof_chars, ui32 offset) {
		size length = strlen(source) - nof_chars - offset;
		if (length < strlen(source)) { throw run_error(__FILE__, __LINE__); }
		schar* buf = mem_sys::get().new_arr<schar>(length);
		strcpy_s(buf, length, source);
		cstr result = buf;
		mem_sys::get().del_arr<schar>(buf, length);
		return result;
	}
	cstr str_sub_right(cstr source, ui32 nof_chars, ui32 offset) {
		size length = strlen(source) - nof_chars - offset;
		if (length < strlen(source)) { throw run_error(__FILE__, __LINE__); }
		schar* buf = mem_sys::get().new_arr<schar>(length);
		strcpy_s(buf, length, source);
		cstr result = buf;
		mem_sys::get().del_arr<schar>(buf, length);
		return result;
	}
	bit str_is_equal(cstr str0, cstr str1) {
		size ncurr = 0;
		while(str0[ncurr++] != '\0') { if (str0[ncurr] != str1[ncurr]) { return false; } }
		return true;
	}
}