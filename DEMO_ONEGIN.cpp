#include "TXLib.h"
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

int Strcompare (const void*  a, const void* b);
int My_Strcmp (const char* first_string, const char* second_string);
void Swap (const void* first, const void* second, size_t single_size);

int main ()
{
    int a = 10, b = 2500000;
    int* ptr1 = &a;
    int* ptr2 = &b;


    Swap(ptr1, ptr2, sizeof(int));
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
}
//=============================================================================
int Strcompare (const void*  a, const void* b)
{
    assert (a);
    assert (b);

    const char* real_a = *(char**) a;
    const char* real_b = *(char**) b;

    return My_Strcmp(real_a, real_b);
}
//=============================================================================
int My_Strcmp (const char* first_string, const char* second_string)
{
    assert (first_string);
    assert (second_string);

    int i = 0;
    for (; toupper(first_string[i]) == toupper(second_string[i]); i++)
        if (first_string[i] == '\0')
            return 0;
    return  first_string[i] - second_string[i];
}
//=============================================================================
void Swap (const void* first, const void* second, size_t single_size)
{
    assert (first);
    assert (second);

    char* cast_first = (char*) first;
    char* cast_second = (char*) second;


    for (int i = 0; i < single_size; i++)
    {
        char temp = cast_first[i];
        cast_first[i] = cast_second[i];
        cast_second[i] = temp;
        //printf("temp = %c", temp);
        //printf("symbol second = <%c>\n", cast_second[i]);
    }
}
