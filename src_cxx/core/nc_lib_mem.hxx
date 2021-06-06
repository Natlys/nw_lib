#ifndef NC_LIB_MEMORY_HXX
#   define NC_LIB_MEMORY_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined NC_LIB_CORE_HXX)
/* defines */
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/** constants **/
#       define NC_NULL      (ptr_t)(0) /* empty pointer address */
#       define NC_VOID_PTR  NC_NULL    /* not set pointer address */
#       if !(defined(NC_MEM_USE_SIZE_CELL)) /* memory block size */
#           define NC_MEM_MIN_SIZE_CELL ( 1ul << 3ul ) /* 8 bytes to store a pointer; */
#           define NC_MEM_MID_SIZE_CELL ( 1ul << 4ul ) /* 16 bytes to store a pointer and size; */
#           define NC_MEM_MAX_SIZE_CELL ( 1ul << 5ul ) /* 32 bytes to store 2 pointers and 2 sizes; */
#           define NC_MEM_USE_SIZE_CELL NC_MEM_MID_SIZE_CELL
#           define NC_MEM_ISIDE_SIZE_CELL(size) ( \
                NC_NUM_ISIDE(size,                \
                    NC_MEM_MIN_SIZE_CELL,         \
                    NC_MEM_MAX_SIZE_CELL          \
                )                                 \
            ) /* NC_MEM_ISIDE_SIZE_CELL */
#           define NC_MEM_OSIDE_SIZE_CELL(size) ( \
                NC_NUM_OSIDE(size,                \
                    NC_MEM_MIN_SIZE_CELL,         \
                    NC_MEM_MAX_SIZE_CELL          \
                )                                 \
            ) /* NC_MEM_OSIDE_SIZE_CELL */
#       endif   /* NC_MEM_USE_SIZE_CELL */
#       if !(defined(NC_USE_SIZE_FULL)) /* the biggest amount of bytes to take*/
#           define NC_MEM_MIN_SIZE_FULL ( 1ul << 10ul ) /* 1kbyte */
#           define NC_MEM_MID_SIZE_FULL ( 1ul << 20ul ) /* 1mbyte */
#           define NC_MEM_MAX_SIZE_FULL ( 1ul << 30ul ) /* 1gbyte */
#           define NC_MEM_USE_SIZE_FULL NC_MEM_MID_SIZE_FULL
/* the value is inside of min-max memory range */
#           define NC_MEM_ISIDE_SIZE_FULL(size) ( \
                NC_NUM_ISIDE(size,                \
                    NC_MEM_MIN_SIZE_FULL,         \
                    NC_MEM_MAX_SIZE_FULL          \
                )                                 \
            ) /* NC_MEM_ISIDE_SIZE_FULL */
/* the value is outside of min-max memory range */
#           define NC_MEM_OSIDE_SIZE_FULL(size) ( \
                NC_NUM_OSIDE(size,                \
                    NC_MEM_MIN_SIZE_FULL,         \
                    NC_MEM_MAX_SIZE_FULL          \
                )                                 \
            ) /* NC_MEM_OSIDE_SIZE_FULL */
#       endif   /* NC_MEM_USE_SIZE_FULL */
/** functions **/
#       if (!(defined(NC_SIZEOF)))
#          define NC_SIZEOF_TYPE(tname) ( \
                /* get size of a type     \
                by the name */            \
                sizeof(tname)             \
            ) /* NC_SIZEOF_TYPE */
#           define NC_SIZEOF_DATA(data) ( \
                /* get size of a type     \
                by the pointer */         \
                (data_t)(data + NC_UNIT)  \
                - (data_t)(data)          \
            ) /* NC_SIZEOF_DATA */
#           define NC_SIZEOF_ELEM(elem) ( \
                /* get size of a type     \
                by the element */         \
                NC_SIZEOF_DATA(&elem)     \
            ) /* NC_SIZEOF_ELEM */
#           define NC_SIZEOF(tname) NC_SIZEOF_TYPE(tname)
#       endif   /* NC_SIZEOF */
#       if (!(defined(NC_ALIGOF)))
#           define NC_ALIGOF_TYPE(tname) (  \
                /* get align size of a type \
                by the name */              \
                alignof(tname)              \
            ) /* NC_ALIGOF_TYPE */
#           define NC_ALIGOF_DATA(data) ( \
                /* get size of a type     \
                by the pointer */         \
                (data_t)(data + NC_UNIT)  \
                - (data_t)(data)          \
            ) /* NC_ALIGOF_DATA */
#           define NC_ALIGOF_ELEM(elem) ( \
                /* get size of a type     \
                by the element */         \
                NC_ALIGOF_DATA(&elem);    \
            ) /* NC_ALIGOF_ELEM */
#           define NC_ALIGOF(data) NC_ALIGOF_DATA(data)
#       endif   /* NC_ALIGOF */
#       if (!(defined(NC_SEATOF)))
#           define NC_SEATOF_TYPE(tname, mname) (   \
                /* get offset size of a type member \
                by the name */                      \
                offsetof(tname, mname)              \
            ) /* NC_SEATOF_TYPE */
#           define NC_SEATOF_DATA(tname, mdata) (   \
                /* get offset size of a type member \
                by the pointer */                   \
            ) /* NC_SEATOF_DATA */
#           define NC_SEATOF_ELEM(tname, melem) (       \
                /* get size of a type by the element */ \
            ) /* NC_SEATOF_ELEM */
#           define NC_SEATOF(arg0, arg1) NC_SEATOF_TYPE(arg0, arg1)
#       endif   /* NC_SEATOF */
#       if (!(defined(NC_MEM_TAKE)))
#           define NC_MEM_TAKE_HEAP(data, size) ({ \
                /* write the address of an         \
                allocated block                    \
                with the given size                \
                into the given pointer*/           \
                data = malloc(size);               \
            }) /* NC_MEM_TAKE_HEAP */
#           define NC_MEM_TAKE(data, size) NC_MEM_TAKE_HEAP(data, size)
#       endif   /* NC_MEM_TAKE */
#       if (!(defined(NC_MEM_FREE)))
#           define NC_MEM_FREE_HEAP(data, size) ({ \
                /* deallocate the memory block     \
                of the given size and              \
                reset the given pointer */         \
                free(data); data = NC_NULL;        \
            }) /* NC_MEM_FREE_HEAP */
#           define NC_MEM_FREE(data, size) NC_MEM_FREE_HEAP(data, size)
#       endif   /* NC_MEM_FREE */
#       if (!(defined(NC_MEM_EDIT)))
/* memory_edit
 * description:
 * -> takes a pointer to free and copy the memory;
 * -> takes an iput size to free the memory;
 * -> takes an oput size to take the memory;
 * -> to take memory: data != 0; isize == 0; osize != 0;
 * -> to free memory: data != 0; isize != 0; osize == 0;
 * -> to edit memory: data != 0; isize != 0; osize != 0;
*/
#           define NC_MEM_EDIT_HEAP(data, isize, osize) ({ \
                if (isize != NC_ZERO) {                    \
                    if (osize == NC_ZERO) {                \
                        free(data);                        \
                        data = NC_NULL;                    \
                    } else {                               \
                        register ptr_t temp = data;        \
                        register size_t csize = NC_ZERO;   \
                        csize = NC_MIN(isize, osize);      \
                        data = malloc(osize);              \
                        memmove(data, temp, csize);        \
                        free(temp);                        \
                        temp = NC_NULL;                    \
                    }                                      \
                } if (osize > NC_ZERO) {                   \
                    data = malloc(osize);                  \
                }                                          \
                if (osize > isize) {                       \
                    register ptr_t odata = data + isize;   \
                    memset(odata, NC_ZERO, osize - isize); \
                }                                          \
            }) /* NC_MEM_EDIT_HEAP */
#           define NC_MEM_EDIT(data, isize, osize) NC_MEM_EDIT_HEAP(data, isize, osize)
#       endif   /* NC_MEM_EDIT */
#       if (!(defined(NC_MEM_NEW1)))
#           define NC_MEM_NEW1(data, type) ({ \
                register size_t size;         \
                register size_t alig;         \
                size = NC_SIZEOF(type);       \
                alig = NC_ALIGOF(type);       \
                size = NC_ALIG(size, alig);  \
                NC_MEM_TAKE(data, size);      \
            }) /* NC_MEM_NEW1 */
#       endif   /* NC_MEM_NEW1 */
#       if (!(defined(NC_MEM_DEL1)))
#           define NC_MEM_DEL1(data, type) ({ \
                register size_t size;         \
                register size_t alig;         \
                size = NC_SIZEOF(type);       \
                alig = NC_ALIGOF(type);       \
                size = NC_ALIG(size, alig);   \
                NC_MEM_FREE(data, size);      \
            }) /* NC_MEM_DEL1 */
#       endif   /* NC_MEM_DEL1 */
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else	/* NC_LIB_CORE_HXX */
#	    error "nc_lib_core.hxx must be included before this header!"
#   endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif  /* NC_LIB_MEMORY_HXX */