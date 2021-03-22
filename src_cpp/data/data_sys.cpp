#include <nwl_pch.hpp>
#include "data_sys.h"
#if (defined NW_WAPI)
#include <nwl_math.hpp>
#include <core/nwl_cln.h>
#include <core/nwl_str.h>
#include <io/io_stm.h>
#include <io/io_err.h>
using namespace std::filesystem;
#if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
    // --getters
    data_sys::path data_sys::get_path() { return curr_path(); }
    data_sys::path data_sys::get_path(cstr file_path) { return curr_path() / file_path; }
    data_sys::path data_sys::get_path(cstr file_path, cstr file_name) { return curr_path() / file_path / file_name; }
    cstr data_sys::get_path_str() { return &curr_path().string()[0]; }
    cstr data_sys::get_path_str(cstr file_path) { return &(curr_path() / file_path).string()[0]; }
    cstr data_sys::get_path_str(cstr file_path, cstr file_name) { return &(curr_path() / file_path / file_name).string()[0]; }
    // --setters
    void data_sys::set_path_root(path root_path) {
        curr_path(root_path);
    }
    // --==<core_methods>==--
    void data_sys::on_init()
    {
        if (!get_path().has_over_path()) { throw init_error(__FILE__, __LINE__); return; }
        if (str_is_equal(str_part_right(&get_path().over_path().string()[0], NW_CHAR_DIR), NW_STR_LOC)) {}
        set_path_root(&curr_path().over_path().string()[0]);
        std::cout << "data_system has been initialized;" << std::endl;
        std::cout << "new root directory: " << get_path() << ";" << std::endl;
    }
    void data_sys::on_quit()
    {
        std::cout << "data_system has been quitted;" << std::endl;
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
    bit data_sys::load_file(cstr file_path, ptr buffer, size nof_bytes)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(buffer), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, dstr& buffer)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            buffer.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&buffer[0], buffer.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, a_data_rsc& resource) {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios_base::in | std::ios_base::binary);
            fstm >> resource;
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
    bit data_sys::save_file(cstr file_path, ptr buffer, size nof_bytes)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios::out | std::ios::binary);
            fstm.write(static_cast<sbyte*>(buffer), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, dstr& buffer)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios_base::out | std::ios_base::binary);
            fstm.write(&buffer[0], buffer.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, a_data_rsc& resource)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_path_str(file_path), std::ios_base::out | std::ios_base::binary);
            fstm << resource;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --==</core_methods>==--
}
#endif
#endif  // NW_WAPI