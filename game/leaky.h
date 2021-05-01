#include <stdio.h>
#include <stdlib.h>

void* tmalloc(size_t __size, int line, char* func)
{
    printf("MALLOC CALLED AT %d in %s USING %d", line, func, __size);
    return malloc(__size);
}

#define malloc(t) tmalloc(t, __LINE__, __func__)
