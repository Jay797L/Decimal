#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = 1;
  if (dst != NULL) {
    nuulic(dst);
    dst->bits[0] = abs(src);
    sign_input(dst, src < 0);
    status = 0;
  }
  return status;
}  // COMPLETED