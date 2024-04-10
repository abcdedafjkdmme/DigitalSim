#include "pch.h"
#include "74LS_IC/logic_gates.h"
#include "74LS_IC/sequential_gates.h"

TEST(s_74LS, nand_gate) {
	auto A_inputs = { 5,0,0,0 };
	auto B_inputs = { 0,0,0,0 };
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_two_input_nand_gate(A_inputs, B_inputs).Y[0]), 1);
}

TEST(s_74LS, and_gate) {
	auto A_inputs = { 5,0,0,0 };
	auto B_inputs = { 0,0,0,0 };
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_two_input_and_gate(A_inputs, B_inputs).Y[0]), 0);
}

TEST(s_74LS, nor_gate) {
	auto A_inputs = { 5,0,0,0 };
	auto B_inputs = { 0,0,0,0 };
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_two_input_nor_gate(A_inputs, B_inputs).Y[0]), 0);
}

TEST(s_74LS, or_gate) {
	auto A_inputs = { 5,0,0,0 };
	auto B_inputs = { 0,0,0,0 };
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_two_input_or_gate(A_inputs, B_inputs).Y[0]), 1);
}
TEST(s_74LS, not_gate) {
	auto A_inputs = { 5,0,0,0 };
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_single_input_not_gate(A_inputs).Y[0]), 0);
}

TEST(s_74LS, d_flip_flop) {
	s_74LS::multi_d_flip_flop_inputs<2> input{};
	s_74LS::multi_flip_flop_outputs<2> output{};

	input = { .PRE_inv = {0,5}, .CLR_inv = {5,5} };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 0);

	input = { .PRE_inv = {5,5}, .CLR_inv = {0,5}, .CLK = {0}, };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	input = { .PRE_inv = {0,5}, .CLR_inv = {0,5}, .CLK = {0}, };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .D = {5} };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 0);


	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .D = {0} };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	volt prev_Q = output.Q[0];
	volt prev_Q_inv = output.Q_inv[0];
	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {0}, .D = {1000} };
	s_74LS::dual_d_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), s_74LS::volt_to_bool(prev_Q));
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), s_74LS::volt_to_bool(prev_Q_inv));

}

TEST(s_74LS, jk_flip_flop) {
	s_74LS::multi_jk_flip_flop_inputs<2> input{};
	s_74LS::multi_flip_flop_outputs<2> output{};


	input = { .PRE_inv = {0,5}, .CLR_inv = {5,5} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 0);

	input = { .PRE_inv = {5,5}, .CLR_inv = {0,5}, .CLK = {0}, .J = {}, .K = {} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	input = { .PRE_inv = {0,5}, .CLR_inv = {0,5}, .CLK = {0}, .J = {}, .K = {} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .J = {5}, .K = {0} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 0);


	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .J = {0}, .K = {5} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);

	volt prev_Q = output.Q[0];
	volt prev_Q_inv = output.Q_inv[0];
	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .J = {0}, .K = {0} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), s_74LS::volt_to_bool(prev_Q));
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), s_74LS::volt_to_bool(prev_Q_inv));

	prev_Q = output.Q[0];
	prev_Q_inv = output.Q_inv[0];
	input = { .PRE_inv = {5,5}, .CLR_inv = {5,5}, .CLK = {5}, .J = {5}, .K = {5} };
	s_74LS::dual_jk_flip_flop(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), !s_74LS::volt_to_bool(prev_Q));
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), !s_74LS::volt_to_bool(prev_Q_inv));
}

TEST(s_74LS, quad_latch) {
	s_74LS::multi_latch_inputs<4> input{};
	s_74LS::multi_flip_flop_outputs<4> output{};

	input = { .EN = {5}, .D = {0} };
	s_74LS::quad_latch(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 1);


	input = { .EN = {5}, .D = {5} };
	s_74LS::quad_latch(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), 0);

	volt prev_Q = output.Q[0];
	volt prev_Q_inv = output.Q_inv[0];
	input = { .EN = {0}, .D = {5} };
	s_74LS::quad_latch(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), s_74LS::volt_to_bool(prev_Q));
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q_inv[0]), s_74LS::volt_to_bool(prev_Q_inv));
}

TEST(s_74LS, four_bit_counter) {
	s_74LS::counter_inputs<4> input{.EN = 5, .CLR_inv = 5, .CLK = 5};
	s_74LS::counter_outputs<4> output{};

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);



	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);



	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 1);

	s_74LS::four_bit_counter(input, output);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[0]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[1]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[2]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.Q[3]), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(output.ripple_carry), 1);
}