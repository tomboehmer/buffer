#ifndef ___BUFFER_TYPES_H___
#define ___BUFFER_TYPES_H___

#define BUFFER(T, N)\
	struct \
	{ \
		T data[N]; \
		size_t count; \
	}

#define SLICE(T)\
	struct\
	{\
		T* data;\
		size_t count;\
	}

#endif /* ___BUFFER_TYPES_H___ */
