#ifndef ___BUFFER_OPS_H___
#define ___BUFFER_OPS_H___

#include "buffer/types.h"

#include <string.h>
#include <assert.h>

#ifndef static_assert
#define static_assert(C, M) assert(C)
#endif

#define BUFFER_INTERNAL_LENGTH(A) (sizeof(A) / sizeof((A)[0]))
#define BUFLENGTH(BUF) BUFFER_INTERNAL_LENGTH((BUF)->data)
#define BUFSIZE(BUF) sizeof((BUF)->data)
#define BUFMSIZE(BUF) sizeof((BUF)->data[0])

#define BUFFER_IS_SLICE(BUF) (BUFSIZE(BUF) == sizeof(&(BUF)->data[0]))

#define BUFFER_CAN_APPEND(BUF,PTR,CNT)\
	(BUFFER_IS_SLICE(BUF) || BUFSIZE(BUF) - BUFMSIZE(BUF) * (BUF)->count >= sizeof((PTR)[0]) * (CNT))
#define BUFFER_CAN_COPY(BUF,PTR,CNT)\
	(BUFFER_IS_SLICE(BUF) || BUFSIZE(BUF) >= sizeof((PTR)[0]) * (CNT))

#define slice_init(SLC, PTR, CNT)\
({ \
	typeof(SLC) __si_slc = (SLC); \
	typeof(PTR) __si_ptr = (PTR); \
	typeof(CNT) __si_cnt = (CNT); \
	__si_slc->data = __si_ptr;\
	__si_slc->count = __si_cnt;\
	__si_slc;\
})

#define slice_from_buffer(SLC, BUF)\
({ \
	typeof(SLC) __sfb_slc = (SLC); \
	typeof(BUF) __sfb_buf = (BUF); \
	slice_init(__sfb_slc, &__sfb_buf->data[0], __sfb_buf->count);\
})

#define buffer_eq(LHS, RHS) \
({ \
	typeof(LHS) __beq_lhs = (LHS); \
	typeof(RHS) __beq_rhs = (RHS); \
	static_assert(BUFMSIZE(__beq_lhs) == BUFMSIZE(__beq_rhs), "contained types must have the same size");\
	__beq_lhs->count != __beq_rhs->count\
		? 0\
 		: !memcmp(__beq_lhs->data, __beq_rhs->data, __beq_rhs->count * BUFMSIZE(__beq_rhs)); \
})

#define buffer_copy_n(BUF, PTR, CNT)\
({\
	typeof(BUF) __bcn_buf = (BUF);\
	typeof(PTR) __bcn_ptr = (PTR);\
	typeof(CNT) __bcn_cnt = (CNT);\
	static_assert(BUFMSIZE(__bcn_buf) == sizeof(__bcn_ptr[0]),  "contained types must have the same size");\
	assert(BUFFER_CAN_COPY(__bcn_buf, __bcn_ptr, __bcn_cnt));\
	memcpy(__bcn_buf->data, __bcn_ptr, __bcn_cnt * sizeof(__bcn_buf->data[0]));\
	__bcn_buf->count = __bcn_cnt;\
	__bcn_buf;\
})

#define buffer_append_n(BUF, PTR, CNT)\
({\
	typeof(BUF) __ban_buf = (BUF);\
	typeof(PTR) __ban_ptr = (PTR);\
	typeof(CNT) __ban_cnt = (CNT);\
	static_assert(BUFMSIZE(__ban_buf) == sizeof(__ban_ptr[0]), "contained types must have the same size");\
	assert(BUFFER_CAN_APPEND(__ban_buf, __ban_ptr, __ban_cnt));\
	memcpy(__ban_buf->data + __ban_buf->count, __ban_ptr, __ban_cnt * BUFMSIZE(__ban_buf));\
	__ban_buf->count += __ban_cnt;\
	__ban_buf;\
})

#define buffer_copy(LHS, RHS)\
({\
	typeof(LHS) __bc_lhs = (LHS);\
	typeof(RHS) __bc_rhs = (RHS);\
	buffer_copy_n(__bc_lhs, &__bc_rhs->data[0], __bc_rhs->count);\
})

#define buffer_append(LHS, RHS)\
({\
	typeof(LHS) __ba_lhs = (LHS);\
	typeof(RHS) __ba_rhs = (RHS);\
	buffer_append_n(__ba_lhs, &__ba_rhs->data[0], __ba_rhs->count);\
})

#endif /* ___BUFFER_OPS_H___ */
