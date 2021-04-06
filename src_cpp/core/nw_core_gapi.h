#ifndef NW_CORE_GAPI_H
#define NW_CORE_GAPI_H
#include "nw_lib_pch.hpp"
#if(defined NW_LIB_CORE_HPP & defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
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
// // faces_sides_directions
#		define NW_FACE_LFT     0x0406 // GL_LEFT 
#		define NW_FACE_RHT     0x0407 // GL_RIGHT
#		define NW_FACE_LFT_RHT 0x0001 // none
#		define NW_FACE_BOT     0x0003 // none
#		define NW_FACE_TOP     0x0002 // none
#		define NW_FACE_BOT_TOP 0x0004 // none
#		define NW_FACE_BCK     0x0405 // GL_BACK
#		define NW_FACE_FRT     0x0404 // GL_FRONT
#		define NW_FACE_BCK_FRT 0x0408 // GL_FRONT_AND_BACK 
#		define NW_FACE_BCK_LFT 0x0402 // GL_BACK_LEFT
#		define NW_FACE_BCK_RHT 0x0403 // GL_BACK_RIGHT
#		define NW_FACE_FRT_LFT 0x0400 // GL_FRONT_LEFT
#		define NW_FACE_FRT_RHT 0x0401 // GL_FRONT_RIGHT
// // operators
#		define NW_LOGIC_ALWAYS  0x0207 // GL_ALWAYS
#		define NW_LOGIC_NEVER   0x0200 // GL_NEVER
#		define NW_LOGIC_GRETR   0x0204 // GL_GREATER
#		define NW_LOGIC_LESSR   0x0201 // GL_LESS
#		define NW_LOGIC_EQUAL   0x0202 // GL_EQUAL
#		define NW_LOGIC_NEQUAL  0x0205 // GL_NEQUAL
#		define NW_LOGIC_GEQUAL  0x0206 // GL_GEQUAL
#		define NW_LOGIC_LEQUAL  0x0203 // GL_LEQUAL
#		define NW_LOGIC_AND     0x1501 // GL_AND
#		define NW_LOGIC_AND_REV 0x1502 // GL_AND_REVERSE
#		define NW_LOGIC_AND_INV 0x1504 // GL_AND_INVERTED
#		define NW_LOGIC_OR      0x1507 // GL_OR
#		define NW_LOGIC_OR_NOT  0x1508 // GL_NOR 
#		define NW_LOGIC_OR_EXC  0x1506 // GL_XOR
#		define NW_LOGIC_NO_OPER 0x1505 // GL_NOOP 
// // stencil testing
#		define NW_STENCIL_DECR 0x1E03 // GL_DECR
#		define NW_STENCIL_INCR 0x1E02 // GL_INCR
#		define NW_STENCIL_KEEP 0x1E00 // GL_KEEP
#		define NW_STENCIL_ZERO 0x0000 // GL_ZERO
#		define NW_STENCIL_REPL 0x1E01 // GL_REPLACE
#		define NW_STENCIL_INVT 0x0000 // GL_INVERT
// // color blending
#		define NW_BLEND_SRC_ALPHA		    0x0302 // GL_SRC_ALPHA
#		define NW_BLEND_DST_ALPHA		    0x0304 // GL_DST_ALPHA
#		define NW_BLEND_SRC_COLOR		    0x0300 // GL_SRC_COLOR
#		define NW_BLEND_DST_COLOR		    0x0306 // GL_DST_COLOR
#		define NW_BLEND_ONE_MINUS_SRC_ALPHA 0x0303 // GL_ONE_MINUS_SRC_ALPHA
#		define NW_BLEND_ONE_MUNUS_DST_ALPHA 0x0305 // GL_ONE_MUNUS_DST_ALPHA
#		define NW_BLEND_ONE_MINUS_SRC_COLOR 0x0301 // GL_ONE_MINUS_SRC_COLOR
#		define NW_BLEND_ONE_MINUS_DST_COLOR 0x0307 // GL_ONE_MINUS_DST_COLOR
// // face culling
#		define NW_CULL_CLOCK  0x0900 // GL_CW
#		define NW_CULL_COUNT  0x0901 // GL_CCW
// // geometry filling
#		define NW_FILL_LINE   0x1B01 // GL_LINE
#		define NW_FILL_FACE   0x1B02 // GL_FILL
// // primitives
#		define NW_PRIM_POINTS         0x0000 // GL_POINTS
#		define NW_PRIM_LINES          0x0001 // GL_LINES
#		define NW_PRIM_LINE_LOOP      0x0002 // GL_LINE_LOOP
#		define NW_PRIM_LINE_STRIP     0x0003 // GL_LINE_STRIP
#		define NW_PRIM_TRIANGLES      0x0004 // GL_TRIANGLES
#		define NW_PRIM_TRIANGLE_STRIP 0x0005 // GL_TRIANGLE_STRIP
#		define NW_PRIM_TRIANGLE_FAN   0x0006 // GL_TRIANGLE_FAN
// // texture wraps
#		define NW_WRAP_REPEAT  0x2901 // GL_REPEAT
#		define NW_WRAP_CLAMP   0x812F // GL_CLAMP_TO_EDGE
#		define NW_WRAP_BORDER  0x812D // GL_CLAMP_TO_BORDER
// // texture filters
#		define NW_FILTER_LINEAR  0x2601 // GL_LINEAR
#		define NW_FILTER_NEAREST 0x2600 // GL_NEAREST
// // texture formats
#		define NW_FMT_RGB   0x1907 // GL_RGB
#		define NW_FMT_RGBA  0x1908 // GL_RGBA
#		define NW_FMT_IDX   0x1903 // GL_RED
#		define NW_FMT_MONO  0x1903 // GL_RED
// // pixel formats
#		define NW_FMT_R8_S8        0x8231 // GL_R8I
#		define NW_FMT_R8_U8        0x8232 // GL_R8UI
#		define NW_FMT_R16_S16      0x8233 // GL_R16I
#		define NW_FMT_R16_U16      0x8234 // GL_R16UI
#		define NW_FMT_R32_S32      0x8235 // GL_R32I
#		define NW_FMT_R8G8_U16     0x8236 // GL_RG8UI
#		define NW_FMT_R8G8_S16     0x8237 // GL_RG8I
#		define NW_FMT_R16G16_S32   0x0000 // none
#		define NW_FMT_R8G8B8_S32   0x0001 // none
#		define NW_FMT_R8G8B8A8_S32 0x0002 // none
#		define NW_FMT_R32_U32      0x8236 // GL_R32UI
#		define NW_FMT_R16G16_U32   0x0003 // none
#		define NW_FMT_R8G8B8_U32   0x0004 // none
#		define NW_FMT_R8G8B8A8_U32 0x0005 // none
#		define NW_FMT_S8_S8        0x0006 // none
#		define NW_FMT_D32_S32      0x0007 // none
#		define NW_FMT_S8_U8        0x0008 // none
#		define NW_FMT_D32_U32      0x84FA // GL_UNSIGNED_INT_24_8
#		define NW_FMT_D24S8_S32    0x84FA // GL_UNSIGNED_INT_24_8
#		define NW_FMT_D24S8_U32    0x84FA // GL_UNSIGNED_INT_24_8
#	endif	// GAPI_OGL
#	if(NW_GAPI & NW_GAPI_D3D)
#	endif	// GAPI_D3D
#	if (NW_GAPI & NW_GAPI_D3D)
// // types
#		if (defined device_handle)
#			undef device_handle
#		endif
#		define device_handle    ID3D11Device*
#		if (defined device_handle)
#			undef context_handle
#		endif
#		define context_handle   ID3D11DeviceContext*
#	endif	// GAPI_D3D
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP & NW_GAPI
#endif	// NW_CORE_GAPI_H