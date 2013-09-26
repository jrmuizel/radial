#include "minpng.h"
#include <math.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

char buf[256*256];
void first()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		for (int j=0; j<256; j++) {
			int x = i-128;
			int y = j-128;
			buf[i*256+j] = sqrt(x*x+y*y);
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}
void second()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		for (int j=0; j<256; j++) {
			int x = j-128;
			buf[i*256+j] = sqrt(x*x+y);
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}
#if 0
int32_t SkSqrtBits(int32_t x, int count) {
    SkASSERT(x >= 0 && count > 0 && (unsigned)count <= 30);

    uint32_t    root = 0;
    uint32_t    remHi = 0;
    uint32_t    remLo = x;

    do {
        root <<= 1;

        remHi = (remHi<<2) | (remLo>>30);
        remLo <<= 2;

        uint32_t testDiv = (root << 1) + 1;
        if (remHi >= testDiv) {
            remHi -= testDiv;
            root++;
        }
    } while (--count >= 0);

    return root;
}
#endif

void third()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = 0;
		int diff = 0;
		for (int j=0; j<256; j++) {
			int x = j-128;
			int target = x*x + y;
			int result = previous + diff;
			int next = result;
			do {
				result = next;
				if (diff < 0) {
					// we have overestimated
				} else {
					// we have underestimated
				}
				next = result+1;
			} while (next*next < target);
			buf[i*256+j] = result;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void fourth()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = 0;
		int diff = 0;
		for (int j=0; j<256; j++) {
			int x = j-128;
			int target = x*x + y;
			int count = 0;
			if (previous*previous < target) {
				while (previous*previous < target) {
					previous++;
					count++;
				}
				previous--;
			} else {
				while (previous*previous > target) {
					previous--;
					count++;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void fifth()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		for (int j=0; j<256; j++) {
			int x = j-128;
			int target = x*x + y;
			int count = 0;
			if (previous*previous < target) {
				while (previous*previous < target) {
					previous++;
					count++;
				}
				previous--;
			} else {
				while (previous*previous > target) {
					previous--;
					count++;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void sixth()
{

	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		for (int j=0; j<256; j++) {
			int x = j-128;
			int target = x*x + y;
			int count = 0;
			int result = previous*previous;
			if (result < target) {
				while (result < target) {
					result += previous*2+1;
					previous++;
				}
				previous--;
			} else {
				while (result > target) {
					result -= (previous*2-1);
					previous--;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void seventh()
{
	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		int x = -128;
		int target = x*x + y;
		for (int j=0; j<256; j++) {
			int x = j-128;
			target += (x<<1)+1;
			int count = 0;
			int result = previous*previous;
			if (result < target) {
				while (result + ((previous)*2+1) < target) {
					result += previous*2+1;
					previous++;
				}
			} else {
				while (result > target) {
					result -= (previous*2-1);
					previous--;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}


#include <assert.h>
void eighth()
{
	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		int x = -128;
		int target = x*x + y;
		int result = previous*previous;
		for (int j=0; j<256; j++) {
			int x = j-128;
			target += (x<<1)+1;
			if (result < target) {
				while (result + ((previous)*2+1) < target) {
					result += previous*2+1;
					previous++;
				}
			} else {
				while (result > target) {
					result -= (previous*2-1);
					previous--;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void ninth()
{
	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		int x = -128;
		int target = x*x + y;
		int result = previous*previous;
		for (int j=0; j<256; j++) {
			int x = j-128;
			target += (x<<1)+1;
			if (result < target) {
				while (result + ((previous)*2+1) < target) {
					result += previous*2+1;
					previous++;
				}
			} else {
				while (result > target) {
					result -= (previous*2-1);
					previous--;
				}
			}

			buf[i*256+j] = previous;
		}
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}

void tenth()
{
	long long start = mach_absolute_time();
	for (int i=0; i<256; i++) {
		int y = i-128;
		y*=y;
		int previous = sqrt(-128*-128+y);
		int diff = 0;
		int x = -128;
		int target = x*x + y;
		int result = previous*previous;
		for (int j=0; j<256; j++) {
			int x = j-128;
			target += (x<<1)+1;
			if (result < target) {
				printf("<");
				while (result + ((previous)*2+1) < target) {
					result += previous*2+1;
					previous++;
					printf(" ");
				}
			} else {
				printf(">");
				while (result > target) {
					result -= (previous*2-1);
					previous--;
					printf(" ");
				}
			}

			buf[i*256+j] = previous;
		}
		printf("\n");
	}
	printf("%20s %lld\n", __func__, mach_absolute_time()-start);

	write_png_a8("out.png", buf, 256, 256, 256);
}




int main()
{
	first();
	second();
	third();
	fourth();
	fifth();
	sixth();
	seventh();
	eighth();
	ninth();
	tenth();
}
