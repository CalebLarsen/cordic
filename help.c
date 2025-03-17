#include <stdio.h>
#include <math.h>
#include "fixed.h"

int main() {
  const int iters = 40;
  // K constant
  double k = 1.0;
  for (int i = 0; i < iters; i++){
    k *= 1.0 / (sqrt(1 + pow(2.0, (-2.0 * i))));
  }
  printf("k:\n\t.quad 0x%0llx\n", to_fixed(k));
  // arc_tan Look up table
  double d;
  printf("atan_lut:\n");
  for (int i = 0; i < iters; i++){
    d = atan2(1.0, pow(2.0, i));
    printf("\t.quad 0x%0llx\n", to_fixed(d));
  }
}
