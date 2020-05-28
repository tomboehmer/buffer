#ifndef ___BUFFER_FILEOPS_H___
#define ___BUFFER_FILEOPS_H___

#include "buffer/ops.h"

#include <stdio.h>

#define buffer_read_n(X, F, N)\
({\
	typeof(X) __brn_x = (X);\
	typeof(F) __brn_f = (F);\
	typeof(N) __brn_n = (N);\
	assert(__brn_n <= BUFLENGTH(__brn_x));\
	__brn_x->count = fread(__brn_x->data, BUFMSIZE(__brn_x), __brn_n, __brn_f);\
	__brn_x;\
})

#define buffer_read_append_n(X, F, N)\
({\
	typeof(X) __bran_x = (X);\
	typeof(F) __bran_f = (F);\
	typeof(N) __bran_n = (N);\
	assert(__bran_n <= BUFLENGTH(__bran_x) - __bran_x->count);\
	__bran_x->count += fread(__bran_x->data + __bran_x->count, BUFMSIZE(__bran_x), __bran_n, __bran_f);\
	__bran_x;\
})

#define buffer_write(X, F)\
({\
	typeof(X) __bw_x = (X);\
	typeof(F) __bw_f = (F);\
	fwrite(__bw_x->data, BUFMSIZE(__bw_x), __bw_x->count, __bw_f);\
	__bw_x;\
})

#define buffer_read(X, F)\
({\
	typeof(X) __br_x = (X);\
	typeof(F) __br_f = (F);\
	buffer_read_n(__br_x, __br_f, BUFLENGTH(__br_x));\
})

#define buffer_read_append(X, F)\
({\
	typeof(X) __bra_x = (X);\
	typeof(F) __bra_f = (F);\
	buffer_read_append_n(__bra_x, __bra_f, BUFLENGTH(__bra_x) - __bra_x->count);\
})

#endif /* ___BUFFER_FILEOPS_H___ */
