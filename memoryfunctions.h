#include <aio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <stddef.h>

void* malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void* calloc(size_t nelem, size_t elsize);
