#pragma once

#include <cstdio>

using volt = double;
constexpr volt volt_floating = -1;
constexpr volt volt_invalid = -2;

constexpr bool volt_to_bool(volt in, volt VH_min, volt VL_max) {
	if (in > VH_min) {
		return true;
	}
	else if (in < VL_max) {
		return false;
	}
	else if (in > ((VL_max + VH_min) / 2)) {
		return true;
	}
	else { return false; }
}
constexpr volt bool_to_volt(bool in, volt VH, volt VL) {
	if (in) {
		return VH;
	}
	else {
		return VL;
	}
}

#define expect(value) \
    do \
    { \
        if constexpr (!(value)) \
        { \
            fprintf(stderr, "%s failed in %s:%d\n", #value, __FILE__, __LINE__); \
        } \
    } while(0)