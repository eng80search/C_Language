#include <stdio.h>
#include <stdlib.h>

static void
showaddr(char *label, void *a)
{
    unsigned long n = (unsigned long)a;

    printf("%s   = %lx\n", label, n);
    printf("%s%%4 = %ld\n", label, n % 4);
    printf("%s%%8 = %ld\n", label, n % 8);
}

int
main(int argc, char *argv[])
{
    struct some {
	char c1;
	char c2;
	long n;
    } st1;
    struct any {
	union {
	    char c;
            long n;
	} u1;
	union {
	    char c;
            long n;
	} u2;
	long n;
    } st2;

    showaddr("st1.c1  ", &st1.c1);
    showaddr("st1.c2  ", &st1.c2);
    showaddr("st1.n   ", &st1.n);
    showaddr("st2.u1.c", &st2.u1.c);
    showaddr("st2.u2.c", &st2.u2.c);
    showaddr("st2.n   ", &st2.n);
    exit(0);
}
