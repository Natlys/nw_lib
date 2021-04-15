#ifndef NW_CORE_GAPI_H
#define NW_CORE_GAPI_H
#include "nw_lib_pch.hpp"
#if(defined NW_LIB_CORE_HPP & defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
// // types
#		define device_handle    wapi_device_handle
#		define context_handle   wapi_context_handle
namespace NW
{
	typedef signed char    GLbyte;
	typedef char           GLchar;
	typedef short          GLshort;
	typedef int            GLint;
	typedef int            GLsizei;
	typedef unsigned char  GLboolean;
	typedef unsigned char  GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned short GLhalf;
	typedef unsigned int   GLenum;
	typedef unsigned int   GLuint;
	typedef unsigned int   GLbitfield;
	typedef float          GLfloat;
	typedef float          GLclampf;
	typedef double         GLdouble;
	typedef double         GLclampd;
	typedef void           GLvoid;
	typedef ptrdiff_t      GLintptr;
	typedef ptrdiff_t      GLsizeiptr;
}
#	endif	// GAPI_OGL
#	if(NW_GAPI & NW_GAPI_D3D)
#	endif	// GAPI_D3D
#	if (NW_GAPI & NW_GAPI_D3D)
// // types
#		define device_handle    ID3D11Device*
#		define context_handle   ID3D11DeviceContext*
#	endif	// GAPI_D3D
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP & NW_GAPI
#endif	// NW_CORE_GAPI_H