#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 0;
  int scale_value = scale(value);
  if (scale_value == 0) {
    *result = value;
  } else if (scale_value >= 0 && scale_value <= 28) {
    s21_decimal temp = {{0, 0, 0, 0}};
    s21_decimal temp1 = {{0, 0, 0, 0}};
    s21_truncate(value, &temp);
    s21_sub(value, temp, &temp1);
    s21_decimal half = {{5, 0, 0, 0}};
    scale_input(&half, 1);
    scale_input(&temp1, scale(value));
    sign_input(&temp1, 0);
    s21_decimal one = {{1, 0, 0, 0}};
    if (s21_is_greater_or_equal(temp1, half)) {
      sign_input(&one, sign(value));
      s21_add(temp, one, &temp);
    }
    *result = temp;
  } else {
    status = 1;
  }
  return status;
}