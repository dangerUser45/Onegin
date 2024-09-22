#define __DBACK
#ifdef __DBACK
#define __danya_back( ... )  __VA_ARGS__
#else
#define __danya_back(...)
#endif

#include "TxLib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

#define DEBUG

#ifdef DEBUG
#define dbg        if (1)
#define DBG(...)   __VA_ARGS__
#else
#define dbg        if (0)
#define DBG(...)
#endif

typedef int(*Cmpr_fn_t)(const void*  a, const void* b);

struct STRING
{
    char* str_addr;
    char* end_addr;
};

struct ONEGIN
{
    long fsize, string_quantity;
    char* buffer_addr;
    STRING* str_data;
    STRING* original_data;
    const char * name;
};

void File_Common (ONEGIN* file);
long file_size (const char * name);
void Strings_Number (ONEGIN* file);
void Read_File (ONEGIN* file);
void Check_fsize (long fsize);
void Check_argc (int argc);
void Address_String (ONEGIN* file);
void Free (ONEGIN* file);
void Print_text (ONEGIN* file, STRING* str_data);
void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common);
void Swap (const void* first, const void* second, size_t single_size);
int Forward_Strcmp (const char* first_string, const char* second_string);
int Forward_Strcompare (const void*  a, const void* b);
int Back_Strcmp (const char* first_string, const char* second_string);
int Back_Strcompare (const void*  a, const void* b);
void Save_Original_Data (ONEGIN* file);
__danya_back(void DBG_Print (ONEGIN* file);)

int main (int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    Check_argc (argc);
    ONEGIN file = {};
    file.name = argv[1];

    File_Common (&file);

    dbg {
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf ("        FILE STRUCT INFORMATION\n");
        printf("Name of file: \"%s\"\n", file.name);
        printf("Size of file: %ld\n", file.fsize);
        printf("String Quantity = %ld\n", file.string_quantity);
        printf("Buffer Address = %llu\n", file.buffer_addr);
        printf("String_Data = %llu\n", file.str_data);
        for(int i = 0; i < file.string_quantity; i++)
        {
            printf("number of string = %d:\n", i+1);
            printf("file.str_data[i].str_addr = %llu, his addr = %llu\n", file.str_data[i].str_addr, &file.str_data[i].str_addr);
            printf("file.str_data[i].end_addr = %llu, his addr = %llu\n", file.str_data[i].end_addr, &file.str_data[i].end_addr);
        }
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    Save_Original_Data (&file);

    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Forward_Strcompare);
    //Print_text (&file, file.str_data);

    __danya_back(DBG_Print (&file);)
    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Back_Strcompare);
    Print_text (&file, file.str_data);
    __danya_back(printf("IN MAIN\n");)

    //Print_text (&file, file.original_data);

    Free (&file);

    dbg printf("You go to end of MAiN, MAN ");
    return 0;
}
//=============================================================================
void File_Common (ONEGIN* file)
{
    assert(file);

    long fsize = file->fsize = file_size (file->name);
    dbg printf("fsize = %llu\n", fsize);
    Check_fsize (fsize);
    Read_File (file);

    Strings_Number (file);
    Address_String (file);
}
//=============================================================================
long file_size (const char* name)
{
    assert(name);

    struct stat stbuf = {};
    stat(name, &stbuf);
    return stbuf.st_size;
}
//=============================================================================
void Strings_Number (ONEGIN* file)
{
    char* buffer_addr = file-> buffer_addr;
    assert (buffer_addr);

    buffer_addr[file->fsize] = '#';
    buffer_addr[(file->fsize)-1] = '\0';

    long string_quantity = 1;
    while (*buffer_addr != '#')
    {
        if (*buffer_addr == '\r')
            *buffer_addr = '\0';
        if (*buffer_addr == '\n')
            string_quantity++;
        buffer_addr++;
    }
    __danya_back(DBG_Print (file);)
    file->string_quantity = string_quantity;
}
//=============================================================================
void Check_fsize (long fsize)
{
    if (fsize == 0)
    {
        fprintf(stderr, "Error: empty file");
        exit(-1);
    }
}
//=============================================================================
void Read_File (ONEGIN* file)
{
    assert(file);

    FILE* fp = fopen (file->name, "rb");
    assert(fp);

    long fsize = file->fsize;

    char* buffer_addr = file->buffer_addr = (char*) calloc(fsize + 1 , sizeof(char));

    fread(buffer_addr, sizeof(char), fsize + 1, fp);
    dbg printf("READ_file: addr buffer_adr = %llu\n", buffer_addr);

    fclose (fp);
    assert(fp);
}
//=============================================================================
void Check_argc (int argc)
{
    if (argc != 2)
    {
        fprintf (stderr, "Error: the file name was not received\n");
        exit(1);
    }
}
//=============================================================================
void Address_String (ONEGIN* file)
{
    STRING* str_data = file->str_data = (STRING*)calloc ((file->string_quantity), sizeof(STRING));
    assert(str_data);

    char* buffer_addr = file->buffer_addr;
    long n_string = 1;
    str_data[0].str_addr = buffer_addr;
    dbg printf("  ADDR_STR str_data = %llu\n", str_data);
    dbg printf("ADDR_STR: adrr begin str = %llu\n", str_data[0].str_addr);

    while(*buffer_addr != '#')
    {
        if (*buffer_addr == '\n')
        {
            str_data[n_string-1].end_addr = buffer_addr;
            str_data[n_string].str_addr = buffer_addr+1;

            dbg printf("ADDR_STR: adrr end str = %llu\n", str_data[n_string-1].end_addr);
            dbg printf("ADDR_STR: adrr begin str = %llu\n", str_data[n_string].str_addr);


            n_string++;
        }
        buffer_addr++;
    }
    str_data[n_string-1].end_addr = buffer_addr - 1;
   file->buffer_addr[file->fsize-1] = '\n';
   file->buffer_addr[file->fsize] = '\n';
    dbg printf("addr buffer_addr = %llu\n", buffer_addr);
    dbg printf("buffer_addr[file->fsize-1] = <%d>\n", buffer_addr[file->fsize-1]);
    dbg printf("buffer_addr[file->fsize-1] = <%d>\n", buffer_addr[file->fsize-1]);
    dbg printf("file->buffer_addr[file->fsize-1] = <%d>\n", file->buffer_addr[file->fsize-1]);
    dbg printf("file->buffer_addr[file->fsize] = <%d>\n",   file->buffer_addr[file->fsize]);
    dbg printf("ADDR_STR: adrr end str = %llu\n", str_data[n_string-1].end_addr);

}
//=============================================================================
void Free (ONEGIN* file)
{
    free (file->buffer_addr);
    free (file->str_data);

    assert (file->buffer_addr);
    assert (file->str_data);
}
//=============================================================================
void Print_text (ONEGIN* file, STRING* str_data)
{
    long string_quantity = file->string_quantity;
    for (int i = 0; i < string_quantity; i++)
    {
        fputs (str_data[i].str_addr, stdout);
        putchar('\n');
    }
     putchar('\n');
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
/*
bytes_to_copy  bytes_to_copy_this_time
800            100
700            100
600            100
500            100
400            100
300            100
200            100
100            100
9              9
0
*/
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
    __danya_back(printf("cycle ¹%d\n", dedlox);)
    __danya_back(printf("length1 = %ld\n", length1);)
    __danya_back(printf("length2 = %ld\n", length2);)
    __danya_back(printf("min = %ld\n", min);)
    __danya_back(printf("end1 = %llu\n", end1);)
    __danya_back(printf("end2 = %llu\n", end2);)
    __danya_back(printf("symbol of end1 = <%c>\n", *end1);)
    __danya_back(printf("symbol of end2 = <%c>\n", *end2);)

    dedlox++;


    int i = 0;
    for (int cnt = 0; cnt < min; i--, cnt++)
    {
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
void Save_Original_Data (ONEGIN* file)
{
    STRING* original_data = file->original_data = (STRING*) calloc (file->string_quantity, sizeof(STRING));
    memcpy (file->original_data, file->str_data, (file->string_quantity * sizeof(STRING)));
}
//=============================================================================
int Back_Strcompare (const void*  a, const void* b)
{
    assert (a);
    assert (b);

    return Back_Strcmp ( (const STRING*) a, (const STRING*) b);
}

__danya_back(void DBG_Print (ONEGIN* file)
{
    long fsize = file->fsize;

    printf("=============================================================================\n");
    for(int i = 0; i < fsize+1; i++)
        if (file->buffer_addr[i] == '\n')
            printf("symbol = <\\n>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\r')
            printf("symbol = <\\r>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\0')
           printf("symbol = <\\0>, addr = %llu\n", file->buffer_addr + i );
        else
        printf("Symbol = <%c>, his addr = %llu\n", file->buffer_addr[i], file->buffer_addr + i);
    printf("=============================================================================\n");
})


