#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, sign1, sign2;
  big_decimal big_value_1, big_value_2, big_result;
  nuulic(result);
  normalisation(value_1, value_2, &big_value_1, &big_value_2);
  sign1 = sign(value_1);
  sign2 = sign(value_2);
  sign_input(&value_1, 0);
  sign_input(&value_2, 0);
  if (sign1 == sign2) {
    abs_add(big_value_1, big_value_2, &big_result);
    error = big_decimal_to_decimal(big_result, result);
    sign_input(result, sign1);
  } else if (s21_is_greater(value_1, value_2)) {
    abs_sub(big_value_1, big_value_2, &big_result);
    error = big_decimal_to_decimal(big_result, result);
    sign_input(result, sign1);
  } else {
    abs_sub(big_value_2, big_value_1, &big_result);
    error = big_decimal_to_decimal(big_result, result);
    sign_input(result, sign2);
  }
  if (sign(*result)) error = error * 2;
  return error;
}