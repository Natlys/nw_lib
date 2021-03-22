#include <nwl_pch.hpp>
#include "data_sys.h"
#if (defined NW_WAPI)
#include <nwl_math.hpp>
#include <core/nwl_cln.h>
#include <core/nwl_str.h>
#include <io/io_stm.h>
#include <io/io_err.h>
using namespace std::experimental::filesystem;
#if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
    data_sys::data_sys() :
        m_path_curr(current_path())
    {
        if (!get_path().has_parent_path()) { throw init_error(__FILE__, __LINE__); return; }
        if (get_path().parent_path().filename() != NW_STR_NAME) { throw init_error(__FILE__, __LINE__); return; }
        set_path_curr(&get_path().get_over().get_str()[0]);

        std::cout << "data_system has been initialized;" << std::endl;
        std::cout << "current_path: " << get_path() << ";" << std::endl;
    }
    data_sys::~data_sys()
    {
    }
    // --setters
    void data_sys::set_path_curr(cstr cpath) {
        current_path(cpath);
        m_path_curr = current_path();
    }
    // --==<core_methods>==--
    void data_sys::new_drct(cstr dpath)
    {
        if (!is_drct_path(dpath)) { return; }
        SECURITY_ATTRIBUTES scr_atbs{ 0 };
        CreateDirectory(dpath, &scr_atbs);
    }
    void data_sys::del_drct(cstr dpath)
    {
        if (!is_drct_path(dpath)) { return; }
        RemoveDirectory(dpath);
    }
    // --loading
    cstr data_sys::dialog_load(cstr filter, window_handle wnd)
    {
        static constexpr si32 max_chars = 256;
        static char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = max_chars;
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
    }
    bit data_sys::load_file(cstr file_path, ptr destination, size nof_bytes)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_path(file_path), std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(destination), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, dstr& destination)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path(file_path), std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            destination.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&destination[0], destination.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, a_data_cmp& destination) {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path(file_path), std::ios_base::in | std::ios_base::binary);
            fstm >> destination;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --saving
    cstr data_sys::dialog_save(cstr filter, window_handle wnd)
    {
        static constexpr si32 max_chars = 256;
        static char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = sizeof(str_res);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
    }
    bit data_sys::save_file(cstr file_path, ptr source, size nof_bytes)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_path(file_path), std::ios::out | std::ios::binary);
            fstm.write(static_cast<sbyte*>(source), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, dstr& source)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path(file_path), std::ios_base::out | std::ios_base::binary);
            fstm.write(&source[0], source.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, a_data_cmp& source)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path(file_path), std::ios_base::out | std::ios_base::binary);
            fstm << source;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --==</core_methods>==--
}
#endif
#endif  // NW_WAPI