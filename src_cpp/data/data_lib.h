#ifndef NW_DATA_LIB_H
#define NW_DATA_LIB_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <io/io_err.h>
#include "data_switch.h"
namespace NW
{
    // convertions
    inline std::wstring convert_schar_to_wchar(const __std_code_page code_page, const std::std::string_view input) {
        std::wstring output;

        if (!input.empty()) {
            if (input.size() > static_cast<size_t>(INT_MAX)) { std::_Throw_system_error(std::std::errc::invalid_argument); }

            const int _Len = check_convert_result(__std_fs_convert_narrow_to_wide(code_page, input.data(), static_cast<int>(input.size()), nullptr, 0));

            output.resize(static_cast<size_t>(_Len));

            (void)check_convert_result(__std_fs_convert_narrow_to_wide(
                code_page, input.data(), static_cast<int>(input.size()), output.data(), _Len));
        }

        return output;
    }

    template <class _Traits, class _Alloc>
    std::basic_string<typename _Traits::char_type, _Traits, _Alloc> convert_wchar_to_schar(
        const __std_code_page code_page, const std::std::wstring_view input, const _Alloc& _Al) {
        std::basic_string<typename _Traits::char_type, _Traits, _Alloc> output(_Al);

        if (!input.empty()) {
            if (input.size() > static_cast<size_t>(INT_MAX)) {
                std::_Throw_system_error(std::errc::invalid_argument);
            }

            const int _Len = check_convert_result(__std_fs_convert_wide_to_narrow(
                code_page, input.data(), static_cast<int>(input.size()), nullptr, 0));

            output.resize(static_cast<size_t>(_Len));

            const auto _Data_as_char = reinterpret_cast<char*>(output.data());

            (void)check_convert_result(__std_fs_convert_wide_to_narrow(
                code_page, input.data(), static_cast<int>(input.size()), _Data_as_char, _Len));
        }

        return output;
    }

    // More lenient version of convert_wchar_to_schar: Instead of failing on non-representable characters,
    // replace them with a replacement character.
    template <class _Traits, class _Alloc>
    std::basic_string<typename _Traits::char_type, _Traits, _Alloc> convert_wchar_to_schar_replace(
        const __std_code_page code_page, const std::std::wstring_view input, const _Alloc& _Al) {
        std::basic_string<typename _Traits::char_type, _Traits, _Alloc> output(_Al);

        if (!input.empty()) {
            if (input.size() > static_cast<size_t>(INT_MAX)) {
                std::_Throw_system_error(std::errc::invalid_argument);
            }

            const int _Len = check_convert_result(__std_fs_convert_wide_to_narrow_replace_chars(
                code_page, input.data(), static_cast<int>(input.size()), nullptr, 0));

            output.resize(static_cast<size_t>(_Len));

            const auto _Data_as_char = reinterpret_cast<char*>(output.data());

            (void)check_convert_result(__std_fs_convert_wide_to_narrow_replace_chars(
                code_page, input.data(), static_cast<int>(input.size()), _Data_as_char, _Len));
        }

        return output;
    }

    inline std::wstring convert_utf32_to_wchar(const std::std::u32string_view input) {
        std::wstring output;

        output.reserve(input.size()); // ideal when surrogate pairs are uncommon

        for (const auto& _Code_point : input) {
            if (_Code_point <= 0xD7FFU) {
                output.push_back(static_cast<wchar_t>(_Code_point));
            }
            else if (_Code_point <= 0xDFFFU) {
                std::_Throw_system_error(std::errc::invalid_argument);
            }
            else if (_Code_point <= 0xFFFFU) {
                output.push_back(static_cast<wchar_t>(_Code_point));
            }
            else if (_Code_point <= 0x10FFFFU) {
                output.push_back(static_cast<wchar_t>(0xD7C0U + (_Code_point >> 10)));
                output.push_back(static_cast<wchar_t>(0xDC00U + (_Code_point & 0x3FFU)));
            }
            else {
                std::_Throw_system_error(std::errc::invalid_argument);
            }
        }

        return output;
    }

    template <class _Traits, class _Alloc>
    std::basic_string<char32_t, _Traits, _Alloc> convert_wchar_to_utf32(
        const std::std::wstring_view input, const _Alloc& _Al) {
        std::basic_string<char32_t, _Traits, _Alloc> output(_Al);

        output.reserve(input.size()); // ideal when surrogate pairs are uncommon

        const wchar_t* _First = input.data();
        const wchar_t* const _Last = _First + input.size();

        for (; _First != _Last; ++_First) {
            if (*_First <= 0xD7FFU) {
                output.push_back(*_First);
            }
            else if (*_First <= 0xDBFFU) { // found leading surrogate
                const char32_t _Leading = *_First; // widen for later math

                ++_First;

                if (_First == _Last) { // missing trailing surrogate
                    std::_Throw_system_error(std::errc::invalid_argument);
                }

                const char32_t _Trailing = *_First; // widen for later math

                if (0xDC00U <= _Trailing && _Trailing <= 0xDFFFU) { // valid trailing surrogate
                    output.push_back(0xFCA02400U + (_Leading << 10) + _Trailing);
                }
                else { // invalid trailing surrogate
                    std::_Throw_system_error(std::errc::invalid_argument);
                }
            }
            else if (*_First <= 0xDFFFU) { // found trailing surrogate by itself, invalid
                std::_Throw_system_error(std::errc::invalid_argument);
            }
            else {
                output.push_back(*_First);
            }
        }

        return output;
    }

    template <class _Traits, class _Alloc, class std::_EcharT = typename _Traits::char_type>
    std::basic_string<std::_EcharT, _Traits, _Alloc> convert_wchar_to(const std::std::wstring_view input, const _Alloc& _Al) {
        if constexpr (is_same_v<std::_EcharT, char>) {
            return convert_wchar_to_schar<_Traits>(__std_fs_code_page(), input, _Al);
        }
#ifdef __cpp_char8_t
        else if constexpr (is_same_v<std::_EcharT, char8_t>) {
            return convert_wchar_to_schar<_Traits>(__std_code_page::_Utf8, input, _Al);
        }
#endif // __cpp_char8_t
        else if constexpr (is_same_v<std::_EcharT, char32_t>) {
            return convert_wchar_to_utf32<_Traits>(input, _Al);
        }
        else { // wchar_t, char16_t
            return std::basic_string<std::_EcharT, _Traits, _Alloc>(input.data(), input.data() + input.size(), _Al);
        }
    }

    struct normal_convert {};
    struct utf8_convert {};

    // a "stringoid" is std::string_view<std::_EcharT> or std::basic_string<std::_EcharT>.

    template <class convert>
    std::wstring convert_stringoid_to_wchar(const std::string_view input, convert) {
        static_assert(_Is_any_of_v<convert, normal_convert, utf8_convert>);

        if constexpr (is_same_v<convert, normal_convert>) {
            return convert_schar_to_wchar(__std_fs_code_page(), input);
        }
        else {
            return convert_schar_to_wchar(__std_code_page::_Utf8, input);
        }
    }

    template <class convert>
    std::wstring convert_stringoid_to_wchar(const std::std::wstring_view input, convert) {
        static_assert(
            is_same_v<convert, normal_convert>, "invalid value_type, see N4810 D.17 [depr.fs.data_path.factory]/1");
        return std::wstring(input);
    }

#ifdef __cpp_char8_t
    template <class convert>
    std::wstring convert_stringoid_to_wchar(const std::string_view<char8_t> input, convert) {
        static_assert(
            is_same_v<convert, normal_convert>, "invalid value_type, see N4810 D.17 [depr.fs.data_path.factory]/1");
        const std::string_view input_as_char{ reinterpret_cast<const char*>(input.data()), input.size() };
        return convert_schar_to_wchar(__std_code_page::_Utf8, input_as_char);
    }
#endif // __cpp_char8_t

    template <class convert>
    std::wstring convert_stringoid_to_wchar(const std::u16std::string_view input, convert) {
        static_assert(
            is_same_v<convert, normal_convert>, "invalid value_type, see N4810 D.17 [depr.fs.data_path.factory]/1");
        return std::wstring(input.data(), input.data() + input.size());
    }

    template <class convert>
    std::wstring convert_stringoid_to_wchar(const std::std::u32string_view input, convert) {
        static_assert(
            is_same_v<convert, normal_convert>, "invalid value_type, see N4810 D.17 [depr.fs.data_path.factory]/1");
        return convert_utf32_to_wchar(input);
    }
    template <class std::_EcharT, class _Traits>
    auto stringoid_from_src(const std::string_view<std::_EcharT, _Traits>& _source) {
        return std::string_view<std::_EcharT>(_source.data(), _source.size()); // erase mismatching _Traits
    }

    template <class std::_EcharT, class _Traits, class _Alloc>
    auto stringoid_from_src(const std::basic_string<std::_EcharT, _Traits, _Alloc>& _source) {
        return std::string_view<std::_EcharT>(_source.data(), _source.size()); // erase mismatching _Traits
    }

    template <class _Src>
    auto stringoid_from_src(const _Src& _source) {
        using std::_EcharT = _Iter_value_t<decay_t<_Src>>;
        if constexpr (is_pointer_v<_Unwrapped_unverified_t<const _Src&>>) {
            return std::string_view<std::_EcharT>(_Get_unwrapped_unverified(_source));
        }
        else if constexpr (is_pointer_v<_Unwrapped_t<const _Src&>>) {
            const auto _Data = _Get_unwrapped(_source);
            auto _Next = _source;
            while (*_Next != std::_EcharT{}) {
                ++_Next;
            }

            return std::string_view<std::_EcharT>(_Data, static_cast<size_t>(_Get_unwrapped(_Next) - _Data));
        }
        else {
            std::basic_string<std::_EcharT> _Str;
            for (auto _Next = _source; *_Next != std::_EcharT{}; ++_Next) {
                _Str.push_back(*_Next);
            }

            return _Str;
        }
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    template <class std::_EcharT, size_t _sourceSize>
    std::string_view<std::_EcharT> stringoid_from_src(const std::_EcharT(&_Src)[_sourceSize]) {
        for (size_t _Idx = 0;; ++_Idx) {
            _STL_VERIFY(_Idx < _sourceSize, "data_path input not null terminated");
            if (_Src[_Idx] == std::_EcharT{}) {
                return std::string_view<std::_EcharT>(_Src, _Idx);
            }
        }
    }
#endif // _ITERATOR_DEBUG_LEVEL == 2

    template <class _Src, class convert = normal_convert>
    std::wstring convert_src_to_wchar(const _Src& _source, convert _Tag = {}) {
        return convert_stringoid_to_wchar(stringoid_from_src(_source), _Tag);
    }

    template <class _InIt>
    auto stringoid_from_range(_InIt _First, _InIt _Last) {
        _Adl_verify_range(_First, _Last);
        const auto _UFirst = _Get_unwrapped(_First);
        const auto _ULast = _Get_unwrapped(_Last);

        if constexpr (is_pointer_v<decltype(_UFirst)>) {
            return std::string_view<_Iter_value_t<_InIt>>(_UFirst, static_cast<size_t>(_ULast - _UFirst));
        }
        else {
            return std::basic_string<_Iter_value_t<_InIt>>(_UFirst, _ULast);
        }
    }

    template <class _InIt, class convert = normal_convert>
    std::wstring _Convert_range_to_wchar(_InIt _First, _InIt _Last, convert _Tag = {}) {
        return convert_stringoid_to_wchar(stringoid_from_range(_First, _Last), _Tag);
    }

    inline std::wstring convert_stringoid_with_locale_to_wchar(const std::string_view input, const locale& _Loc) {
        const auto& _Facet = _STD use_facet<codecvt<wchar_t, char, mbstate_t>>(_Loc);

        std::wstring output(input.size(), L'\0'); // almost always sufficient

        for (;;) {
            mbstate_t _State{};
            const char* const _From_begin = input.data();
            const char* const _From_end = _From_begin + input.size();
            const char* _From_next = nullptr;
            wchar_t* const _To_begin = output.data();
            wchar_t* const _To_end = _To_begin + output.size();
            wchar_t* _To_next = nullptr;

            const auto res = _Facet.in(_State, _From_begin, _From_end, _From_next, _To_begin, _To_end, _To_next);

            if (_From_next < _From_begin || _From_next > _From_end || _To_next < _To_begin || _To_next > _To_end) {
                std::_Throw_system_error(std::errc::invalid_argument);
            }

            switch (res) {
            case std::codecvt_base::ok:
                output.resize(static_cast<size_t>(_To_next - _To_begin));
                return output;

            case std::codecvt_base::partial:
                // N4810 28.4.1.4.2 [locale.codecvt.virtuals]/5:
                // "A return value of partial, if (from_next == from_end), indicates that either the
                // destination sequence has not absorbed all the available destination elements,
                // or that additional source elements are needed before another destination element can be produced."
                if ((_From_next == _From_end && _To_next != _To_end) || output.size() > output.max_size() / 2) {
                    std::_Throw_system_error(std::errc::invalid_argument);
                }

                output.resize(output.size() * 2);
                break; // out of switch, keep looping

            case std::codecvt_base::error:
            case std::codecvt_base::noconv:
            default:
                std::_Throw_system_error(std::errc::invalid_argument);
            }
        }
    }
}
// constants
namespace NW
{
    template <class> inline constexpr bool is_echar_t = false;
    template <> inline constexpr bool is_echar_t<char> = true;
    template <> inline constexpr bool is_echar_t<wchar_t> = true;
#ifdef __cpp_char8_t
    template <> inline constexpr bool is_echar_t<char8_t> = true;
#endif // __cpp_char8_t
    template <> inline constexpr bool is_echar_t<char16_t> = true;
    template <> inline constexpr bool is_echar_t<char32_t> = true;

    template <class _Ty, class = void>
    inline constexpr bool is_src_impl = false;

    template <class _Ty>
    inline constexpr bool is_src_impl<_Ty, void_t<typename iterator_traits<_Ty>::value_type>> =
        is_echar_t<typename iterator_traits<_Ty>::value_type>;

    template <class _Ty>
    inline constexpr bool is_src = is_src_impl<decay_t<_Ty>>;

    // to avoid constraint recursion via the converting constructor and
    // iterator_traits when determining if data_path is copyable.
    template <> inline constexpr bool is_src<data_path> = false;

    template <class _Elem, class _Traits, class _Alloc>
    inline constexpr bool is_src<std::basic_string<_Elem, _Traits, _Alloc>> = is_echar_t<_Elem>;

    template <class _Elem, class _Traits>
    inline constexpr bool is_src<std::string_view<_Elem, _Traits>> = is_echar_t<_Elem>;
}
// drive functions
namespace NW
{
    // FUNCTION TEMPLATE unalign_load
    template <class _Ty>
    _Ty unalign_load(const void* _Ptr) { // load a _Ty from _Ptr
        static_assert(is_trivial_v<_Ty>, "Unaligned loads require trivial types");
        _Ty _Tmp;
        _CSTD memcpy(&_Tmp, _Ptr, sizeof(_Tmp));
        return _Tmp;
    }

    inline bool is_drive_prefix(const wchar_t* const _First) {
        // test if _First points to a prefix of the form X:
        // pre: _First points to at least 2 wchar_t instances
        // pre: Little endian
        auto _Value = unalign_load<unsigned int>(_First);
        _Value &= 0xFFFF'FFDFu; // transform lowercase drive letters into uppercase ones
        _Value -= (static_cast<unsigned int>(L':') << (sizeof(wchar_t) * CHAR_BIT)) | L'A';
        return _Value < 26;
    }

    inline bool has_drive_letter_prefix(const wchar_t* const _First, const wchar_t* const _Last) {
        // test if [_First, _Last) has a prefix of the form X:
        return _Last - _First >= 2 && is_drive_prefix(_First);
    }
}
namespace NW
{
    /// file_status class
    class file_status
    {
    public:
        // [fs.file_status.cons], constructors and destructor
        file_status() noexcept = default;
        explicit file_status(file_type _Ft, file_perms _Perms = file_perms::unknown) noexcept :
            _Myftype(_Ft), _Myfile_perms(_Perms) {}
        file_status(const file_status&) noexcept = default;
        file_status(file_status&&) noexcept = default;
        ~file_status() noexcept = default;
        // operators
        file_status& operator=(const file_status&) noexcept = default;
        file_status& operator=(file_status&&) noexcept = default;
        // --setters
        void type(file_type _Ft) noexcept { _Myftype = _Ft; }
        void permissions(file_perms _Perms) noexcept { _Myfile_perms = _Perms; }
        // --getters
        file_type type() const noexcept { return _Myftype; }
        file_perms permissions() const noexcept { return _Myfile_perms; }

        void _Refresh(const __std_win_error _Error, const __std_fs_stats& _Stats) noexcept {
            if (_Error == __std_win_error::_Success) {
                const auto _Attrs = _Stats._Attributes;

                if (_Bitmask_includes(_Attrs, __std_fs_file_attr::_Readonly)) {
                    this->permissions(file_perms::_File_attribute_readonly);
                } else {
                    this->permissions(file_perms::all);
                }

                if (_Bitmask_includes(_Attrs, __std_fs_file_attr::_Reparse_point)) {
                    if (_Stats._Reparse_point_tag == __std_fs_reparse_tag::_Symlink) {
                        this->type(file_type::symlink);
                        return;
                    }

                    if (_Stats._Reparse_point_tag == __std_fs_reparse_tag::_Mount_point) {
                        this->type(file_type::junction);
                        return;
                    }
                    // all other reparse points considered ordinary files or directories
                }

                if (_Bitmask_includes(_Attrs, __std_fs_file_attr::_Directory)) { this->type(file_type::directory); }
                else { this->type(file_type::regular); }
                return;
            }
            this->permissions(file_perms::unknown);
            this->type(__std_is_file_not_found(_Error) ? file_type::not_found : file_type::none);
        }
    private:
        file_type _Myftype = file_type::none;
        file_perms _Myfile_perms = file_perms::unknown;
    };
    // --predicates
    // tests whether _Status indicates an existing file
    inline bool exists(const file_status _Status) noexcept {
        switch (_Status.type()) {
        case file_type::none:
        case file_type::not_found: return false;
        case file_type::regular:
        case file_type::directory:
        case file_type::symlink:
        case file_type::block:
        case file_type::character:
        case file_type::fifo:
        case file_type::socket:
        case file_type::unknown:
        case file_type::junction:
        default: return true;
        }
    }
    // tests whether _Status indicates a block file
    inline bool is_block_file(const file_status _Status) noexcept { return _Status.type() == file_type::block; }
    // tests whether _Status indicates a character file
    inline bool is_character_file(const file_status _Status) noexcept { return _Status.type() == file_type::character; }
    // tests whether _Status indicates a directory
    inline bool is_directory(const file_status _Status) noexcept { return _Status.type() == file_type::directory; }
    // tests whether _Status indicates a fifo
    inline bool is_fifo(const file_status _Status) noexcept { return _Status.type() == file_type::fifo; }
    // tests whether _Status indicates other file types
    inline bool is_other(const file_status _Status) noexcept {
        switch (_Status.type()) {
        case file_type::none:
        case file_type::not_found:
        case file_type::regular:
        case file_type::directory:
        case file_type::symlink: return false;
        case file_type::block:
        case file_type::character:
        case file_type::fifo:
        case file_type::socket:
        case file_type::unknown:
        case file_type::junction:
        default: return true;
        }
    }

    inline bool is_regular_file(const file_status _Status) noexcept {
        // tests whether _Status indicates a regular file
        return _Status.type() == file_type::regular;
    }

    inline bool is_socket(const file_status _Status) noexcept {
        // tests whether _Status indicates a socket
        return _Status.type() == file_type::socket;
    }

    inline bool is_symlink(const file_status _Status) noexcept {
        // tests whether _Status indicates a symlink
        return _Status.type() == file_type::symlink;
    }

    // STRUCT _File_status_and_error
    struct _File_status_and_error
    {
        file_status _Status;
        __std_win_error _Error;

        bool _Not_good() const noexcept {
            // [fs.op.status]/Throws: result values of file_status(file_type::not_found) and
            // file_status(file_type::unknown) are not considered failures and do not cause an exception to be thrown.
            return _Error != __std_win_error::_Success && _Status.type() != file_type::not_found
                   && _Status.type() != file_type::unknown;
        }
    };

    inline constexpr auto _Status_stats_flags =
        __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Follow_symlinks;

    inline constexpr auto _Symlink_status_stats_flags =
        __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;

    // ALIAS file_time_type
    struct _File_time_clock { // Implementation of trivial-clock
        using rep        = long long;
        using period     = ratio_multiply<ratio<_XTIME_NSECS_PER_TICK, 1>, nano>;
        using duration   = chrono::duration<rep, period>;
        using time_point = chrono::time_point<_File_time_clock>;

        static constexpr bool is_steady = false;

        static time_point now() noexcept { // get current time; undo epoch adjustment
            return time_point(duration(_Xtime_get_ticks() + __std_fs_file_time_epoch_adjustment)); // TRANSITION, ABI
        }
    };

    using file_time_type = chrono::time_point<_File_time_clock>;

    /// directory_entry class
    class directory_entry {
    public:
        // [fs.dir.entry.cons], constructors and destructor
        directory_entry() noexcept : _Cached_data{}, _Path() {}

        directory_entry(const directory_entry&)     = default;
        directory_entry(directory_entry&&) noexcept = default;
        explicit directory_entry(const filesystem::data_path& _Path_arg) : _Cached_data{}, _Path(_Path_arg) {
            (void) _Refresh(_Cached_data, _Path);
        }

        directory_entry(const filesystem::data_path& _Path_arg, std::error_code& _Ec) : _Cached_data{}, _Path(_Path_arg) {
            _Ec.clear();
            (void) _Refresh(_Cached_data, _Path);
        }

        ~directory_entry() = default;

        // assignments
        directory_entry& operator=(const directory_entry&) = default;
        directory_entry& operator=(directory_entry&&) noexcept = default;

        // [fs.dir.entry.mods], modifiers
        void assign(const filesystem::data_path& _Path_arg) {
            _Path.assign(_Path_arg);
            (void) _Refresh(_Cached_data, _Path);
        }

        void assign(const filesystem::data_path& _Path_arg, std::error_code& _Ec) {
            _Ec.clear(); // for exception safety
            _Path.assign(_Path_arg);
            (void) _Refresh(_Cached_data, _Path);
        }

        void repl_fname(const filesystem::data_path& _Path_arg) {
            _Path.repl_fname(_Path_arg);
            (void) _Refresh(_Cached_data, _Path);
        }

        void repl_fname(const filesystem::data_path& _Path_arg, std::error_code& _Ec) {
            _Ec.clear(); // for exception safety
            _Path.repl_fname(_Path_arg);
            (void) _Refresh(_Cached_data, _Path);
        }

        void refresh() {
            const auto _Error = _Refresh(_Cached_data, _Path);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_entry::refresh", _Error, _Path);
            }
        }

        void refresh(std::error_code& _Ec) noexcept {
            _Ec = make_err_code(_Refresh(_Cached_data, _Path));
        }

#if _HAS_CXX20
        void clear_cache() noexcept {
            _Cached_data._Available = __std_fs_stats_flags::_None;
        }
#endif // _HAS_CXX20

    private:
        bool _Has_cached_attribute(const __std_fs_file_attr _Attrs) const noexcept {
            return _Bitmask_includes(_Cached_data._Attributes, _Attrs);
        }

    public:
        // [fs.dir.entry.obs], observers
        const filesystem::data_path& data_path() const noexcept {
            return _Path;
        }

        operator const filesystem::data_path &() const noexcept {
            return _Path;
        }

        bool exists() const {
            const auto _Type = this->status().type();
            return _Type != file_type::not_found && _Type != file_type::none;
        }

        bool exists(std::error_code& _Ec) const noexcept {
            const auto _Type = this->status(_Ec).type();
            return _Type != file_type::not_found && _Type != file_type::none;
        }

        bool is_block_file() const {
            return false;
        }

        bool is_block_file(std::error_code& _Ec) const noexcept {
            _Ec.clear();
            return false;
        }

        bool is_character_file() const {
            return false;
        }

        bool is_character_file(std::error_code& _Ec) const noexcept {
            _Ec.clear();
            return false;
        }

        bool is_directory() const {
            return _STD filesystem::is_directory(this->status());
        }

        bool is_directory(std::error_code& _Ec) const noexcept {
            return _STD filesystem::is_directory(this->status(_Ec));
        }

        bool is_fifo() const {
            return false;
        }

        bool is_fifo(std::error_code& _Ec) const noexcept {
            _Ec.clear();
            return false;
        }

        bool is_other() const {
            return _STD filesystem::is_other(this->status());
        }

        bool is_other(std::error_code& _Ec) const noexcept {
            return _STD filesystem::is_other(this->status(_Ec));
        }

        bool is_regular_file() const {
            return _STD filesystem::is_regular_file(this->status());
        }

        bool is_regular_file(std::error_code& _Ec) const noexcept {
            return _STD filesystem::is_regular_file(this->status(_Ec));
        }

        bool is_socket() const {
            return false;
        }

        bool is_socket(std::error_code& _Ec) const noexcept {
            _Ec.clear();
            return false;
        }

        bool _Is_symlink_or_junction() const noexcept {
            return _Has_cached_attribute(__std_fs_file_attr::_Reparse_point)
                   && (_Cached_data._Reparse_point_tag == __std_fs_reparse_tag::_Symlink
                       || _Cached_data._Reparse_point_tag == __std_fs_reparse_tag::_Mount_point);
        }

        bool is_symlink() const {
            return _STD filesystem::is_symlink(this->symlink_status());
        }

        bool is_symlink(std::error_code& _Ec) const noexcept {
            return _STD filesystem::is_symlink(this->symlink_status(_Ec));
        }

        bool _Available(const __std_fs_stats_flags _Flags) const noexcept {
            return _Bitmask_includes(_Cached_data._Available, _Flags);
        }

    private:
        __std_win_error _File_size(uintmax_t& res) const noexcept {
            if (_Available(__std_fs_stats_flags::_File_size)) {
                res = _Cached_data._File_size;
                return __std_win_error::_Success;
            }

            __std_fs_stats _Stats;
            constexpr auto _Flags = __std_fs_stats_flags::_File_size | __std_fs_stats_flags::_Follow_symlinks;
            const auto _Error =
                __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes());
            if (_Error == __std_win_error::_Success) {
                res = _Stats._File_size;
            } else {
                res = static_cast<uintmax_t>(-1);
            }

            return _Error;
        }

    public:
        uintmax_t file_size() const {
            uintmax_t res;
            const auto _Error = _File_size(res);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_entry::file_size", _Error, _Path);
            }

            return res;
        }

        uintmax_t file_size(std::error_code& _Ec) const noexcept {
            uintmax_t res;
            _Ec = make_err_code(_File_size(res));
            return res;
        }

    private:
        __std_win_error _Hard_link_count(uintmax_t& res) const noexcept {
            if (_Available(__std_fs_stats_flags::_Link_count)) {
                res = _Cached_data._Link_count;
                return __std_win_error::_Success;
            }

            __std_fs_stats _Stats;
            constexpr auto _Flags = __std_fs_stats_flags::_Link_count | __std_fs_stats_flags::_Follow_symlinks;
            const auto _Error =
                __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes());
            if (_Error == __std_win_error::_Success) {
                res = _Stats._Link_count;
            } else {
                res = static_cast<uintmax_t>(-1);
            }

            return _Error;
        }

    public:
        uintmax_t hard_link_count() const {
            uintmax_t res;
            const auto _Error = _Hard_link_count(res);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_entry::hard_link_count", _Error, _Path);
            }

            return res;
        }

        uintmax_t hard_link_count(std::error_code& _Ec) const noexcept {
            uintmax_t res;
            _Ec = make_err_code(_Hard_link_count(res));
            return res;
        }

    private:
        __std_win_error _Last_write_time(file_time_type& res) const noexcept {
            if (_Available(__std_fs_stats_flags::_Last_write_time)) {
                res = file_time_type{file_time_type::duration{_Cached_data._Last_write_time}};
                return __std_win_error::_Success;
            }

            __std_fs_stats _Stats;
            constexpr auto _Flags = __std_fs_stats_flags::_Last_write_time | __std_fs_stats_flags::_Follow_symlinks;
            const auto _Error =
                __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes());
            if (_Error == __std_win_error::_Success) {
                res = file_time_type{file_time_type::duration{_Stats._Last_write_time}};
            } else {
                res = file_time_type{file_time_type::duration{LLONG_MIN}};
            }

            return _Error;
        }

    public:
        file_time_type last_write_time() const {
            file_time_type res;
            const auto _Error = _Last_write_time(res);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_entry::last_write_time", _Error, _Path);
            }

            return res;
        }

        file_time_type last_write_time(std::error_code& _Ec) const noexcept {
            file_time_type res;
            _Ec = make_err_code(_Last_write_time(res));
            return res;
        }

    private:
        _File_status_and_error _Get_any_status(const __std_fs_stats_flags _Flags) const noexcept {
            _File_status_and_error res;
            __std_fs_stats _Stats;

            if (_Bitmask_includes_all(_Cached_data._Available, _Flags)) {
                res._Error = __std_win_error::_Success;
                res._Status._Refresh(__std_win_error::_Success, _Cached_data);
            } else {
                const auto _Error =
                    __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes());
                res._Error = _Error;
                res._Status._Refresh(_Error, _Stats);
            }

            return res;
        }

    public:
        file_status status() const {
            const auto res = _Get_any_status(_Status_stats_flags);
            if (res._Not_good()) {
                throw_file_sys_err("directory_entry::status", res._Error, _Path);
            }

            return res._Status;
        }

        file_status status(std::error_code& _Ec) const noexcept {
            const auto res = _Get_any_status(_Status_stats_flags);
            _Ec                = make_err_code(res._Error);
            return res._Status;
        }

        file_status symlink_status() const {
            const auto res = _Get_any_status(_Symlink_status_stats_flags);
            if (res._Not_good()) {
                throw_file_sys_err("directory_entry::symlink_status", res._Error, _Path);
            }

            return res._Status;
        }

        file_status symlink_status(std::error_code& _Ec) const noexcept {
            const auto res = _Get_any_status(_Symlink_status_stats_flags);
            _Ec                = make_err_code(res._Error);
            return res._Status;
        }

        bool operator<(const directory_entry& _Rhs) const noexcept {
            return _Path < _Rhs._Path;
        }

        bool operator==(const directory_entry& _Rhs) const noexcept {
            return _Path == _Rhs._Path;
        }

        bool operator!=(const directory_entry& _Rhs) const noexcept {
            return _Path != _Rhs._Path;
        }

        bool operator<=(const directory_entry& _Rhs) const noexcept {
            return _Path <= _Rhs._Path;
        }

        bool operator>(const directory_entry& _Rhs) const noexcept {
            return _Path > _Rhs._Path;
        }

        bool operator>=(const directory_entry& _Rhs) const noexcept {
            return _Path >= _Rhs._Path;
        }

    private:
        void _Refresh(const __std_fs_find_data& _Data) noexcept {
            _Cached_data._Attributes        = _Data._Attributes;
            _Cached_data._Reparse_point_tag = _Data._Reparse_point_tag;
            _Cached_data._Available         = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;
            if (!_Bitmask_includes(_Data._Attributes, __std_fs_file_attr::_Reparse_point)) {
                _Cached_data._File_size = (static_cast<uintmax_t>(_Data._File_size_high) << 32)
                                          + static_cast<uintmax_t>(_Data._File_size_low);
                _CSTD memcpy(
                    &_Cached_data._Last_write_time, &_Data._Last_write_time, sizeof(_Cached_data._Last_write_time));
                _Cached_data._Available |= __std_fs_stats_flags::_File_size | __std_fs_stats_flags::_Last_write_time;
            }
        }

        static __std_win_error _Refresh(__std_fs_stats& _Stats, const filesystem::data_path& _Path) noexcept {
            const auto _Error = __std_fs_get_stats(_Path.c_str(), &_Stats, __std_fs_stats_flags::_All_data);
            if (_Error == __std_win_error::_Success) {
                if (_Bitmask_includes(_Stats._Attributes, __std_fs_file_attr::_Reparse_point)) {
                    _Stats._Available = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;
                } else {
                    _Stats._Available = __std_fs_stats_flags::_All_data;
                }
            } else {
                _Stats._Available = __std_fs_stats_flags::_None;
            }

            return _Error;
        }

        friend struct dir_enum_impl;
        friend struct recur_dir_enum_impl;
        friend void _Copy_impl(
            const directory_entry& _From, const _STD filesystem::data_path& _To, copy_options _Options, std::error_code& _Ec);

        __std_fs_stats _Cached_data;
        filesystem::data_path _Path;
    };

    // ENUM CLASS directory_options
    enum class directory_options { none = 0, follow_directory_symlink = 1, skip_permission_denied = 2 };
    _BITMASK_OPS(directory_options)

    struct dir_enum_impl {
        static __std_win_error advance_reset_if_no_more(shared_ptr<dir_enum_impl>& _Ptr) {
            auto& _Impl = *_Ptr;
            __std_fs_find_data _Data;
            do {
                const auto _Error = __std_fs_directory_iterator_advance(_Impl._Dir._Handle, &_Data);
                if (_Error == __std_win_error::_No_more_files) {
                    _Ptr.reset();
                    return __std_win_error::_Success;
                }

                if (_Error != __std_win_error::_Success) {
                    return _Error;
                }
            } while (_Is_dot_or_dotdot(_Data));
            _Impl._Refresh(_Data); // can throw
            return __std_win_error::_Success;
        }

        static __std_win_error _Skip_dots(
            __std_fs_dir_handle _Dir_handle, __std_fs_find_data& _Data) noexcept {
            while (_Is_dot_or_dotdot(_Data)) {
                const auto _Error = __std_fs_directory_iterator_advance(_Dir_handle, &_Data);
                if (_Error != __std_win_error::_Success) {
                    return _Error;
                }
            }

            return __std_win_error::_Success;
        }

        static __std_win_error _Open_dir(
            data_path& _Path, const directory_options _Options_arg, fhandle_finder& _Dir, __std_fs_find_data& _Data) {
            using namespace _STD std::string_view_literals; // TRANSITION, VSO-571749
            const size_t _Null_term_len = _CSTD wcslen(_Path.c_str());
            if (_Null_term_len == 0 || _Null_term_len != _Path.native().size()) {
                return __std_win_error::_File_not_found;
            }

            _Path /= L"*"sv;
            auto _Error = _Dir._Open(_Path.c_str(), &_Data);
            if (_Error == __std_win_error::_Success) {
                return _Skip_dots(_Dir._Handle, _Data);
            }

            if (_Error == __std_win_error::_Access_denied
                && _Bitmask_includes(_Options_arg, directory_options::skip_permission_denied)) {
                _Error = __std_win_error::_No_more_files;
            }

            return _Error;
        }

        // creator
        // factored out part common to recursive and non-recursive implementation
        struct _Creator
        {
            data_path _Path;
            fhandle_finder _Dir;
            __std_fs_find_data find_data;

            struct _Create_status {
                bool _Should_create_impl;
                __std_win_error _Error;
            };

            _Create_status _Status;

            _Creator(const data_path& _Path_arg, const directory_options _Options) : _Path(_Path_arg) {
                const auto _Error = _Open_dir(_Path, _Options, _Dir, find_data);
                if (_Error == __std_win_error::_Success) {
                    _Status = {true, __std_win_error::_Success};
                } else if (_Error == __std_win_error::_No_more_files) {
                    _Status = {false, __std_win_error::_Success};
                } else {
                    _Status = {false, _Error};
                }
            }
        };

        void _Refresh(const __std_fs_find_data& _Data) {
            _Entry._Refresh(_Data);
            _Entry._Path.repl_fname(std::std::wstring_view{_Data._File_name});
        }

        explicit dir_enum_impl(_Creator&& _Create_data, const directory_options = {})
            : _Dir(_STD move(_Create_data._Dir)) {
            // directory_options provided, but unused to keep signature identical to recursive_directory_iterator
            _Entry._Path = _STD move(_Create_data._Path);
            _Refresh(_Create_data.find_data);
        }

        template <class _Dir_enum_kind>
        static __std_win_error _Initialize_dir_enum(
            shared_ptr<_Dir_enum_kind>& _Impl, const data_path& _Path, const directory_options _Options = {}) {
            _Creator _Create_data(_Path, _Options);
            if (_Create_data._Status._Should_create_impl) {
                _Impl = _STD make_shared<_Dir_enum_kind>(_STD move(_Create_data), _Options);
            }
            return _Create_data._Status._Error;
        }

        directory_entry _Entry;
        fhandle_finder _Dir;
    };

    // _Directory_entry_proxy struct
    struct _Directory_entry_proxy
    {
        directory_entry operator*() && noexcept {
            return _STD move(_Entry);
        }

    private:
        friend directory_iterator;
        friend recursive_directory_iterator;

        explicit _Directory_entry_proxy(const directory_entry& _Entry_arg) : _Entry(_Entry_arg) {}

        directory_entry _Entry;
    };

    /// directory_iterator class
    class directory_iterator
    {
    public:
        using iterator_category = input_iterator_tag;
        using value_type        = directory_entry;
        using difference_type   = ptrdiff_t;
        using pointer           = const directory_entry*;
        using reference         = const directory_entry&;

        // [fs.dir.itr.members], member functions
        directory_iterator() noexcept = default;
        explicit directory_iterator(const data_path& _Path) {
            const auto _Error = dir_enum_impl::_Initialize_dir_enum(_Impl, _Path);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_iterator::directory_iterator", _Error, _Path);
            }
        }

        directory_iterator(const data_path& _Path, const directory_options _Options) {
            const auto _Error = dir_enum_impl::_Initialize_dir_enum(_Impl, _Path, _Options);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_iterator::directory_iterator", _Error, _Path);
            }
        }

        directory_iterator(const data_path& _Path, std::error_code& _Ec) {
            _Ec = make_err_code(dir_enum_impl::_Initialize_dir_enum(_Impl, _Path));
        }

        directory_iterator(const data_path& _Path, const directory_options _Options, std::error_code& _Ec) {
            _Ec = make_err_code(dir_enum_impl::_Initialize_dir_enum(_Impl, _Path, _Options));
        }

        directory_iterator(const directory_iterator&) noexcept = default; // strengthened
        directory_iterator(directory_iterator&&) noexcept      = default;
        ~directory_iterator() noexcept                         = default;

        directory_iterator& operator=(const directory_iterator&) noexcept = default; // strengthened
        directory_iterator& operator=(directory_iterator&&) noexcept = default;

        const directory_entry& operator*() const noexcept /* strengthened */ {
            return _Impl->_Entry;
        }

        const directory_entry* operator->() const noexcept /* strengthened */ {
            return &**this;
        }

        directory_iterator& operator++() {
            const auto _Error = dir_enum_impl::advance_reset_if_no_more(_Impl);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("directory_iterator::operator++", _Error);
            }

            return *this;
        }

        directory_iterator& increment(std::error_code& _Ec) {
            _Ec = make_err_code(dir_enum_impl::advance_reset_if_no_more(_Impl));
            return *this;
        }

        // other members as required by [input.iterators]:
        bool operator==(const directory_iterator& _Rhs) const noexcept /* strengthened */ {
            return _Impl == _Rhs._Impl;
        }

        bool operator!=(const directory_iterator& _Rhs) const noexcept /* strengthened */ {
            return _Impl != _Rhs._Impl;
        }

        _Directory_entry_proxy operator++(int) {
            _Directory_entry_proxy _Proxy(**this);
            ++*this;
            return _Proxy;
        }

        bool _At_end() const noexcept {
            return !_Impl;
        }

    private:
        shared_ptr<dir_enum_impl> _Impl;
    };

    inline directory_iterator begin(directory_iterator _Iter) noexcept {
        return _Iter;
    }

    inline directory_iterator end(directory_iterator) noexcept {
        return {};
    }

    struct _Should_recurse_result {
        bool _Should_recurse;
        __std_win_error _Error;
    };

    struct recur_dir_enum_impl : dir_enum_impl {
        vector<fhandle_finder> _Stack;
        directory_options _Options = {};
        bool _Recursion_pending    = true;

        _Should_recurse_result _Should_recurse() const noexcept {
            bool _Should_recurse   = false;
            __std_win_error _Error = __std_win_error::_Success;
            if (_Recursion_pending) {
                if (_Entry._Is_symlink_or_junction()) {
                    if (_Bitmask_includes(_Options, directory_options::follow_directory_symlink)) {
                        // check for broken symlink/junction
                        __std_fs_stats _Target_stats;
                        constexpr auto _Flags =
                            __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Follow_symlinks;
                        _Error = __std_fs_get_stats(
                            _Entry._Path.c_str(), &_Target_stats, _Flags, _Entry._Cached_data._Attributes);
                        if (_Error == __std_win_error::_Success) {
                            _Should_recurse =
                                _Bitmask_includes(_Target_stats._Attributes, __std_fs_file_attr::_Directory);
                        } else if (__std_is_file_not_found(_Error)
                                   || (_Error == __std_win_error::_Access_denied
                                       && _Bitmask_includes(_Options, directory_options::skip_permission_denied))) {
                            // skip broken symlinks and permission denied (when configured)
                            _Error = __std_win_error::_Success;
                        }
                    }
                } else {
                    _Should_recurse = _Entry._Has_cached_attribute(__std_fs_file_attr::_Directory);
                }
            }

            return {_Should_recurse, _Error};
        }

        __std_win_error _Advance_and_skip_dots(__std_fs_find_data& _Data) noexcept {
            const auto _Error = __std_fs_directory_iterator_advance(_Dir._Handle, &_Data);
            if (_Error != __std_win_error::_Success) {
                return _Error;
            }

            return _Skip_dots(_Dir._Handle, _Data);
        }

        static __std_win_error _Pop_and_reset_if_no_more_files(shared_ptr<recur_dir_enum_impl>& _Ptr) {
            __std_win_error _Error;
            auto& _Impl = *_Ptr;
            __std_fs_find_data _Data;

            _Impl._Recursion_pending = true;

            do {
                if (_Impl._Stack.empty()) {
                    _Error = __std_win_error::_Success;
                    break;
                }

                _Impl._Dir = _STD move(_Impl._Stack.back());
                _Impl._Stack.pop_back();
                _Impl._Entry._Path.rmv_fname_sep();
                _Error = _Impl._Advance_and_skip_dots(_Data);

                if (_Error == __std_win_error::_Success) {
                    _Impl._Refresh(_Data);
                    return __std_win_error::_Success;
                }
            } while (_Error == __std_win_error::_No_more_files);

            _Ptr.reset();
            return _Error;
        }

        static __std_win_error advance_reset_if_no_more(
            shared_ptr<recur_dir_enum_impl>& _Ptr) {
            auto& _Impl = *_Ptr;
            __std_fs_find_data _Data;
            auto [_Should_recurse, _Error] = _Impl._Should_recurse();
            if (_Error != __std_win_error::_Success) {
                _Ptr.reset();
                return _Error;
            }

            if (_Should_recurse) {
                _Impl._Stack.push_back(_STD move(_Impl._Dir));
                _Error = _Open_dir(_Impl._Entry._Path, _Impl._Options, _Impl._Dir, _Data);
            } else {
                _Error = _Impl._Advance_and_skip_dots(_Data);
            }

            _Impl._Recursion_pending = true;
            for (;; _Error = _Impl._Advance_and_skip_dots(_Data)) {
                if (_Error == __std_win_error::_Success) {
                    _Impl._Refresh(_Data);
                    return __std_win_error::_Success;
                }

                if (_Error != __std_win_error::_No_more_files) {
                    break;
                }

                // no more files at this level, see if we can pop
                if (_Impl._Stack.empty()) { // nothing to pop, clear the error, reset and return
                    _Error = __std_win_error::_Success;
                    break;
                }

                _Impl._Dir = _STD move(_Impl._Stack.back());
                _Impl._Stack.pop_back();
                _Impl._Entry._Path.rmv_fname_sep();
            }

            _Ptr.reset();
            return _Error;
        }

        recur_dir_enum_impl(dir_enum_impl::_Creator&& _Create_data, const directory_options _Options_arg)
            : dir_enum_impl(_STD move(_Create_data)), _Options(_Options_arg) {}
    };

    /// recursive_directory_iterator class
    class recursive_directory_iterator
    {
    public:
        using iterator_category = input_iterator_tag;
        using value_type        = directory_entry;
        using difference_type   = ptrdiff_t;
        using pointer           = const directory_entry*;
        using reference         = const directory_entry&;

        // [fs.rec.dir.itr.members], constructors and destructor

        recursive_directory_iterator() noexcept = default;
        explicit recursive_directory_iterator(const data_path& _Path) {
            const auto _Error = dir_enum_impl::_Initialize_dir_enum(_Impl, _Path);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("recursive_directory_iterator::recursive_directory_iterator", _Error, _Path);
            }
        }

        recursive_directory_iterator(const data_path& _Path, const directory_options _Options) {
            const auto _Error = dir_enum_impl::_Initialize_dir_enum(_Impl, _Path, _Options);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("recursive_directory_iterator::recursive_directory_iterator", _Error, _Path);
            }
        }

        recursive_directory_iterator(const data_path& _Path, const directory_options _Options, std::error_code& _Ec) {
            _Ec = make_err_code(dir_enum_impl::_Initialize_dir_enum(_Impl, _Path, _Options));
        }

        recursive_directory_iterator(const data_path& _Path, std::error_code& _Ec) {
            _Ec = make_err_code(dir_enum_impl::_Initialize_dir_enum(_Impl, _Path));
        }

        recursive_directory_iterator(const recursive_directory_iterator&) noexcept = default; // strengthened
        recursive_directory_iterator(recursive_directory_iterator&&) noexcept      = default;
        ~recursive_directory_iterator() noexcept                                   = default;

        // [fs.rec.dir.itr.members], observers
        directory_options options() const noexcept /* strengthened */ {
            return _Impl->_Options;
        }
        int depth() const noexcept /* strengthened */ {
            // NT uses uint32_t to store the length of the data_path
            // that allows us 2^31 wchar_t per data_path.
            // A directory name should be at least 1 character, otherwise
            // adjacent directory separators will be treated as one.
            // Hence, we can only get to 2^30 entries in the stack.
            return static_cast<int>(_Impl->_Stack.size());
        }
        bool recursion_pending() const noexcept /* strengthened */ {
            return _Impl->_Recursion_pending;
        }

        const directory_entry& operator*() const noexcept /* strengthened */ {
            return _Impl->_Entry;
        }

        const directory_entry* operator->() const noexcept /* strengthened */ {
            return &**this;
        }

        // [fs.rec.dir.itr.members], modifiers
        recursive_directory_iterator& operator=(recursive_directory_iterator&&) noexcept = default;
        recursive_directory_iterator& operator=(const recursive_directory_iterator&) noexcept = default; // strengthened

        recursive_directory_iterator& operator++() {
            const auto _Error = recur_dir_enum_impl::advance_reset_if_no_more(_Impl);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("recursive_directory_iterator::operator++", _Error);
            }
            return *this;
        }

        recursive_directory_iterator& increment(std::error_code& _Ec) {
            _Ec = make_err_code(recur_dir_enum_impl::advance_reset_if_no_more(_Impl));
            return *this;
        }

        void pop() {
            const auto _Error = recur_dir_enum_impl::_Pop_and_reset_if_no_more_files(_Impl);
            if (_Error != __std_win_error::_Success) {
                throw_file_sys_err("recursive_directory_iterator::pop", _Error);
            }
        }

        void pop(std::error_code& _Ec) {
            _Ec = make_err_code(recur_dir_enum_impl::_Pop_and_reset_if_no_more_files(_Impl));
        }

        void disable_recursion_pending() noexcept {
            _Impl->_Recursion_pending = false;
        }

        // other members as required by [input.iterators]:
        bool operator==(const recursive_directory_iterator& _Rhs) const noexcept {
            return _Impl == _Rhs._Impl;
        }

        bool operator!=(const recursive_directory_iterator& _Rhs) const noexcept {
            return _Impl != _Rhs._Impl;
        }

        _Directory_entry_proxy operator++(int) {
            _Directory_entry_proxy _Proxy(**this);
            ++*this;
            return _Proxy;
        }

    private:
        shared_ptr<recur_dir_enum_impl> _Impl;
    };

    inline recursive_directory_iterator begin(recursive_directory_iterator _Iter) noexcept {
        return _Iter;
    }

    inline recursive_directory_iterator end(recursive_directory_iterator) noexcept {
        return {};
    }

    // FUNCTION absolute
    inline __std_win_error absolute(data_path& res, const std::wstring& _Text) { // pre: res.empty()
        if (_Text.empty()) {
            return __std_win_error::_Success;
        }

        res._Text.resize(__std_fs_max_path);
        __std_win_error _Err;
        for (;;) {
            const auto _Requested_size = static_cast<unsigned long>(res._Text.size());
            const auto _Full_path_result =
                __std_fs_get_full_path_name(_Text.c_str(), _Requested_size, res._Text.data());
            _Err = _Full_path_result._Error;
            res._Text.resize(_Full_path_result._Size);
            if (_Full_path_result._Size < _Requested_size) {
                break;
            }
        }

        return _Err;
    }

    inline data_path absolute(const data_path& input) {
        // normalize data_path according to system semantics, without touching the disk
        // calls GetFullPathNameW
        data_path res;
        const auto _Err = absolute(res, input.native());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("absolute", _Err, input);
        }

        return res;
    }

    inline data_path absolute(const data_path& input, std::error_code& _Ec) {
        // normalize data_path according to system semantics, without touching the disk
        // calls GetFullPathNameW
        _Ec.clear(); // for exception safety
        data_path res;
        _Ec = make_err_code(absolute(res, input.native()));
        return res;
    }

    // FUNCTION canonical
    inline __std_win_error canonical(data_path& res, const std::wstring& _Text) { // pre: res.empty()
        using namespace _STD std::string_view_literals; // TRANSITION, VSO-571749
        if (_Text.empty()) {
            return __std_win_error::_Success;
        }

        auto _Name_kind = __std_fs_volume_name_kind::_Dos;
        {
            __std_win_error _Err;
            const _Fs_file _Handle(_Text.c_str(), __std_access_rights::_File_read_attributes,
                __std_fs_file_flags::_Backup_semantics, &_Err);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }

            res._Text.resize(__std_fs_max_path);
            for (;;) {
                const auto _Requested_size    = static_cast<unsigned long>(res._Text.size());
                const auto _Final_path_result = __std_fs_get_final_path_name_by_handle(
                    _Handle._Raw, res._Text.data(), _Requested_size, _Name_kind);
                _Err = _Final_path_result._Error;
                if (_Final_path_result._Size == 0) {
                    if (_Err == __std_win_error::_Path_not_found && _Name_kind == __std_fs_volume_name_kind::_Dos) {
                        // maybe there is no DOS name for the supplied data_path, retry with NT data_path
                        _Name_kind = __std_fs_volume_name_kind::_Nt;
                        continue;
                    }

                    res._Text.clear();
                    return _Err;
                }

                res._Text.resize(_Final_path_result._Size);
                if (_Final_path_result._Size < _Requested_size) {
                    break;
                }
            }
        } // close _Handle

        if (_Name_kind == __std_fs_volume_name_kind::_Dos) {
            if (is_drive_prefix_with_slash_slash_question(res._Text)) {
                // the result contains a \\?\ prefix but is just a drive letter, strip the \\?\ prefix
                res._Text.erase(0, 4);
            } else if (res._Text._Starts_with(LR"(\\?\UNC\)"sv)) {
                // the result contains a \\?\UNC\ prefix, replace with the simpler \\ prefix
                res._Text.erase(2, 6); // chop out ?\UNC\ leaving two preferred-separators
            }
        } else { // result is in the NT namespace, so apply the DOS to NT namespace prefix
            res._Text.insert(0, LR"(\\?\GLOBALROOT)"sv);
        }

        return __std_win_error::_Success;
    }

    inline data_path canonical(const data_path& input) {
        // resolve the final data_path according to system semantics, by opening the file
        // calls GetFinalPathNameByHandleW
        data_path res;
        const auto _Err = canonical(res, input.native());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("canonical", _Err, input);
        }

        return res;
    }

    inline data_path canonical(const data_path& input, std::error_code& _Ec) {
        // resolve the final data_path according to system semantics, by opening the file
        // calls GetFinalPathNameByHandleW
        _Ec.clear(); // for exception safety
        data_path res;
        _Ec = make_err_code(canonical(res, input.native()));
        return res;
    }

    // FUNCTION create_directory_symlink
    inline unique_ptr<wchar_t[]> _Get_cleaned_symlink_target(const data_path& _To) noexcept {
        // transforms /s in the root-name to \s, and all other directory-separators into single \s
        // example: a/\/b -> a\b
        // example: //server/a////////b////////c////////d -> \\server\a\b\c\d
        const auto& _To_str = _To.native();
        // protected from overflow by std::wstring's max_size cap:
        unique_ptr<wchar_t[]> _Cleaned_link(::new (nothrow) wchar_t[_To_str.size() + 1]);
        if (!_Cleaned_link) {
            return _Cleaned_link;
        }

        const auto _First = _To_str.c_str();
        const auto _Last  = _First + _To_str.size();
        auto _Next        = find_root_name_end(_First, _Last);
        auto _Dest        = _STD replace_copy_if(_First, _Next, _Cleaned_link.get(), _Is_slash, L'\\');
        for (;;) {
            const wchar_t _Ch = *_Next;
            if (_Is_slash(_Ch)) {
                *_Dest = L'\\';
                do {
                    ++_Next;
                } while (_Is_slash(*_Next));
            } else {
                *_Dest = _Ch;
                if (_Ch == L'\0') {
                    break;
                }

                ++_Next;
            }

            ++_Dest;
        }

        return _Cleaned_link;
    }

    inline void create_directory_symlink(const data_path& _To, const data_path& _New_symlink) {
        // create a symlink for a directory, _New_symlink -> _To
        const auto _Cleaned = _Get_cleaned_symlink_target(_To);
        if (!_Cleaned) {
            _Xbad_alloc();
        }

        // note reversed parameter order:
        const auto _Err = __std_fs_create_directory_symbolic_link(_New_symlink.c_str(), _Cleaned.get());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("create_directory_symlink", _Err, _To, _New_symlink);
        }
    }

    inline void create_directory_symlink(const data_path& _To, const data_path& _New_symlink, std::error_code& _Ec) noexcept {
        // create a symlink for a directory, _New_symlink -> _To
        const auto _Cleaned = _Get_cleaned_symlink_target(_To);
        if (_Cleaned) {
            // note reversed parameter order:
            _Ec = make_err_code(__std_fs_create_directory_symbolic_link(_New_symlink.c_str(), _Cleaned.get()));
        } else {
            _Ec = _STD make_error_code(std::errc::not_enough_memory);
        }
    }

    // FUNCTION create_hard_link
    inline void create_hard_link(const data_path& _To, const data_path& _New_hard_link) {
        // create a hard link for a file, _New_hard_link -> _To
        // note reversed parameter order:
        const auto _Err = __std_fs_create_hard_link(_New_hard_link.c_str(), _To.c_str());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("create_hard_link", _Err, _To, _New_hard_link);
        }
    }

    inline void create_hard_link(const data_path& _To, const data_path& _New_hard_link, std::error_code& _Ec) noexcept {
        // create a hard link for a file, _New_hard_link -> _To
        // note reversed parameter order:
        _Ec = make_err_code(__std_fs_create_hard_link(_New_hard_link.c_str(), _To.c_str()));
    }

    // FUNCTION create_symlink
    inline void create_symlink(const data_path& _To, const data_path& _New_symlink) {
        // create a symlink for a file, _New_symlink -> _To
        const auto _Cleaned = _Get_cleaned_symlink_target(_To);
        if (!_Cleaned) {
            _Xbad_alloc();
        }

        // note reversed parameter order:
        const auto _Err = __std_fs_create_symbolic_link(_New_symlink.c_str(), _Cleaned.get());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("create_symlink", _Err, _To, _New_symlink);
        }
    }

    inline void create_symlink(const data_path& _To, const data_path& _New_symlink, std::error_code& _Ec) noexcept {
        // create a symlink for a file, _New_symlink -> _To
        const auto _Cleaned = _Get_cleaned_symlink_target(_To);
        if (_Cleaned) {
            // note reversed parameter order:
            _Ec = make_err_code(__std_fs_create_symbolic_link(_New_symlink.c_str(), _Cleaned.get()));
        } else {
            _Ec = _STD make_error_code(std::errc::not_enough_memory);
        }
    }

    // FUNCTION read_symlink
    inline __std_win_error read_symlink_reparse_data(
        const _Fs_file& _Handle, unique_ptr<char[]>& _Buffer_unique_ptr) noexcept {
        constexpr auto _Buffer_size = 16 * 1024 + sizeof(wchar_t); // MAXIMUM_REPARSE_DATA_BUFFER_SIZE + sizeof(wchar_t)

        _Buffer_unique_ptr.reset(::new (nothrow) char[_Buffer_size]);
        if (!_Buffer_unique_ptr) {
            return __std_win_error::_Not_enough_memory;
        }

        const auto _Buffer         = reinterpret_cast<__std_fs_reparse_data_buffer*>(_Buffer_unique_ptr.get());
        const __std_win_error _Err = __std_fs_read_reparse_data_buffer(_Handle._Raw, _Buffer, _Buffer_size);
        if (_Err != __std_win_error::_Success) {
            return _Err;
        }

        return __std_win_error::_Success;
    }

    inline __std_win_error read_symlink(const data_path& _Symlink_path, data_path& res) noexcept {
        __std_win_error _Err;
        unique_ptr<char[]> _Buffer_unique_ptr;
        {
            const _Fs_file _Handle(_Symlink_path.c_str(), __std_access_rights::_File_read_attributes,
                __std_fs_file_flags::_Backup_semantics | __std_fs_file_flags::_Open_reparse_point, &_Err);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }

            _Err = read_symlink_reparse_data(_Handle, _Buffer_unique_ptr);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }
        } // Close _Handle

        const auto _Buffer = reinterpret_cast<__std_fs_reparse_data_buffer*>(_Buffer_unique_ptr.get());
        unsigned short _Length;
        wchar_t* _Offset;
        _Err = __std_fs_read_name_from_reparse_data_buffer(_Buffer, &_Offset, &_Length);
        if (_Err != __std_win_error::_Success) {
            return _Err;
        }

        res._Text.resize(_Length);
        _CSTD memcpy(res._Text.data(), _Offset, _Length * sizeof(wchar_t));

        return __std_win_error::_Success;
    }

    inline data_path read_symlink(const data_path& _Symlink_path, std::error_code& _Ec) {
        _Ec.clear();
        data_path res;
        _Ec = make_err_code(read_symlink(_Symlink_path, res));
        return res;
    }

    inline data_path read_symlink(const data_path& _Symlink_path) {
        data_path res;
        const auto _Err = read_symlink(_Symlink_path, res);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("read_symlink", _Err, _Symlink_path);
        }
        return res;
    }

    // FUNCTION copy_symlink
    inline __std_win_error _Copy_symlink(const data_path& _Symlink, const data_path& _New_symlink) noexcept {
        __std_win_error _Err;
        unique_ptr<char[]> _Buffer_unique_ptr;
        bool _Is_directory;
        {
            const _Fs_file _Handle(_Symlink.c_str(), __std_access_rights::_File_read_attributes,
                __std_fs_file_flags::_Backup_semantics | __std_fs_file_flags::_Open_reparse_point, &_Err);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }

            _Err = read_symlink_reparse_data(_Handle, _Buffer_unique_ptr);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }

            unsigned long _File_attributes;
            _Err = __std_fs_get_file_attributes_by_handle(_Handle._Raw, &_File_attributes);
            if (_Err != __std_win_error::_Success) {
                return _Err;
            }

            _Is_directory = (_File_attributes & static_cast<unsigned long>(__std_fs_file_attr::_Directory)) != 0;
        } // Close _Handle

        const auto _Buffer = reinterpret_cast<__std_fs_reparse_data_buffer*>(_Buffer_unique_ptr.get());
        unsigned short _Length;
        wchar_t* _Offset;
        _Err = __std_fs_read_name_from_reparse_data_buffer(_Buffer, &_Offset, &_Length);
        if (_Err != __std_win_error::_Success) {
            return _Err;
        }

        _Offset[_Length] = L'\0';

        if (_Is_directory) {
            _Err = __std_fs_create_directory_symbolic_link(_New_symlink.c_str(), _Offset);
        } else {
            _Err = __std_fs_create_symbolic_link(_New_symlink.c_str(), _Offset);
        }

        return _Err;
    }

    inline void copy_symlink(const data_path& _Symlink, const data_path& _New_symlink, std::error_code& _Ec) {
        _Ec = make_err_code(_Copy_symlink(_Symlink, _New_symlink));
    }

    inline void copy_symlink(const data_path& _Symlink, const data_path& _New_symlink) {
        const auto _Err = _Copy_symlink(_Symlink, _New_symlink);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("copy_symlink", _Err, _Symlink, _New_symlink);
        }
    }

    // FUNCTION copy_file
    inline bool copy_file(const data_path& _From, const data_path& _To, const copy_options _Options, std::error_code& _Ec) noexcept
    /* strengthened */ {
        // copy a file _From -> _To according to _Options
        const auto res =
            __std_fs_copy_file(_From.c_str(), _To.c_str(), static_cast<__std_fs_copy_options>(_Options));
        _Ec = make_err_code(res._Error);
        return res._Copied;
    }

    inline bool copy_file(const data_path& _From, const data_path& _To, const copy_options _Options) {
        // copy a file _From -> _To according to _Options
        const auto res =
            __std_fs_copy_file(_From.c_str(), _To.c_str(), static_cast<__std_fs_copy_options>(_Options));
        if (res._Error != __std_win_error::_Success) {
            throw_file_sys_err("copy_file", res._Error, _From, _To);
        }

        return res._Copied;
    }

    inline bool copy_file(const data_path& _From, const data_path& _To, std::error_code& _Ec) noexcept /* strengthened */ {
        // copy a file _From -> _To, failing if the destination exists
        return _STD filesystem::copy_file(_From, _To, copy_options::none, _Ec);
    }

    inline bool copy_file(const data_path& _From, const data_path& _To) {
        // copy a file _From -> _To, failing if the destination exists
        return _STD filesystem::copy_file(_From, _To, copy_options::none);
    }

    // FUNCTION equivalent
    inline pair<__std_win_error, bool> _Equivalent(
        const wchar_t* const _Lhs, const wchar_t* const _Rhs) noexcept {
        __std_fs_file_id _Left_id;
        __std_fs_file_id _Right_id;
        auto _Last_error = __std_fs_get_file_id(&_Left_id, _Lhs);
        if (_Last_error != __std_win_error::_Success) {
            return {_Last_error, false};
        }

        _Last_error = __std_fs_get_file_id(&_Right_id, _Rhs);
        if (_Last_error != __std_win_error::_Success) {
            return {_Last_error, false};
        }

        return {__std_win_error::_Success, _CSTD memcmp(&_Left_id, &_Right_id, sizeof(__std_fs_file_id)) == 0};
    }

    inline bool equivalent(const data_path& _Lhs, const data_path& _Rhs) {
        // test if the paths _Lhs and _Rhs refer to the same file
        const auto res = _Equivalent(_Lhs.c_str(), _Rhs.c_str());
        if (res.first != __std_win_error::_Success) {
            throw_file_sys_err("equivalent", res.first, _Lhs, _Rhs);
        }

        return res.second;
    }

    inline bool equivalent(const data_path& _Lhs, const data_path& _Rhs, std::error_code& _Ec) noexcept {
        // test if the paths _Lhs and _Rhs refer to the same file
        const auto res = _Equivalent(_Lhs.c_str(), _Rhs.c_str());
        _Ec                = make_err_code(res.first);
        return res.second;
    }

    // FUNCTION exists
    inline file_status status(const data_path& _Path);
    inline file_status status(const data_path& _Path, std::error_code& _Ec) noexcept;
    inline file_status symlink_status(const data_path& _Path);
    inline file_status symlink_status(const data_path& _Path, std::error_code& _Ec) noexcept;

    inline bool exists(const data_path& _Target, std::error_code& _Ec) noexcept {
        const auto _Type = _STD filesystem::status(_Target, _Ec).type();
        if (_Type != file_type::none) {
            _Ec.clear();
            return _Type != file_type::not_found;
        }

        return false;
    }

    inline bool exists(const data_path& _Target) {
        std::error_code _Ec;
        const bool res = _STD filesystem::exists(_Target, _Ec);
        if (_Ec) {
            throw_file_sys_err("exists", _Ec, _Target);
        }

        return res;
    }

    // FUNCTION file_size
    inline __std_win_error _File_size(const data_path& _Path, uintmax_t& res) noexcept {
        __std_fs_stats _Stats;
        const auto _Error = __std_fs_get_stats(
            _Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_File_size);
        if (_Error == __std_win_error::_Success) {
            res = _Stats._File_size;
        } else {
            res = static_cast<uintmax_t>(-1);
        }

        return _Error;
    }

    inline uintmax_t file_size(const data_path& _Path) {
        uintmax_t res;
        const auto _Error = _File_size(_Path, res);
        if (_Error != __std_win_error::_Success) {
            throw_file_sys_err("file_size", _Error, _Path);
        }

        return res;
    }

    inline uintmax_t file_size(const data_path& _Path, std::error_code& _Ec) noexcept {
        uintmax_t res;
        _Ec = make_err_code(_File_size(_Path, res));
        return res;
    }

    // FUNCTION hard_link_count
    inline __std_win_error _Hard_link_count(const data_path& _Path, uintmax_t& res) noexcept {
        __std_fs_stats _Stats;
        const auto _Error = __std_fs_get_stats(
            _Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_Link_count);
        if (_Error == __std_win_error::_Success) {
            res = _Stats._Link_count;
        } else {
            res = static_cast<uintmax_t>(-1);
        }

        return _Error;
    }

    inline uintmax_t hard_link_count(const data_path& _Target) { // get the number of hard links to _Target
        uintmax_t res;
        const auto _Err = _Hard_link_count(_Target.c_str(), res);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("hard_link_count", _Err, _Target);
        }

        return res;
    }

    inline uintmax_t hard_link_count(const data_path& _Target, std::error_code& _Ec) noexcept {
        // get the number of hard links to _Target
        uintmax_t res;
        _Ec = make_err_code(_Hard_link_count(_Target.c_str(), res));
        return res;
    }

    // FUNCTION is_block_file
    inline bool is_block_file(const data_path&) noexcept /* strengthened */ {
        // tests whether the input data_path is a block special file (never on Windows)
        return false;
    }

    inline bool is_block_file(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether the input data_path is a block special file (never on Windows)
        (void) _STD filesystem::status(_Path, _Ec);
        return false; // note status sets _Ec to an error on nonexistent input
    }

    // FUNCTION is_character_file
    inline bool is_character_file(const data_path&) noexcept /* strengthened */ {
        // tests whether the input data_path is a character special file (never on Windows)
        return false;
    }

    inline bool is_character_file(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether the input data_path is a character special file (never on Windows)
        (void) _STD filesystem::status(_Path, _Ec);
        return false; // note status sets _Ec to an error on nonexistent input
    }

    // FUNCTION is_directory
    inline bool is_directory(const data_path& _Path) { // tests whether _Path is a directory
        return _STD filesystem::is_directory(_STD filesystem::status(_Path));
    }

    inline bool is_directory(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether _Path is a directory
        return _STD filesystem::is_directory(_STD filesystem::status(_Path, _Ec));
    }

    // FUNCTION is_empty
    inline bool is_empty(const data_path& _Path, std::error_code& _Ec) {
        // test whether _Path refers to a zero sized file or empty directory
        constexpr auto _Flags = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_File_size
                                | __std_fs_stats_flags::_Follow_symlinks;
        __std_fs_stats _Stats;
        const auto _Error = __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags);
        _Ec               = make_err_code(_Error);
        if (_Error != __std_win_error::_Success) {
            return false;
        }

        if ((_Stats._Attributes & __std_fs_file_attr::_Directory) == __std_fs_file_attr{}) {
            return _Stats._File_size == 0;
        } else {
            directory_iterator _Iter(_Path, _Ec);
            return !_Ec && _Iter._At_end();
        }
    }

    inline bool is_empty(const data_path& _Path) {
        // test whether _Path refers to a zero sized file or empty directory
        std::error_code _Ec;
        const bool res = is_empty(_Path, _Ec);
        if (_Ec) {
            throw_file_sys_err("is_empty", _Ec, _Path);
        }

        return res;
    }

    // FUNCTION is_fifo
    inline bool is_fifo(const data_path&) noexcept /* strengthened */ {
        // tests whether the input data_path is a fifo (never on Windows)
        return false;
    }

    inline bool is_fifo(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether the input data_path is a fifo (never on Windows)
        (void) _STD filesystem::status(_Path, _Ec);
        return false; // note status sets _Ec to an error on nonexistent input
    }

    // FUNCTION is_other
    inline bool is_other(const data_path& _Path) { // tests whether _Path is an other file (such as a junction)
        return _STD filesystem::is_other(_STD filesystem::status(_Path));
    }

    inline bool is_other(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether _Path is an other file (such as a junction)
        return _STD filesystem::is_other(_STD filesystem::status(_Path, _Ec));
    }

    // FUNCTION is_regular_file
    inline bool is_regular_file(const data_path& _Path) { // tests whether _Path is a regular file
        return _STD filesystem::is_regular_file(_STD filesystem::status(_Path));
    }

    inline bool is_regular_file(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether _Path is a regular file
        return _STD filesystem::is_regular_file(_STD filesystem::status(_Path, _Ec));
    }

    // FUNCTION is_socket
    inline bool is_socket(const data_path&) noexcept /* strengthened */ {
        // tests whether the input data_path is a socket (never on Windows)
        return false;
    }

    inline bool is_socket(const data_path& _Path, std::error_code& _Ec) noexcept {
        // tests whether the input data_path is a socket (never on Windows)
        (void) _STD filesystem::status(_Path, _Ec);
        return false; // note status sets _Ec to an error on nonexistent input
    }

    // FUNCTION is_symlink
    inline bool is_symlink(const data_path& _Path) { // tests whether _Path is a symlink
        return _STD filesystem::is_symlink(_STD filesystem::symlink_status(_Path));
    }

    inline bool is_symlink(const data_path& _Path, std::error_code& _Ec) noexcept { // tests whether _Path is a symlink
        return _STD filesystem::is_symlink(_STD filesystem::symlink_status(_Path, _Ec));
    }

    // FUNCTION remove
    inline bool remove(const data_path& _Target) {
        // remove file _Target (even if it is a directory); returns whether the file was removed
        // note !exists(_Target) is not an error, and merely returns false
        const auto res = __std_fs_remove(_Target.c_str());
        if (res._Error != __std_win_error::_Success) {
            throw_file_sys_err("remove", res._Error, _Target);
        }

        return res._Removed;
    }

    inline bool remove(const data_path& _Target, std::error_code& _Ec) noexcept {
        // remove file _Target (even if it is a directory); returns whether the file was removed
        // note !exists(_Target) is not an error, and merely returns false
        const auto res = __std_fs_remove(_Target.c_str());
        _Ec                = make_err_code(res._Error);
        return res._Removed;
    }

    // FUNCTION rename
    inline void rename(const data_path& _Old_p, const data_path& _New_p) {
        // rename _Old_p to _New_p, overwriting _New_p if it is an existing non-directory file
        // the standard explicitly allows an implementation to not replace _New_p if it is a directory,
        // and we take advantage of that here to be able to use MoveFileEx(... MOVEFILE_REPLACE_EXISTING)
        const auto _Err = __std_fs_rename(_Old_p.c_str(), _New_p.c_str());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("rename", _Err, _Old_p, _New_p);
        }
    }

    inline void rename(const data_path& _Old_p, const data_path& _New_p, std::error_code& _Ec) noexcept {
        // rename _Old_p to _New_p, overwriting _New_p if it is an existing non-directory file
        // the standard explicitly allows an implementation to not replace _New_p if it is a directory,
        // and we take advantage of that here to be able to use MoveFileEx(... MOVEFILE_REPLACE_EXISTING)
        _Ec = make_err_code(__std_fs_rename(_Old_p.c_str(), _New_p.c_str()));
    }

    // FUNCTION resize_file
    inline void resize_file(const data_path& _Target, const uintmax_t _New_size) {
        // set the size of _Target to _New_size
        const auto _Err = __std_fs_resize_file(_Target.c_str(), _New_size);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("resize_file", _Err, _Target);
        }
    }

    inline void resize_file(const data_path& _Target, const uintmax_t _New_size, std::error_code& _Ec) noexcept {
        // set the size of _Target to _New_size
        _Ec = make_err_code(__std_fs_resize_file(_Target.c_str(), _New_size));
    }

    // FUNCTION space
    struct space_info {
        uintmax_t capacity;
        uintmax_t free;
        uintmax_t available;
    };

    inline space_info space(const data_path& _Target) {
        // get capacity information for the volume on which the file _Target resides
        space_info res;
        const auto _Last_error = __std_fs_space(_Target.c_str(), &res.available, &res.capacity, &res.free);
        if (_Last_error != __std_win_error::_Success) {
            throw_file_sys_err("space", _Last_error, _Target);
        }

        return res;
    }

    inline space_info space(const data_path& _Target, std::error_code& _Ec) noexcept {
        // get capacity information for the volume on which the file _Target resides
        space_info res;
        _Ec = make_err_code(__std_fs_space(_Target.c_str(), &res.available, &res.capacity, &res.free));
        return res;
    }

    // FUNCTION status_known
    inline bool status_known(const file_status _Status) noexcept {
        return _Status.type() != file_type::none;
    }

    // FUNCTION status
    inline _File_status_and_error _Get_any_status(
        const data_path& _Path, const __std_fs_stats_flags _Flags) noexcept {
        _File_status_and_error res;
        __std_fs_stats _Stats;

        const auto _Error = __std_fs_get_stats(_Path.c_str(), &_Stats, _Flags);
        res._Error    = _Error;
        res._Status._Refresh(_Error, _Stats);

        return res;
    }

    inline file_status status(const data_path& _Path, std::error_code& _Ec) noexcept {
        const auto res = _Get_any_status(_Path, _Status_stats_flags);
        _Ec                = make_err_code(res._Error);
        return res._Status;
    }

    inline file_status status(const data_path& _Path) {
        const auto res = _Get_any_status(_Path, _Status_stats_flags);
        if (res._Not_good()) {
            throw_file_sys_err("status", res._Error, _Path);
        }
        return res._Status;
    }

    // FUNCTION symlink_status
    inline file_status symlink_status(const data_path& _Path, std::error_code& _Ec) noexcept {
        const auto res = _Get_any_status(_Path, _Symlink_status_stats_flags);
        _Ec                = make_err_code(res._Error);
        return res._Status;
    }

    inline file_status symlink_status(const data_path& _Path) {
        const auto res = _Get_any_status(_Path, _Symlink_status_stats_flags);
        if (res._Not_good()) {
            throw_file_sys_err("symlink_status", res._Error, _Path);
        }

        return res._Status;
    }

    // FUNCTION create_directory
    inline bool create_directory(const data_path& _Path) {
        const auto res = __std_fs_create_directory(_Path.c_str());
        if (res._Error != __std_win_error::_Success) {
            throw_file_sys_err("create_directory", res._Error, _Path);
        }

        return res._Created;
    }

    inline bool create_directory(const data_path& _Path, std::error_code& _Ec) noexcept {
        const auto res = __std_fs_create_directory(_Path.c_str());
        _Ec                = make_err_code(res._Error);
        return res._Created;
    }

    inline bool create_directory(const data_path& _Path, const data_path& _Existing_p) {
        const auto res = __std_fs_create_directory(_Path.c_str());
        if (res._Error != __std_win_error::_Success) {
            throw_file_sys_err("create_directory", res._Error, _Path, _Existing_p);
        }

        return res._Created;
    }

    inline bool create_directory(const data_path& _Path, const data_path&, std::error_code& _Ec) noexcept {
        const auto res = __std_fs_create_directory(_Path.c_str());
        _Ec                = make_err_code(res._Error);
        return res._Created;
    }

    // FUNCTION create_directories
    inline bool create_directories(const data_path& _Path, std::error_code& _Ec) {
        _Ec.clear(); // for exception safety
        const std::wstring& _Text = _Path.native();
        std::wstring _Tmp;
        _Tmp.reserve(_Text.size());
        auto _Cursor        = _Text.data();
        const auto _End     = _Text.data() + _Text.size();
        auto _Root_path_end = find_rel_path(_Cursor, _End);
        if (_Root_path_end != _Cursor && _End - _Root_path_end >= 3 && is_drive_prefix(_Root_path_end)
            && _Is_slash(_Root_path_end[2])) {
            // \\?\ prefixes may have a drive letter suffix Windows will reject, strip
            _Root_path_end += 2;
        }

        _Tmp.append(_Cursor, _Root_path_end);
        _Cursor = _Root_path_end;

        // When creating directories, sometimes we get error reports on earlier directories.
        // Consider a case like X:\foo\bar\baz, where we get the following errors:
        // X: ERROR_ACCESS_DENIED
        // X:\foo ERROR_ALREADY_EXISTS
        // X:\foo\bar ERROR_ACCESS_DENIED
        // X:\foo\bar\baz ERROR_FILE_NOT_FOUND
        // Here, the previous access denied error prevented us from creating a over directory,
        // and the subsequent ERROR_FILE_NOT_FOUND is not the interesting error for the user.
        // Therefore:
        //   If the last directory creation reports success, we return success.
        //   If the last directory creation fails, we return the most recent non-file-not-found error.
        //   If there is no such non-file-not-found error, we return the most recent error.

        bool _Created_last                              = false;
        __std_win_error _Error                          = __std_win_error::_Success;
        __std_win_error _Most_recent_not_file_not_found = __std_win_error::_Success;
        while (_Cursor != _End) {
            const auto _Added_end = _STD find_if(_STD find_if_not(_Cursor, _End, _Is_slash), _End, _Is_slash);
            _Tmp.append(_Cursor, _Added_end);
            const auto _Create_result = __std_fs_create_directory(_Tmp.c_str());
            _Error                    = _Create_result._Error;
            _Created_last             = _Create_result._Created;
            _Error                    = _Create_result._Error;
            if (_Error != __std_win_error::_Success && !__std_is_file_not_found(_Error)) {
                _Most_recent_not_file_not_found = _Error;
            }

            _Cursor = _Added_end;
        }

        if (_Error != __std_win_error::_Success && _Most_recent_not_file_not_found != __std_win_error::_Success) {
            _Error = _Most_recent_not_file_not_found;
        }

        _Ec = make_err_code(_Error);
        return _Created_last;
    }

    inline bool create_directories(const data_path& _Path) {
        std::error_code _Ec;
        const bool res = _STD filesystem::create_directories(_Path, _Ec);
        if (_Ec) {
            throw_file_sys_err("create_directories", _Ec, _Path);
        }

        return res;
    }

    // FUNCTION remove_all
    inline constexpr int _Remove_all_retry_count = 10;

    inline void _Remove_all_dir(const data_path& _Path, std::error_code& _Ec, uintmax_t& _Removed_count) {
        // remove _Path, including any contents
        for (directory_iterator _It(_Path, _Ec);; _It.increment(_Ec)) { // remove nonempty directory contents
            if (_Ec) {
                if (_Ec.category() != _STD system_category()
                    || !__std_is_file_not_found(static_cast<__std_win_error>(_Ec.value()))) {
                    return;
                }

                break;
            }

            if (_It._At_end()) {
                break;
            }

            const auto& _Subpath  = _It->data_path();
            const auto _Substatus = _It->symlink_status(_Ec);
            if (_Ec) {
                return;
            }

            if (_Substatus.type() == file_type::directory) {
                _Remove_all_dir(_Subpath, _Ec, _Removed_count);
            } else {
                _Removed_count += _STD filesystem::remove(_Subpath, _Ec);
            }

            if (_Ec) {
                return;
            }
        }

        for (int _Retry = 0; _Retry < _Remove_all_retry_count; ++_Retry) {
            // retry up to _Remove_all_retry_count for resilience against
            // A/V tools, search indexers, backup tools, etc.
            const auto _Path_remove_result = __std_fs_remove(_Path.c_str());
            _Removed_count += _Path_remove_result._Removed;
            _Ec = make_err_code(_Path_remove_result._Error);
            if (_Path_remove_result._Error != __std_win_error::_Directory_not_empty
                && _Path_remove_result._Error != __std_win_error::_Access_denied) {
                // ERROR_DIRECTORY_NOT_EMPTY if we're waiting for handles to children to be closed,
                // ERROR_ACCESS_DENIED if the directory we're targeting itself is marked for deletion.
                return;
            }
        }
    }

    inline uintmax_t remove_all(const data_path& _Path, std::error_code& _Ec) { // remove _Path, including any contents
        _Ec.clear(); // for exception safety
        const auto _First_remove_result = __std_fs_remove(_Path.c_str());
        uintmax_t _Removed_count        = _First_remove_result._Removed;
        _Ec                             = make_err_code(_First_remove_result._Error);
        if (_First_remove_result._Error == __std_win_error::_Directory_not_empty) {
            _Remove_all_dir(_Path, _Ec, _Removed_count);
        }

        if (_Ec) {
            _Removed_count = static_cast<uintmax_t>(-1);
        }

        return _Removed_count;
    }

    inline uintmax_t remove_all(const data_path& _Path) {
        std::error_code _Ec;
        const auto _Removed_count = _STD filesystem::remove_all(_Path, _Ec);
        if (_Ec) {
            throw_file_sys_err("remove_all", _Ec, _Path);
        }

        return _Removed_count;
    }

    // FUNCTION last_write_time
    inline __std_win_error _Last_write_time(const data_path& _Path, file_time_type& res) noexcept {
        __std_fs_stats _Stats;
        const auto _Error = __std_fs_get_stats(
            _Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_Last_write_time);
        if (_Error == __std_win_error::_Success) {
            res = file_time_type{file_time_type::duration{_Stats._Last_write_time}};
        } else {
            res = (file_time_type::min)();
        }

        return _Error;
    }

    inline file_time_type last_write_time(const data_path& _Path) {
        file_time_type res;
        const auto _Error = _Last_write_time(_Path, res);
        if (_Error != __std_win_error::_Success) {
            throw_file_sys_err("last_write_time", _Error, _Path);
        }

        return res;
    }

    inline file_time_type last_write_time(const data_path& _Path, std::error_code& _Ec) noexcept {
        file_time_type res;
        _Ec = make_err_code(_Last_write_time(_Path, res));
        return res;
    }

    inline void last_write_time(const data_path& _Target, const file_time_type _New_time) {
        // set the last write time of _Target to _New_time
        const auto _Err = __std_fs_set_last_write_time(_New_time.time_since_epoch().count(), _Target.c_str());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("last_write_time", _Err, _Target);
        }
    }

    inline void last_write_time(const data_path& _Target, const file_time_type _New_time, std::error_code& _Ec) noexcept {
        // set the last write time of _Target to _New_time
        _Ec = make_err_code(__std_fs_set_last_write_time(_New_time.time_since_epoch().count(), _Target.c_str()));
    }

    // FUNCTION permissions
    enum class perm_options { replace = 0x1, add = 0x2, remove = 0x4, nofollow = 0x8 };

    _BITMASK_OPS(perm_options)

    inline __std_win_error _Permissions(
        const data_path& _Target, const file_perms _Perms, perm_options _Options) noexcept {
        bool _Readonly;
        const bool _Follow_symlinks = (_Options & perm_options::nofollow) == perm_options{};
        _Options &= ~perm_options::nofollow;
        const auto _Write_file_perms = _Perms & file_perms::_All_write;
        switch (_Options) {
        case perm_options::replace:
            // always apply FILE_ATTRIBUTE_READONLY according to _Perms
            _Readonly = _Write_file_perms == file_perms::none;
            break;
        case perm_options::add:
            if (_Write_file_perms == file_perms::none) {
                // if we aren't adding any write bits, then we won't change
                // FILE_ATTRIBUTE_READONLY, so there's nothing to do
                return __std_win_error::_Success;
            }

            _Readonly = false;
            break;
        case perm_options::remove:
            if (_Write_file_perms != file_perms::_All_write) {
                // if we aren't removing all write bits, then we won't change
                // FILE_ATTRIBUTE_READONLY, so there's nothing to do
                return __std_win_error::_Success;
            }

            _Readonly = true;
            break;
        case perm_options::nofollow: // avoid C4061
        default:
            return __std_win_error::_Invalid_parameter;
        }

        return __std_fs_change_permissions(_Target.c_str(), _Follow_symlinks, _Readonly);
    }

    inline void permissions(
        const data_path& _Target, const file_perms _Perms, const perm_options _Options = perm_options::replace) {
        const auto _Err = _Permissions(_Target, _Perms, _Options);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("permissions", _Err, _Target);
        }
    }

    inline void permissions(
        const data_path& _Target, const file_perms _Perms, const perm_options _Options, std::error_code& _Ec) noexcept {
        _Ec = make_err_code(_Permissions(_Target, _Perms, _Options));
    }

    inline void permissions(const data_path& _Target, const file_perms _Perms, std::error_code& _Ec) noexcept {
        _STD filesystem::permissions(_Target, _Perms, perm_options::replace, _Ec);
    }

    // FUNCTION temp_dir_path
    inline data_path temp_dir_path(std::error_code& _Ec) {
        // get a location suitable for temporary storage, and verify that it is a directory
        _Ec.clear(); // for exception safety
        data_path res;
        res._Text.resize(__std_fs_temp_path_max);
        const auto _Temp_result = __std_fs_get_temp_path(res._Text.data());
        res._Text.resize(_Temp_result._Size);
        if (_Temp_result._Error == __std_win_error::_Max) { // data_path could be retrieved, but was not a directory
            _Ec = _STD make_error_code(std::errc::not_a_directory);
        } else {
            _Ec = make_err_code(_Temp_result._Error);
        }

        return res;
    }

    inline data_path temp_dir_path() {
        // get a location suitable for temporary storage, and verify that it is a directory
        std::error_code _Ec; // unusual arrangement to allow thrown std::error_code to have generic_category()
        data_path res(_STD filesystem::temp_dir_path(_Ec));
        if (_Ec) {
            throw_file_sys_err("temp_dir_path", _Ec, res);
        }
        return res;
    }

    // FUNCTION curr_path
    inline __std_win_error _curr_path(data_path& res) noexcept {
        res._Text.resize(__std_fs_max_path);
        for (;;) {
            const auto _Requested_size = static_cast<unsigned long>(res._Text.size());
            const auto _Temp_result    = __std_fs_get_current_path(_Requested_size, res._Text.data());
            res._Text.resize(_Temp_result._Size);
            if (_Temp_result._Size < _Requested_size) {
                return _Temp_result._Error;
            }
        }
    }

    inline data_path curr_path(std::error_code& _Ec) {
        _Ec.clear();
        data_path res;
        _Ec = make_err_code(_curr_path(res));
        return res;
    }

    inline data_path curr_path() {
        data_path res;
        const auto _Err = _curr_path(res);
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("curr_path()", _Err);
        }
        return res;
    }

    inline void curr_path(const data_path& _To, std::error_code& _Ec) noexcept { // set the current data_path
        _Ec = make_err_code(__std_fs_set_current_path(_To._Text.data()));
    }

    inline void curr_path(const data_path& _To) { // set the current data_path
        const auto _Err = __std_fs_set_current_path(_To._Text.data());
        if (_Err != __std_win_error::_Success) {
            throw_file_sys_err("curr_path(const data_path&)", _Err, _To);
        }
    }

    // FUNCTION weakly_canonical
    inline data_path weakly_canonical(const data_path& input, std::error_code& _Ec) {
        // eventually calls GetFinalPathNameByHandleW
        _Ec.clear(); // for exception safety

        data_path _Temp;

        {
            const auto _Err = canonical(_Temp, input.native());

            if (_Err == __std_win_error::_Success) {
                return _Temp;
            }

            if (!__std_is_file_not_found(_Err)) {
                _Ec = make_err_code(_Err);
                return {};
            }
        }

        const data_path _Normalized = input.lexically_normal();

        data_path res = _Normalized.root_path();

        const data_path _Normalized_relative = _Normalized.rel_path();

        bool _Call_canonical = true;

        for (const auto& _Elem : _Normalized_relative) {
            res /= _Elem;

            if (_Call_canonical) {
                _Temp.clear();

                const auto _Err = canonical(_Temp, res.native());

                if (_Err == __std_win_error::_Success) {
                    res = _STD move(_Temp);
                } else if (__std_is_file_not_found(_Err)) {
                    _Call_canonical = false;
                } else {
                    _Ec = make_err_code(_Err);
                    return {};
                }
            }
        }

        return res;
    }

    inline data_path weakly_canonical(const data_path& input) {
        // eventually calls GetFinalPathNameByHandleW
        std::error_code _Ec;

        data_path res = _STD filesystem::weakly_canonical(input, _Ec);

        if (_Ec) {
            throw_file_sys_err("weakly_canonical", _Ec, input);
        }

        return res;
    }

    // FUNCTION proximate
    inline data_path proximate(const data_path& _Path, const data_path& _Base = _STD filesystem::curr_path()) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Weakly_canonical_path = _STD filesystem::weakly_canonical(_Path);
        const data_path _Weakly_canonical_base = _STD filesystem::weakly_canonical(_Base);
        return _Weakly_canonical_path.lexically_proximate(_Weakly_canonical_base);
    }

    inline data_path proximate(const data_path& _Path, const data_path& _Base, std::error_code& _Ec) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Weakly_canonical_path = _STD filesystem::weakly_canonical(_Path, _Ec);

        if (_Ec) {
            return {};
        }

        const data_path _Weakly_canonical_base = _STD filesystem::weakly_canonical(_Base, _Ec);

        if (_Ec) {
            return {};
        }

        return _Weakly_canonical_path.lexically_proximate(_Weakly_canonical_base);
    }

    inline data_path proximate(const data_path& _Path, std::error_code& _Ec) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Base = _STD filesystem::curr_path(_Ec);
        // N4810 29.11.14.27 [fs.op.proximate]/1 incorrectly calls curr_path()
        if (_Ec) {
            return {};
        }

        return _STD filesystem::proximate(_Path, _Base, _Ec);
    }

    // FUNCTION relative
    inline data_path relative(const data_path& _Path, const data_path& _Base = _STD filesystem::curr_path()) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Weakly_canonical_path = _STD filesystem::weakly_canonical(_Path);
        const data_path _Weakly_canonical_base = _STD filesystem::weakly_canonical(_Base);
        return _Weakly_canonical_path.lexically_relative(_Weakly_canonical_base);
    }

    inline data_path relative(const data_path& _Path, const data_path& _Base, std::error_code& _Ec) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Weakly_canonical_path = _STD filesystem::weakly_canonical(_Path, _Ec);

        if (_Ec) {
            return {};
        }

        const data_path _Weakly_canonical_base = _STD filesystem::weakly_canonical(_Base, _Ec);

        if (_Ec) {
            return {};
        }

        return _Weakly_canonical_path.lexically_relative(_Weakly_canonical_base);
    }

    inline data_path relative(const data_path& _Path, std::error_code& _Ec) {
        // eventually calls GetFinalPathNameByHandleW
        const data_path _Base = _STD filesystem::curr_path(_Ec);
        // N4810 29.11.14.29 [fs.op.relative]/1 incorrectly calls curr_path()
        if (_Ec) {
            return {};
        }

        return _STD filesystem::relative(_Path, _Base, _Ec);
    }

    // FUNCTION copy
    inline void _Copy_impl(
        const directory_entry& _From, const data_path& _To, const copy_options _Options, std::error_code& _Ec) {
        // implement copy, does not clear _Ec for callers
        // Standard quotes herein are relative to N4810
        // The following parts of LWG-3057 are implemented:
        // * guarding equivalent() from nonexistent to
        // * replacing unspecified recursion prevention tag with copy_options::directories_only
        // Other parts of LWG-3057 remain under discussion in the committee and are not yet implemented.
        //  (In particular, changes to existing destination flags, and error handling).
        const bool _Flink = (_Options & (copy_options::skip_symlinks | copy_options::copy_symlinks))
            != copy_options::none; // create_symlinks intentionally removed by LWG-3057
        const auto _Fstat = _From._Get_any_status(_Flink ? _Symlink_status_stats_flags : _Status_stats_flags);
        if (_Fstat._Error != __std_win_error::_Success) { // report an error if exists(f) is false
            _Ec = make_err_code(_Fstat._Error);
            return;
        }

        const bool _Tlink =
            (_Options & (copy_options::create_symlinks | copy_options::skip_symlinks)) != copy_options::none;
        const auto _Tstat = _Get_any_status(_To, _Tlink ? _Symlink_status_stats_flags : _Status_stats_flags);
        if (_Tstat._Not_good()) {
            _Ec = make_err_code(_Tstat._Error);
            return;
        }

        if (_STD filesystem::exists(_Tstat._Status)) {
            if (_STD filesystem::equivalent(_From, _To, _Ec)) { // report an error if equivalent(from, to) is true
                _Ec = _STD make_error_code(std::errc::file_exists);
                return;
            }

            if (_Ec) {
                return;
            }
        }

        if (_STD filesystem::is_other(_Fstat._Status) || _STD filesystem::is_other(_Tstat._Status)) {
            // report an error if is_other(f) || is_other(t) is true
            _Ec = _STD make_error_code(std::errc::operation_not_supported);
            return;
        }

        if (_STD filesystem::is_directory(_Fstat._Status) && _STD filesystem::is_regular_file(_Tstat._Status)) {
            // report an error if is_directory(f) && is_regular_file(t) is true
            _Ec = _STD make_error_code(std::errc::file_exists);
            return;
        }

        if (_STD filesystem::is_symlink(_Fstat._Status)) {
            if ((_Options & copy_options::skip_symlinks) != copy_options::none) {
                return;
            }

            if (!_STD filesystem::exists(_Tstat._Status)
                && (_Options & copy_options::copy_symlinks) != copy_options::none) {
                // if (condition) then copy_symlink(from, to)
                _STD filesystem::copy_symlink(_From, _To, _Ec);
                return;
            }

            // otherwise report an error
            _Ec = _STD make_error_code(std::errc::operation_not_supported);
            return;
        }

        if (_STD filesystem::is_regular_file(_Fstat._Status)) {
            if ((_Options & copy_options::directories_only) != copy_options::none) {
                return;
            }

            if ((_Options & copy_options::create_symlinks) != copy_options::none) {
                // Otherwise, if (condition) then create a symbolic link to the source file
                _STD filesystem::create_symlink(_From, _To, _Ec);
                return;
            }

            if ((_Options & copy_options::create_hard_links) != copy_options::none) {
                // Otherwise, if (condition) then create a hard link to the source file
                _STD filesystem::create_hard_link(_From, _To, _Ec);
                return;
            }

            if (_STD filesystem::is_directory(_Tstat._Status)) {
                // Otherwise, if is_directory(t), then copy_file(from, to / from.fname(), options)
                _STD filesystem::copy_file(_From, _To / _From.data_path().fname(), _Options, _Ec);
                return;
            }

            // Otherwise, copy_file(_From, _To, _Options)
            _STD filesystem::copy_file(_From, _To, _Options, _Ec);
            return;
        }

        // The following condition modified by LWG-3057:
        if (_STD filesystem::is_directory(_Fstat._Status)) {
            if ((_Options & copy_options::create_symlinks) != copy_options::none) {
                _Ec = _STD make_error_code(std::errc::is_a_directory);
                return;
            }

            _STD filesystem::create_directory(_To, _From, _Ec);
            if (_Ec) {
                return;
            }

            // Note LWG-3057 uses directories_only as the flag, instead of an unspecified copy_options value:
            if ((_Options & copy_options::recursive) != copy_options::none
                || (_Options & copy_options::directories_only) == copy_options::none) {
                for (directory_iterator _It(_From, _Ec);; _It.increment(_Ec)) {
                    if (_Ec || _It._At_end()) {
                        return;
                    }

                    // if ((options & copy_options::recursive) != copy_options::none ||
                    //      !is_directory(linkf ? symlink_status(x.data_path()) : status(x.data_path())))
                    //        copy(x.data_path(), to/x.data_path().fname(), options);
                    bool _Recurse = (_Options & copy_options::recursive) != copy_options::none;
                    if (!_Recurse) {
                        const auto _Child_status_result =
                            _It->_Get_any_status(_Flink ? _Symlink_status_stats_flags : _Status_stats_flags);
                        if (_Child_status_result._Error != __std_win_error::_Success) {
                            _Ec = make_err_code(_Child_status_result._Error);
                            return;
                        }

                        _Recurse = !_STD filesystem::is_directory(_Child_status_result._Status);
                    }

                    if (_Recurse) {
                        _Copy_impl(*_It, _To / _It->data_path().fname(), _Options, _Ec);
                        if (_Ec) {
                            return;
                        }
                    }
                }
            }
        }
        // otherwise, no effects.
    }
    namespace NW
    {
    inline void copy(const data_path& _From, const data_path& _To, const copy_options _Options, std::error_code& _Ec) {
        const directory_entry _From_dir(_From, _Ec);
        if (_Ec) { // report an error if exists(f) is false
            return;
        }

        _Copy_impl(_From_dir, _To, _Options, _Ec);
    }

    inline void copy(const data_path& _From, const data_path& _To, const copy_options _Options) {
        std::error_code _Ec;
        _STD filesystem::copy(_From, _To, _Options, _Ec);
        if (_Ec) {
            throw_file_sys_err("copy", _Ec, _From, _To);
        }
    }

    inline void copy(const data_path& _From, const data_path& _To, std::error_code& _Ec) {
        return _STD filesystem::copy(_From, _To, copy_options::none, _Ec);
    }

    inline void copy(const data_path& _From, const data_path& _To) {
        return _STD filesystem::copy(_From, _To, copy_options::none);
    }
}

#endif // NW_DATA_LIB_H