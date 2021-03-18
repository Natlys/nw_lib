#include <nwl_pch.hpp>
#include "data_sys.h"
#if (defined NW_OS)
#include <nwl_math.hpp>
#include <core/nwl_cln.h>
#include <core/nwl_str.h>
#include <io/io_stm.h>
#include <io/io_err.h>
using namespace std::filesystem;
NW::dstr NW::data_sys::s_root_path = "default";
NW::dstr NW::data_sys::s_temp_path = "default";
#if (NW_OS & NW_OS_WIN)
namespace NW
{
    // --getters
    cstr data_sys::get_path() {
        s_root_path = current_path().string();
        return &s_root_path[0];
    }
    cstr data_sys::get_path(cstr file_path) {
        s_temp_path = (current_path() / file_path).string();
        return &s_temp_path[0];
    }
    data_sys::paths data_sys::get_directory_paths(){
        paths result;
        auto dir = directory_iterator(current_path());
        for (auto& ipath : dir) {
            result.push_back(ipath.path().string());
        }
        return result;
    }
    // --setters
    void data_sys::set_dir_root(cstr root_directory) {
        if (!::SetCurrentDirectoryA(root_directory)) { throw a_error("failed to set new directory"); }
    }
    // --==<core_methods>==--
    void data_sys::on_init()
    {
        s_root_path.resize(256);
        set_dir_root(&current_path().parent_path().string()[0]);
        std::cout << "data_system has been initialized;" << std::endl;
        std::cout << "new root directory: " << get_path() << ";" << std::endl;
    }
    void data_sys::on_quit()
    {
        std::cout << "data_system has been quitted;" << std::endl;
        s_root_path = "default";
    }
    // --loading
    cstr data_sys::dialog_load(cstr filter, window_handle wnd)
    {
        constexpr si32 max_chars = 256;
        char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = max_chars;
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) { return &(s_temp_path = ofn.lpstrFile)[0]; }
        else { return ""; }
    }
    bit data_sys::load_file(cstr file_path, ptr data, size nof_bytes)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, dstr& data)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            data.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::load_file(cstr file_path, a_data_rsc& data) {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::in | std::ios_base::binary);
            fstm >> data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --saving
    cstr data_sys::dialog_save(cstr filter, window_handle wnd)
    {
        constexpr si32 max_chars = 256;
        char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = sizeof(str_res);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return &(s_temp_path = ofn.lpstrFile)[0]; }
        else { return ""; }
    }
    bit data_sys::save_file(cstr file_path, ptr data, size nof_bytes)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios::out | std::ios::binary);
            fstm.write(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, dstr& data)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::out | std::ios_base::binary);
            fstm.write(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bit data_sys::save_file(cstr file_path, a_data_rsc& data)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::out | std::ios_base::binary);
            fstm << data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --==</core_methods>==--
}
#endif
#endif  // NW_OS