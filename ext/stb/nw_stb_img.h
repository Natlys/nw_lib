#ifndef NW_STB_IMAGE_H
#define NW_STB_IMAGE_H
#if (1)
#   if (1)
#ifndef STBI_NO_STDIO
#include "stdio.h"
#endif // STBI_NO_STDIO

#define STBI_VERSION 1

enum
{
    STBI_default = 0, // only used for desired_channels

    STBI_grey = 1,
    STBI_grey_alpha = 2,
    STBI_rgb = 3,
    STBI_rgb_alpha = 4
};

#include "stdlib.h"
typedef unsigned char stbi_uc;
typedef unsigned short stbi_us;

#ifdef __cplusplus
extern "C" {
#endif

#define STBIDEF extern

    typedef struct
    {
        int      (*read)  (void* user, char* data, int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
        void     (*skip)  (void* user, int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
        int      (*eof)   (void* user);                       // returns nonzero if we are at end of file/data
    } stbi_io_callbacks;

    ////////////////////////////////////
    //
    // 8-bits-per-channel interface
    //

    STBIDEF stbi_uc* stbi_load_from_memory(stbi_uc           const* buffer, int len, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF stbi_uc* stbi_load_from_callbacks(stbi_io_callbacks const* clbk, void* user, int* x, int* y, int* channels_in_file, int desired_channels);

#ifndef STBI_NO_STDIO
    STBIDEF stbi_uc* stbi_load(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF stbi_uc* stbi_load_from_file(FILE* f, int* x, int* y, int* channels_in_file, int desired_channels);
    // for stbi_load_from_file, file pointer is left pointing immediately after image
#endif

#ifndef STBI_NO_GIF
    STBIDEF stbi_uc* stbi_load_gif_from_memory(stbi_uc const* buffer, int len, int** delays, int* x, int* y, int* z, int* comp, int req_comp);
#endif

#ifdef STBI_WINDOWS_UTF8
    STBIDEF int stbi_convert_wchar_to_utf8(char* buffer, size_t bufferlen, const wchar_t* input);
#endif

    ////////////////////////////////////
    //
    // 16-bits-per-channel interface
    //

    STBIDEF stbi_us* stbi_load_16_from_memory(stbi_uc const* buffer, int len, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF stbi_us* stbi_load_16_from_callbacks(stbi_io_callbacks const* clbk, void* user, int* x, int* y, int* channels_in_file, int desired_channels);

#ifndef STBI_NO_STDIO
    STBIDEF stbi_us* stbi_load_16(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF stbi_us* stbi_load_from_file_16(FILE* f, int* x, int* y, int* channels_in_file, int desired_channels);
#endif

    ////////////////////////////////////
    //
    // float-per-channel interface
    //
#ifndef STBI_NO_LINEAR
    STBIDEF float* stbi_loadf_from_memory(stbi_uc const* buffer, int len, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF float* stbi_loadf_from_callbacks(stbi_io_callbacks const* clbk, void* user, int* x, int* y, int* channels_in_file, int desired_channels);

#ifndef STBI_NO_STDIO
    STBIDEF float* stbi_loadf(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels);
    STBIDEF float* stbi_loadf_from_file(FILE* f, int* x, int* y, int* channels_in_file, int desired_channels);
#endif
#endif

#ifndef STBI_NO_HDR
    STBIDEF void   stbi_hdr_to_ldr_gamma(float gamma);
    STBIDEF void   stbi_hdr_to_ldr_scale(float scale);
#endif // STBI_NO_HDR

#ifndef STBI_NO_LINEAR
    STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma);
    STBIDEF void   stbi_ldr_to_hdr_scale(float scale);
#endif // STBI_NO_LINEAR

    // stbi_is_hdr is always defined, but always returns false if STBI_NO_HDR
    STBIDEF int    stbi_is_hdr_from_callbacks(stbi_io_callbacks const* clbk, void* user);
    STBIDEF int    stbi_is_hdr_from_memory(stbi_uc const* buffer, int len);
#ifndef STBI_NO_STDIO
    STBIDEF int      stbi_is_hdr(char const* filename);
    STBIDEF int      stbi_is_hdr_from_file(FILE* f);
#endif // STBI_NO_STDIO


    // get a VERY brief reason for failure
    // on most compilers (and ALL modern mainstream compilers) this is threadsafe
    STBIDEF const char* stbi_failure_reason(void);

    // free the loaded image -- this is just free()
    STBIDEF void     stbi_image_free(void* retval_from_stbi_load);

    // get image dimensions & components without fully decoding
    STBIDEF int      stbi_info_from_memory(stbi_uc const* buffer, int len, int* x, int* y, int* comp);
    STBIDEF int      stbi_info_from_callbacks(stbi_io_callbacks const* clbk, void* user, int* x, int* y, int* comp);
    STBIDEF int      stbi_is_16_bit_from_memory(stbi_uc const* buffer, int len);
    STBIDEF int      stbi_is_16_bit_from_callbacks(stbi_io_callbacks const* clbk, void* user);

#ifndef STBI_NO_STDIO
    STBIDEF int      stbi_info(char const* filename, int* x, int* y, int* comp);
    STBIDEF int      stbi_info_from_file(FILE* f, int* x, int* y, int* comp);
    STBIDEF int      stbi_is_16_bit(char const* filename);
    STBIDEF int      stbi_is_16_bit_from_file(FILE* f);
#endif



    // for image formats that explicitly notate that they have premultiplied alpha,
    // we just return the colors as stored in the file. set this flag to force
    // unpremultiplication. results are undefined if the unpremultiply overflow.
    STBIDEF void stbi_set_unpremultiply_on_load(int flag_true_if_should_unpremultiply);

    // indicate whether we should process iphone images back to canonical format,
    // or just pass them through "as-is"
    STBIDEF void stbi_convert_iphone_png_to_rgb(int flag_true_if_should_convert);

    // flip the image vertically, so the first pixel in the output array is the bottom left
    STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);

    // as above, but only applies to images loaded on the thread that calls the function
    // this function is only available if your compiler supports thread-local variables;
    // calling it will fail to link if your compiler doesn't
    STBIDEF void stbi_set_flip_vertically_on_load_thread(int flag_true_if_should_flip);

    // ZLIB client - used by PNG, available for other purposes

    STBIDEF char* stbi_zlib_decode_malloc_guesssize(const char* buffer, int len, int initial_size, int* outlen);
    STBIDEF char* stbi_zlib_decode_malloc_guesssize_headerflag(const char* buffer, int len, int initial_size, int* outlen, int parse_header);
    STBIDEF char* stbi_zlib_decode_malloc(const char* buffer, int len, int* outlen);
    STBIDEF int   stbi_zlib_decode_buffer(char* obuffer, int olen, const char* ibuffer, int ilen);

    STBIDEF char* stbi_zlib_decode_noheader_malloc(const char* buffer, int len, int* outlen);
    STBIDEF int   stbi_zlib_decode_noheader_buffer(char* obuffer, int olen, const char* ibuffer, int ilen);


#ifdef __cplusplus
}
#endif
/* stb_image_write - v1.15 - public domain - http://nothings.org/stb
   writes out PNG/BMP/TGA/JPEG/HDR images to C stdio - Sean Barrett 2010-2015
                                     no warranty implied; use at your own risk

   Before #including,

       #define STB_IMAGE_WRITE_IMPLEMENTATION

   in the file that you want to have the implementation.

   Will probably not work correctly with strict-aliasing optimizations.

ABOUT:

   This header file is a library for writing images to C stdio or a callback.

   The PNG output is not optimal; it is 20-50% larger than the file
   written by a decent optimizing implementation; though providing a custom
   zlib compress function (see STBIW_ZLIB_COMPRESS) can mitigate that.
   This library is designed for source code compactness and simplicity,
   not optimal image file size or run-time performance.

BUILDING:

   You can #define STBIW_ASSERT(x) before the #include to avoid using assert.h.
   You can #define STBIW_MALLOC(), STBIW_REALLOC(), and STBIW_FREE() to replace
   malloc,realloc,free.
   You can #define STBIW_MEMMOVE() to replace memmove()
   You can #define STBIW_ZLIB_COMPRESS to use a custom zlib-style compress function
   for PNG compression (instead of the builtin one), it must have the following signature:
   unsigned char * my_compress(unsigned char *data, int data_len, int *out_len, int quality);
   The returned data will be freed with STBIW_FREE() (free() by default),
   so it must be heap allocated with STBIW_MALLOC() (malloc() by default),

UNICODE:

   If compiling for Windows and you wish to use Unicode filenames, compile
   with
       #define STBIW_WINDOWS_UTF8
   and pass utf8-encoded filenames. Call stbiw_convert_wchar_to_utf8 to convert
   Windows wchar_t filenames to utf8.

USAGE:

   There are five functions, one for each image file format:

     int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
     int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
     int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
     int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
     int stbi_write_hdr(char const *filename, int w, int h, int comp, const float *data);

     void stbi_flip_vertically_on_write(int flag); // flag is non-zero to flip data vertically

   There are also five equivalent functions that use an arbitrary write function. You are
   expected to open/close your file-equivalent before and after calling these:

     int stbi_write_png_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void  *data, int stride_in_bytes);
     int stbi_write_bmp_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void  *data);
     int stbi_write_tga_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void  *data);
     int stbi_write_hdr_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const float *data);
     int stbi_write_jpg_to_func(stbi_write_func *func, void *context, int x, int y, int comp, const void *data, int quality);

   where the callback is:
      void stbi_write_func(void *context, void *data, int size);

   You can configure it with these global variables:
      int stbi_write_tga_with_rle;             // defaults to true; set to 0 to disable RLE
      int stbi_write_png_compression_level;    // defaults to 8; set to higher for more compression
      int stbi_write_force_png_filter;         // defaults to -1; set to 0..5 to force a filter mode


   You can define STBI_WRITE_NO_STDIO to disable the file variant of these
   functions, so the library will not use stdio.h at all. However, this will
   also disable HDR writing, because it requires stdio for formatted output.

   Each function returns 0 on failure and non-0 on success.

   The functions create an image file defined by the parameters. The image
   is a rectangle of pixels stored from left-to-right, top-to-bottom.
   Each pixel contains 'comp' channels of data stored interleaved with 8-bits
   per channel, in the following order: 1=Y, 2=YA, 3=RGB, 4=RGBA. (Y is
   monochrome color.) The rectangle is 'w' pixels wide and 'h' pixels tall.
   The *data pointer points to the first byte of the top-left-most pixel.
   For PNG, "stride_in_bytes" is the distance in bytes from the first byte of
   a row of pixels to the first byte of the next row of pixels.

   PNG creates output files with the same number of components as the input.
   The BMP format expands Y to RGB in the file format and does not
   output alpha.

   PNG supports writing rectangles of data even when the bytes storing rows of
   data are not consecutive in memory (e.g. sub-rectangles of a larger image),
   by supplying the stride between the beginning of adjacent rows. The other
   formats do not. (Thus you cannot write a native-format BMP through the BMP
   writer, both because it is in BGR order and because it may have padding
   at the end of the line.)

   PNG allows you to set the deflate compression level by setting the global
   variable 'stbi_write_png_compression_level' (it defaults to 8).

   HDR expects linear float data. Since the format is always 32-bit rgb(e)
   data, alpha (if provided) is discarded, and for monochrome data it is
   replicated across all three channels.

   TGA supports RLE or non-RLE compressed data. To use non-RLE-compressed
   data, set the global variable 'stbi_write_tga_with_rle' to 0.

   JPEG does ignore alpha channels in input data; quality is between 1 and 100.
   Higher quality looks better but results in a bigger image.
   JPEG baseline (no JPEG progressive).

CREDITS:


   Sean Barrett           -    PNG/BMP/TGA
   Baldur Karlsson        -    HDR
   Jean-Sebastien Guay    -    TGA monochrome
   Tim Kelsey             -    misc enhancements
   Alan Hickman           -    TGA RLE
   Emmanuel Julien        -    initial file IO callback implementation
   Jon Olick              -    original jo_jpeg.cpp code
   Daniel Gibson          -    integrate JPEG, allow external zlib
   Aarni Koskela          -    allow choosing PNG filter

   bugfixes:
      github:Chribba
      Guillaume Chereau
      github:jry2
      github:romigrou
      Sergio Gonzalez
      Jonas Karlsson
      Filip Wasil
      Thatcher Ulrich
      github:poppolopoppo
      Patrick Boettcher
      github:xeekworx
      Cap Petschulat
      Simon Rodriguez
      Ivan Tikhonov
      github:ignotion
      Adam Schackart

LICENSE

  See end of file for license information.

*/
#   endif
#include <stdlib.h>
#   if (1)
// if STB_IMAGE_WRITE_STATIC causes problems, try defining STBIWDEF to 'inline' or 'static inline'
#ifndef STBIWDEF
#ifdef STB_IMAGE_WRITE_STATIC
#define STBIWDEF  static
#else
#ifdef __cplusplus
#define STBIWDEF  extern "C"
#else
#define STBIWDEF  extern
#endif
#endif
#endif

#ifndef STB_IMAGE_WRITE_STATIC  // C++ forbids static forward declarations
extern int stbi_write_tga_with_rle;
extern int stbi_write_png_compression_level;
extern int stbi_write_force_png_filter;
#endif

#ifndef STBI_WRITE_NO_STDIO
STBIWDEF int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
STBIWDEF int stbi_write_bmp(char const* filename, int w, int h, int comp, const void* data);
STBIWDEF int stbi_write_tga(char const* filename, int w, int h, int comp, const void* data);
STBIWDEF int stbi_write_hdr(char const* filename, int w, int h, int comp, const float* data);
STBIWDEF int stbi_write_jpg(char const* filename, int x, int y, int comp, const void* data, int quality);

#ifdef STBI_WINDOWS_UTF8
STBIWDEF int stbiw_convert_wchar_to_utf8(char* buffer, size_t bufferlen, const wchar_t* input);
#endif
#endif

typedef void stbi_write_func(void* context, void* data, int size);

STBIWDEF int stbi_write_png_to_func(stbi_write_func* func, void* context, int w, int h, int comp, const void* data, int stride_in_bytes);
STBIWDEF int stbi_write_bmp_to_func(stbi_write_func* func, void* context, int w, int h, int comp, const void* data);
STBIWDEF int stbi_write_tga_to_func(stbi_write_func* func, void* context, int w, int h, int comp, const void* data);
STBIWDEF int stbi_write_hdr_to_func(stbi_write_func* func, void* context, int w, int h, int comp, const float* data);
STBIWDEF int stbi_write_jpg_to_func(stbi_write_func* func, void* context, int x, int y, int comp, const void* data, int quality);

STBIWDEF void stbi_flip_vertically_on_write(int flip_boolean);

/* Revision history
      1.14  (2020-02-02) updated JPEG writer to downsample chroma channels
      1.13
      1.12
      1.11  (2019-08-11)

      1.10  (2019-02-07)
             support utf8 filenames in Windows; fix warnings and platform ifdefs
      1.09  (2018-02-11)
             fix typo in zlib quality API, improve STB_I_W_STATIC in C++
      1.08  (2018-01-29)
             add stbi__flip_vertically_on_write, external zlib, zlib quality, choose PNG filter
      1.07  (2017-07-24)
             doc fix
      1.06 (2017-07-23)
             writing JPEG (using Jon Olick's code)
      1.05   ???
      1.04 (2017-03-03)
             monochrome BMP expansion
      1.03   ???
      1.02 (2016-04-02)
             avoid allocating large structures on the stack
      1.01 (2016-01-16)
             STBIW_REALLOC_SIZED: support allocators with no realloc support
             avoid race-condition in crc initialization
             minor compile issues
      1.00 (2015-09-14)
             installable file IO function
      0.99 (2015-09-13)
             warning fixes; TGA rle support
      0.98 (2015-04-08)
             added STBIW_MALLOC, STBIW_ASSERT etc
      0.97 (2015-01-18)
             fixed HDR asserts, rewrote HDR rle logic
      0.96 (2015-01-17)
             add HDR output
             fix monochrome BMP
      0.95 (2014-08-17)
               add monochrome TGA output
      0.94 (2014-05-31)
             rename private functions to avoid conflicts with stb_image.h
      0.93 (2014-05-27)
             warning fixes
      0.92 (2010-08-01)
             casts to unsigned char to fix warnings
      0.91 (2010-07-17)
             first public release
      0.90   first internal release
*/
/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
#   endif
#endif  // NW_API
#endif	// NW_STB_IMAGE_H