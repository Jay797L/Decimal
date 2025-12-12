#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = 1;
  if (dst != NULL) {
    double result = 0.0;
    *dst = 0.0;
    int exp = scale(src);
    int znak = sign(src);
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit(src, i)) {
        result += pow(2.0, i);
      }
    }
    while (exp != 0) {
      result /= 10.0;
      exp--;
    }  // был массив из степеней числа 10
    if (znak) result *= -1.0;
    *dst = result;
    status = 0;
  }

  return status;
}