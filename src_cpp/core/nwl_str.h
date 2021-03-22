#ifndef NWL_STRING_H
#define NWL_STRING_H
#include <nwl_core.hpp>
namespace NW
{
	using str = char*;
	using cstr = const char*;
	using dstr = std::string;
	using stm_io_str = std::stringstream;
	using cstr16 = const wchar_t*;
	using dstr16 = std::wstring;
	using dstr_view = std::string_view;
	using dstr16_view = std::wstring_view;
}
namespace NW
{
	NW_API void str_format_var(str buffer, cstr format, va_list& arg_list);
	NW_API dstr str_format_var(cstr format, va_list& arg_list);
	NW_API dstr str_format(cstr format, ...);
	NW_API cstr str_part_left(cstr source, schar delim_char, ui32 from_left = 0);
	NW_API cstr str_part_right(cstr source, schar delim_char, ui32 from_right = 0);
	NW_API cstr str_sub_left(cstr source, ui32 nof_chars, ui32 offset = 0);
	NW_API cstr str_sub_right(cstr source, ui32 nof_chars, ui32 offset = 0);
	NW_API bit str_is_equal(cstr str0, cstr str1);
}
// data_path functions
namespace NW
{
    inline cstr16 find_root_name_end(cstr16 const _First, cstr16 const _Last) {
        // attempt to parse [_First, _Last) as a data_path and return the end of root-name if it exists; otherwise, _First

        // This is the place in the generic grammar where library implementations have the most freedom.
        // Below are example Windows paths, and what we've decided to do with them:
        // * X:DriveRelative, X:\DosAbsolute
        //   We parse X: as root-name, if and only if \ is present we consider that root-directory
        // * \RootRelative
        //   We parse no root-name, and \ as root-directory
        // * \\server\share
        //   We parse \\server as root-name, \ as root-directory, and share as the first element in relative-data_path.
        //   Technically, Windows considers all of \\server\share the logical "root", but for purposes
        //   of decomposition we want those split, so that data_path(R"(\\server\share)").repl_fname("other_share")
        //   is \\server\other_share
        // * \\?\device
        // * \??\device
        // * \\.\device
        //   CreateFile appears to treat these as the same thing; we will set the first three characters as root-name
        //   and the first \ as root-directory. Support for these prefixes varies by particular Windows version, but
        //   for the purposes of data_path decomposition we don't need to worry about that.
        // * \\?\UNC\server\share
        //   MSDN explicitly documents the \\?\UNC syntax as a special case. What actually happens is that the device
        //   Mup, or "Multiple UNC provider", owns the data_path \\?\UNC in the NT namespace, and is responsible for the
        //   network file access. When the user says \\server\share, CreateFile translates that into
        //   \\?\UNC\server\share to get the remote server access behavior. Because NT treats this like any other
        //   device, we have chosen to treat this as the \\?\ case above.
        if (_Last - _First < 2) { return _First; }

        // check for X: first because it's the most common root-name
        if (std::has_drive_letter_prefix(_First, _Last)) { return _First + 2; }

        // all the other root-names start with a slash; check that first because
        // we expect paths without a leading slash to be very common
        if (!std::_Is_slash(_First[0])) { return _First; }

        // $ means anything other than a slash, including potentially the end of the input
        if (_Last - _First >= 4 && std::_Is_slash(_First[3]) && (_Last - _First == 4 || !std::_Is_slash(_First[4])) // \xx\$
            && ((std::_Is_slash(_First[1]) && (_First[2] == L'?' || _First[2] == L'.')) // \\?\$ or \\.\$
                || (_First[1] == L'?' && _First[2] == L'?'))) { // \??\$
            return _First + 3;
        }

        // \\server
        if (_Last - _First >= 3 && std::_Is_slash(_First[1]) && !std::_Is_slash(_First[2])) { return std::find_if(_First + 3, _Last, std::_Is_slash); }

        // no match
        return _First;
    }

    inline std::wstring_view parse_root_name(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the root-name if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        return std::wstring_view(_First, static_cast<size_t>(find_root_name_end(_First, _Last) - _First));
    }

    inline const wchar_t* find_rel_path(const wchar_t* const _First, const wchar_t* const _Last) {
        // attempt to parse [_First, _Last) as a data_path and return the start of relative-data_path
        return _STD find_if_not(find_root_name_end(_First, _Last), _Last, std::_Is_slash);
    }

    inline std::wstring_view parse_root_dir(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the root-directory if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        const auto _Root_name_end = find_root_name_end(_First, _Last);
        const auto _Relative_path = std::find_if_not(_Root_name_end, _Last, std::_Is_slash);
        return std::wstring_view(_Root_name_end, static_cast<size_t>(_Relative_path - _Root_name_end));
    }

    inline std::wstring_view parse_root_path(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the root-data_path if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        return std::wstring_view(_First, static_cast<size_t>(find_rel_path(_First, _Last) - _First));
    }

    inline std::wstring_view parse_rel_path(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the relative-data_path if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        const auto _Relative_path = find_rel_path(_First, _Last);
        return std::wstring_view(_Relative_path, static_cast<size_t>(_Last - _Relative_path));
    }

    inline std::wstring_view parse_over_path(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the over_path if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        auto _Last = _First + _Str.size();
        const auto _Relative_path = find_rel_path(_First, _Last);
        // case 1: relative-data_path ends in a directory-separator, remove the separator to remove "magic empty data_path"
        //  for example: R"(/foo/bar/\//\)"
        // case 2: relative-data_path doesn't end in a directory-separator, remove the fname and last directory-separator
        //  to prevent creation of a "magic empty data_path"; for example: "/foo/bar";

        // handle case 2 by removing trailing fname, puts us into case 1
        while (_Relative_path != _Last && !std::_Is_slash(_Last[-1])) { --_Last; }
        // handle case 1 by removing trailing slashes
        while (_Relative_path != _Last && std::_Is_slash(_Last[-1])) { --_Last; }

        return std::wstring_view(_First, static_cast<size_t>(_Last - _First));
    }

    inline const wchar_t* find_fname(const wchar_t* const _First, const wchar_t* _Last) {
        // attempt to parse [_First, _Last) as a data_path and return the start of fname if it exists; otherwise, _Last
        const auto _Relative_path = find_rel_path(_First, _Last);
        while (_Relative_path != _Last && !std::_Is_slash(_Last[-1])) { --_Last; }
        return _Last;
    }

    inline std::wstring_view parse_fname(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the fname if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        const auto _Filename = find_fname(_First, _Last);
        return std::wstring_view(_Filename, static_cast<size_t>(_Last - _Filename));
    }

    constexpr const wchar_t* find_ext(const wchar_t* const _Filename, const wchar_t* const _Ads) {
        // find dividing point between stem and ext in a generic format fname consisting of [_Filename, _Ads)
        auto _Extension = _Ads;
        // empty data_path
        if (_Filename == _Extension) { return _Ads; }
        --_Extension;
        // data_path is length 1 and either dot, or has no dots; either way, ext() is empty
        if (_Filename == _Extension) { return _Ads; }
        // we might have found the end of stem
        if (*_Extension == L'.') {
            // dotdot special case
            if (_Filename == _Extension - 1 && _Extension[-1] == L'.') { return _Ads; }
            // name.
            else { return _Extension; }
        }

        while (_Filename != --_Extension) {
            // found a dot which is not in first position, so it starts ext()
            if (*_Extension == L'.') { return _Extension; }
        }

        // if we got here, either there are no dots, in which case ext is empty, or the first element
        // is a dot, in which case we have the leading single dot special case, which also makes ext empty
        return _Ads;
    }

    inline std::wstring_view parse_stem(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the stem if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        const auto _Filename = find_fname(_First, _Last);
        const auto _Ads =
            _STD find(_Filename, _Last, L':'); // strip alternate data streams in intra-fname decomposition
        const auto _Extension = find_ext(_Filename, _Ads);
        return std::wstring_view(_Filename, static_cast<size_t>(_Extension - _Filename));
    }

    inline std::wstring_view parse_ext(const std::wstring_view _Str) {
        // attempt to parse _Str as a data_path and return the ext if it exists; otherwise, an empty view
        const auto _First = _Str.data();
        const auto _Last = _First + _Str.size();
        const auto _Filename = find_fname(_First, _Last);
        const auto _Ads =
            _STD find(_Filename, _Last, L':'); // strip alternate data streams in intra-fname decomposition
        const auto _Extension = find_ext(_Filename, _Ads);
        return std::wstring_view(_Extension, static_cast<size_t>(_Ads - _Extension));
    }

    // 3 way compare [_Lfirst, _Llast) with [_Rfirst, _Rlast)
    inline int _Range_compare(cstr16 const _Lfirst, cstr16 const _Llast, cstr16 const _Rfirst, cstr16 const _Rlast) {
        return std::_Traits_compare<std::char_traits<wchar_t>>(_Lfirst, static_cast<size_t>(_Llast - _Lfirst), _Rfirst, static_cast<size_t>(_Rlast - _Rfirst));
    }

    inline bool is_drive_prefix_with_slash_slash_question(const std::wstring_view _Text) {
        // test if _Text starts with a \\?\X: prefix
        using namespace std::string_view_literals; // TRANSITION, VSO-571749
        return _Text.size() >= 6 && _Text._Starts_with(LR"(\\?\)"sv) && std::is_drive_prefix(_Text.data() + 4);
    }

    inline bool is_dot_or_dotdot(const __std_fs_find_data& _Data) {
        // tests if _File_name of __std_fs_find_data is . or ..
        if (_Data._File_name[0] != L'.') {
            return false;
        }

        const auto _Second_char = _Data._File_name[1];
        if (_Second_char == 0) {
            return true;
        }

        if (_Second_char != L'.') {
            return false;
        }

        return _Data._File_name[2] == 0;
    }
}
#endif // NWL_STRING_H