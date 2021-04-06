#include "nw_lib_pch.hpp"
#include "nw_io_sys.h"
#if (defined NW_WAPI)
    #if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
	io_sys::io_sys() :
		m_input(nullptr),
        m_path_curr(flib::current_path())
	{
		if (m_input != nullptr) { return; }
		m_input = new input();
		m_output = &std::cout;
        
        if (!get_fpath().has_parent_path()) { throw init_error(__FILE__, __LINE__); return; }
        if (get_fpath().parent_path().filename() != NW_NAME) { throw init_error(__FILE__, __LINE__); return; }
        set_path_curr(&get_fpath().get_over().get_full()[0]);

        std::cout << "nw_io_system has been initialized;" << std::endl;
        std::cout << "current_path: " << get_fpath() << ";" << std::endl;
    }
	io_sys::~io_sys()
	{
		if (m_input == nullptr) { return; }
		delete m_input;
		m_input = nullptr;
		m_output = nullptr;
	}
	// --setters
	void io_sys::set_output(output& stm) {
		m_output = &stm;
	}
    void io_sys::set_path_curr(cstr cpath) {
        flib::current_path(cpath);
        m_path_curr = flib::current_path();
    }
	// --==<core_methods>==--
	void io_sys::update()
	{
		get_output() << get_input().str();
		get_input().str("");
	}
	// --==</core_methods>==--

    // --==<directories>==--
    void io_sys::new_drct(cstr dpath)
    {
        if (!is_drct_path(dpath)) { return; }
        SECURITY_ATTRIBUTES scr_atbs{ 0 };
        ::CreateDirectory(dpath, &scr_atbs);
    }
    void io_sys::del_drct(cstr dpath)
    {
        if (!is_drct_path(dpath)) { return; }
        ::RemoveDirectory(dpath);
    }
	// --==</directories>==--

	// --==<file_loading>==--
    cstr io_sys::load_dlg(cstr filter, window_handle wnd)
    {
        static constexpr size max_chars = 256;
        static char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = max_chars;
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (::GetOpenFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
    }
    bool io_sys::load_file(cstr file_path, ptr destination, size nof_bytes)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(destination), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bool io_sys::load_file(cstr file_path, dstr& destination)
    {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            destination.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&destination[0], destination.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bool io_sys::load_file(cstr file_path, cmp& destination) {
        stm_in_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios_base::in | std::ios_base::binary);
            fstm >> destination;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return false; }
        return true;
    }
	// --==</file_loading>==--
	
	// --==<file_saving>==--
    cstr io_sys::save_dlg(cstr filter, window_handle wnd)
    {
        static constexpr size max_chars = 256;
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
    bool io_sys::save_file(cstr file_path, cptr source, size nof_bytes)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios::out | std::ios::binary);
            fstm.write(static_cast<const sbyte*>(source), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bool io_sys::save_file(cstr file_path, cdstr& source)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios_base::out | std::ios_base::binary);
            fstm.write(&source[0], source.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    bool io_sys::save_file(cstr file_path, ccmp& source)
    {
        stm_out_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(get_fpath(file_path), std::ios_base::out | std::ios_base::binary);
            fstm << source;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return false; }
        return true;
    }
    // --==</file_saving>==--

	// --==<logging>==--
	void io_sys::write_info(cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_information>==--" << std::endl <<
			"::message:" << format << std::endl <<
			"--==</log_information>==--" << std::endl;
		va_end(arguments);
	}
	void io_sys::write_warn(cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_warning>==--" << std::endl <<
			"::message:" << format << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(arguments);
        NW_BREAK;
	}
	void io_sys::write_error(error_codes err_code, cstr format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_input() <<
			"--==<log_error>==--" << std::endl <<
			"code:" << err_code << std::endl <<
			"::message:" << format << std::endl <<
			"--==</log_error>==--" << std::endl;
		va_end(arguments);
		NW_BREAK;
	}
	// --==</logging>==--
}
#   endif  // WAPI_WIN
#endif  // NW_WAPI