#include "TXLib.h"
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

struct STRING
{
    char* str_addr;
    char* end_addr;
};

void Swap (const void* first, const void* second, size_t single_size);
int Back_Strcmp (const STRING* first_string, const STRING* second_string);

int main ()
{
    int a = 10, b = 2500000;
    int* ptr1 = &a;
    int* ptr2 = &b;


    Back_Strcmp ();
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
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
//=============================================================================
int Back_Strcmp (const STRING* first_string, const STRING* second_string)
{
    assert (first_string);
    assert (second_string);

    long length1 = first_string->end_addr - first_string->str_addr;
    long length2 = second_string->end_addr -  second_string->str_addr;

    char* end1 = ((STRING*) first_string)->end_addr;
    char* end2 = ((STRING*) second_string)->end_addr;

    long min =  length1 < length2 ? length1 : length2;

    int i = 0;
    for (int cnt = 0; cnt < min; i--, cnt++)
    {
        if (toupper(end1[i]) == toupper(end2[i]))
            continue;
        return end1[i] - end2[i];
    }
    return min - length2;
}
