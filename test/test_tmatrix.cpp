#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> v(4);
	TDynamicMatrix<int> v2(v);
	EXPECT_EQ(v, v2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> v(4);
	TDynamicMatrix<int> v2(v);
	v2[0][0] = 1;
	EXPECT_NE(v, v2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(4);
	v[0][0] = 9;

	EXPECT_EQ(9, v[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v[-4][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v[8][0]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(5);
	EXPECT_EQ(true, v == v);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(5);
	v1[1][0] = 3;
	EXPECT_EQ(false, v1 == v2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	v1 = v2;
	v1[5][0] = 3;
	EXPECT_EQ(3, v1[5][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	EXPECT_EQ(false, v1 == v2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(v1);
	EXPECT_EQ(true, v1 == v2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(5);
	EXPECT_EQ(true, v == v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	EXPECT_EQ(false, v1 == v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(2);
	v2[0][0] = 2;	v2[0][1] = 2;
	v2[1][0] = 2;	v2[1][1] = 2;
	v1[0][0] = 1;	v1[0][1] = 1;
	v1[1][0] = 1;	v1[1][1] = 1;
	EXPECT_EQ(v1 + v1, v2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(4);
	ASSERT_ANY_THROW(v1 + v2);
}


TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(2);
	v2[0][0] = 2;	v2[0][1] = 2;
	v2[1][0] = 2;	v2[1][1] = 2;
	v1[0][0] = 1;	v1[0][1] = 1;
	v1[1][0] = 1;	v1[1][1] = 1;
	EXPECT_EQ(v2 - v1, v1);
}

//
TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(2);
	TDynamicMatrix<int> v3(2);
	v2[0][0] = 2;	v2[0][1] = 3;
	v2[1][0] = 4;	v2[1][1] = -1;
	v1[0][0] = 1;	v1[0][1] = 0;
	v1[1][0] = 5;	v1[1][1] = -2;
	v3[0][0] = 17;	v3[0][1] = -6;
	v3[1][0] = -1;	v3[1][1] = 2;
	EXPECT_EQ(v2 * v1, v3);
}

//
TEST(TDynamicMatrix, can_divaide_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(2);
	TDynamicMatrix<int> v3(2);
	v2[0][0] = 1;	v2[0][1] = 2;
	v2[1][0] = 3;	v2[1][1] = 4;
	v1[0][0] = 1;	v1[0][1] = 5;
	v1[1][0] = 0;	v1[1][1] = -2;

	v3[0][0] = 11;	v3[0][1] = -4;
	v3[1][0] = 23;	v3[1][1] = -8;
	EXPECT_EQ(v2/v1, v3);
}


TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v1(2);
	TDynamicMatrix<int> v2(3);

	ASSERT_ANY_THROW(v2 - v1);
}

