#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 1;
  // проверка на скале, после деления зануляем скалу
  // нам нужно обрезать всю дробную часть, то есть занулить всю экспоненту,
  // кроме знака
  if (scale(value) == 0) {
    *result = value;
    status = 0;
  } else {
    int exp = scale(value);
    big_decimal temp = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    // big_decimal res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    from_decimal_to_big(value, &temp);
    while (exp != 0) {
      mod(temp, &temp);
      exp--;
    }
    big_decimal_to_decimal(temp, result);
    if (sign(value)) {
      sign_input(result, 1);
    }
    status = 0;
  }
  return status;
}  // COMPLETED