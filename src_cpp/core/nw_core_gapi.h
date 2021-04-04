#ifndef NW_CORE_GAPI_H
#define NW_CORE_GAPI_H

#if(defined NW_LIB_CORE_HPP & defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
// // types
#		define GLboolean bool
#		define GLbyte    signed char
#		define GLubyte   unsigned char
#		define GLshort   signed short
#		define GLushort  unsigned short
#		define GLint     signed int
#		define GLuint    unsigned int
#		define GLfloat   float
#		define GLdouble  double
#		define GLenum    unsigned int
#		define GLvoid    void
// // native_types
#		define NW_V1_B     GL_BOOL
#		define NW_V2_B     GL_BOOL
#		define NW_V3_B     GL_BOOL
#		define NW_V4_B     GL_BOOL
// // signed int 8 bit
#		define NW_V1_S8    GL_BYTE
#		define NW_V2_S8    GL_BYTE
#		define NW_V3_S8    GL_BYTE
#		define NW_V4_S8    GL_BYTE
// // unsigned int 8 bit
#		define NW_V1_U8    GL_UNSIGNED_BYTE
#		define NW_V2_U8    GL_UNSIGNED_BYTE
#		define NW_V3_U8    GL_UNSIGNED_BYTE
#		define NW_V4_U8    GL_UNSIGNED_BYTE
// // signed int 16 bit
#		define NW_V1_S16   GL_SHORT
#		define NW_V2_S16   GL_SHORT
#		define NW_V3_S16   GL_SHORT
#		define NW_V4_S16   GL_SHORT
// // unsigned int 16 bit
#		define NW_V1_U16   GL_UNSIGNED_SHORT
#		define NW_V2_U16   GL_UNSIGNED_SHORT
#		define NW_V3_U16   GL_UNSIGNED_SHORT
#		define NW_V4_U16   GL_UNSIGNED_SHORT
// // signed int 32 bit
#		define NW_V1_S32   GL_INT
#		define NW_V2_S32   GL_INT
#		define NW_V3_S32   GL_INT
#		define NW_V4_S32   GL_INT
// // unsigned int 32 bit
#		define NW_V1_U32   GL_UNSIGNED_INT
#		define NW_V2_U32   GL_UNSIGNED_INT
#		define NW_V3_U32   GL_UNSIGNED_INT
#		define NW_V4_U32   GL_UNSIGNED_INT
// // signed int 64 bit
#		define NW_V1_S64   GL_LONG
#		define NW_V2_S64   GL_LONG
#		define NW_V3_S64   GL_LONG
#		define NW_V4_S64   GL_LONG
// // unsigned int 64 bit
#		define NW_V1_U64   GL_UNSIGNED_LONG
#		define NW_V2_U64   GL_UNSIGNED_LONG
#		define NW_V3_U64   GL_UNSIGNED_LONG
#		define NW_V4_U64   GL_UNSIGNED_LONG
// // float 32 bit
#		define NW_V1_F32   GL_FLOAT
#		define NW_V2_F32   GL_FLOAT
#		define NW_V3_F32   GL_FLOAT
#		define NW_V4_F32   GL_FLOAT
// // float 64 bit
#		define NW_V1_F64   GL_DOUBLE
#		define NW_V2_F64   GL_DOUBLE
#		define NW_V3_F64   GL_DOUBLE
#		define NW_V4_F64   GL_DOUBLE
// // constants
#		define NW_ZERO     GL_ZERO
#		define NW_ONE      GL_ONE
#		define NW_FALSE    GL_FALSE
#		define NW_TRUE     GL_TRUE
// // faces_sides_directions
#		define NW_LEFT             GL_LEFT
#		define NW_RIGTH            GL_RIGHT
#		define NW_LEFT_AND_RIGHT   GL_LEFT_AND_RIGHT
#		define NW_TOP              GL_TOP
#		define NW_BOT              GL_BOTTOM
#		define NW_BOT_AND_TOP      GL_TOP_AND_BOTTOM
#		define NW_BACK             GL_BACK
#		define NW_FRONT            GL_FRONT
#		define NW_BACK_AND_FRONT   GL_BACK_AND_FRONT
// // operators
#		define NW_ALWAYS     GL_ALWAYS
#		define NW_NEVER      GL_NEVER
#		define NW_EQUAL      GL_EQUAL
#		define NW_GREATER    GL_GREATER
#		define NW_LESSER     GL_LESS
#		define NW_GEQUAL     GL_GEQUAL
#		define NW_LEQUAL     GL_LEQUAL
// // stencil testing
#		define NW_STENCIL_INCR
#		define NW_STENCIL_DECR
#		define NW_STENCIL_KEEP
#		define NW_STENCIL_ZERO
#		define NW_STENCIL_REPL
#		define NW_STENCIL_INVERT
// // color blending
#		define NW_BLEND_SRC_ALPHA		    GL_BLEND_SRC_ALPHA
#		define NW_BLEND_DST_ALPHA		    GL_BLEND_DST_ALPHA
#		define NW_BLEND_SRC_COLOR		    GL_BLEND_SRC_COLOR
#		define NW_BLEND_DST_COLOR		    GL_BLEND_DST_COLOR
#		define NW_BLEND_ONE_MINUS_SRC_ALPHA GL_BLEND_ONE_MINUS_SRC_ALPHA
#		define NW_BLEND_ONE_MUNUS_DST_ALPHA GL_BLEND_ONE_MUNUS_DST_ALPHA
#		define NW_BLEND_ONE_MINUS_SRC_COLOR GL_BLEND_ONE_MINUS_SRC_COLOR
#		define NW_BLEND_ONE_MINUS_DST_COLOR GL_BLEND_ONE_MINUS_DST_COLOR
// // face culling
#		define NW_CULL_CLOCK
#		define NW_CULL_COUNTER
// // geometry filling
#		define NW_FILL_FACE
#		define NW_FILL_LINE
// // primitives
#		define NW_PRIM_POINTS         GL_POINTS
#		define NW_PRIM_LINES          GL_LINES
#		define NW_PRIM_LINE_LOOP      GL_LINE_LOOP
#		define NW_PRIM_LINE_STRIP     GL_LINE_STRIP
#		define NW_PRIM_TRIANGLES      GL_TRIANGLES
#		define NW_PRIM_TRIANGLE_FAN   GL_TRIANGLE_FAN
#		define NW_PRIM_TRIANGLE_STRIP GL_TRIANGLE_STRIP
// // texture wraps
#		define NW_WRAP_REPEAT  GL_REPEAT
#		define NW_WRAP_CLAMP   GL_CLAMP_TO_EDGE
#		define NW_WRAP_BORDER  GL_CLAMP_TO_BORDER
// // texture filters
#		define NW_FILTER_LINEAR  GL_LINEAR
#		define NW_FILTER_NEAREST GL_NEAREST
// // texture formats
// // pixel formats
#		define NW_FMT_R8_S8
#		define NW_FMT_R8_U8
#		define NW_FMT_R16_S16
#		define NW_FMT_R8G8_S16
#		define NW_FMT_R16_U16
#		define NW_FMT_R8G8_U16
#		define NW_FMT_R32_S32
#		define NW_FMT_R16G16_S32
#		define NW_FMT_R8G8B8_S32
#		define NW_FMT_R8G8B8A8_S32
#		define NW_FMT_R32_U32
#		define NW_FMT_R16G16_U32
#		define NW_FMT_R8G8B8_U32
#		define NW_FMT_R8G8B8A8_U32
#		define NW_FMT_S8_S8
#		define NW_FMT_D32_S32
#		define NW_FMT_S8_U8
#		define NW_FMT_D32_U32
#		define NW_FMT_D24S8_S32
#		define NW_FMT_D24S8_U32
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