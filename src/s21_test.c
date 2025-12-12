#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

// �������������� ���������
START_TEST(test_s21_add_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 8);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 1);
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 1);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 1);  // ������������
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_s21_sub_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_s21_sub_2) {
  s21_decimal a = {{0, 1, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], UINT_MAX);
  ck_assert_uint_eq(result.bits[1], 0);
}
END_TEST

START_TEST(test_s21_sub_3) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], UINT_MAX);
  ck_assert_uint_eq(result.bits[1], UINT_MAX);
  ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_4) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_5) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], UINT_MAX - 1);
  ck_assert_uint_eq(result.bits[1], 1);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);  // ������������
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_div_1) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 5);
}
END_TEST

// C# VERSION:
// using System;

// public class Program
// {
// 	public static void Main()
// 	{
// 		// decimal x = 1;
// 		// decimal y = 3;
// 		decimal x = new decimal(9, 7, 6, false, 0);
// 		decimal y = new decimal(5, 6, 7, false, 0);
// 		decimal r = x/y;
// 		int[] bits = decimal.GetBits(r);
// 		Console.Write(bits[0]);
// 		Console.Write("\n");
// 		Console.Write(bits[1]);
// 		Console.Write("\n");
// 		Console.Write(bits[2]);
// 		Console.Write("\n");
// 		Console.Write(bits[3]);
// 	}
// }

START_TEST(test_s21_div_1_1) {
  s21_decimal a = {{9, 7, 6, 0}};
  s21_decimal b = {{5, 6, 7, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq((int)result.bits[0], -1267494101);
  ck_assert_int_eq((int)result.bits[1], -189642634);
  ck_assert_int_eq((int)result.bits[2], 464658073);
  ck_assert_int_eq((int)result.bits[3], 1835008);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  // ���������, ��� ��������� ������ � 0.333...
  ck_assert_uint_eq(result.bits[0], 89478485);
  ck_assert_uint_eq(result.bits[1], 347537611);
  ck_assert_uint_eq(result.bits[2], 180700362);
  ck_assert_uint_eq(result.bits[3], 1835008);
  ck_assert_uint_eq(scale(result), 28);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 3);  // ������� �� ����
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], UINT_MAX);
  ck_assert_uint_eq(result.bits[1], UINT_MAX);
  ck_assert_uint_eq(result.bits[2], UINT_MAX);
}
END_TEST

// ��������� ���������
START_TEST(test_s21_is_less_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_less(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_less(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_less(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};  // �������������
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_less(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};  // �������������
  int result = s21_is_less(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal a = {{4, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{4, 0, 0, 0}};
  int result = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  int result = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_greater(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_greater(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  int result = s21_is_greater(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal a = {{4, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_equal_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);  // ���� ������ �������������
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  scale_input(&a, 2);
  scale_input(&b, 3);
  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);  // ������ ��������
}
END_TEST

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  int result = s21_is_not_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_not_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0}};
  int result = s21_is_not_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  int result = s21_is_not_equal(a, b);
  ck_assert_int_eq(result, 0);  // ���� ������ �������������
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  scale_input(&a, 1);
  scale_input(&b, 2);
  int result = s21_is_not_equal(a, b);
  ck_assert_int_eq(result, 1);  // ������ ��������
}
END_TEST

// ����������
START_TEST(test_s21_from_int_to_decimal_1) {
  s21_decimal result;
  int status = s21_from_int_to_decimal(123, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(sign(result), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  s21_decimal result;
  int status = s21_from_int_to_decimal(-456, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 456);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  s21_decimal result;
  int status = s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(sign(result), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  s21_decimal result;
  int status = s21_from_int_to_decimal(INT_MAX, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], INT_MAX);
  ck_assert_uint_eq(sign(result), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  s21_decimal result;
  int status = s21_from_int_to_decimal(-2147483647, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 2147483647);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_1) {
  s21_decimal result;
  int status = s21_from_float_to_decimal(123.456f, &result);
  ck_assert_int_eq(status, 0);
  // ��������� ��������������� ��������
  float f;
  s21_from_decimal_to_float(result, &f);
  ck_assert(fabsf(123.456f - f) < 1e-5f);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  s21_decimal result;
  int status = s21_from_float_to_decimal(-789.123f, &result);
  printf("%d %d\n", result.bits[0], scale(result));
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(sign(result), 1);
  float f;
  s21_from_decimal_to_float(result, &f);
  ck_assert(fabsf(-789.123f - f) < 1e-4f);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  s21_decimal result;
  int status = s21_from_float_to_decimal(0.0f, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(sign(result), 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  s21_decimal result;
  int status = s21_from_float_to_decimal(1e-20f, &result);
  ck_assert_int_eq(status, 0);  // ������� ��������� �����
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5) {
  s21_decimal result;
  int status = s21_from_float_to_decimal(1e30f, &result);
  ck_assert_int_eq(status, 1);  // ������� ������� �����
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_1) {
  s21_decimal src;
  s21_from_int_to_decimal(123, &src);
  int result;
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_2) {
  s21_decimal src;
  s21_from_int_to_decimal(-456, &src);
  int result;
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, -456);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_3) {
  s21_decimal src = {{123456, 0, 0, 0}};
  scale_input(&src, 3);  // 123.456
  int result;
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, 123);  // ������� ����� �������������
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_4) {
  s21_decimal src = {{INT_MAX, 0, 0, 0}};
  int result;
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(status, 0);  // ������������
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_5) {
  s21_decimal src = {{0, 0, 0, 0}};
  int result;
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_1) {
  s21_decimal src;
  s21_from_float_to_decimal(123.456f, &src);
  float result;
  int status = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert(fabsf(123.456f - result) < 1e-6f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_2) {
  s21_decimal src;
  s21_from_float_to_decimal(-789.123f, &src);
  float result;
  int status = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert(fabsf(-789.123f - result) < 1e-6f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  float result;
  int status = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_4) {
  s21_decimal src = {{123456, 0, 0, 0}};
  scale_input(&src, 3);  // 123.456
  float result;
  int status = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert(fabsf(123.456f - result) < 1e-6f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_5) {
  s21_decimal src = {{123456, 0, 0, 0x80000000}};  // -123456
  scale_input(&src, 3);                            // -123.456
  float result;
  int status = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(status, 0);
  ck_assert(fabsf(-123.456f - result) < 1e-6f);
}
END_TEST

// ������ �������
START_TEST(test_s21_floor_1) {
  s21_decimal value = {{123456, 0, 0, 0}};
  scale_input(&value, 3);  // 123.456
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(scale(result), 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal value = {{123456, 0, 0, 0x80000000}};  // -123.456
  scale_input(&value, 3);
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 124);
  ck_assert_uint_eq(sign(result), 1);  // -124
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal value = {{0, 0, 0, 0}};
  scale_input(&value, 2);  // 0.00
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(scale(result), 0);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal value = {{999999, 0, 0, 0}};
  scale_input(&value, 3);  // 999.999
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 999);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal value = {{1000, 0, 0, 0}};
  scale_input(&value, 1);  // 100.0
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 100);
}
END_TEST

START_TEST(test_s21_round_1) {
  s21_decimal value = {{123456, 0, 0, 0}};
  scale_input(&value, 3);  // 123.456
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal value = {{123556, 0, 0, 0}};
  scale_input(&value, 3);  // 123.556
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 124);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal value = {{123556, 0, 0, 0x80000000}};  // -123.556
  scale_input(&value, 3);
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 124);
  ck_assert_uint_eq(sign(result), 1);  // -124
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal value = {{0, 0, 0, 0}};
  scale_input(&value, 2);  // 0.00
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal value = {{5, 0, 0, 0}};
  scale_input(&value, 1);  // 0.5
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 1);  // ���������� �����
}
END_TEST

START_TEST(test_s21_truncate_1) {
  s21_decimal value = {{123456, 0, 0, 0}};
  scale_input(&value, 3);  // 123.456
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(scale(result), 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal value = {{123456, 0, 0, 0x80000000}};  // -123.456
  scale_input(&value, 3);
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(sign(result), 1);  // -123
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal value = {{0, 0, 0, 0}};
  scale_input(&value, 2);  // 0.00
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_truncate_4) {
  s21_decimal value = {{999999, 0, 0, 0}};
  scale_input(&value, 3);  // 999.999
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 999);
}
END_TEST

START_TEST(test_s21_truncate_5) {
  s21_decimal value = {{1000, 0, 0, 0}};
  scale_input(&value, 1);  // 100.0
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 100);
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal result;
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value = {{456, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 456);
  ck_assert_uint_eq(sign(result), 0);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(sign(result), 1);  // ���� �������� �������������
}
END_TEST

START_TEST(test_s21_negate_4) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result;
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], UINT_MAX);
  ck_assert_uint_eq(result.bits[1], UINT_MAX);
  ck_assert_uint_eq(result.bits[2], UINT_MAX);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_5) {
  s21_decimal value = {{1, 0, 0, 0}};
  scale_input(&value, 2);  // 0.01
  s21_decimal result;
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(scale(result), 2);
  ck_assert_uint_eq(sign(result), 1);
}
END_TEST
START_TEST(test_big_decimal_operations_1) {
  // ���� ����������� decimal -> big_decimal -> decimal
  s21_decimal original = {{123456, 0, 0, 0}};
  scale_input(&original, 3);
  sign_input(&original, 0);

  big_decimal big;
  from_decimal_to_big(original, &big);

  s21_decimal result;
  int status = big_decimal_to_decimal(big, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], original.bits[0]);
  ck_assert_uint_eq(result.bits[1], original.bits[1]);
  ck_assert_uint_eq(result.bits[2], original.bits[2]);
  ck_assert_uint_eq(result.bits[3], original.bits[3]);
}
END_TEST

START_TEST(test_big_decimal_operations_2) {
  // ���� check_bigger_bit
  big_decimal val = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  int res = check_bigger_bit(val);
  ck_assert_int_eq(res, 0);

  val.bits[3] = 1;  // ������������� ��� � ������� �����
  res = check_bigger_bit(val);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_big_decimal_operations_4) {
  // ���� s21_is_even
  big_decimal even = {{2, 0, 0, 0, 0, 0, 0}, 0, 0};
  big_decimal odd = {{3, 0, 0, 0, 0, 0, 0}, 0, 0};

  ck_assert_int_eq(s21_is_even(even), 1);
  ck_assert_int_eq(s21_is_even(odd), 0);
}
END_TEST

START_TEST(test_big_decimal_operations_5) {
  // ���� max_bit
  big_decimal value = {{0, 0, 1, 0, 0, 0, 0}, 0, 0};  // ��� 64 ����������
  int res = max_bit(value);
  ck_assert_int_eq(res, 64);
}
END_TEST

// ����� ����������� ����� decimal � big_decimal
START_TEST(test_conversion_1) {
  // ����������� ������������� decimal ��������
  s21_decimal max_decimal = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  scale_input(&max_decimal, 0);

  big_decimal big;
  from_decimal_to_big(max_decimal, &big);

  s21_decimal result;
  int status = big_decimal_to_decimal(big, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], max_decimal.bits[0]);
  ck_assert_uint_eq(result.bits[1], max_decimal.bits[1]);
  ck_assert_uint_eq(result.bits[2], max_decimal.bits[2]);
}
END_TEST

START_TEST(test_conversion_2) {
  // ����������� � ���������
  s21_decimal value = {{123456, 0, 0, 0}};
  scale_input(&value, 5);
  sign_input(&value, 1);

  big_decimal big;
  from_decimal_to_big(value, &big);

  ck_assert_uint_eq(big.scale, 5);
  ck_assert_uint_eq(big.sign, 1);
  ck_assert_uint_eq(big.bits[0], 123456);
}
END_TEST

// ����� ������� �������
START_TEST(test_edge_cases_1) {
  // ������������ �������� decimal
  s21_decimal max_val = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal result;

  int status = s21_add(max_val, one, &result);
  ck_assert_int_eq(status, 1);  // ������ ���� ������������
}
END_TEST

START_TEST(test_edge_cases_2) {
  // ����������� �������� (�������������)
  s21_decimal min_val = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  sign_input(&min_val, 1);
  s21_decimal one = {{1, 0, 0, 0}};
  sign_input(&one, 1);
  s21_decimal result;

  int status = s21_add(min_val, one, &result);
  ck_assert_int_eq(status, 2);  // ������ ���� ������������� ������������
}
END_TEST

START_TEST(test_edge_cases_3) {
  // ������� �� ����� ��������� �����
  s21_decimal small = {{1, 0, 0, 0}};
  scale_input(&small, 28);
  s21_decimal large = {{1000000, 0, 0, 0}};
  s21_decimal result;

  int status = s21_div(large, small, &result);
  ck_assert_int_eq(status, 1);  // ������ ���� ������������
}
END_TEST

// ����� ������ �������� NULL ����������
// START_TEST(test_null_pointers_1) {
//   int status = s21_add((s21_decimal){0}, (s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_2) {
//   int status = s21_sub((s21_decimal){0}, (s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_3) {
//   int status = s21_mul((s21_decimal){0}, (s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_4) {
//   int status = s21_div((s21_decimal){0}, (s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_5) {
//   int status = s21_floor((s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_6) {
//   int status = s21_round((s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_7) {
//   int status = s21_truncate((s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// START_TEST(test_null_pointers_8) {
//   int status = s21_negate((s21_decimal){0}, NULL);
//   ck_assert_int_eq(status, 1);
// }
// END_TEST

// ������������� �������� ����������� ����������
// START_TEST(test_bankers_rounding_1) {
//   // 0.5 -> 0 (���������� � �������)
//   s21_decimal value = {{5, 0, 0, 0}};
//   scale_input(&value, 1);
//   s21_decimal result;

//   int status = s21_round(value, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_uint_eq(result.bits[0], 0);
// }
// END_TEST

// START_TEST(test_bankers_rounding_2) {
//   // 1.5 -> 2 (���������� � �������)
//   s21_decimal value = {{15, 0, 0, 0}};
//   scale_input(&value, 1);
//   s21_decimal result;

//   int status = s21_round(value, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_uint_eq(result.bits[0], 2);
// }
// END_TEST

// START_TEST(test_bankers_rounding_3) {
//   // 2.5 -> 2 (���������� � �������)
//   s21_decimal value = {{25, 0, 0, 0}};
//   scale_input(&value, 1);
//   s21_decimal result;

//   int status = s21_round(value, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_uint_eq(result.bits[0], 2);
// }
// END_TEST

// START_TEST(test_bankers_rounding_4) {
//   // 3.5 -> 4 (���������� � �������)
//   s21_decimal value = {{35, 0, 0, 0}};
//   scale_input(&value, 1);
//   s21_decimal result;

//   int status = s21_round(value, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_uint_eq(result.bits[0], 4);
// }
// END_TEST

// START_TEST(test_bankers_rounding_5) {
//   // -0.5 -> 0 (���������� � �������, �������������)
//   s21_decimal value = {{5, 0, 0, 0}};
//   scale_input(&value, 1);
//   sign_input(&value, 1);
//   s21_decimal result;

//   int status = s21_round(value, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_uint_eq(result.bits[0], 0);
//   ck_assert_uint_eq(sign(result), 1);
// }
// END_TEST

// �������� suite � tcase
Suite *decimal_suite(void) {
  Suite *s = suite_create("Decimal");

  // ����������
  TCase *tc_arithmetic = tcase_create("Arithmetic");
  tcase_add_test(tc_arithmetic, test_s21_add_1);
  tcase_add_test(tc_arithmetic, test_s21_add_2);
  tcase_add_test(tc_arithmetic, test_s21_add_3);
  tcase_add_test(tc_arithmetic, test_s21_add_4);
  tcase_add_test(tc_arithmetic, test_s21_add_5);
  tcase_add_test(tc_arithmetic, test_s21_sub_1);
  tcase_add_test(tc_arithmetic, test_s21_sub_2);
  tcase_add_test(tc_arithmetic, test_s21_sub_3);
  tcase_add_test(tc_arithmetic, test_s21_sub_4);
  tcase_add_test(tc_arithmetic, test_s21_sub_5);
  tcase_add_test(tc_arithmetic, test_s21_mul_1);
  tcase_add_test(tc_arithmetic, test_s21_mul_2);
  tcase_add_test(tc_arithmetic, test_s21_mul_3);
  tcase_add_test(tc_arithmetic, test_s21_mul_4);
  tcase_add_test(tc_arithmetic, test_s21_mul_5);
  tcase_add_test(tc_arithmetic, test_s21_div_1);
  tcase_add_test(tc_arithmetic, test_s21_div_1_1);
  tcase_add_test(tc_arithmetic, test_s21_div_2);
  tcase_add_test(tc_arithmetic, test_s21_div_3);
  tcase_add_test(tc_arithmetic, test_s21_div_4);
  tcase_add_test(tc_arithmetic, test_s21_div_5);

  // ���������
  TCase *tc_comparison = tcase_create("Comparison");
  tcase_add_test(tc_comparison, test_s21_is_less_1);
  tcase_add_test(tc_comparison, test_s21_is_less_2);
  tcase_add_test(tc_comparison, test_s21_is_less_3);
  tcase_add_test(tc_comparison, test_s21_is_less_4);
  tcase_add_test(tc_comparison, test_s21_is_less_5);
  tcase_add_test(tc_comparison, test_s21_is_less_or_equal_1);
  tcase_add_test(tc_comparison, test_s21_is_less_or_equal_2);
  tcase_add_test(tc_comparison, test_s21_is_less_or_equal_3);
  tcase_add_test(tc_comparison, test_s21_is_less_or_equal_4);
  tcase_add_test(tc_comparison, test_s21_is_less_or_equal_5);
  tcase_add_test(tc_comparison, test_s21_is_greater_1);
  tcase_add_test(tc_comparison, test_s21_is_greater_2);
  tcase_add_test(tc_comparison, test_s21_is_greater_3);
  tcase_add_test(tc_comparison, test_s21_is_greater_4);
  tcase_add_test(tc_comparison, test_s21_is_greater_5);
  tcase_add_test(tc_comparison, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc_comparison, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc_comparison, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc_comparison, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc_comparison, test_s21_is_greater_or_equal_5);
  tcase_add_test(tc_comparison, test_s21_is_equal_1);
  tcase_add_test(tc_comparison, test_s21_is_equal_2);
  tcase_add_test(tc_comparison, test_s21_is_equal_3);
  tcase_add_test(tc_comparison, test_s21_is_equal_4);
  tcase_add_test(tc_comparison, test_s21_is_equal_5);
  tcase_add_test(tc_comparison, test_s21_is_not_equal_1);
  tcase_add_test(tc_comparison, test_s21_is_not_equal_2);
  tcase_add_test(tc_comparison, test_s21_is_not_equal_3);
  tcase_add_test(tc_comparison, test_s21_is_not_equal_4);
  tcase_add_test(tc_comparison, test_s21_is_not_equal_5);

  // ����������
  TCase *tc_conversion = tcase_create("Conversion");
  tcase_add_test(tc_conversion, test_s21_from_int_to_decimal_1);
  tcase_add_test(tc_conversion, test_s21_from_int_to_decimal_2);
  tcase_add_test(tc_conversion, test_s21_from_int_to_decimal_3);
  tcase_add_test(tc_conversion, test_s21_from_int_to_decimal_4);
  tcase_add_test(tc_conversion, test_s21_from_int_to_decimal_5);
  tcase_add_test(tc_conversion, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc_conversion, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc_conversion, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc_conversion, test_s21_from_float_to_decimal_4);
  tcase_add_test(tc_conversion, test_s21_from_float_to_decimal_5);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_int_1);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_int_2);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_int_3);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_int_4);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_int_5);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_float_1);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_float_2);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_float_3);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_float_4);
  tcase_add_test(tc_conversion, test_s21_from_decimal_to_float_5);

  // ������ �������
  TCase *tc_other = tcase_create("Other");
  tcase_add_test(tc_other, test_s21_floor_1);
  tcase_add_test(tc_other, test_s21_floor_2);
  tcase_add_test(tc_other, test_s21_floor_3);
  tcase_add_test(tc_other, test_s21_floor_4);
  tcase_add_test(tc_other, test_s21_floor_5);
  tcase_add_test(tc_other, test_s21_round_1);
  tcase_add_test(tc_other, test_s21_round_2);
  tcase_add_test(tc_other, test_s21_round_3);
  tcase_add_test(tc_other, test_s21_round_4);
  tcase_add_test(tc_other, test_s21_round_5);
  tcase_add_test(tc_other, test_s21_truncate_1);
  tcase_add_test(tc_other, test_s21_truncate_2);
  tcase_add_test(tc_other, test_s21_truncate_3);
  tcase_add_test(tc_other, test_s21_truncate_4);
  tcase_add_test(tc_other, test_s21_truncate_5);
  tcase_add_test(tc_other, test_s21_negate_1);
  tcase_add_test(tc_other, test_s21_negate_2);
  tcase_add_test(tc_other, test_s21_negate_3);
  tcase_add_test(tc_other, test_s21_negate_4);
  tcase_add_test(tc_other, test_s21_negate_5);

  suite_add_tcase(s, tc_arithmetic);
  // tcase_set_timeout(tc_arithmetic,
  //                   40);  // УСТАНОВИЛ!! время на всю арифметику, потому, что
  //                         // при тестах ругался на  div:2
  suite_add_tcase(s, tc_comparison);
  suite_add_tcase(s, tc_conversion);
  suite_add_tcase(s, tc_other);
  // ����� �����
  TCase *tc_big_decimal = tcase_create("Big Decimal Operations");
  tcase_add_test(tc_big_decimal, test_big_decimal_operations_1);
  tcase_add_test(tc_big_decimal, test_big_decimal_operations_2);
  tcase_add_test(tc_big_decimal, test_big_decimal_operations_4);
  tcase_add_test(tc_big_decimal, test_big_decimal_operations_5);

  TCase *tc_conversion1 = tcase_create("Conversion");
  tcase_add_test(tc_conversion1, test_conversion_1);
  tcase_add_test(tc_conversion1, test_conversion_2);

  TCase *tc_edge_cases = tcase_create("Edge Cases");
  tcase_add_test(tc_edge_cases, test_edge_cases_1);
  tcase_add_test(tc_edge_cases, test_edge_cases_2);
  tcase_add_test(tc_edge_cases, test_edge_cases_3);

  // TCase *tc_null_pointers = tcase_create("Null Pointers");
  // tcase_add_test(tc_null_pointers, test_null_pointers_1);
  // tcase_add_test(tc_null_pointers, test_null_pointers_2);
  // tcase_add_test(tc_null_pointers, test_null_pointers_3);
  // tcase_add_test(tc_null_pointers, test_null_pointers_4);
  // tcase_add_test(tc_null_pointers, test_null_pointers_5);
  // tcase_add_test(tc_null_pointers, test_null_pointers_6);
  // tcase_add_test(tc_null_pointers, test_null_pointers_7);
  // tcase_add_test(tc_null_pointers, test_null_pointers_8);

  // TCase *tc_bankers_rounding = tcase_create("Bankers Rounding");
  // tcase_add_test(tc_bankers_rounding, test_bankers_rounding_1);
  // tcase_add_test(tc_bankers_rounding, test_bankers_rounding_2);
  // tcase_add_test(tc_bankers_rounding, test_bankers_rounding_3);
  // tcase_add_test(tc_bankers_rounding, test_bankers_rounding_4);
  // tcase_add_test(tc_bankers_rounding, test_bankers_rounding_5);

  suite_add_tcase(s, tc_big_decimal);
  suite_add_tcase(s, tc_conversion);
  suite_add_tcase(s, tc_edge_cases);
  // suite_add_tcase(s, tc_null_pointers);
  // suite_add_tcase(s, tc_bankers_rounding);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = decimal_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}