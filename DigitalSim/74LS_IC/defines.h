#pragma once
#include "common.h"

namespace s_74LS {
	constexpr volt VCC_min = 4.75;
	constexpr volt VCC_max = 5.25;
	constexpr volt VIH_min = 2;
	constexpr volt VIL_max = 0.8;
	constexpr volt VOH_typ = 3.4;
	constexpr volt VOL_typ = 0.35;

	constexpr bool volt_to_bool(volt in) {
		return ::volt_to_bool(in, VIH_min, VIL_max);
	}
	constexpr volt bool_to_volt(bool in) {
		return ::bool_to_volt(in, VOH_typ, VOL_typ);
	}
}