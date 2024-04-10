#pragma once

#include "defines.h"
#include <bitset>

namespace s_74LS {

	template<size_t size>
	struct multi_d_flip_flop_inputs {
		std::array<volt, size> PRE_inv{};
		std::array<volt, size> CLR_inv{};
		std::array<volt, size> CLK{};
		std::array<volt, size> D{};
	};

	template<size_t size>
	struct multi_jk_flip_flop_inputs {
		std::array<volt, size> PRE_inv{};
		std::array<volt, size> CLR_inv{};
		std::array<volt, size> CLK{};
		std::array<volt, size> J{};
		std::array<volt, size> K{};
	};

	template<size_t size>
	struct multi_latch_inputs {
		std::array<volt, size> EN{};
		std::array<volt, size> D{};
	};

	template<size_t size>
	struct multi_flip_flop_outputs {
		std::array<volt, size> Q{};
		std::array<volt, size> Q_inv{};
	};

	template<size_t num_of_bits>
	struct counter_inputs {
		volt EN{};
		volt CLR_inv{};
		volt CLK{};
		volt LOAD{};
		std::array<volt, num_of_bits> data{};
	};
	template<size_t num_of_bits>
	struct counter_outputs {
		std::array<volt, num_of_bits> Q{};
		volt ripple_carry{};
	};

	static void single_jk_flip_flop(volt PRE_inv, volt CLR_inv, volt CLK, volt J, volt K, volt& Q, volt& Q_inv) {
		if ((volt_to_bool(PRE_inv) == 0) && (volt_to_bool(CLR_inv) == 1)) {
			Q = bool_to_volt(1);
			Q_inv = bool_to_volt(0);
			return;
		}
		if ((volt_to_bool(PRE_inv) == 1) && (volt_to_bool(CLR_inv) == 0)) {
			Q = bool_to_volt(0);
			Q_inv = bool_to_volt(1);
			return;
		}
		if ((volt_to_bool(PRE_inv) == 0) && (volt_to_bool(CLR_inv) == 0)) {
			Q = bool_to_volt(1);
			Q_inv = bool_to_volt(1);
			expect(false && "d flip flop's PRE_inv and CLR_inv are both 0");
			return;
		}
		if (volt_to_bool(CLK) == 1) {
			if (volt_to_bool(J) == 1 && volt_to_bool(K) == 1) {
				std::swap(Q, Q_inv);
				return;
			}
			if (volt_to_bool(J) == 1) {
				Q = bool_to_volt(1);
				Q_inv = bool_to_volt(0);
				return;
			}
			if (volt_to_bool(K) == 1) {
				Q = bool_to_volt(0);
				Q_inv = bool_to_volt(1);
				return;
			}
		}
	}
	template<size_t num>
	static void multi_jk_flip_flop(multi_jk_flip_flop_inputs<num> const& input, multi_flip_flop_outputs<num>& output) {
		for (size_t i = 0; i < num; i++) {
			single_jk_flip_flop(input.PRE_inv[i], input.CLR_inv[i], input.CLK[i], input.J[i], input.K[i], output.Q[i], output.Q_inv[i]);
		}
	}
	void dual_jk_flip_flop(multi_jk_flip_flop_inputs<2> const& input, multi_flip_flop_outputs<2>& output) {
		multi_jk_flip_flop<2>(input, output);
	}


	static void single_d_flip_flop(volt PRE_inv, volt CLR_inv, volt CLK, volt D, volt& Q, volt& Q_inv) {
		if ((volt_to_bool(PRE_inv) == 0) && (volt_to_bool(CLR_inv) == 1)) {
			Q = bool_to_volt(1);
			Q_inv = bool_to_volt(0);
			return;
		}
		if ((volt_to_bool(PRE_inv) == 1) && (volt_to_bool(CLR_inv) == 0)) {
			Q = bool_to_volt(0);
			Q_inv = bool_to_volt(1);
			return;
		}
		if ((volt_to_bool(PRE_inv) == 0) && (volt_to_bool(CLR_inv) == 0)) {
			Q = bool_to_volt(1);
			Q_inv = bool_to_volt(1);
			expect(false && "d flip flop's PRE_inv and CLR_inv are both 0");
			return;
		}
		if (volt_to_bool(CLK) == 1) {
			Q = D;
			Q_inv = bool_to_volt(!volt_to_bool(D));
			return;
		}
	}
	template<size_t num>
	static void multi_d_flip_flop(multi_d_flip_flop_inputs<num> const& input, multi_flip_flop_outputs<num>& output) {
		for (int i = 0; i < num; i++) {
			single_d_flip_flop(input.PRE_inv[i], input.CLR_inv[i], input.CLK[i], input.D[i], output.Q[i], output.Q_inv[i]);
		}
	}
	void dual_d_flip_flop(multi_d_flip_flop_inputs<2> const& input, multi_flip_flop_outputs<2>& output) {
		multi_d_flip_flop<2>(input, output);
	}
	template<size_t num>
	static void multi_latch(multi_latch_inputs<num> const& input, multi_flip_flop_outputs<num>& output) {
		for (int i = 0; i < num; i++) {
			single_d_flip_flop(bool_to_volt(1), bool_to_volt(1), input.EN[i], input.D[i], output.Q[i], output.Q_inv[i]);
		}
	}
	void quad_latch(multi_latch_inputs<4> const& input, multi_flip_flop_outputs<4>& output) {
		multi_latch<4>(input, output);
	}
	template<size_t num_of_bits,typename data_Iterator,typename Q_Iterator>
	static void counter(volt EN, volt CLR_inv, volt CLK, volt LOAD, data_Iterator data_begin, data_Iterator data_end, Q_Iterator Q_begin, Q_Iterator Q_end, volt& ripple_carry) {
		
		assert(num_of_bits == std::distance(data_begin, data_end));
		assert(num_of_bits == std::distance(Q_begin, Q_end));


		if (EN == 0) {
			return;
		}
		if (volt_to_bool(CLR_inv) == 0) {
			std::fill(Q_begin, Q_end, 0);
		}
		if (volt_to_bool(LOAD) == 1) {
			std::copy(data_begin, data_end, Q_begin);
		}

		if (volt_to_bool(CLK) == 0) {
			return;
		}

		//turn Q to a bool bitset
		std::bitset<num_of_bits> Q_as_bitset{};
		int i = 0;
		for (auto Q_it = Q_begin; Q_it != Q_end; ++Q_it) {

			Q_as_bitset[i] = volt_to_bool(*Q_it);
			i++;
		}

		if (Q_as_bitset.to_ullong() == (pow(2, num_of_bits) - 1)) {
			ripple_carry = bool_to_volt(1);
		}
		//increment the bitset
		Q_as_bitset = Q_as_bitset.to_ullong() + 1;

		//turn the bitset back into Q
		i = 0;
		for (auto Q_it = Q_begin; Q_it != Q_end; ++Q_it) {
			*Q_it = bool_to_volt(Q_as_bitset[i]);
			i++;
		}

	}
	template<size_t num_of_bits, typename inputs_Container, typename Q_Container>
	static void counter(volt EN, volt CLR_inv, volt CLK, volt LOAD, inputs_Container const& data, Q_Container& Q, volt& ripple_carry) {
		counter<num_of_bits>(EN, CLR_inv, CLK, LOAD, data.begin(), data.end(), Q.begin(), Q.end(), ripple_carry);
	}
	void four_bit_counter(counter_inputs<4> const& inputs, counter_outputs<4>& outputs) {
		counter<4>(inputs.EN, inputs.CLR_inv, inputs.CLK, inputs.LOAD, inputs.data, outputs.Q, outputs.ripple_carry);
	}
}