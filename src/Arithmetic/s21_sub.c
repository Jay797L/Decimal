#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 1;
  if (result != NULL) {
    s21_negate(value_2, &value_2);
    error = s21_add(value_1, value_2, result);
  }
  return error;
}  // COMPLETE