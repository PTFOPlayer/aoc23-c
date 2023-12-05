#include <stdlib.h>
#include <stdio.h>

typedef struct vector
{
    void *_internal;
    size_t _physical_size;
    size_t usable_size;
} vector;

vector create_from_ptr(void *ptr, size_t n)
{
    vector v = {
        ._internal = ptr,
        ._physical_size = n,
        .usable_size = n};
    return v;
}

size_t v_size(vector *v)
{
    return v->usable_size;
}

void push(vector *v, int value)
{
    if (v->_physical_size <= v->usable_size)
    {
        if (v->_physical_size == 0)
        {
            v->_physical_size = 1;
        }

        v->_physical_size = v->_physical_size * 2;
        v->_internal = (int *)realloc(v->_internal, v->_physical_size * sizeof(long long));
        v->usable_size++;
        ((int *)v->_internal)[v->usable_size] = value;
    }
    else
    {
        v->usable_size++;
        ((int *)v->_internal)[v->usable_size] = value;
    }
}

int v_index(vector *v, size_t idx, void *val)
{
    if (idx < 0)
        return -1;
    if (idx > v->usable_size - 1)
    {
        return -2;
    }

    *((int *)val) = ((int *)v->_internal)[idx + 1];

    return 0;
}