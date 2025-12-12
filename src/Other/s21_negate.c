#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;

  if (result != NULL) {
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
    sign_input(result, sign(value) ? 0 : 1);
  } else
    status = 1;
  return status;
}  // COMPLETE