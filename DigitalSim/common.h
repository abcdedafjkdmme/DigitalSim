#pragma once

#include <cstdio>

#define expect(value) \
    do \
    { \
        if constexpr (!(value)) \
        { \
            fprintf(stderr, "%s failed in %s:%d\n", #value, __FILE__, __LINE__); \
        } \
    } while(0)