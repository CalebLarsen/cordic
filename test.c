#include <stdio.h>
#include <string.h>
#include "fixed.h"

// 1 == Pass
// 0 == Fail

int test_exp_1(){
  double half = 0.5;
  i64 expected = -1;
  i64 got = get_exponent(half);
  if (got != expected){
    printf("test_exp_1: Line %d\n", __LINE__);
    printf("\tError: Got != Expected for 0.5\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}
int test_exp_2(){
  double one = 1.0;
  i64 expected = 0;
  i64 got = get_exponent(one);
  if (got != expected){
    printf("test_exp_2: Line %d\n", __LINE__);
    printf("\tError: Got != Expected for 1.0\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}
int test_exp_3(){
  double zero = 0.0;
  i64 expected = -1023;
  i64 got = get_exponent(zero);
  if (got != expected){
    printf("test_exp_3: Line %d\n", __LINE__);
    printf("\tError: Got != Expected for 0.0\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}
int test_exp_4(){
  double eight = 0.125;
  i64 expected = -3;
  i64 got = get_exponent(eight);
  if (got != expected){
    printf("test_exp_4: Line %d\n", __LINE__);
    printf("\tError: Got != Expected for 0.125\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fixed_1(){
  double half = 0.5;
  Fixed expected = 0x1000000000000000;
  Fixed got = to_fixed(half);
  if (got != expected){
    printf("test_fixed_1: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0.5\n\tExpected: 0x%016llx\n\t     Got: 0x%016llx\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fixed_2(){
  double one = 1.0;
  Fixed expected = 0x2000000000000000;
  Fixed got = to_fixed(one);
  if (got != expected){
    printf("test_fixed_2: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 1.0\n\tExpected: 0x%016llx\n\t     Got: 0x%016llx\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fixed_3(){
  double zero = 0.0;
  Fixed expected = 0x0000000000000000;
  Fixed got = to_fixed(zero);
  if (got != expected){
    printf("test_fixed_3: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0.0\n\tExpected: 0x%016llx\n\t     Got: 0x%016llx\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fixed_4(){
  double eight = 0.125;
  Fixed expected = 0x0400000000000000;
  Fixed got = to_fixed(eight);
  if (got != expected){
    printf("test_fixed_4: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0.125\n\tExpected: 0x%016llx\n\t     Got: 0x%016llx\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fixed_5(){
  double smol = 0.000030517578125;
  Fixed expected = 0x0000400000000000;
  Fixed got = to_fixed(smol);
  if (got != expected){
    printf("test_fixed_5: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0.000030517578125\n\tExpected: 0x%016llx\n\t     Got: 0x%016llx\n", expected, got);
    return 0;
  }
  return 1;
}

int test_from_1(){
  Fixed in = 0x1000000000000000;
  double expected = 0.5;
  double got = from_fixed(in);
  if (got != expected){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &expected, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Fexp: %lld\n", fixed_exponent(in));
    printf("Error: Got != Expected for 0x%016llx\n\tExpected: %f (0x%016llx) (Exp: %lld)\n\t     Got: %f (0x%016llx) (Exp: %lld)\n", in, expected, fx_exp, get_exponent(expected),got, fx_got, get_exponent(got));    
    return 0;
  }
  return 1;
}

int test_from_2(){
  Fixed in = 0x2000000000000000;
  double expected = 1.0;
  double got = from_fixed(in);
  if (got != expected){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &expected, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for 0x%016llx\n\tExpected: %f (0x%016llx) (Exp: %lld)\n\t     Got: %f (0x%016llx) (Exp: %lld)\n", in, expected, fx_exp, get_exponent(expected),got, fx_got, get_exponent(got));    
    return 0;
  }
  return 1;
}

int test_from_3(){
  Fixed in = 0x0400000000000000;
  double expected = 0.125;
  double got = from_fixed(in);
  if (got != expected){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &expected, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for 0x%016llx\n\tExpected: %f (0x%016llx) (Exp: %lld)\n\t     Got: %f (0x%016llx) (Exp: %lld)\n", in, expected, fx_exp, get_exponent(expected),got, fx_got, get_exponent(got));    
    return 0;
  }
  return 1;
}

int test_from_4(){
  Fixed in = 0x0000000000000000;
  double expected = 0.0;
  double got = from_fixed(in);
  if (got != expected){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &expected, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for 0x%016llx\n\tExpected: %f (0x%016llx) (Exp: %lld)\n\t     Got: %f (0x%016llx) (Exp: %lld)\n", in, expected, fx_exp, get_exponent(expected),got, fx_got, get_exponent(got));    
    return 0;
  }
  return 1;
}

int test_from_5(){
  Fixed in = 0x0800000000000000;
  double expected = 0.25;
  double got = from_fixed(in);
  if (got != expected){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &expected, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for 0x%016llx\n\tExpected: %f (0x%016llx) (Exp: %lld)\n\t     Got: %f (0x%016llx) (Exp: %lld)\n", in, expected, fx_exp, get_exponent(expected),got, fx_got, get_exponent(got));
    return 0;
  }
  return 1;
}

int test_fix_exp_1(){
  Fixed eight = 0x0400000000000000;
  u64 expected = -3 + 1023;
  u64 got = fixed_exponent(eight);
  if (got != expected){
    printf("test_fix_exp_1: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0x0800000000000000\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fix_exp_2(){
  Fixed zero = 0x2000000000000000;
  u64 expected = 0 + 1023;
  u64 got = fixed_exponent(zero);
  if (got != expected){
    printf("test_fix_exp_2: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0x4000000000000000\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}

int test_fix_exp_3(){
  Fixed half = 0x1000000000000000;
  u64 expected = -1 + 1023;
  u64 got = fixed_exponent(half);
  if (got != expected){
    printf("test_fix_exp_3: Line %d\n", __LINE__);
    printf("Error: Got != Expected for 0x2000000000000000\n\tExpected: %lld\n\t     Got: %lld\n", expected, got);
    return 0;
  }
  return 1;
}

int test_round_1(){
  double in = 0.5;
  double got = from_fixed(to_fixed(in));
  if (got != in){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &in, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for %f\n\tExpected: %f (0x%016llx)\n\t     Got: %f (0x%016llx) \n", in, in, fx_exp, got, fx_got);    
    return 0;
  }
  return 1;
}
int test_round_2(){
  double in = 1.5;
  double got = from_fixed(to_fixed(in));
  if (got != in){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &in, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for %f\n\tExpected: %f (0x%016llx)\n\t     Got: %f (0x%016llx) \n", in, in, fx_exp, got, fx_got);    
    return 0;
  }
  return 1;
}

int test_round_3(){
  double in = 0.0;
  double got = from_fixed(to_fixed(in));
  if (got != in){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &in, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for %f\n\tExpected: %f (0x%016llx)\n\t     Got: %f (0x%016llx) \n", in, in, fx_exp, got, fx_got);    
    return 0;
  }
  return 1;
}
int test_round_4(){
  double in = 0.0;
  double got = from_fixed(to_fixed(in));
  if (got != in){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &in, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for %f\n\tExpected: %f (0x%016llx)\n\t     Got: %f (0x%016llx) \n", in, in, fx_exp, got, fx_got);    
    return 0;
  }
  return 1;
}
int test_round_5(){
  double in = 0.3;
  double got = from_fixed(to_fixed(in));
  if (got != in){
    Fixed fx_exp, fx_got;
    memcpy(&fx_exp, &in, sizeof(Fixed));
    memcpy(&fx_got, &got, sizeof(Fixed));
    printf("%s: Line %d\n", __func__, __LINE__);
    printf("Error: Got != Expected for %f\n\tExpected: %f (0x%016llx)\n\t     Got: %f (0x%016llx) \n", in, in, fx_exp, got, fx_got);    
    return 0;
  }
  return 1;
}

int main(){
  printf("\n");
  test_exp_1();
  test_exp_2();
  test_exp_3();
  test_exp_4();
  test_fixed_1();
  test_fixed_2();
  test_fixed_3();
  test_fixed_4();
  test_fixed_5();
  test_from_1();
  test_from_2();
  test_from_3();
  test_from_4();
  test_from_5();
  test_fix_exp_1();
  test_fix_exp_2();
  test_fix_exp_3();
  test_round_1();
  test_round_2();
  test_round_3();
  test_round_4();
  test_round_5();
}
