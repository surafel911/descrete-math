#include <time.h>
#include <stdio.h>

#define BASE	50

long
fib_r(long base)
{
	switch (base) {
	case 0:
		return 0;
	case 1:
		return 1;
	}

	return fib_r(base - 1) + fib_r(base - 2);
}

long
fib_i(long base)
{
	switch (base) {
	case 0:
		return 0;
	case 1:
		return 1;
	}

	long sum, n_1 = 0, n_2 = 1;
	for (int i = 2; i <= base; i++) {
		sum = n_2 + n_1;
		n_1 = n_2;
		n_2 = sum;
	}

	return sum;
}

void
fib1(void)
{
	puts(__func__);

	for (int i = 1; i <= BASE; i++) {
		printf("%ld\n", fib_r(i));
	}

	puts("");
}

void
fib2(void)
{
	puts(__func__);

	for (int i = 1; i <= BASE; i++) {
		printf("%ld\n", fib_i(i));
	}

	puts("");
}

int
main(int argc, char* argv[])
{
	double seconds;
	time_t end, begin;

	begin = time(NULL); 
	fib1();
	end = time(NULL);
	seconds = difftime(end, begin);
	printf("time: %lfs\n\n", seconds);

	begin = time(NULL); 
	fib2();
	end = time(NULL);
	seconds = difftime(end, begin);
	printf("time: %lfs\n\n", seconds);
}
