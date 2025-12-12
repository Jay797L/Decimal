#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, sign_1, sign_2;
  sign_1 = sign(value_1);
  sign_2 = sign(value_2);
  big_decimal big_value_1, big_value_2;
  normalisation(value_1, value_2, &big_value_1, &big_value_2);

  if ((sign_1 == sign_2) ||
      (big_is_zero(big_value_1) && big_is_zero(big_value_2))) {
    res = (compare_mantisa(big_value_1, big_value_2) != 0);
  } else
    res = 1;
  return res;
}