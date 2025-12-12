#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, sign_1, sign_2;
  sign_1 = sign(value_1);
  sign_2 = sign(value_2);
  big_decimal big_value_1, big_value_2;
  normalisation(value_1, value_2, &big_value_1, &big_value_2);

  if (sign_1 == sign_2) {
    if (sign_1 == 0) {
      res = (compare_mantisa(big_value_1, big_value_2) > 0);
    } else {
      res = (compare_mantisa(big_value_1, big_value_2) < 0);
    }
  } else
    res = (sign_1 == 0 ? 1 : 0);
  return res;
}