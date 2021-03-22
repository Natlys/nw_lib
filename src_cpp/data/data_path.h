#ifndef NWL_DATA_PATH_H
#define NWL_DATA_PATH_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <core/nwl_cln.h>
#define NW_DATA_PATH_STD
#ifdef NW_DATA_PATH_STD
#include "data/data_lib.h"
namespace NW
{
    class data_path
    {
    private:
        // functions
        friend inline __std_win_error absolute(data_path& _Result, const dstr16& _Text);
        friend inline __std_win_error canonical(data_path& _Result, const dstr16& _Text);
        friend inline data_path temp_dir_path(std::error_code& _Ec);
        friend inline __std_win_error _curr_path(data_path& _Result) noexcept;
        friend inline void curr_path(const data_path& _To);
        friend inline void curr_path(const data_path& _To, std::error_code& _Ec) noexcept;
        friend inline __std_win_error read_symlink(const data_path& _Symlink_path, data_path& _Result) noexcept;
    public: // types
        template <class aiter> friend class data_path_iter;
        using value_type = wchar_t;
        using string_type = std::wstring;

        static constexpr wchar_t preferred_separator = L'\\';

        enum format { auto_format, native_format, generic_format };
    public:     // constructors
        data_path() = default;
        data_path(const data_path& cpy) = default;
        data_path(data_path&& cpy) = default;
        ~data_path() = default;
        data_path(string_type&& _source) : m_str(std::move(_source)) { }
        data_path(string_type&& _source, format fmt) : m_str(std::move(_source)) {
            // format has no meaning for this implementation, as the generic grammar is acceptable as a native data_path
        }

        template <class _Src, std::enable_if_t<is_src<_Src>, int> = 0>
        data_path(const _Src& _source, format = auto_format) : m_str(convert_src_to_wchar(_source)) {
            // format has no meaning for this implementation, as the generic grammar is acceptable as a native data_path
        }

        template <class _InIt>
        data_path(_InIt _First, _InIt _Last, format = auto_format) : m_str(_Convert_range_to_wchar(_First, _Last)) {
            // format has no meaning for this implementation, as the generic grammar is acceptable as a native data_path
            static_assert(is_echar_t<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3");
        }

        template <class _Src, std::enable_if_t<is_src<_Src>, int> = 0>
        data_path(const _Src& _source, const std::locale& _Loc, format = auto_format)
            : m_str(convert_stringoid_with_locale_to_wchar(stringoid_from_src(_source), _Loc)) {
            // format has no meaning for this implementation, as the generic grammar is acceptable as a native data_path
            using stringoid = decltype(stringoid_from_src(_source));
            static_assert(is_same_v<typename stringoid::value_type, char>,
                "invalid value_type, see N4810 29.11.7.4.1 [fs.data_path.construct]/6");
        }

        template <class _InIt>
        data_path(_InIt _First, _InIt _Last, const locale& _Loc, format = auto_format)
            : m_str(convert_stringoid_with_locale_to_wchar(stringoid_from_range(_First, _Last), _Loc)) {
            // format has no meaning for this implementation, as the generic grammar is acceptable as a native data_path
            static_assert(is_same_v<_Iter_value_t<_InIt>, char>,
                "invalid value_type, see N4810 29.11.7.4.1 [fs.data_path.construct]/6");
        }
    public:     // operators
        data_path& operator=(const data_path& cpy) = default;

        data_path& operator=(data_path&& cpy) noexcept = default;

        data_path& operator=(string_type&& _source) noexcept /* strengthened */ {
            // set native() to _source
            m_str = std::move(_source);
            return *this;
        }

        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& operator=(const _Src& _source) { // set native() to _source
            m_str = convert_src_to_wchar(_source);
            return *this;
        }

        data_path& operator/=(const data_path& _Other) {
            // set *this to the data_path lexically resolved by _Other relative to *this
            // examples:
            // data_path("foo") / "c:/bar"; // yields "c:/bar"
            // data_path("foo") / "c:"; // yields "c:"
            // data_path("c:") / ""; // yields "c:"
            // data_path("c:foo") / "/bar"; // yields "c:/bar"
            // data_path("c:foo") / "c:bar"; // yields "c:foo/bar"
            // data_path("c:foo") / "d:bar"; // yields "d:bar"
            // several places herein quote the standard, but the standard's variable p is replaced with _Other

            if (_Other.is_absolute()) { // if _Other.is_absolute(), then op=(_Other)
                return operator=(_Other);
            }

            const auto _My_first = m_str.data();
            const auto _My_last = _My_first + m_str.size();
            const auto _Other_first = _Other.m_str.data();
            const auto _Other_last = _Other_first + _Other.m_str.size();
            const auto _My_root_name_end = find_root_name_end(_My_first, _My_last);
            const auto _Other_root_name_end = find_root_name_end(_Other_first, _Other_last);
            if (_Other_first != _Other_root_name_end
                && _Range_compare(_My_first, _My_root_name_end, _Other_first, _Other_root_name_end) != 0) {
                // if _Other.has_root_name() && _Other.root_name() != root_name(), then op=(_Other)
                return operator=(_Other);
            }

            if (_Other_root_name_end != _Other_last && _Is_slash(*_Other_root_name_end)) {
                // If _Other.has_root_dir() removes any root directory and relative-data_path from *this
                m_str.erase(static_cast<size_t>(_My_root_name_end - _My_first));
            }
            else {
                // Otherwise, if (!has_root_dir && is_absolute) || has_fname appends data_path::preferred_separator
                if (_My_root_name_end == _My_last) {
                    // Here, !has_root_dir && !has_fname
                    // Going through our root_name kinds:
                    // X: can't be absolute here, since those paths are absolute only when has_root_dir
                    // \\?\ can't exist without has_root_dir
                    // \\server can be absolute here
                    if (_My_root_name_end - _My_first >= 3) {
                        m_str.push_back(preferred_separator);
                    }
                }
                else {
                    // Here, has_root_dir || has_fname
                    // If there is a trailing slash, the trailing slash might be part of root_dir.
                    // If it is, has_root_dir && !has_fname, so the test fails.
                    // If there is a trailing slash not part of root_dir, then !has_fname, so only
                    // (!has_root_dir && is_absolute) remains
                    // Going through our root_name kinds:
                    // X:foo\ needs a root_dir to be absolute
                    // \\server\foo must have a root_dir to exist with a rel_path
                    // \\?\ must have a root_dir to exist
                    // As a result, the test fails if there is a trailing slash.
                    // If there is no trailing slash, then has_fname, so the test passes.
                    // Therefore, the test passes if and only if there is no trailing slash.
                    if (!_Is_slash(_My_last[-1])) {
                        m_str.push_back(preferred_separator);
                    }
                }
            }

            // Then appends the native format pathname of _Other, omitting any root-name from its generic format
            // pathname, to the native format pathname.
            m_str.append(_Other_root_name_end, static_cast<size_t>(_Other_last - _Other_root_name_end));
            return *this;
        }

        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& operator/=(const _Src& _source) {
            return operator/=(data_path(_source));
        }

        data_path& operator+=(const data_path& _Added) { // concat _Added to native()
            m_str._Orphan_all();
            m_str += _Added.m_str;
            return *this;
        }

        data_path& operator+=(const string_type& _Added) { // concat _Added to native()
            m_str._Orphan_all();
            m_str += _Added;
            return *this;
        }

        data_path& operator+=(const wstring_view _Added) { // concat _Added to native()
            m_str._Orphan_all();
            m_str += _Added;
            return *this;
        }

        data_path& operator+=(const value_type* const _Added) { // concat _Added to native()
            m_str._Orphan_all();
            m_str += _Added;
            return *this;
        }

        data_path& operator+=(const value_type _Added) { // concat _Added to native()
            m_str._Orphan_all();
            m_str += _Added;
            return *this;
        }

        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& operator+=(const _Src& _Added) { // concat _Added to native()
            return operator+=(data_path(_Added));
        }

        template <class _EcharT, enable_if_t<is_echar_t<_EcharT>, int> = 0>
        data_path& operator+=(const _EcharT _Added) { // concat _Added to native()
            return operator+=(data_path(&_Added, &_Added + 1));
        }

        // implicitly convert *this into a string containing the native format
        operator string_type() const { return m_str; }
        operator const char* () const { return &string()[0]; }
        operator wchar_t* () const { return &wstring()[0]; }
    public:     // core_methods
        data_path& assign(string_type&& _source) noexcept /* strengthened */ {
            // set native() to _source
            m_str = std::move(_source);
            return *this;
        }

        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& assign(const _Src& _source) { // set native() to _source
            m_str = convert_src_to_wchar(_source);
            return *this;
        }

        template <class _InIt>
        data_path& assign(_InIt _First, _InIt _Last) { // set native() to [_First, _Last)
            static_assert(is_echar_t<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3");
            m_str = _Convert_range_to_wchar(_First, _Last);
            return *this;
        }

        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& append(const _Src& _source) { return operator/=(data_path(_source)); }

        template <class _InIt>
        data_path& append(_InIt _First, _InIt _Last) {
            static_assert(is_echar_t<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3");
            return operator/=(data_path(_First, _Last));
        }

        // concat _Added to native()
        template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
        data_path& concat(const _Src& _Added) { return operator+=(data_path(_Added)); }

        template <class _InIt>
        data_path& concat(_InIt _First, _InIt _Last) { // concat [_First, _Last) to native()
            static_assert(is_echar_t<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3");
            return operator+=(data_path(_First, _Last));
        }

        void clear() noexcept { // set *this to the empty data_path
            m_str._Orphan_all();
            m_str.clear();
        }

        data_path& make_preferred() noexcept /* strengthened */ {
            // transform each fallback-separator into preferred-separator
            m_str._Orphan_all();
            std::replace(m_str.begin(), m_str.end(), L'/', L'\\');
            return *this;
        }

        data_path& rmv_fname() noexcept /* strengthened */ {
            // remove any fname from *this
            const auto _First = m_str.data();
            const auto _Last = _First + m_str.size();
            const auto _Filename = find_fname(_First, _Last);
            m_str._Orphan_all();
            m_str.erase(static_cast<size_t>(_Filename - _First));
            return *this;
        }

        void rmv_fname_sep() noexcept { // remove fname and preceding non-root directory-separator
            const auto _First = m_str.data();
            const auto _Last = _First + m_str.size();
            const auto _Root_name_end = find_root_name_end(_First, _Last);
            const auto _Root_dir_end =
                (_Root_name_end != _Last && _Is_slash(*_Root_name_end)) ? _Root_name_end + 1 : _Root_name_end;

            using _Reverse_iter = reverse_iterator<const wchar_t*>;

            const _Reverse_iter _Rbegin{ _Last };
            const _Reverse_iter _Rend{ _Root_dir_end };

            const auto _Rslash_first = std::find_if(_Rbegin, _Rend, _Is_slash);
            const auto _Rslash_last = std::find_if_not(_Rslash_first, _Rend, _Is_slash);

            const _Reverse_iter _Rlast{ _First };

            m_str._Orphan_all();
            m_str.erase(static_cast<size_t>(_Rlast - _Rslash_last));
        }

        data_path& repl_fname(const data_path& _Replacement) { // remove any fname from *this and append _Replacement
            rmv_fname();
            return operator/=(_Replacement);
        }

        data_path& repl_ext(/* const data_path& _Replacement = {} */) noexcept /* strengthened */ {
            // remove any ext() (and alternate data stream references) from *this's fname()
            const wchar_t* _First = m_str.data();
            const auto _Last = _First + m_str.size();
            const auto _Filename = find_fname(_First, _Last);
            const auto _Ads = std::find(_Filename, _Last, L':');
            const auto _Extension = find_ext(_Filename, _Ads);
            m_str._Orphan_all();
            m_str.erase(static_cast<size_t>(_Extension - _First));
            return *this;
        }

        data_path& repl_ext(const data_path& _Replacement) {
            // remove any ext() (and alternate data stream references) from *this's fname(), and concatenate
            // _Replacement
            repl_ext();
            if (!_Replacement.empty() && _Replacement.m_str[0] != L'.') {
                m_str.push_back(L'.');
            }

            return operator+=(_Replacement);
        }

        void swap(data_path& _Rhs) noexcept {
            m_str.swap(_Rhs.m_str);
        }

        _NODISCARD const string_type& native() const noexcept {
            // return a reference to the internally stored wstring in the native format
            return m_str;
        }

        _NODISCARD const value_type* c_str() const noexcept {
            // return a NTCTS to the internally stored data_path in the native format
            return m_str.c_str();
        }

        template <class _EcharT, class _Traits = char_traits<_EcharT>, class _Alloc = allocator<_EcharT>,
            enable_if_t<is_echar_t<_EcharT>, int> = 0>
            _NODISCARD basic_string<_EcharT, _Traits, _Alloc> string(const _Alloc& _Al = _Alloc()) const {
            // convert the native data_path from this instance into a basic_string
            return convert_wchar_to<_Traits>(m_str, _Al);
        }
        // convert the native data_path from this instance into a string
        _NODISCARD std::string string() const { return string<char>(); }
        // copy the native data_path from this instance into a wstring
        _NODISCARD std::wstring wstring() const { return m_str; }

        // convert the native data_path from this instance into a UTF-8 string
        _NODISCARD auto u8string() const {
#ifdef __cpp_lib_char8_t
            using _U8Ty = char8_t;
#else // ^^^ __cpp_lib_char8_t / !__cpp_lib_char8_t vvv
            using _U8Ty = char;
#endif // __cpp_lib_char8_t
            return convert_wchar_to_schar<char_traits<_U8Ty>>(__std_code_page::_Utf8, m_str, allocator<_U8Ty>{});
        }
        // convert the native data_path from this instance into a u16string
        _NODISCARD std::u16string u16string() const { return string<char16_t>(); }
        // convert the native data_path from this instance into a u32string
        _NODISCARD std::u32string u32string() const { return string<char32_t>(); }

        template <class _EcharT, class _Traits = char_traits<_EcharT>, class _Alloc = allocator<_EcharT>,
            enable_if_t<is_echar_t<_EcharT>, int> = 0>
            _NODISCARD basic_string<_EcharT, _Traits, _Alloc> generic_string(const _Alloc& _Al = _Alloc()) const {
            // convert the native data_path from this instance into a generic basic_string
            using _Alwide = _Rebind_alloc_t<_Alloc, wchar_t>;
            _Alwide _Al_wchar(_Al);
            basic_string<wchar_t, char_traits<wchar_t>, _Alwide> _Generic_str(_Al_wchar);
            _Generic_str.resize(m_str.size());
            std::replace_copy(m_str.begin(), m_str.end(), _Generic_str.begin(), L'\\', L'/');
            return convert_wchar_to<_Traits>(_Generic_str, _Al);
        }

        _NODISCARD std::string generic_string() const {
            // convert the native data_path from this instance into a generic string
            return generic_string<char>();
        }

        _NODISCARD std::wstring generic_wstring() const {
            // convert the current native data_path into a copy of it in the generic format
            // note: intra-fname() observers stem() and ext() strip alternate data
            // streams, but fnames with alternate data streams inside can serve as
            // perfectly valid values of fname in the generic format, so in the interest of
            // destroying less information we have preserved them here.
            std::wstring _Result;
            _Result.resize(m_str.size());
            std::replace_copy(m_str.begin(), m_str.end(), _Result.begin(), L'\\', L'/');
            return _Result;
        }

        _NODISCARD auto generic_u8string() const {
            // convert the native data_path from this instance into a generic UTF-8 string
            auto _Result = u8string();
            using _U8Ty = decltype(_Result)::value_type;
            std::replace(_Result.begin(), _Result.end(), _U8Ty{ u8'\\' }, _U8Ty{ u8'/' });
            return _Result;
        }

        _NODISCARD std::u16string generic_u16string() const {
            // convert the native data_path from this instance into a generic u16string
            std::u16string _Result = u16string();
            std::replace(_Result.begin(), _Result.end(), u'\\', u'/');
            return _Result;
        }

        _NODISCARD std::u32string generic_u32string() const {
            // convert the native data_path from this instance into a generic u32string
            std::u32string _Result = u32string();
            std::replace(_Result.begin(), _Result.end(), U'\\', U'/');
            return _Result;
        }

        _NODISCARD int compare(const data_path& _Other) const noexcept { // compare *this with _Other
            return compare(static_cast<wstring_view>(_Other.m_str));
        }

        _NODISCARD int compare(const string_type& _Other) const noexcept /* strengthened */ {
            // compare *this with _Other
            return compare(static_cast<wstring_view>(_Other));
        }

        _NODISCARD int compare(const basic_string_view<value_type> _Other) const noexcept /* strengthened */ {
            // compare *this with _Other
            // several places herein quote the standard, but the standard's variable p is replaced with _Other
            const auto _My_first = m_str.data();
            const auto _My_last = _My_first + m_str.size();
            const auto _My_root_name_end = find_root_name_end(_My_first, _My_last);
            const auto _Other_first = _Other.data();
            const auto _Other_last = _Other_first + _Other.size();
            const auto _Other_root_name_end = find_root_name_end(_Other_first, _Other_last);

            // Let rootNameComparison be the result of this->root_name().native().compare(_Other.root_name().native())
            const int _Root_cmp = _Range_compare(_My_first, _My_root_name_end, _Other_first, _Other_root_name_end);
            if (_Root_cmp != 0) { // If rootNameComparison is not 0, rootNameComparison
                return _Root_cmp;
            }

            auto _My_relative = std::find_if_not(_My_root_name_end, _My_last, _Is_slash);
            auto _Other_relative = std::find_if_not(_Other_root_name_end, _Other_last, _Is_slash);
            const bool _My_has_root_name = _My_root_name_end != _My_relative;
            const bool _Other_has_root_name = _Other_root_name_end != _Other_relative;
            // If !this->has_root_dir() and _Other.has_root_dir(), a value less than 0
            // If this->has_root_dir() and !_Other.has_root_dir(), a value greater than 0
            const int _Root_name_cmp = _My_has_root_name - _Other_has_root_name;
            if (_Root_name_cmp != 0) {
                return _Root_name_cmp;
            }

            // Otherwise, lexicographic by element
            for (;;) {
                const bool _My_empty = _My_relative == _My_last;
                const bool _Other_empty = _Other_relative == _Other_last;
                const int _Empty_cmp = _Other_empty - _My_empty;
                if (_My_empty || _Empty_cmp != 0) {
                    return _Empty_cmp;
                }

                const bool _My_slash = _Is_slash(*_My_relative);
                const bool _Other_slash = _Is_slash(*_Other_relative);
                const int _Slash_cmp = _Other_slash - _My_slash;
                if (_Slash_cmp != 0) {
                    return _Slash_cmp;
                }

                if (_My_slash) { // comparing directory-separator
                    _My_relative = std::find_if_not(_My_relative + 1, _My_last, _Is_slash);
                    _Other_relative = std::find_if_not(_Other_relative + 1, _Other_last, _Is_slash);
                    continue;
                }

                const int _Cmp = *_My_relative - *_Other_relative;
                if (_Cmp != 0) {
                    return _Cmp;
                }

                ++_My_relative;
                ++_Other_relative;
            }
        }

        _NODISCARD int compare(const value_type* const _Other) const noexcept /* strengthened */ {
            // compare *this with _Other
            return compare(static_cast<wstring_view>(_Other));
        }

        _NODISCARD data_path root_name() const {
            // parse the root-name from *this and return a copy if present; otherwise, return the empty data_path
            return parse_root_name(m_str);
        }

        _NODISCARD data_path root_dir() const {
            // parse the root-directory from *this and return a copy if present; otherwise, return the empty data_path
            return parse_root_dir(m_str);
        }

        _NODISCARD data_path root_path() const {
            // parse the root-data_path from *this and return a copy if present; otherwise, return the empty data_path
            return parse_root_path(m_str);
        }

        _NODISCARD data_path rel_path() const {
            // parse the relative-data_path from *this and return a copy if present; otherwise, return the empty data_path
            return parse_rel_path(m_str);
        }

        _NODISCARD data_path over_path() const {
            // parse the over-data_path from *this and return a copy if present; otherwise, return the empty data_path
            return parse_over_path(m_str);
        }

        _NODISCARD data_path fname() const {
            // parse the fname from *this and return a copy if present; otherwise, return the empty data_path
            return parse_fname(m_str);
        }

        _NODISCARD data_path stem() const {
            // parse the stem from *this and return a copy if present; otherwise, return the empty data_path
            return parse_stem(m_str);
        }

        _NODISCARD data_path ext() const {
            // parse the ext from *this and return a copy if present; otherwise, return the empty data_path
            return parse_ext(m_str);
        }

        _NODISCARD bool empty() const noexcept {
            return m_str.empty();
        }

        _NODISCARD bool has_root_name() const noexcept /* strengthened */ {
            // parse the root-name from *this and return whether it exists
            return !parse_root_name(m_str).empty();
        }

        _NODISCARD bool has_root_dir() const noexcept /* strengthened */ {
            // parse the root-directory from *this and return whether it exists
            return !parse_root_dir(m_str).empty();
        }

        _NODISCARD bool has_root_path() const noexcept /* strengthened */ {
            // parse the root-data_path from *this and return whether it exists
            return !parse_root_path(m_str).empty();
        }

        _NODISCARD bool has_rel_path() const noexcept /* strengthened */ {
            // parse the relative-data_path from *this and return whether it exists
            return !parse_rel_path(m_str).empty();
        }

        _NODISCARD bool has_over_path() const noexcept /* strengthened */ {
            // parse the over-data_path from *this and return whether it exists
            return !parse_over_path(m_str).empty();
        }

        _NODISCARD bool has_fname() const noexcept /* strengthened */ {
            // parse the fname from *this and return whether it exists
            return !parse_fname(m_str).empty();
        }

        _NODISCARD bool has_stem() const noexcept /* strengthened */ {
            // parse the stem from *this and return whether it exists
            return !parse_stem(m_str).empty();
        }

        _NODISCARD bool has_ext() const noexcept /* strengthened */ {
            // parse the ext from *this and return whether it exists
            return !parse_ext(m_str).empty();
        }

        _NODISCARD bool is_absolute() const noexcept /* strengthened */ {
            // paths with a root-name that is a drive letter and no root-directory are drive relative, such as x:example
            // paths with no root-name or root-directory are relative, such as example
            // paths with no root-name but a root-directory are root relative, such as \example
            // all other paths are absolute
            const auto _First = m_str.data();
            const auto _Last = _First + m_str.size();
            if (has_drive_letter_prefix(_First, _Last)) { // test for X:\ but not X:foo
                return _Last - _First >= 3 && _Is_slash(_First[2]);
            }

            // if root-name is otherwise nonempty, then it must be one of the always-absolute prefixes like
            // \\?\ or \\server, so the data_path is absolute. Otherwise it is relative.
            return _First != find_root_name_end(_First, _Last);
        }

        _NODISCARD bool is_relative() const noexcept /* strengthened */ {
            // test if *this is a relative data_path
            return !is_absolute();
        }

        _NODISCARD data_path lexically_normal() const {
            using namespace std::string_view_literals; // TRANSITION, VSO-571749

            constexpr wstring_view _Dot = L"."sv;
            constexpr wstring_view _Dot_dot = L".."sv;

            // N4810 29.11.7.1 [fs.data_path.generic]/6:
            // "Normalization of a generic format pathname means:"

            // "1. If the data_path is empty, stop."
            if (empty()) {
                return {};
            }

            // "2. Replace each slash character in the root-name with a preferred-separator."
            const auto _First = m_str.data();
            const auto _Last = _First + m_str.size();
            const auto _Root_name_end = find_root_name_end(_First, _Last);
            string_type _Normalized(_First, _Root_name_end);
            std::replace(_Normalized.begin(), _Normalized.end(), L'/', L'\\');

            // "3. Replace each directory-separator with a preferred-separator.
            // [ Note: The generic pathname grammar (29.11.7.1) defines directory-separator
            // as one or more slashes and preferred-separators. -end note ]"
            list<wstring_view> _Lst; // Empty wstring_view means directory-separator
                                     // that will be normalized to a preferred-separator.
                                     // Non-empty wstring_view means fname.
            for (auto _Next = _Root_name_end; _Next != _Last;) {
                if (_Is_slash(*_Next)) {
                    if (_Lst.empty() || !_Lst.back().empty()) {
                        // collapse one or more slashes and preferred-separators to one empty wstring_view
                        _Lst.emplace_back();
                    }

                    ++_Next;
                }
                else {
                    const auto _Filename_end = std::find_if(_Next + 1, _Last, _Is_slash);
                    _Lst.emplace_back(_Next, static_cast<size_t>(_Filename_end - _Next));
                    _Next = _Filename_end;
                }
            }

            // "4. Remove each dot fname and any immediately following directory-separator."
            for (auto _Next = _Lst.begin(); _Next != _Lst.end();) {
                if (*_Next == _Dot) {
                    _Next = _Lst.erase(_Next); // erase dot fname

                    if (_Next != _Lst.end()) {
                        _Next = _Lst.erase(_Next); // erase immediately following directory-separator
                    }
                }
                else {
                    ++_Next;
                }
            }

            // "5. As long as any appear, remove a non-dot-dot fname immediately followed by a
            // directory-separator and a dot-dot fname, along with any immediately following directory-separator."
            for (auto _Next = _Lst.begin(); _Next != _Lst.end();) {
                auto _Prev = _Next;

                ++_Next; // If we aren't going to erase, keep advancing.
                         // If we're going to erase, _Next now points past the dot-dot fname.

                if (*_Prev == _Dot_dot && _Prev != _Lst.begin() && --_Prev != _Lst.begin() && *--_Prev != _Dot_dot) {
                    if (_Next != _Lst.end()) { // dot-dot fname has an immediately following directory-separator
                        ++_Next;
                    }

                    _Lst.erase(_Prev, _Next); // _Next remains valid
                }
            }

            // "6. If there is a root-directory, remove all dot-dot fnames
            // and any directory-separators immediately following them.
            // [ Note: These dot-dot fnames attempt to refer to nonexistent over directories. -end note ]"
            if (!_Lst.empty() && _Lst.front().empty()) { // we have a root-directory
                for (auto _Next = _Lst.begin(); _Next != _Lst.end();) {
                    if (*_Next == _Dot_dot) {
                        _Next = _Lst.erase(_Next); // erase dot-dot fname

                        if (_Next != _Lst.end()) {
                            _Next = _Lst.erase(_Next); // erase immediately following directory-separator
                        }
                    }
                    else {
                        ++_Next;
                    }
                }
            }

            // "7. If the last fname is dot-dot, remove any trailing directory-separator."
            if (_Lst.size() >= 2 && _Lst.back().empty() && *(std::prev(_Lst.end(), 2)) == _Dot_dot) {
                _Lst.pop_back();
            }

            // Build up _Normalized by flattening _Lst.
            for (const auto& _Elem : _Lst) {
                if (_Elem.empty()) {
                    _Normalized += preferred_separator;
                }
                else {
                    _Normalized += _Elem;
                }
            }

            // "8. If the data_path is empty, add a dot."
            if (_Normalized.empty()) {
                _Normalized = _Dot;
            }

            // "The result of normalization is a data_path in normal form, which is said to be normalized."
            data_path _Result(std::move(_Normalized));

            return _Result;
        }

        _NODISCARD inline data_path lexically_relative(const data_path& _Base) const;

        _NODISCARD data_path lexically_proximate(const data_path& _Base) const {
            data_path _Result = lexically_relative(_Base);

            if (_Result.empty()) {
                _Result = *this;
            }

            return _Result;
        }

        using iterator = path_iter<string_type::const_iterator>;
        using const_iterator = iterator;

        _NODISCARD inline iterator begin() const;
        _NODISCARD inline iterator end() const noexcept; // strengthened

        template <class _Elem, class _Traits>
        friend std::basic_ostream<_Elem, _Traits>& operator<<( // TRANSITION, VSO-570323
            std::basic_ostream<_Elem, _Traits>& _Ostr, const data_path& _Path) { // TRANSITION, VSO-570323
            // insert a data_path into a stream
            return _Ostr << std::quoted(_Path.string<_Elem, _Traits>());
        }

        template <class _Elem, class _Traits>
        friend std::basic_istream<_Elem, _Traits>& operator>>( // TRANSITION, VSO-570323
            std::basic_istream<_Elem, _Traits>& _Istr, data_path& _Path) { // TRANSITION, VSO-570323
            // extract a data_path from a stream
            basic_string<_Elem, _Traits> _Tmp;
            _Istr >> std::quoted(_Tmp);
            _Path = std::move(_Tmp); // obvious optimization not depicted in N4810 29.11.7.6 [fs.data_path.io]/3
            return _Istr;
        }

        _NODISCARD friend bool operator==(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) == 0;
        }

        _NODISCARD friend bool operator!=(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) != 0;
        }

        _NODISCARD friend bool operator<(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) < 0;
        }

        _NODISCARD friend bool operator>(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) > 0;
        }

        _NODISCARD friend bool operator<=(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) <= 0;
        }

        _NODISCARD friend bool operator>=(const data_path& _Left, const data_path& _Right) noexcept {
            return _Left.compare(_Right) >= 0;
        }

        _NODISCARD friend data_path operator/(const data_path& _Left, const data_path& _Right) { // append a pair of paths together
            return data_path(_Left) /= _Right;
        }

    private:
        string_type m_str;
    };
}
namespace NW
{
    template <class _Src, enable_if_t<is_src<_Src>, int> = 0>
    // construct a data_path from utf-8 _source
    _CXX20_DEPRECATE_U8PATH _NODISCARD data_path u8path(const _Src& _source) { return data_path(convert_src_to_wchar(_source, utf8_convert{})); }

    template <class _InIt>
    _CXX20_DEPRECATE_U8PATH _NODISCARD data_path u8path(_InIt _First, _InIt _Last) {
        // construct a data_path from UTF-8 [_First, _Last)
        static_assert(is_echar_t<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3");
        return data_path(_Convert_range_to_wchar(_First, _Last, utf8_convert{}));
    }

    // templated path_iter class
    template <class aiter>
    class path_iter
    { // almost bidirectional iterator for data_path
    public:
        // Note that the data_path::iterator can be decremented and can be dereferenced multiple times,
        // but doesn't actually meet the forward iterator requirements. See N4810 29.11.7.5 [fs.data_path.itr]/2:
        //  ... for dereferenceable iterators a and b of type data_path::iterator with a == b, there is no requirement
        //  that *a and *b are bound to the same object
        // This means that you can't give data_path::iterator to std::reverse_iterator, as operator* there ends
        // up returning a reference to a destroyed temporary. Other algorithms requiring bidirectional
        // iterators may be similarly affected, so we've marked input for now.
        // Also note, in the vector<data_path>(p.begin(), p.end()) case, the user actually probably wants
        // input behavior, as distance()-ing a data_path is fairly expensive.
        using iterator_category = input_iterator_tag;
        using value_type = data_path;
        using difference_type = ptrdiff_t;
        using pointer = const data_path*;
        using reference = const data_path&;

        path_iter() = default;

        path_iter(const aiter& _Position_, const data_path* _Mypath_) noexcept
            : _Position(_Position_), _Element(), _Mypath(_Mypath_) {}

        path_iter(const aiter& _Position_, wstring_view _Element_text, const data_path* _Mypath_)
            : _Position(_Position_), _Element(_Element_text), _Mypath(_Mypath_) {}

        path_iter(const path_iter&) = default;
        path_iter(path_iter&&) = default;
        path_iter& operator=(const path_iter&) = default;
        path_iter& operator=(path_iter&&) = default;

        _NODISCARD reference operator*() const noexcept {
            return _Element;
        }

        _NODISCARD pointer operator->() const noexcept {
            return std::addressof(_Element);
        }

        path_iter& operator++() {
            const auto& m_str = _Mypath->native();
            const auto _Size = _Element.native().size();
            _Adl_verify_range(m_str.begin(), _Position); // engaged when *this is checked
            const auto _Begin = m_str.data();
            const auto _End = _Begin + m_str.size();
            _Adl_verify_range(_Begin, _Position); // engaged when *this is unchecked
            if (_Begin == _Get_unwrapped(_Position)) { // test if the next element will be root-directory
                _Position += static_cast<ptrdiff_t>(_Size);
                const auto _First = m_str.data();
                const auto _Last = _First + m_str.size();
                const auto _Root_name_end = find_root_name_end(_First, _Last);
                const auto _Root_directory_end = std::find_if_not(_Root_name_end, _Last, _Is_slash);
                if (_First != _Root_name_end && _Root_name_end != _Root_directory_end) {
                    // current element is root-name, root-directory exists, so next is root-directory
                    _Element.m_str.assign(_Root_name_end, _Root_directory_end);
                    return *this;
                }

                // If we get here, either there is no root-name, and by !_Is_slash(*_Position), no root-directory,
                // or, current element is root-name, and root-directory doesn't exist.
                // Either way, the next element is the first of relative-data_path
            }
            else if (_Is_slash(*_Position)) { // current element is root-directory, or the "magic empty data_path"
                if (_Size == 0) { // current element was "magic empty data_path", become end()
                    ++_Position;
                    return *this;
                }

                // current element was root-directory, advance to relative-data_path
                _Position += static_cast<ptrdiff_t>(_Size);
            }
            else { // current element is one of relative-data_path
                _Position += static_cast<ptrdiff_t>(_Size);
            }

            if (_Get_unwrapped(_Position) == _End) {
                _Element.clear();
                return *this;
            }

            // at this point, the next element is a standard fname from rel_path(), and _Position
            // points at the preferred-separator or fallback-separator after the previous element
            while (_Is_slash(*_Position)) { // advance to the start of the following data_path element
                if (_Get_unwrapped(++_Position) == _End) { // "magic" empty element selected
                    --_Position;
                    _Element.clear();
                    return *this;
                }
            }

            _Element.m_str.assign(_Get_unwrapped(_Position), std::find_if(_Get_unwrapped(_Position), _End, _Is_slash));
            return *this;
        }

        path_iter operator++(int) {
            path_iter _Tmp = *this;
            ++* this;
            return _Tmp;
        }

        path_iter& operator--() {
            const auto& m_str = _Mypath->native();
            _Adl_verify_range(m_str.begin(), _Position); // engaged when *this is checked
            const auto _First = m_str.data();
            _Adl_verify_range(_First, _Position); // engaged when *this is unchecked
            const auto _Last = _First + m_str.size();
            const auto _Root_name_end_ptr = find_root_name_end(_First, _Last);
            const auto _Root_directory_end_ptr = std::find_if_not(_Root_name_end_ptr, _Last, _Is_slash);

            if (_Root_name_end_ptr != _Root_directory_end_ptr && _Get_unwrapped(_Position) == _Root_directory_end_ptr) {
                // current element is the first of relative-data_path, and the prev element is root-directory
                _Seek_wrapped(_Position, _Root_name_end_ptr);
                _Element.m_str.assign(
                    _Root_name_end_ptr, static_cast<size_t>(_Root_directory_end_ptr - _Root_name_end_ptr));
                return *this;
            }

            if (_First != _Root_name_end_ptr && _Get_unwrapped(_Position) == _Root_name_end_ptr) {
                // current element is root-directory or, if that doesn't exist, first
                // element of relative-data_path prev element therefore is root-name
                _Seek_wrapped(_Position, _First);
                _Element.m_str.assign(_First, static_cast<size_t>(_Root_name_end_ptr - _First));
                return *this;
            }

            // from here, the result will be somewhere in relative-data_path
            if (_Get_unwrapped(_Position) == _Last && _Is_slash(_Position[-1])) { // target is "magic empty data_path"
                --_Position;
                _Element.clear();
                return *this;
            }

            while (_Root_directory_end_ptr != _Get_unwrapped(_Position) && _Is_slash(_Position[-1])) {
                --_Position;
            }

            const auto _New_end = _Position;
            while (_Root_directory_end_ptr != _Get_unwrapped(_Position) && !_Is_slash(_Position[-1])) {
                --_Position;
            }

            _Element.m_str.assign(_Position, _New_end);
            return *this;
        }

        path_iter operator--(int) {
            path_iter _Tmp = *this;
            --* this;
            return _Tmp;
        }

        _NODISCARD friend bool operator==(const path_iter& _Lhs, const path_iter& _Rhs) {
            return _Lhs._Position == _Rhs._Position;
        }

        _NODISCARD friend bool operator!=(const path_iter& _Lhs, const path_iter& _Rhs) {
            return _Lhs._Position != _Rhs._Position;
        }

#if _ITERATOR_DEBUG_LEVEL != 0
        friend void _Verify_range(const path_iter& _Lhs, const path_iter& _Rhs) {
            _Verify_range(_Lhs._Position, _Rhs._Position);
        }
#endif // _ITERATOR_DEBUG_LEVEL != 0

        using _Prevent_inheriting_unwrap = path_iter;

        template <class _Iter2 = aiter, enable_if_t<_Unwrappable_v<const _Iter2&>, int> = 0>
        _NODISCARD path_iter<_Unwrapped_t<const _Iter2&>> _Unwrapped() const {
            return { _Position._Unwrapped(), _Element.native(), _Mypath };
        }

        static constexpr bool _Unwrap_when_unverified = _Do_unwrap_when_unverified_v<aiter>;

        template <class _Other>
        friend class path_iter;

        template <class _Other, enable_if_t<_Wrapped_seekable_v<aiter, const _Other&>, int> = 0>
        constexpr void _Seek_to(const path_iter<_Other>& _It) {
            _Position._Seek_to(_It._Position);
            _Element = _It._Element;
            // _Mypath intentionally unchanged
        }

    private:
        // if the current element is the "magic empty data_path",
        //   points to preferred-separator or fallback-separator immediately before
        // otherwise, points to the first element of _Element
        aiter _Position{};
        data_path _Element{};
        const data_path* _Mypath{};
    };

    inline void swap(data_path& _Left, data_path& _Right) noexcept { _Left.swap(_Right); }

    _NODISCARD inline data_path::iterator data_path::begin() const {
        const auto _First = m_str.data();
        const auto _Last = _First + m_str.size();
        const auto _Root_name_end = find_root_name_end(_First, _Last);
        const wchar_t* _First_end;
        if (_First == _Root_name_end) { // first element isn't root-name
            auto _Root_directory_end = std::find_if_not(_Root_name_end, _Last, _Is_slash);
            if (_First == _Root_directory_end) { // first element is first relative-data_path entry
                _First_end = std::find_if(_Root_directory_end, _Last, _Is_slash);
            }
            else { // first element is root-directory
                _First_end = _Root_directory_end;
            }
        }
        else { // first element is root-name
            _First_end = _Root_name_end;
        }

        return iterator(m_str.cbegin(), wstring_view(_First, static_cast<size_t>(_First_end - _First)), this);
    }

    _NODISCARD inline data_path::iterator data_path::end() const noexcept { return iterator(m_str.cend(), this); }

    _NODISCARD inline data_path data_path::lexically_relative(const data_path& _Base) const {
        using namespace std::string_view_literals; // TRANSITION, VSO-571749

        constexpr wstring_view _Dot = L"."sv;
        constexpr wstring_view _Dot_dot = L".."sv;

        data_path _Result;

        if (root_name() != _Base.root_name() || is_absolute() != _Base.is_absolute()
            || (!has_root_dir() && _Base.has_root_dir()) || rel_path_has_root_name(*this)
            || rel_path_has_root_name(_Base)) {
            return _Result;
        }

        const iterator _This_end = end();
        const iterator _Base_begin = _Base.begin();
        const iterator _Base_end = _Base.end();

        auto _Mismatched = std::mismatch(begin(), _This_end, _Base_begin, _Base_end);
        iterator& _A_iter = _Mismatched.first;
        iterator& _B_iter = _Mismatched.second;

        if (_A_iter == _This_end && _B_iter == _Base_end) {
            _Result = _Dot;
            return _Result;
        }

        { // Skip root-name and root-directory elements, N4810 29.11.7.5 [fs.data_path.itr]/4.1, 4.2
            ptrdiff_t _B_dist = std::distance(_Base_begin, _B_iter);

            const ptrdiff_t _Base_root_dist =
                static_cast<ptrdiff_t>(_Base.has_root_name()) + static_cast<ptrdiff_t>(_Base.has_root_dir());

            while (_B_dist < _Base_root_dist) {
                ++_B_iter;
                ++_B_dist;
            }
        }

        ptrdiff_t _Num = 0;

        for (; _B_iter != _Base_end; ++_B_iter) {
            const data_path& _Elem = *_B_iter;

            if (_Elem.empty()) { // skip empty element, N4810 29.11.7.5 [fs.data_path.itr]/4.4
            }
            else if (_Elem == _Dot) { // skip fname elements that are dot, N4810 29.11.7.4.11 [fs.data_path.gen]/4.2
            }
            else if (_Elem == _Dot_dot) {
                --_Num;
            }
            else {
                ++_Num;
            }
        }

        if (_Num < 0) {
            return _Result;
        }

        if (_Num == 0 && (_A_iter == _This_end || _A_iter->empty())) {
            _Result = _Dot;
            return _Result;
        }

        for (; _Num > 0; --_Num) {
            _Result /= _Dot_dot;
        }

        for (; _A_iter != _This_end; ++_A_iter) {
            _Result /= *_A_iter;
        }

        return _Result;
    }

    _NODISCARD inline size_t hash_value(const data_path& _Path) noexcept {
        // calculate a hash value for _Path
        // See data_path::compare; we effectively decompose the data_path with special handling for root_name, root_dir.
        // Examples:
        // c:\foo\bar =>  {"c:", true , "foo", "bar"}
        // c:foo\bar =>   {"c:", false, "foo", "bar"}
        // \foo\bar =>    {""  , true , "foo", "bar"}
        // foo\bar =>     {""  , false, "foo", "bar"}
        // c:\foo\bar\ => {"c:", true , "foo", "bar", ""}
        size_t _Val = _FNV_offset_basis;
        const auto& m_str = _Path.native();
        const auto _First = m_str.data();
        const auto _Last = _First + m_str.size();

        // First, like compare, examine the raw root_name directly
        auto _Next = find_root_name_end(_First, _Last);
        _Val = _Fnv1a_append_range(_Val, _First, _Next);

        // The remaining data_path elements, including root_dir, are effectively hashed by normalizing each
        // directory-separator into a single preferred-separator when that goes into the hash function.
        // data_path::compare has special handling for root_dir to ensure c:\foo sorts before c:foo, but hash only
        // cares about equality, so no special case is necessary.
        bool _Slash_inserted = false;
        for (; _Next != _Last; ++_Next) {
            if (_Is_slash(*_Next)) {
                if (!_Slash_inserted) {
                    _Val = _Fnv1a_append_value(_Val, data_path::preferred_separator);
                    _Slash_inserted = true;
                }
            }
            else {
                _Val = _Fnv1a_append_value(_Val, *_Next);
                _Slash_inserted = false;
            }
        }

        return _Val;
    }

    _NODISCARD inline bool rel_path_has_root_name(const data_path& _Path) {
        for (const auto& _File_name : _Path.rel_path()) {
            if (!parse_root_name(_File_name.native()).empty()) {
                return true;
            }
        }
        return false;
    }
}
#else
namespace NW
	class data_path
	{
		using data_path = data_path;
		using cpath = const data_path;
		using sub = data_path;
		using subs = darray<data_path>;
		using csubs = const darray<data_path>;
	public:
		data_path();
		data_path(cstr source);
		~data_path();
		// --getters
		inline cstr get_str() const		{ return &m_str[0]; }
		inline data_path get_over() const	{ return data_path(str_part_right(&m_str[0], NW_DIR, 0)); }
		inline csubs get_subs() const	{ return m_subs; }
		// --setters
		// --predicates
		inline bit is_directory() const	{ return m_is_dir; }
		// --operators
		inline operator cstr()					{ return &m_str[0]; }
		inline operator cstr() const			{ return &m_str[0]; }
		inline operator dstr&()					{ return m_str; }
		inline operator cdstr&() const			{ return m_str; }
		inline data_path operator/(cstr src) const	{ return data_path(&(m_str + src)[0]); }
		inline data_path operator/(cpath pth) const	{ return data_path(&(m_str + pth.m_str)[0]); }
		inline data_path& operator/=(cstr src)		{ m_str += src; return *this; }
		inline data_path& operator/=(cpath& pth)		{ m_str += pth.m_str; return *this; }
		// --core_methods
		bit remake();
		inline subs::iterator begin()	{ return m_subs.begin(); }
		inline subs::iterator end()		{ return m_subs.end(); }
	private:
		dstr m_str;
		subs m_subs;
		bit m_is_dir;
	};
}
#endif	// NW_DATA_PATH_STD
#endif	// NWL_DATA_PATH_H