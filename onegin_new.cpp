//#include "TxLib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

#define dbg if(1)

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
void Print_text (ONEGIN* file);
void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common);
void Swap (const void* first, const void* second, size_t single_size);
int My_Strcmp (const char* first_string, const char* second_string);
int Strcompare (const void*  a, const void* b);


int main (int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    Check_argc (argc);
    ONEGIN file = {};
    file.name = argv[1];

    File_Common (&file);
    dbg {
        for(int i = 0; i < file.string_quantity; i++)
        {
            printf("i = %d:\n", i);
            printf("file.str_data[i].str_addr = %llu\n", file.str_data[i].str_addr);
            printf("file.str_data[i].end_addr = %llu\n", file.str_data[i].end_addr);
        }
    }

    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Strcompare);
    //Print_text (&file);

    Free (&file);

    printf("You go to end of MAiN, MAN ");
    return 0;
}


void File_Common (ONEGIN* file)
{
    assert(file);

    long fsize = file->fsize = file_size (file->name);
    dbg printf("fsize = %llu", fsize);
    Check_fsize (fsize);
    Read_File (file);

    Strings_Number (file);
    Address_String (file);
}


long file_size (const char* name)
{
    assert(name);

    struct stat stbuf = {};
    stat(name, &stbuf);
    return stbuf.st_size;
}

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
        dbg printf("symbol = <%c>, addr = %llu\n", *buffer_addr, buffer_addr);
        if (*buffer_addr == '\n')
            string_quantity++;
        buffer_addr++;
    }
    file->string_quantity = string_quantity;
}

void Check_fsize (long fsize)
{
    if (fsize == 0)
    {
        fprintf(stderr, "Error: empty file");
        exit(-1);
    }
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void Address_String (ONEGIN* file)
{
    STRING* str_data = file->str_data = (STRING*)calloc ((file->string_quantity), sizeof(STRING));
    assert(str_data);

    char* buffer_addr = file->buffer_addr;
    long n_string = 1;
    str_data[0].str_addr = buffer_addr;
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
    buffer_addr[file->fsize] = '\n';
    dbg printf("ADDR_STR: adrr end str = %llu\n", str_data[n_string-1].end_addr);

}

void Free (ONEGIN* file)
{
    free (file->buffer_addr);
    free (file->str_data);

    assert (file->buffer_addr);
    assert (file->str_data);
}

void Print_text (ONEGIN* file)
{
    STRING* str_data = file->str_data;
    long string_quantity = file->string_quantity;
    for (int i = 0; i < string_quantity; i++)
    {
        fputs (str_data[i].str_addr, stdout);
        putchar('\n');
    }
     putchar('\n');
}


void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common)
{
    assert(Compare_common);
    assert(data);
    #define DATA1_ ((const char*)data +  j    * single_size)
    #define DATA2_ ((const char*)data + (j+1) * single_size)

    for (size_t i = 1; i < quantity; i++)
        for (size_t j = 0; j < quantity - i; j++)
        {
            if (Compare_common (DATA1_, DATA2_) > 0)
            Swap (DATA1_, DATA2_, single_size);
        }
    #undef DATA1_
    #undef DATA2_
}

void Swap (const void* first, const void* second, size_t single_size)
{
    assert (first);
    assert (second);

    char* buffer = (char*)calloc (single_size, 1);
    assert(buffer);

    char* cast_first = (char*) first;
    char* cast_second = (char*) second;

    *buffer = *cast_first;
    *cast_first = *cast_second;
    *cast_second= *buffer;

    free (buffer);

}

int Strcompare (const void*  a, const void* b)
{
    assert (a);
    assert (b);

    const char* real_a = *(char**) a;
    const char* real_b = *(char**) b;

    return My_Strcmp(real_a, real_b);
}

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

