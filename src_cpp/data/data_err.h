#ifndef DATA_ERROR_H
#define DATA_ERROR_H
#include <nwl_core.hpp>
#include "data_path.h"
#include "data_switch.h"
namespace NW
{
    /// filesystem_error class
    class filesystem_error : public std::system_error
    { // base of all filesystem-error exceptions
    public:
        filesystem_error(const std::string& _Message, const std::error_code _Errcode) :
            std::system_error(_Errcode, _Message), _What(std::runtime_error::what()) {}

        filesystem_error(const std::string& _Message, const data_path& _Path1_arg, const std::error_code _Errcode) :
            std::system_error(_Errcode, _Message), _Path1(_Path1_arg), _Path2(),
            _What(_Pretty_message(std::runtime_error::what(), _Path1_arg)) {}

        filesystem_error(const std::string& _Message, const data_path& _Path1_arg, const data_path& _Path2_arg,
            const std::error_code _Errcode) :
            std::system_error(_Errcode, _Message), _Path1(_Path1_arg), _Path2(_Path2_arg),
            _What(_Pretty_message(std::runtime_error::what(), _Path1_arg, _Path2_arg)) {}
        // --getters
        const data_path& path1() const noexcept { return _Path1; }
        const data_path& path2() const noexcept { return _Path2; }
        virtual const char* what() const noexcept override { return _What.c_str(); }
    private:
        static std::string _Pretty_message(const std::string_view _Op, const data_path& _Path1, const data_path& _Path2 = {}) {
            using namespace std::string_view_literals; // TRANSITION, VSO-571749
            std::string res;
            // Convert the paths to narrow encoding in a way that gracefully handles non-encodable characters
            const auto code_page = __std_fs_code_page();
            const std::string _Path1_str = convert_wchar_to_schar_replace<char_traits<char>>(
                code_page, _Path1.native(), allocator<char>{});
            const std::string _Path2_str = convert_wchar_to_schar_replace<char_traits<char>>(
                code_page, _Path2.native(), allocator<char>{});
            res.reserve(_Op.size() + (_Path2_str.empty() ? 4 : 8) + _Path1_str.size() + _Path2_str.size());
            res += _Op;
            res += R"(: ")"sv; // 3 chars
            res += _Path1_str;
            if (!_Path2_str.empty()) {
                res += R"(", ")"sv; // 4 chars
                res += _Path2_str;
            }
            res += '"'; // 1 char
            return res;
        }
    private:
        data_path _Path1;
        data_path _Path2;
        std::string _What;
    };

    inline void throw_file_sys_err(cstr _Op, __std_win_error _Error) {
        throw (filesystem_error(_Op, make_err_code(_Error)));
    }

    inline void throw_file_sys_err(cstr _Op, __std_win_error _Error, const data_path& _Path1) {
        throw (filesystem_error(_Op, _Path1, make_err_code(_Error)));
    }

    inline void throw_file_sys_err(
        const char* _Op, __std_win_error _Error, const data_path& _Path1, const data_path& _Path2) {
        throw (filesystem_error(_Op, _Path1, _Path2, make_err_code(_Error)));
    }

    inline void throw_file_sys_err(cstr _Op, const std::error_code& _Error, const data_path& _Path1) {
        throw (filesystem_error(_Op, _Path1, _Error));
    }

    inline void throw_file_sys_err(cstr _Op, const std::error_code& _Error, const data_path& _Path1, const data_path& _Path2) {
        throw (filesystem_error(_Op, _Path1, _Path2, _Error));
    }
}
#endif	// DATA_ERROR_H