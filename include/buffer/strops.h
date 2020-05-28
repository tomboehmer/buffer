#ifndef ___BUFFER_STROPS_H___
#define ___BUFFER_STROPS_H___

#include "buffer/ops.h"

#define slice_from_str(SLC, PTR)\
({\
 typeof(SLC) __sfs_slc = (SLC);\
 typeof(PTR) __sfs_ptr = (PTR);\
 slice_init(__sfs_slc, &__sfs_ptr[0], strlen(__sfs_ptr));\
})

#define buffer_copy_str(BUF, PTR)\
({\
 typeof(BUF) __bcs_buf = (BUF);\
 typeof(PTR) __bcs_ptr = (PTR);\
 buffer_copy_n(__bcs_buf, &__bcs_ptr[0], strlen(__bcs_ptr));\
})

#define buffer_append_str(BUF, PTR)\
({\
 typeof(BUF) __bas_buf = (BUF);\
 typeof(PTR) __bas_ptr = (PTR);\
 buffer_append_n(__bas_buf, &__bas_ptr[0], strlen(__bas_ptr));\
})

#endif /* ___BUFFER_STROPS_H___ */
