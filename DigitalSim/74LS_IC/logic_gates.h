#pragma once
#include <cassert>
#include <array>
#include "defines.h"

namespace s_74LS {
	enum class multi_input_logic_func {
		and_gate,
		nand_gate,
		nor_gate,
		or_gate
	};
	template<size_t size>
	struct multi_gate_output {
		std::array<volt, size> Y{};
	};


	template<typename Iterator>
	static volt single_multi_input_logic_gate(Iterator inputs_begin, Iterator inputs_end, multi_input_logic_func logic_func) {
		bool result{};
		for (auto it = inputs_begin; it != inputs_end; ++it) {
			if (logic_func == multi_input_logic_func::and_gate || logic_func == multi_input_logic_func::nand_gate) {
				result = result && volt_to_bool(*it);
			}
			else if (logic_func == multi_input_logic_func::or_gate || logic_func == multi_input_logic_func::nor_gate) {
				result = result || volt_to_bool(*it);
			}
		}
		if (logic_func == multi_input_logic_func::nand_gate) {
			result = !result;
		}
		else if (logic_func == multi_input_logic_func::nor_gate) {
			result = !result;
		}
		return bool_to_volt(result);
	}
	template<typename Container>
	static volt single_multi_input_logic_gate(Container const& cont, multi_input_logic_func logic_func) {
		return single_multi_input_logic_gate(cont.begin(), cont.end(), logic_func);
	}



	template<size_t num_of_outputs, typename A_inputs_iter, typename B_inputs_iter>
	static multi_gate_output<num_of_outputs> multi_two_input_logic_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end, B_inputs_iter B_inputs_begin, B_inputs_iter B_inputs_end, multi_input_logic_func logic_func) {

		assert(std::distance(A_inputs_begin, A_inputs_end) == num_of_outputs);
		assert(std::distance(B_inputs_begin, B_inputs_end) == num_of_outputs);

		multi_gate_output<num_of_outputs> result{};

		auto A_it = A_inputs_begin;
		auto B_it = B_inputs_begin;
		for (int i = 0; i < num_of_outputs; i++) {

			auto inputs = { *A_it, *B_it };
			result.Y[i] = single_multi_input_logic_gate(inputs, logic_func);

			++A_it;
			++B_it;
		}
		return result;
	}
	template<size_t num_of_outputs, typename A_Container, typename B_Container>
	static multi_gate_output<num_of_outputs> multi_two_input_logic_gate(A_Container const& A_inputs, B_Container const& B_inputs, multi_input_logic_func logic_func) {
		return multi_input_logic_gate(A_inputs.begin(), A_inputs.end(), B_inputs.begin(), B_inputs.end(), logic_func);
	}


	static volt single_single_input_not_gate(volt A) {
		return bool_to_volt(!volt_to_bool(A));
	}
	template<size_t num_of_outputs, typename Iterator>
	static multi_gate_output<num_of_outputs> multi_single_input_not_gate(Iterator A_inputs_begin, Iterator A_inputs_end) {
		multi_gate_output<num_of_outputs> result{};
		int i = 0;
		for (auto A_it = A_inputs_begin; A_it != A_inputs_begin; ++A_it) {
			result.Y[i] = single_single_input_not_gate(*A_it);
			i++;
		}
		return result;
	}
	template<size_t num_of_outputs, typename A_Container>
	static multi_gate_output<num_of_outputs> multi_single_input_not_gate(A_Container const& A_inputs) {
		return multi_single_input_not_gate(A_inputs.begin(), A_inputs.end());
	}


	template<typename A_inputs_iter, typename B_inputs_iter>
	multi_gate_output<4> quad_two_input_nand_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end, B_inputs_iter B_inputs_begin, B_inputs_iter B_inputs_end) {
		return multi_two_input_logic_gate<4>(A_inputs_begin, A_inputs_end, B_inputs_begin, B_inputs_end, multi_input_logic_func::nand_gate);
	}
	template<typename A_Container, typename B_Container>
	multi_gate_output<4> quad_two_input_nand_gate(A_Container const& A_inputs, B_Container const& B_inputs) {
		return quad_two_input_nand_gate(A_inputs.begin(), A_inputs.end(), B_inputs.begin(), B_inputs.end());
	}
	template<typename A_inputs_iter, typename B_inputs_iter>
	multi_gate_output<4> quad_two_input_and_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end, B_inputs_iter B_inputs_begin, B_inputs_iter B_inputs_end) {
		return multi_two_input_logic_gate<4>(A_inputs_begin, A_inputs_end, B_inputs_begin, B_inputs_end, multi_input_logic_func::and_gate);
	}
	template<typename A_Container, typename B_Container>
	multi_gate_output<4> quad_two_input_and_gate(A_Container const& A_inputs, B_Container const& B_inputs) {
		return quad_two_input_and_gate(A_inputs.begin(), A_inputs.end(), B_inputs.begin(), B_inputs.end());
	}
	template<typename A_inputs_iter, typename B_inputs_iter>
	multi_gate_output<4> quad_two_input_or_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end, B_inputs_iter B_inputs_begin, B_inputs_iter B_inputs_end) {
		return multi_two_input_logic_gate<4>(A_inputs_begin, A_inputs_end, B_inputs_begin, B_inputs_end, multi_input_logic_func::or_gate);
	}
	template<typename A_Container, typename B_Container>
	multi_gate_output<4> quad_two_input_or_gate(A_Container const& A_inputs, B_Container const& B_inputs) {
		return quad_two_input_or_gate(A_inputs.begin(), A_inputs.end(), B_inputs.begin(), B_inputs.end());
	}
	template<typename A_inputs_iter, typename B_inputs_iter>
	multi_gate_output<4> quad_two_input_nor_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end, B_inputs_iter B_inputs_begin, B_inputs_iter B_inputs_end) {
		return multi_two_input_logic_gate<4>(A_inputs_begin, A_inputs_end, B_inputs_begin, B_inputs_end, multi_input_logic_func::nor_gate);
	}
	template<typename A_Container, typename B_Container>
	multi_gate_output<4> quad_two_input_nor_gate(A_Container const& A_inputs, B_Container const& B_inputs) {
		return quad_two_input_nor_gate(A_inputs.begin(), A_inputs.end(), B_inputs.begin(), B_inputs.end());
	}
	template<typename A_inputs_iter>
	multi_gate_output<4> quad_single_input_not_gate(A_inputs_iter A_inputs_begin, A_inputs_iter A_inputs_end) {
		return multi_single_input_not_gate<4>(A_inputs_begin, A_inputs_end);
	}
	template<typename A_Container>
	multi_gate_output<4> quad_single_input_not_gate(A_Container const& A_inputs) {
		return multi_single_input_not_gate<4>(A_inputs.begin(), A_inputs.end());
	}



	
	/*
	void dual_d_flip_flop(multi_d_flip_flop_inputs<2> const& input, multi_d_flip_flop_output<2>& result) {
		single_d_flip_flop_output res1{ .Q = res.Q1, .Q_inv = res.Q1_inv };
		single_d_flip_flop_output res2{ .Q = res.Q2, .Q_inv = res.Q2_inv };

		single_d_flip_flop(PRE1_inv, CLR1_inv, CLK1, D1, res1);
		single_d_flip_flop(PRE2_inv, CLR2_inv, CLK2, D2, res2);

		res.Q1 = res1.Q;
		res.Q1_inv = res1.Q_inv;
		res.Q2 = res2.Q;
		res.Q2_inv = res2.Q_inv;
	}

	
	static volt nand_single(volt A, volt B) {
		return bool_to_volt(!(volt_to_bool(A) && volt_to_bool(B)));
	}

	quad_gate_result quad_nand_gate(volt Vcc, volt GND, volt A1, volt B1, volt A2, volt B2, volt A3, volt B3, volt A4, volt B4) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		quad_gate_result res{};
		res.Y1 = nand_single(A1, B1);
		res.Y2 = nand_single(A2, B2);
		res.Y3 = nand_single(A3, B3);
		res.Y4 = nand_single(A4, B4);
		return res;
	}


	static volt and_single(volt A, volt B) {
		return bool_to_volt(volt_to_bool(A) && volt_to_bool(B));
	}

	quad_gate_result quad_and_gate(volt Vcc, volt GND, volt A1, volt B1, volt A2, volt B2, volt A3, volt B3, volt A4, volt B4) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		quad_gate_result res{};
		res.Y1 = and_single(A1, B1);
		res.Y2 = and_single(A2, B2);
		res.Y3 = and_single(A3, B3);
		res.Y4 = and_single(A4, B4);
		return res;
	}

	static volt nor_single(volt A, volt B) {
		return bool_to_volt(!(volt_to_bool(A) || volt_to_bool(B)));
	}

	quad_gate_result quad_nor_gate(volt Vcc, volt GND, volt A1, volt B1, volt A2, volt B2, volt A3, volt B3, volt A4, volt B4) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		quad_gate_result res{};
		res.Y1 = nor_single(A1, B1);
		res.Y2 = nor_single(A2, B2);
		res.Y3 = nor_single(A3, B3);
		res.Y4 = nor_single(A4, B4);

		return res;
	}
	static volt or_single(volt A, volt B) {
		return bool_to_volt(volt_to_bool(A) || volt_to_bool(B));
	}

	quad_gate_result quad_or_gate(volt Vcc, volt GND, volt A1, volt B1, volt A2, volt B2, volt A3, volt B3, volt A4, volt B4) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		quad_gate_result res{};
		res.Y1 = or_single(A1, B1);
		res.Y2 = or_single(A2, B2);
		res.Y3 = or_single(A3, B3);
		res.Y4 = or_single(A4, B4);

		return res;
	}

	static volt xor_single(volt A, volt B) {
		return bool_to_volt(volt_to_bool(A) != volt_to_bool(B));
	}

	quad_gate_result quad_xor_gate(volt Vcc, volt GND, volt A1, volt B1, volt A2, volt B2, volt A3, volt B3, volt A4, volt B4) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		quad_gate_result res{};
		res.Y1 = xor_single(A1, B1);
		res.Y2 = xor_single(A2, B2);
		res.Y3 = xor_single(A3, B3);
		res.Y4 = xor_single(A4, B4);
		return res;
	}

	static volt inverter_single(volt A) {
		return bool_to_volt(!volt_to_bool(A));
	}
	hex_inverter_result hex_inverter(volt Vcc, volt GND, volt A1, volt A2, volt A3, volt A4, volt A5, volt A6) {
		assert((Vcc - GND) > VCC_min && (Vcc - GND) < VCC_max);

		hex_inverter_result res{};
		res.Y1 = inverter_single(A1);
		res.Y2 = inverter_single(A2);
		res.Y3 = inverter_single(A3);
		res.Y4 = inverter_single(A4);
		res.Y5 = inverter_single(A5);
		res.Y6 = inverter_single(A6);
		return res;
	}
	*/


}