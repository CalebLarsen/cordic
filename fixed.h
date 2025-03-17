#ifndef FIXED_H
#define FIXED_H

typedef unsigned long long u64;
typedef long long i64;
typedef i64 Fixed;

u64 get_sign(double);
i64 get_exponent(double);
u64 get_mantissa(double);

u64 fixed_sign(Fixed);
u64 fixed_exponent(Fixed);

Fixed to_fixed(double);
double from_fixed(Fixed);

#endif
