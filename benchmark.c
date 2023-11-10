#include <stdio.h>
#include <sys/syscall.h>
#include <time.h>

#define ITERATIONS 100000

int main()
{
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        syscall(548, 1);
    }
    printf("Time for %d system calls: %f seconds \n", ITERATIONS, (double)(clock() - start) / CLOCKS_PER_SEC);
}