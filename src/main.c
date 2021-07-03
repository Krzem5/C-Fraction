#include <fraction.h>
#include <stdio.h>



int main(int argc,const char** argv){
	fraction_t f;
	init_fraction(0,1,2,&f);
	print_fraction(&f);
	putchar('\n');
	init_fraction_double(-10.3333333333333333,&f);
	print_fraction(&f);
	putchar('\n');
	return 0;
}
