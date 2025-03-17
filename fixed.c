#include "fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const u64 SIGN_BIT = 63;
const u64 SIGN_MASK = 0x8000000000000000;
const u64 ALL_BUT_SIGN = 0x7FFFFFFFFFFFFFFF;
const i64 EXPONENT_BIAS = 1023;
const u64 EXPONENT_BIT_WIDTH = 11;
const u64 EXPONENT_START_BIT = 52;
const u64 EXPONENT_MASK = 0x7FF0000000000000;
const u64 MANTISSA_BIT_WIDTH = 52;
const u64 MANTISSA_MASK = 0x000FFFFFFFFFFFFF;

void error(const char* msg){
  printf("%s\n", msg);
  exit(1);
}

u64 get_sign(double d){
  u64 d_bits;
  memcpy(&d_bits, &d, sizeof(u64));
  return d_bits & SIGN_MASK;
}

i64 get_exponent(double d){
  u64 d_bits;
  memcpy(&d_bits, &d, sizeof(u64));
  i64 exp = ((d_bits & EXPONENT_MASK) >> EXPONENT_START_BIT) - EXPONENT_BIAS;
  return exp;
}

u64 get_mantissa(double d){
  u64 d_bits;
  memcpy(&d_bits, &d, sizeof(u64));
  return d_bits & MANTISSA_MASK;
}

Fixed to_fixed(double d){
  u64 sign = get_sign(d);
  i64 exp = get_exponent(d);
  u64 mantissa = get_mantissa(d);
  if (exp == -EXPONENT_BIAS){
    if (mantissa == 0){
      return 0;
    }
    else {
      printf("Subnormal: AAAAAAA\n");
      return -23;
    }
  }
  else if (exp > 1 || exp < -61){
    printf("Bad exponent: %lld\n", exp);
    error("Exponent out of range");
  }
  Fixed fx = sign << SIGN_BIT;
  mantissa |= (u64)0x1 << MANTISSA_BIT_WIDTH;
  if (exp >= -9){
    mantissa <<= exp + 9;
  } else {
    mantissa >>= (-exp) - 9;
  }
  fx |= mantissa;
  return fx;
}

u64 fixed_sign(Fixed fx){
  return fx >> SIGN_BIT;
}

u64 fixed_exponent(Fixed fx){
  u64 fx_expo = fx & ALL_BUT_SIGN;
  if (fx_expo == 0){
    return -1023;
  }
  i64 exponent = 1;
  int bit_index = SIGN_BIT - 1;
  while (1) {
    if (fx_expo >> bit_index) {
      break;
    }
    bit_index -= 1;
    exponent -= 1;
  } 
  exponent += EXPONENT_BIAS;
  return exponent;
}

u64 fixed_mantissa(Fixed fx){
  u64 fx_expo = fx & ALL_BUT_SIGN;
  u64 mantissa;
  u64 mant_mask = 1;
  int bit_index = SIGN_BIT - 1;
  if (fx_expo == 0){
    return 0;
  }
  while (1) {
    if (fx_expo >> bit_index) {
      break;
    }
    bit_index -= 1;
  }
  for (int i = 0; i < bit_index; i++){
    mant_mask = (mant_mask << 1) | 1;
  }
  mantissa = fx & mant_mask;
  return mantissa;
}

double from_fixed(Fixed fx){
  if (fx == 0){
    return 0;
  }
  u64 fx_expo = fx & ALL_BUT_SIGN;
  int bit_index = SIGN_BIT - 1;
  while (bit_index > 0) {
    if (fx_expo >> bit_index) {
      break;
    }
    bit_index -= 1;
  }
  u64 sign = fixed_sign(fx);
  u64 exponent = fixed_exponent(fx);
  u64 mantissa = fixed_mantissa(fx);
  u64 pos_sign = sign << SIGN_BIT;
  u64 pos_exponent = exponent << (EXPONENT_START_BIT);
  u64 pos_mantissa;
  if (bit_index > EXPONENT_START_BIT){
    pos_mantissa = mantissa >> (-EXPONENT_START_BIT + bit_index);
  } else {
    pos_mantissa = mantissa << (EXPONENT_START_BIT - bit_index);
  }
  pos_mantissa &= MANTISSA_MASK;
  u64 final = pos_sign | pos_exponent | pos_mantissa;
  double ret;
  memcpy(&ret, &final, sizeof(double));
  return ret;
}

