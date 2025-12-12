#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  // перевод в int проверка на знак
  int status = 1;
  if (result != NULL) {
    int exp = scale(value);
    if (exp >= 0) {
      s21_truncate(value, result);
      if (sign(value) == 1) {
        s21_decimal one = {{1, 0, 0, 0}};
        sign_input(result, 1);
        s21_sub(*result, one, result);
      }
    }
    status = 0;
  }
  return status;
}