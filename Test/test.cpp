#include "pch.h"
#include "74LS_logic_gates.h"

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

//TEST(s_74LS, d_flip_flop) {
//	s_74LS::multi_d_flip_flop_inputs<2> input{};
//	input.PRE_inv = {};
//	s_74LS::dual_d_flip_flop()
//}


/* 
TEST(s_74LS, d_flip_flop) {
	s_74LS::dual_d_flip_flop_result res{};

	s_74LS::dual_d_flip_flop(5, 0, 0, 5, 0, 0, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), 0);

	s_74LS::dual_d_flip_flop(5, 0, 0, 5, 0, 0, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), 0);

	s_74LS::dual_d_flip_flop(5, 0, 0, 0, 0, 0, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), 1);

	s_74LS::dual_d_flip_flop(5, 0, 5, 5, 5, 0, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), 1);

	s_74LS::dual_d_flip_flop(5, 0, 5, 5, 5, 5, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), 0);

	bool prev_Q1 = s_74LS::volt_to_bool(res.Q1);
	bool prev_Q1_inv = s_74LS::volt_to_bool(res.Q1_inv);

	s_74LS::dual_d_flip_flop(5, 0, 5, 5, 0, 5, 5, 5, 0, 0, res);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1), prev_Q1);
	EXPECT_EQ(s_74LS::volt_to_bool(res.Q1_inv), prev_Q1_inv);


}
TEST(s_74LS, nor_gate) {
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_nor_gate(5, 0, 0, 0, 0, 0, 0, 0, 0, 0).Y1), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_nor_gate(5, 0, 0, 0, 5, 0, 0, 0, 0, 0).Y2), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_nor_gate(5, 0, 0, 0, 0, 0, 0, 5, 0, 0).Y3), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_nor_gate(5, 0, 0, 0, 0, 5, 0, 0, 5, 5).Y4), 0);
}

TEST(s_74LS, and_gate) {
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_and_gate(5, 0, 0, 0, 0, 0, 0, 0, 0, 0).Y1), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_and_gate(5, 0, 0, 0, 5, 0, 0, 0, 0, 0).Y2), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_and_gate(5, 0, 0, 0, 0, 0, 0, 5, 0, 0).Y3), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_and_gate(5, 0, 0, 0, 0, 5, 0, 0, 5, 5).Y4), 1);
}

TEST(s_74LS, or_gate) {
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_or_gate(5, 0, 0, 0, 0, 0, 0, 0, 0, 0).Y1), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_or_gate(5, 0, 0, 0, 5, 0, 0, 0, 0, 0).Y2), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_or_gate(5, 0, 0, 0, 0, 0, 0, 5, 0, 0).Y3), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_or_gate(5, 0, 0, 0, 0, 5, 0, 0, 5, 5).Y4), 1);
}


TEST(s_74LS, xor_gate) {
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_xor_gate(5, 0, 0, 0, 0, 0, 0, 0, 0, 0).Y1), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_xor_gate(5, 0, 0, 0, 5, 0, 0, 0, 0, 0).Y2), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_xor_gate(5, 0, 0, 0, 0, 0, 0, 5, 0, 0).Y3), 1);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::quad_xor_gate(5, 0, 0, 0, 0, 5, 0, 0, 5, 5).Y4), 0);
}

TEST(s_74LS, hex_inverter) {
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::hex_inverter(5, 0, 5, 0, 0, 0, 0, 0).Y1), 0);
	EXPECT_EQ(s_74LS::volt_to_bool(s_74LS::hex_inverter(5, 0, 0, 0, 5, 0, 0, 0).Y2), 1);
}
*/