#ifndef floatabc
#define floatabc

#include <stdio.h>

#define FRACTION (1<<14)
int float_float_mul(int f1,int f2);
int float_float_div(int f1,int f2);
int float_float_add(int f1,int f2);
int float_float_sub(int f1,int f2);
int int_float_sub(int i, int f);
int int_float_mul(int i, int f);
int int_float_add(int i, int f);
int float_int_div(int f, int i);

#endif
