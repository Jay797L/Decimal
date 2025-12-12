#include "s21_decimal.h"

int scale(s21_decimal num) {
  bit_3 a;
  a.i = (int)num.bits[3];
  return a.opt.scale;
}
// COMPLETED

int sign(s21_decimal num) {
  bit_3 a;
  a.i = (int)num.bits[3];
  return a.opt.sign;
}
// COMPLETED

void scale_input(s21_decimal *num, int value) {
  bit_3 a;
  a.i = (int)num->bits[3];
  a.opt.scale = value;
  num->bits[3] = a.i;
}
// COMPLETED

void sign_input(s21_decimal *num, int value) {
  bit_3 a;
  a.i = (int)num->bits[3];
  a.opt.sign = value;
  num->bits[3] = a.i;
}
// COMPLETED

int check_last_bits(s21_decimal num) {
  int fail = 0;
  unsigned int mask = CHECK;
  for (int i = 0; i < 32; i++) {
    if ((num.bits[3] & mask) != 0) fail = 1;
    mask >>= 1;
  }
  return fail;
}
// COMPLETED

int normalisation(s21_decimal num_1, s21_decimal num_2, big_decimal *big_num_1,
                  big_decimal *big_num_2) {
  big_nuulic(big_num_1);
  big_nuulic(big_num_2);
  int error = 0;
  from_decimal_to_big(num_1, big_num_1);
  from_decimal_to_big(num_2, big_num_2);
  big_equal_scale(big_num_1, big_num_2);
  if (big_num_1->scale > 96) error = 1;
  return error;
}
// COMPLETED

void big_equal_scale(
    big_decimal *value1,
    big_decimal *value2) {  // приравнивает scale у двух big_decimal
  while (value1->scale != value2->scale) {
    while (value1->scale > value2->scale) {
      mul_10(value2);
      value2->scale += (uint8_t)1;
    }
    while (value2->scale > value1->scale) {
      mul_10(value1);
      value1->scale += 1;
    }
  }
}

int big_decimal_to_decimal(big_decimal big_result, s21_decimal *result) {
  big_decimal value = big_result;
  nuulic(result);
  int exp = (int)value.scale;
  int res = 0;
  if (check_bigger_bit(value) != 0 || exp > 28) {
    while (big_result.scale > 28) {
      res = big_bank_round(&value);
    }
    if (check_bigger_bit(value) != 0) {
      while (check_bigger_bit(value) != 0 && value.scale > 28) {
        res = big_bank_round(&value);
      }
      if (check_bigger_bit(value) != 0 && value.scale == 0) {
        if (value.sign) {
          res = 2;
        } else {
          res = 1;
        }
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    result->bits[i] = big_result.bits[i];
  }
  scale_input(result, (int)big_result.scale);
  sign_input(result, (int)big_result.sign);
  return res;
}
// Переводит big_decimal в s21_decimal
// При помощи check_bigger_bit проводится проверка на то что big_decimal
// вмещается В случае если не вмещается, все 3 бита decimal заполняются
// единицами и функция возвращает 1 Если возможно округление - округлить

int big_bank_round(big_decimal *value) {
  int status = 0;
  big_decimal temp = *value;
  big_decimal half = {{5, 0, 0, 0, 0, 0, 0}, 1, 0};
  big_decimal one = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  int exp = value->scale;
  while (exp != 0) {
    mod(temp, &temp);
    exp--;
  }
  big_decimal drobnaya_chastb = {0};
  big_decimal temp1 = temp;
  big_equal_scale(&temp, value);
  abs_sub(*value, temp, &drobnaya_chastb);
  drobnaya_chastb.scale = value->scale;
  big_equal_scale(&drobnaya_chastb, &half);
  // это спецификация функции compare_mantissa
  //  1 при num1 > num2
  //  0 при num1 == num2
  //  -1 при num 1 < num2
  //  В функцию заходят числа с уже равными значениями scale и отброшенными
  //  знаками.
  if (compare_mantisa(drobnaya_chastb, half) == 0) {
    if (!s21_is_even(temp)) {
      abs_add(temp1, one, &temp1);
    }
  } else if (compare_mantisa(drobnaya_chastb, half) == 1) {
    abs_add(temp1, one, &temp1);
  }
  *value = temp1;
  return status;
}

int mod_ten(big_decimal value) {
  int res = -1;
  big_decimal div = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};  // 123.456
  big_decimal temp = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};  // 12345.6
  if (compare_mantisa(value, div) != -1) {
    abs_div(value, div, &temp);
    printf("%d %d\n", temp.bits[0], temp.scale);
    abs_sub(temp, value, &temp);
  }

  res = temp.bits[0];
  return res;
}

void mod(big_decimal value_1, big_decimal *result) {
  big_decimal mask = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  big_decimal value_2 = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
  int scale = value_1.scale;
  big_nuulic(result);
  for (int i = 223 - max_bit(value_2); i >= 0; i--) {
    if (compare_mantisa(value_1, big_shift_left(value_2, i)) > -1) {
      abs_sub(value_1, big_shift_left(value_2, i), &value_1);
      abs_add(*result, big_shift_left(mask, i), result);
    }
  }
  result->scale = scale;
  result->scale--;
}

void from_decimal_to_big(s21_decimal value, big_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  result->scale = scale(value);
  result->sign = sign(value);
}

int check_bigger_bit(big_decimal val) {
  int res = 0;
  for (int i = 3; i < 7; i++) {
    for (int j = 0; j < 32; j++) {
      if (big_get_bit(val, i * 32 + j)) res = 1;
    }
  }
  return res;
}
// test

int abs_add(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  int or, xor, buf = 0, and, res;
  big_nuulic(result);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 32; j++) {
      res = 0;
      int mask = 1;
      if (buf != 0) {
        buf = 1;
        buf <<= j;
      }
      mask <<= j;
      or = (value_1.bits[i] | value_2.bits[i] | buf) & mask;
      and = (value_1.bits[i] & value_2.bits[i] & buf) & mask;
      xor = ((value_1.bits[i] ^ value_2.bits[i] ^ buf) & mask) & (~and);
      buf = (xor != or);
      res = (and | xor);
      result->bits[i] = result->bits[i] | res;
    }
  }
  result->scale = value_1.scale;
  return (buf != 0);  // Возвращает 1 если число не вместилось
}
// COMPLETED

void abs_sub(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  int xor, and1, and2, res;
  big_nuulic(result);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 32; j++) {
      res = 0;
      int mask = 1;
      mask <<= j;
      xor = (value_1.bits[i] ^ value_2.bits[i]) & mask;
      and1 = (value_1.bits[i]) & mask;
      and2 = (value_2.bits[i]) & mask;
      if (xor == 0) res = 0;
      if ((xor != 0) && (and1 != 0)) res = mask;
      if ((xor != 0) && (and2 != 0)) {
        res = mask;
        rent(&value_1, i, j);
      }
      result->bits[i] = result->bits[i] | res;
    }
  }
  result->scale = value_1.scale;
}
// COMPLETED

void abs_mul(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  big_nuulic(result);
  for (int i = 0; i < 224; i++) {
    if (big_get_bit(value_1, i))
      abs_add(*result, big_shift_left(value_2, i), result);
  }
  result->scale = value_1.scale + value_2.scale;
}
// COMPLETED

void abs_div(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  big_decimal mask = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  int scale = 0;
  big_nuulic(result);
  while ((is_big_zero(value_1) == 0) && (scale < 29)) {
    for (int i = 223 - max_bit(value_2); i >= 0; i--) {
      if (compare_mantisa(value_1, big_shift_left(value_2, i)) > -1) {
        abs_sub(value_1, big_shift_left(value_2, i), &value_1);
        abs_add(*result, big_shift_left(mask, i), result);
      }
    }
    result->scale = scale;
    if (compare_mantisa(value_1, value_2) < 0 && (is_big_zero(value_1) == 0) &&
        ((big_get_bit(*result, 223) == 0) && (big_get_bit(*result, 222) == 0) &&
         (big_get_bit(*result, 221) == 0)) &&
        (scale < 28)) {
      mul_10(&value_1);
      mul_10(result);
      scale += 1;
    } else
      return;
  }
}

void cel_abs_ten(big_decimal value_1, big_decimal *result) {  //
  big_decimal mask = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  big_decimal value_2 = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
  big_nuulic(result);
  for (int i = 223 - max_bit(value_2); i >= 0; i--) {
    if (compare_mantisa(value_1, big_shift_left(value_2, i)) > -1) {
      abs_sub(value_1, big_shift_left(value_2, i), &value_1);
      abs_add(*result, big_shift_left(mask, i), result);
    }
  }
}

int is_big_zero(big_decimal value) {
  int res = 1;
  for (int i = 0; i < 223; i++) {
    if (big_get_bit(value, i)) {
      res = 0;
      break;
    }
  }
  return res;
}

void rent(big_decimal *value, int i, int j) {
  for (; i < 7; i++) {
    for (; j < 32; j++) {
      int mask = 1;
      mask <<= j;
      if ((value->bits[i] & mask) == 0) {
        value->bits[i] = (value->bits[i] | mask);
      } else {
        value->bits[i] = (value->bits[i] & ~mask);
        return;
      }
    }
    j = 0;
  }
}
// COMPLETED

void nuulic(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}
// COMPLETED

void big_nuulic(big_decimal *value) {
  for (int i = 0; i < 7; i++) {
    value->bits[i] = 0;
  }
  value->scale = 0;
  value->sign = 0;
}
// COMPLETED

int s21_get_bit(s21_decimal num, int index) {
  if (index < 0 || index > 95)
    return -1;  // проверка на корректность заданного числа
  int res;
  res = num.bits[index / 32] & (1 << index % 32);
  return (res != 0);
}
// COMPLETED

int big_get_bit(big_decimal num, int index) {
  if (index < 0 || index > 223)
    return -1;  // проверка на корректность заданного числа
  int res;
  res = num.bits[index / 32] & (1 << (index % 32));
  return (res != 0);
}
// COMPLETED

void s21_set_bit(s21_decimal *num, int index, int value) {
  if (index >= 0 && index < 96) {
    if (value == 0) {
      num->bits[index / 32] &= ~(1 << (index % 32));
    } else if (value == 1) {
      num->bits[index / 32] |= (1 << (index % 32));
    }
  }
}
// COMPLETED

void big_set_bit(big_decimal *num, int index, int value) {
  if (index >= 0 && index < 224) {
    if (value == 0) {
      num->bits[index / 32] &= ~(1 << (index % 32));
    } else if (value == 1) {
      num->bits[index / 32] |= (1 << (index % 32));
    }
  }
}
// COMPLETED

int compare_mantisa(big_decimal num1, big_decimal num2) {
  // сравнение мантисс для большого децимала. Должен выдавать:
  //  1 при num1 > num2
  //  0 при num1 == num2
  //  -1 при num 1 < num2
  //  В функцию заходят числа с уже равными значениями scale и отброшенными
  //  знаками.
  int res = 0, size = 224;
  for (int i = size, flag = 1; flag && i >= 0; i--) {
    if (big_get_bit(num1, i) > big_get_bit(num2, i)) {
      res = 1;
      flag = 0;
    } else if (big_get_bit(num1, i) < big_get_bit(num2, i)) {
      res = -1;
      flag = 0;
    }
  }
  return res;
}
// COMPLETED

void mul_10(big_decimal *val) {
  uint8_t exp = val->scale;
  big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
  abs_mul(*val, ten, val);
  val->scale = exp;
}
// COMPLETED

big_decimal big_shift_left(big_decimal value, int shift) {
  big_decimal res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  for (int i = 0; i + shift < 224; i++) {
    big_set_bit(&res, i + shift, big_get_bit(value, i));
  }
  return res;
}
// COMPLETED

int last_num(s21_decimal val) {
  int res = 0;
  int num[4] = {2, 4, 8, 6};
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(val, i)) {
      if (i == 0)
        res += 1;
      else
        res += num[(i - 1) % 4];
    }
  }

  return res;
}
// test

int max_bit(big_decimal value) {
  for (int i = 223; i >= 0; i--) {
    if (big_get_bit(value, i)) {
      return i;
    }
  }
  return 0;
}

int s21_is_even(big_decimal value) {  //
  return (value.bits[0] & 1) != 1;
}

int s21_get_exp_from_str(char *src) {
  int result = 0;
  char *temp = src;
  while (*temp) {
    if (*temp == 'E') {
      temp++;
      result = strtol(temp, NULL, 10);
      break;
    }
    temp++;
  }
  return result;
}

s21_decimal s21_float_str_to_decimal(char *fl) {
  int dig_count = 6;
  s21_decimal res = {0};
  char *temp = fl;
  int exp = s21_get_exp_from_str(fl);
  while (*temp) {
    if (*temp == '.') {
      temp++;
      continue;
    } else if (*temp >= '0' && *temp <= '9') {
      s21_decimal t = {{0, 0, 0, 0}};
      s21_mul(s21_get_from_char(*temp), s21_get_pow_ten(dig_count), &t);
      s21_add(res, t, &res);
      dig_count--;
      temp++;
    } else {
      break;
    }
  }
  exp -= 6;
  if (exp > 0) {
    s21_mul(res, s21_get_pow_ten(exp), &res);
  } else if (exp < 0) {
    if (exp < -28) {
      s21_div(res, s21_get_pow_ten(28), &res);
      exp += 28;
    }
    s21_div(res, s21_get_pow_ten(-exp), &res);
  }
  return res;
}

s21_decimal s21_get_from_char(char src) {
  s21_decimal result = {0};
  int value = src - '0';
  s21_from_int_to_decimal(value, &result);
  return result;
}

s21_decimal s21_get_pow_ten(int count) { return ten_pows[count]; }

int s21_is_zero(s21_decimal src) {
  s21_decimal zero = {{0}};
  int res = 0;
  if (s21_is_equal(src, zero)) {
    res = 1;
  }
  return res;
}

int big_is_zero(big_decimal src) {
  int res = 1;
  for (int i = 0; i < 7; i++) {
    if (src.bits[0] != 0) {
      res = 0;
    }
  }

  return res;
}

// void print_Big_decimal_matrix(big_decimal result) {
//   printf("\nBig Decimal: %d %d %d\n", result.bits[0], result.bits[1],
//          result.bits[2]);
//   for (int i = 0; i < 7; i++) {
//     for (int j = 0; j < 32; j++) {
//       if (j % 8 == 0) printf(" ");
//       printf("%d", big_get_bit(result, i * 32 + j));
//     }
//     printf("\n");
//   }
//   printf("scale %c %d\n", result.sign == 0 ? '+' : '-', result.scale);
//   printf("\n");
// }