#include <nwl_pch.hpp>
#include "data_path.h"
#ifdef NW_DATA_PATH_STD
#else
#include "data_sys.h"
#include <io/io_err.h>
namespace NW
{

	data_path::data_path() :
		data_path(data_sys::get_path())
	{
	}
	data_path::data_path(cstr source) :
		m_str(source),
		m_is_dir(false)
	{
		DWORD attribs = ::GetFileAttributesA(&m_str[0]);
		m_is_dir = attribs & FILE_ATTRIBUTE_DIRECTORY;
		remake();
	}
	data_path::~data_path()
	{
	}
	// --setters
	// --==<core_methods>==--
	bit data_path::remake()
	{
		m_subs.clear();
		WIN32_FIND_DATAA data = { 0 };
		if (is_directory()) {
			HANDLE handle = FindFirstFileA(&(m_str + NW_DIR + "*")[0], &data);
			if (handle == INVALID_HANDLE_VALUE) {
				DWORD err_code = ::GetLastError();
				if (err_code == ERROR_FILE_NOT_FOUND) { }
				::FindClose(handle);
				return false;
			}
			if (::FindNextFileA(handle, &data)) {
				while (::FindNextFileA(handle, &data)) {
					data_path next(&(m_str + NW_DIR + data.cFileName)[0]);
					if (!next.remake()) {}
					m_subs.push_back(next);
				}
				::FindClose(handle);
			}
		}

		return true;
	}
	// --==</core_methods>==--
}
#endif	// NWL_DATA_PATH_STD