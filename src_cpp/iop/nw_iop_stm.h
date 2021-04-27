#ifndef NW_IOP_STREAM_H
#define NW_IOP_STREAM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	// byte streams
	typedef std::basic_istream<byte_t>   ip_stream_t;
	typedef const ip_stream_t           ip_stream_tc;
	typedef std::basic_ostream<byte_t>   op_stream_t;
	typedef const op_stream_t           op_stream_tc;
	typedef std::basic_iostream<byte_t> iop_stream_t;
	typedef const iop_stream_t         iop_stream_tc;
	// file streams
	typedef std::basic_ifstream<byte_t>  ip_fstream_t;
	typedef const ip_fstream_t          ip_fstream_tc;
	typedef std::basic_ofstream<byte_t>  op_fstream_t;
	typedef const op_fstream_t          op_fstream_tc;
	typedef std::basic_fstream<byte_t>  iop_fstream_t;
	typedef const iop_fstream_t         iop_fstream_tc;
}
#endif	// NW_API
#endif	// NW_IOP_STREAM_H
