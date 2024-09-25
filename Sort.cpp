#include "General.h"
#include "Sort.h"

void Save_Original_Data (ONEGIN* file)
{
    STRING* original_data = file->original_data = (STRING*) calloc (file->string_quantity, sizeof(STRING));
    memcpy (file->original_data, file->str_data, (file->string_quantity * sizeof(STRING)));
}
//=============================================================================
void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common)
{
    assert(Compare_common);
    assert(data);
    #define DATA1_ ((const char*)data +  j    * single_size)
    #define DATA2_ ((const char*)data + (j+1) * single_size)

    DBG (int ct = 1, cc = 2;)

    for (size_t i = 1; i < quantity; i++)
        for (size_t j = 0; j < quantity - i; j++)
        {
            DBG (printf("%d) DATA1_ = %llu, DATA2_ = %llu\n", ct, DATA1_, DATA2_ ));
            DBG (ct++;)
            if (Compare_common (DATA1_, DATA2_) > 0)
                Swap (DATA1_, DATA2_, single_size);
        }
    #undef DATA1_
    #undef DATA2_
}
//=============================================================================
void Swap (const void* first, const void* second, size_t single_size)
{
    #define min(a, b) ((a) < (b) ? (a) : (b))

    static char* buffer = 0;
    if (first == NULL && second == NULL)
    free (buffer);

    assert (first);
    assert (second);

    char* cast_first  = (char*) first;
    char* cast_second = (char*) second;
    int   bytes_to_copy = single_size;

    buffer = (char*) calloc (4096, 1);
    while (bytes_to_copy > 0)
    {
        size_t bytes_to_copy_this_time = min (sizeof (buffer), bytes_to_copy);

        memcpy (buffer, cast_first,                      bytes_to_copy_this_time);
        memcpy (        cast_first, cast_second,         bytes_to_copy_this_time);
        memcpy (                    cast_second, buffer, bytes_to_copy_this_time);

        cast_first    += bytes_to_copy_this_time;
        cast_second   += bytes_to_copy_this_time;

        bytes_to_copy -= bytes_to_copy_this_time;
    }
    #undef min
}
//=============================================================================
int Forward_Strcompare (const void*  a, const void* b)
{
    assert (a);
    assert (b);

    const char* real_a = *(char**) a;
    const char* real_b = *(char**) b;

    return Forward_Strcmp(real_a, real_b);
}
//=============================================================================
int Forward_Strcmp (const char* first_string, const char* second_string)
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
int Back_Strcmp (const STRING* first_string, const STRING* second_string)
{
    assert (first_string);
    assert (second_string);

    long length1 = first_string->end_addr - first_string->str_addr + 1;
    long length2 = second_string->end_addr -  second_string->str_addr + 1;

    char* end1 = ((STRING*) first_string)->end_addr;
    char* end2 = ((STRING*) second_string)->end_addr;

    long min =  length1 < length2 ? length1 : length2;

    static int dedlox = 1;
    __danya_back(printf("cycle №%d\n", dedlox);)
    __danya_back(printf("length1 = %ld\n", length1);)
    __danya_back(printf("length2 = %ld\n", length2);)
    __danya_back(printf("min = %ld\n", min);)
    __danya_back(printf("end1 = %llu\n", end1);)
    __danya_back(printf("end2 = %llu\n", end2);)
    __danya_back(printf("symbol of end1 = <%c>\n", *end1);)
    __danya_back(printf("symbol of end2 = <%c>\n", *end2);)

    dedlox++;

    int i = 0, j = 0;

    for (int cnt = 0; cnt < min; i--, j--, cnt++)
    {
        while (ispunct (end1[i])) i--;
        while (ispunct (end2[j])) j--;
        __danya_back(printf("Punct is skipped: end1[%d] = %d; end2[%d] = %d\n", i, end1[i], j, end2[j]);)

        if (toupper(end1[i]) == toupper(end2[i]))
            continue;
        __danya_back(printf("cnt = %d\n", cnt);)
        __danya_back(printf("<%c> - <%c> = %d\n", end1[i], end2[i], end1[i] - end2[i]);)
        __danya_back(printf("end1[i] - end2[i] = %d\n", end1[i] - end2[i]);)
        return end1[i] - end2[i];
    }
    return min - length2;
}
//=============================================================================
int Back_Strcompare (const void*  a, const void* b)
{
    assert (a);
    assert (b);

    return Back_Strcmp ( (const STRING*) a, (const STRING*) b);
}
