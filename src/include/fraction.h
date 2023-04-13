#ifndef __FRACTION_H__
#define __FRACTION_H__ 1
#include <stdint.h>



typedef struct __FRACTION{
	uint64_t w;
	int64_t n;
	uint64_t dn;
} fraction_t;



void init_fraction(uint64_t w,int64_t n,uint64_t dn,fraction_t* o);



void init_fraction_double(double v,fraction_t* o);



void shorten_fraction(fraction_t* f);



void print_fraction(fraction_t* f);



#endif
