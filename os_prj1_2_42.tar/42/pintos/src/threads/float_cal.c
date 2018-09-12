#include "threads/float_cal.h"




int float_float_mul(int f1,int f2){
	int64_t tmp = f1;
	tmp = tmp * f2 / FRACTION;
	return (int)tmp;
}

int float_float_div(int f1,int f2){
	int64_t tmp = f1;
	tmp = tmp * FRACTION / f2;
	return (int)tmp;
}

int float_float_add(int f1,int f2){
	return (f1+f2);
}

int float_float_sub(int f1,int f2){
	return (f1-f2);
}

int int_float_sub(int i, int f){
	return i*FRACTION-f; 
}

int int_float_mul(int i, int f){
	return i*f;
}

int int_float_add(int i, int f){
	return i*FRACTION+f;
}

int float_int_div(int f, int i){
	return f/i ; 

}
