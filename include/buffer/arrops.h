#ifndef ___BUFFER_ARROPS_H___
#define ___BUFFER_ARROPS_H___

#include "buffer/ops.h"

#define slice_from_arr(BUF, ARR)    slice_init((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR))
#define slice_from_chrarr(BUF, ARR) slice_init((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR) - 1)

#define buffer_copy_arr(BUF, ARR)\
({\
	static_assert(BUFFER_CAN_COPY(BUF, &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR)), "");\
	buffer_copy_n((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR));\
})

#define buffer_append_arr(BUF, ARR) buffer_append_n((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR))

#define buffer_copy_chrarr(BUF, ARR)\
({\
	static_assert(BUFFER_CAN_COPY(BUF, &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR) - 1), "");\
	buffer_copy_n((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR) - 1);\
})

#define buffer_append_chrarr(BUF, ARR) buffer_append_n((BUF), &(ARR)[0], BUFFER_INTERNAL_LENGTH(ARR) - 1)

#endif /* ___BUFFER_ARROPS_H___ */
