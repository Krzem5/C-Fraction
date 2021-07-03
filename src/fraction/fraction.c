#include <fraction.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>



#define MAX_DOUBLE_ERROR 11



void init_fraction(uint64_t w,int64_t n,uint64_t dn,fraction_t* o){
	if (!dn){
		n=0;
		dn=1;
	}
	o->w=w;
	o->n=n;
	o->dn=dn;
}



void init_fraction_double(double v,fraction_t* o){
	int8_t s=1;
	if (v<0){
		s=-1;
		v=-v;
	}
	o->w=(uint64_t)v;
	v-=o->w;
	uint64_t mx_b=1;
	uint64_t pw_b=10;
	uint64_t pw_e=MAX_DOUBLE_ERROR-1;
	while (1){
		if (pw_e&1){
			mx_b*=pw_b;
		}
		pw_e>>=1;
		if (!pw_e){
			break;
		}
		pw_b*=pw_b;
	}
	uint64_t mx_a=mx_b*10;
	double err=pow(10,-MAX_DOUBLE_ERROR-1);
	uint64_t a=10;
	double c=v;
	while (c>=err&&a<=mx_a){
		uint64_t b=1;
		while (b<=mx_b&&b<a){
			double df=v*a-v*b;
			c=df-(uint64_t)df;
			if (c<err){
				o->n=s*((uint64_t)df);
				o->dn=a-b;
				shorten_fraction(o);
				return;
			}
			b*=10;
		}
		a*=10;
	}
	o->n=s*((int64_t)(v*mx_a));
	o->dn=mx_a;
	shorten_fraction(o);
}



void shorten_fraction(fraction_t* f){
	uint64_t n=(f->n<0?-f->n:f->n);
	uint64_t a=n;
	uint64_t b=f->dn;
	uint64_t c=0;
	if (a==b){
		f->w++;
		f->n=-1;
		f->dn=0;
	}
	while (1){
		if (!a){
			f->n=(n/(b<<c))*(f->n<0?-1:1);
			f->dn/=b<<c;
			return;
		}
		if (!b){
			f->n=(n/(a<<c))*(f->n<0?-1:1);
			f->dn/=a<<c;
			return;
		}
		if (a&1){
			if (b&1){
				if (a>b){
					a=(a-b)>>1;
				}
				else{
					uint64_t t=(b-a)>>1;
					b=a;
					a=t;
				}
			}
			else{
				b>>=1;
			}
		}
		else{
			if (b&1){
				a>>=1;
			}
			else{
				a>>=1;
				b>>=1;
				c++;
			}
		}
	}
}



void print_fraction(fraction_t* f){
	if (f->n<0){
		putchar('-');
	}
	if (f->dn==0){
		printf("%"PRIu64,f->w);
	}
	else if (f->dn==1){
		printf("%"PRIu64,f->w+f->n);
	}
	else{
		printf("%"PRIu64"%+"PRId64"/%"PRIu64,f->w,f->n,f->dn);
	}
}
