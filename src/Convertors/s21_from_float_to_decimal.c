#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 0;
  if (dst == NULL) {
    status = 1;
  } else if (src == 0.0) {
    s21_decimal result = {{0, 0, 0, 0}};
    *dst = result;
    if (signbit(src) != 0) {
      sign_input(dst, 1);
    }
  } else if (isnan(src) || isinf(src) || (fabsf(src) > MAX_FLOAT_DECIMAL)) {
    status = 1;
    s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    *dst = result;
    if (signbit(src) != 0) {
      sign_input(dst, 1);
    }
  } else if (fabsf(src) < MIN_FLOAT_DECIMAL) {
    status = 1;
    s21_decimal result = {{0, 0, 0, 0}};
    *dst = result;
  } else {
    s21_decimal result = {{0, 0, 0, 0}};
    char fl[128];
    sprintf(fl, "%.6E", fabsf(src));
    // получаем экспоненту, корректируем ее
    int exp = s21_get_exp_from_str(fl);
    if (exp < -23) {
      int precision = exp + 28;
      sprintf(fl, "%.*E", precision, fabsf(src));
    }
    result = s21_float_str_to_decimal(fl);
    // переводим строку с научной нотацией в decimal
    if (signbit(src) != 0) {  // знак
      sign_input(&result, 1);
    }
    *dst = result;
  }
  return status;
}