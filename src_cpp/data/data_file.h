#ifndef NWL_DATA_FILE_H
#define NWL_DATA_FILE_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include "data_switch.h"
namespace NW
{
    struct fhandle_finder
    {
    public:
        __std_fs_dir_handle _Handle = __std_fs_dir_handle::_Invalid;
    public:
        fhandle_finder() noexcept = default;
        fhandle_finder(fhandle_finder&& _Rhs) noexcept :
            _Handle(_STD exchange(_Rhs._Handle, __std_fs_dir_handle::_Invalid)) {}

        fhandle_finder& operator=(fhandle_finder&& _Rhs) noexcept {
            auto _Tmp = _STD exchange(_Rhs._Handle, __std_fs_dir_handle::_Invalid);
            _Tmp = _STD exchange(_Handle, _Tmp);
            __std_fs_directory_iterator_close(_Tmp);
            return *this;
        }

        __std_win_error _Open(cstr16 _Path_spec, __std_fs_find_data* ress) noexcept { return __std_fs_directory_iterator_open(_Path_spec, &_Handle, ress); }

        ~fhandle_finder() noexcept { __std_fs_directory_iterator_close(_Handle); }

        explicit operator bool() const noexcept { return _Handle != __std_fs_dir_handle::_Invalid; }
    };
}
#endif	// NWL_DATA_FILE_H