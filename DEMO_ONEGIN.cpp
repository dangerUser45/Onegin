#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

void Swap (const void* first, const void* second);

int main ()
{
    int q = 5;
    int r = 18;

    int* in1 = &q;
    int* in2 = &r;
    int** adr1 = &in1;
    int** adr2 = &in2;
    printf("in1 = %p\n"
           "in2 = %p\n", in1, in2);
    Swap (adr1, adr2);

    printf("in1 = %p\n"
           "in2 = %p\n", in1, in2);

    return 0;
}

void Swap (const void* first, const void* second)
{
    assert (first);
    assert (second);

    int** real_first = (int**) first;
    int** real_second = (int**) second;

    int* temp = *real_first;
    *real_first = *real_second;
    *real_second = temp;
}
