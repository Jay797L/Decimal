#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 1;
  if (result != NULL) {
    error = 0;

    int sign_1, sign_2;
    big_decimal big_value_1, big_value_2, big_result;
    nuulic(result);
    normalisation(value_1, value_2, &big_value_1, &big_value_2);
    sign_1 = sign(value_1);
    sign_2 = sign(value_2);
    sign_input(&value_1, 0);
    sign_input(&value_2, 0);

    abs_mul(big_value_1, big_value_2, &big_result);

    error = big_decimal_to_decimal(big_result, result);
    if (sign_1 == sign_2) sign_input(result, 0);
    if (sign_1 != sign_2) sign_input(result, 1);
  }
  return error;
}