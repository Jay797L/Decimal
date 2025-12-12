#include <assert.h>

#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_zero(value_2)) return 3;
  int res = 1;
  res = 0;
  int sign_1 = 0, sign_2 = 0;
  big_decimal big_value_1, big_value_2, big_result;
  nuulic(result);
  normalisation(value_1, value_2, &big_value_1, &big_value_2);
  sign_1 = sign(value_1);
  sign_2 = sign(value_2);
  sign_input(&value_1, 0);
  sign_input(&value_2, 0);
  abs_div(big_value_1, big_value_2, &big_result);
  res = big_decimal_to_decimal(big_result, result);
  if (sign_1 == sign_2) sign_input(result, 0);
  if (sign_1 != sign_2) sign_input(result, 1);
  return res;
}
