#ifndef NC_LIB_GAPI_HXX
#   define NC_LIB_GAPI_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
#	    if (NC_GAPI & NC_GAPI_OGL)
/* defines */
/* includes */
/* typedefs */
#	    	define nc_gapi_deivce_t  nc_wapi_device_t
#	    	define nc_gapi_context_t nc_wapi_context_t
#	    	define GLbyte       signed char
#	    	define GLchar       char
#	    	define GLshort      short
#	    	define GLint        int
#	    	define GLsizei      int
#	    	define GLboolean    unsigned char  
#	    	define GLubyte      unsigned char  
#	    	define GLushort     unsigned short
#	    	define GLhalf       unsigned short
#	    	define GLenum       unsigned int
#	    	define GLuint       unsigned int
#	    	define GLbitfield   unsigned int
#	    	define GLfloat      float
#	    	define GLclampf     float
#	    	define GLdouble     double
#	    	define GLclampd     double
#	    	define GLvoid       void
#	    	define GLintptr     ptrdiff_t
#	    	define GLsizeiptr   ptrdiff_t
#	    endif	/* NC_GAPI_OGL */
#	    if (NC_GAPI & NC_GAPI_D3D)
/* defines */
/* includes */
/* typedefs */
#		    define nc_gapi_device_t  ID3D11Device*
#		    define nc_gapi_context_t ID3D11DeviceContext*
#	    endif	/* NC_GAPI_D3D */
#   else
#	    error "nc_lib_core.hxx must be included before this header"
#   endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif	/* NC_LIB_GAPI_HXX */