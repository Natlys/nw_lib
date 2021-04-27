#include "nw_lib_pch.hpp"
#include "nw_iop_sys.h"
#if (defined NW_WAPI)
#   include "../std/nw_std_err.h"
    #if (NW_WAPI & NW_WAPI_WIN)
namespace NW
{
    iop_sys::iop_sys() :
        m_iput(NW_NULL),
        m_oput(NW_NULL),
        m_path(NW_DEFAULT_STR)
    {
    }
	iop_sys::~iop_sys()
	{
        NW_CHECK(!has_path() && !has_iput() && !has_oput(), "no quit!", return);
	}
    v1bit iop_sys::init()
    {
        NW_CHECK(!has_path() && !has_iput() && !has_oput(), "init is already done!", return NW_FALSE);

        m_iput = new iput_t();
        m_oput = &std::cout;

        set_path(flib::current_path());
        NW_CHECK(m_path.has_parent_path(), "cannot be a drive directory!", return NW_FALSE);
        NW_CHECK(get_path().parent_path().filename() == NW_NAME_STR, "must be the project name!", return NW_FALSE);
        set_path(&get_path().get_over().get_full()[0]);

        get_oput() << "nw_iop_system has been initialized;" << std::endl;
        get_oput() << "root path: " << get_path() << ";" << std::endl;
        
        return NW_TRUE;
    }
    v1bit iop_sys::quit()
    {
        NW_CHECK(has_path() && has_iput() && has_oput(), "quit is already done!", return NW_FALSE);

		delete m_iput;
		set_input(NW_NULL);
		set_output(NW_NULL);
        set_path(NW_DEFAULT_STR);
        
        return NW_TRUE;
    }
	// --setters
    v1nil iop_sys::set_input(iput_t* in) {
        m_iput = in;
    }
    v1nil iop_sys::set_output(oput_t* out) {
		m_oput = out;
	}
    v1nil iop_sys::set_path(path_tc& path) {
        if (is_fdir(&path.get_full()[0])) { flib::current_path(path); }
        m_path = path;
    }
	// --==<core_methods>==--
	v1nil iop_sys::update()
	{
		get_oput() << get_iput().str();
		get_iput().str("");
	}
	// --==</core_methods>==--

    // --==<directories>==--
    v1nil iop_sys::new_fdir(cstr_t fpath)
    {
        NW_CHECK(!is_fdir(fpath), "such folder does exist!", return);
        
        SECURITY_ATTRIBUTES scr_atbs{ 0 };
        ::CreateDirectory(fpath, &scr_atbs);
    }
    v1nil iop_sys::del_fdir(cstr_t fpath)
    {
        NW_CHECK(is_fdir(fpath), "such folder does not exist!", return);
        
        ::RemoveDirectory(fpath);
    }
	// --==</directories>==--

	// --==<files>==--
    v1nil iop_sys::new_file(cstr_t fpath)
    {
        NW_CHECK(!is_file(fpath), "such file does exist!", return);

        SECURITY_ATTRIBUTES scr_atbs{ 0 };
        //::CreateFile(fpath, &scr_atbs);
    }
    v1nil iop_sys::del_file(cstr_t fpath)
    {
        NW_CHECK(is_file(fpath), "such file does not exist!", return);

        ::DeleteFile(fpath);
    }
    cstr_t iop_sys::load_dialog(cstr_t filter, window_handle wnd)
    {
        static char_t str_res[NW_MAX_PATH]{ NW_NULL };
        OPENFILENAMEA ofn{ NW_NULL };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = sizeof(str_res);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (::GetOpenFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
    }
    v1bit iop_sys::load_file(cstr_t fpath, ptr_t data, size_t size)
    {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        ip_fstream_t stm;
        stm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            stm.open(full, std::ios::in | std::ios::binary);
            stm.read(static_cast<byte_t*>(data), size);
            stm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    v1bit iop_sys::load_file(cstr_t fpath, dstr_t& data)
    {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        ip_fstream_t stm;
        stm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            stm.open(full, std::ios_base::in | std::ios_base::binary);
            stm.seekg(0, stm.end);
            data.resize(stm.tellg());
            stm.seekg(0, stm.beg);
            stm.read(&data[0], data.size());
            stm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    v1bit iop_sys::load_file(cstr_t fpath, a_ip_cmp& data) {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        ip_fstream_t stm;
        stm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            stm.open(full, std::ios_base::in | std::ios_base::binary);
            stm >> data;
            stm.close();
        }
        catch (std::ios_base::failure exc) { throw load_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    cstr_t iop_sys::save_dialog(cstr_t filter, window_handle wnd)
    {
        static char_t str_res[NW_MAX_PATH]{ NW_NULL };
        OPENFILENAMEA ofn{ NW_NULL };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = sizeof(str_res);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
    }
    v1bit iop_sys::save_file(cstr_t fpath, ptr_tc data, size_t size)
    {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        //NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        op_fstream_t stm;
        stm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            stm.open(full, std::ios::out | std::ios::binary);
            stm.write(static_cast<byte_tc*>(data), size);
            stm.close();
        }
        catch (std::ios_base::failure ex) { throw save_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    v1bit iop_sys::save_file(cstr_t fpath, dstr_tc& data)
    {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        //NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        op_fstream_t stm;
        stm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            stm.open(full , std::ios_base::out | std::ios_base::binary);
            stm.write(&data[0], data.size());
            stm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    v1bit iop_sys::save_file(cstr_t fpath, a_op_cmp& data)
    {
        dstr_t full = (m_path.get_full() + "\\" + fpath);
        //NW_CHECK(is_file(&full[0]), "fpath must be a relaitve name of a file!", return NW_FALSE);
        op_fstream_t stm;
        stm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            stm.open(full, std::ios_base::out | std::ios_base::binary);
            stm << data;
            stm.close();
        }
        catch (std::ios_base::failure exc) { throw save_error(__FILE__, __LINE__); return NW_FALSE; }
        return NW_TRUE;
    }
    // --==</files>==--

	// --==<logging>==--
	v1nil iop_sys::write_info(cstr_t format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_iput() <<
			"--==<log_information>==--" << std::endl <<
			"::message:" << format << std::endl <<
			"--==</log_information>==--" << std::endl;
		va_end(arguments);
	}
	v1nil iop_sys::write_warn(cstr_t format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_iput() <<
			"--==<log_warning>==--" << std::endl <<
			"::message:" << format << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(arguments);
        NW_BREAK;
	}
	v1nil iop_sys::write_error(cv1u err_code, cstr_t format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		get_iput() <<
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