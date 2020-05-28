# Buffer
Header-only implementation of a statically sized size-aware buffer in C that is generic over the contained type and capacity.

# Types
The library provides two types:
```c
struct BUFFER(T, N)
{
	T      data[N];
	size_t count;
}
```
and
```c
struct SLICE(T)
{
	T*     data;
	size_t count;
},
```
The advantage of slices is that they can point anywhere.
On the other hand buffers own their data(no allocation necessary) and their type encodes the
maximum amount of data they can hold in addition to how much data is currently being stored.

# Operations
Some operations are provided to manipulate `data` while keeping `count` updated.

## Copy, Append and Equality
Let `BUFFER(T, N) *buf, *lhs, *rhs; T *ptr; size_t cnt`.
```c
buffer_copy_n(buf, ptr, cnt);   // copy range [ptr, ptr + cnt) into buf
buffer_append_n(buf, ptr, cnt); // append range [ptr, ptr + cnt) to buf
buffer_copy(lhs, rhs);          // copy [rhs->data, rhs->data + rhs->count) into lhs
buffer_append(lhs, rhs);        // append [rhs->data, rhs->data + rhs->count) to lhs
buffer_eq(lhs, rhs);            // evaluates to true if and only if lhs->count == rhs->count
                                // and memcmp(lhs->data, rhs->data, lhs->count) == 0
```

Let `T arr[M]`.
```c
buffer_copy_arr(buf, arr);   // copy range [arr, arr + M) into buf
buffer_append_arr(buf, arr); // append range [arr, arr + M) to buf
```
If T == char `arr` will likely be initialized by `char arr[] = "some string"`, meaning that the last character in arr will be the null-terminator, which we may not want to copy.
```c
buffer_copy_chrarr(buf, arr);   // copy range [arr, arr + M - 1) into buf
buffer_append_chrarr(buf, arr); // append range [arr, arr + M - 1) to buf
```

Let `char const* str`.
```c
buffer_copy_str(buf, str);   // copy range [str, str + strlen(str)) into buf
buffer_append_str(buf, str); // append range [str, str + strlen(str)) to buf
```

Let `FILE* file`.
```c
buffer_read_n(buf, file, cnt);        // fread cnt Ts from file into buf
buffer_read_append_n(buf, file, cnt); // append cnt Ts from file to buf
buffer_write(buf, file);              // fwrite [buf->data, buf->data + buf->count) to file
buffer_read(buf, file);               // fread at most N Ts from file into buf
buffer_read_append(buf, file);        // fread at most N - buf->count Ts from file into buf
                                      // starting at buf->data + buf->count
```

## Initializing slices
```c
slice_init(slice, ptr, cnt);   // slice->data = ptr, slice->count = cnt
slice_from_buffer(slice, buf); // slice->data = buf->data, slice->count = buf->count
slice_from_arr(slice, arr);    // slice->data = arr, slice->count = M;
slice_from_chrarr(slice, arr); // slice->data = arr, slice->count = M - 1;
slice_from_str(slice, str);    // slice->data = str, slice->count = strlen(str)
```

# Bounds checking
The code contains assertions to make sure that none of the operations above write beyond the bounds of the buffer. Assertions can be disabled by defining NDEBUG once you are sure you do not have this bug.

Bounds checking only works on buffers. BUFFER and SLICE are distinguished based on whether
`sizeof(data) == sizeof(&data[0])`; for this reason you may wish to avoid buffers of size 8.
