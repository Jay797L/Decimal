#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 1;
  if (dst != NULL) {
    *dst = 0;
    int exp = scale(src);
    while (exp != 0) {
      s21_truncate(src, &src);
      exp--;
    }
    if (src.bits[1] == 0 && src.bits[2] == 0) {
      status = 0;
      for (int i = 0; i < 32; i++) {
        if (s21_get_bit(src, i)) {
          *dst += pow(2, i);
        }
      }
      if (sign(src)) *dst *= (-1);
    }
  }
  return status;
}  // COMPLETED