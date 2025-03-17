#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fixed.h"

typedef struct {
  double sin;
  double cos;
} Position;

extern Position cordic(double radians);

const int ITERS = 40;
Fixed atan_lut_c[ITERS];

double radians(double degrees){
  return degrees / 360.0 * 2 * M_PI;
}

double correct_angle(double angle, int* flip_cos){
  while (angle > 180){
    angle -= 360;
  }
  while (angle < -180) {
    angle += 360;
  }
  if (angle > 90) {
    angle = 90-(angle-90);
    *flip_cos = 1;
  } else if (angle < -90){
    angle = (-90)-(angle+90);
    *flip_cos = 1;
  }
  angle = radians(angle);
  return angle;
}

void init_lut(){
  double d;
  for (int i = 0; i < ITERS; i++){
    d = atan2(1.0, exp2(i));
    atan_lut_c[i] = to_fixed(d);
  }
}


Position cordic_c(double radians){
  const double one = 1.0;
  const double zero = 0.0;
  const double k = 0.6072529350;
  Fixed x = to_fixed(one);
  Fixed y = to_fixed(zero);
  Fixed z = to_fixed(radians);
  for (unsigned int i = 0; i < ITERS; i++){
    Fixed xi;
    Fixed yi;
    Fixed zi;
    if (z >= 0){
      xi = x - (y >> i);
      yi = y + (x >> i);
      zi = z - atan_lut_c[i];
    } else {
      xi = x + (y >> i);
      yi = y - (x >> i);
      zi = z + atan_lut_c[i];
    }
    x = xi;
    y = yi;
    z = zi;
  }
  double out_x = from_fixed(x) * k;
  double out_y = from_fixed(y) * k;
  Position ret = {.sin = out_y, .cos = out_x};
  return ret;
}

int main(int argc, char** argv) {
  double angle;
  char* linep;
  init_lut();
  if (argc == 1){
    printf("Angle in degrees? ");
    linep = NULL;
    size_t size = 0;
    getline(&linep, &size, stdin);
    angle = strtod(linep, NULL);
  } else {
    angle = strtod(argv[1], NULL);
  }
  int flip_cos = 0;
  angle = correct_angle(angle, &flip_cos);
  Position p = cordic(angle);
  if (flip_cos){
    p.cos *= -1;
  }
  printf("Sin: %f | Cos: %f\n", p.sin, p.cos);
  if (argc == 1){
    free(linep);
  }
}

