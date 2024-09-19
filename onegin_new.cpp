//#include "TxLib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>



typedef int(*Cmpr_fn_t)(const void*  a, const void* b);


struct ONEGIN
{
    long fsize, string_quantity;
    char* buffer_addr;
    char** str_addr;
    const char * name;
};

void File_Common (ONEGIN* file);
long file_size (const char * name);
void Strings_Number (ONEGIN* file);
void Read_File (ONEGIN* file);
void Check_fsize (long fsize);
void Check_argc (int argc);
void Address_String (ONEGIN* file);
void FREE (ONEGIN* file);
void Print_text (ONEGIN* file);
void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common);
void Swap (const void* first, const void* second);
int My_Strcmp (const char* first_string, const char* second_string);
int Strcompare (const void*  a, const void* b);




int main (int argc, char* argv[])
{
    Check_argc (argc);
    ONEGIN file;
    file.name = argv[1];

    File_Common (&file);
    Self_Sort (file.str_addr, file.string_quantity, sizeof(char*), Strcompare);
    Print_text (&file);
    FREE (&file);
    printf("You go to end of main ");
    return 0;
}


void File_Common (ONEGIN* file)
{
    assert(file);

    long fsize = file->fsize = file_size (file->name);                   //����� ������ ����� � ��������

    Check_fsize (fsize);                                                 //�������� �� ������ �� ����
    Read_File (file);                                                    //�������� ���� � ������������� �� � �����

    Strings_Number (file);
    Address_String (file);                            //�������� ���-�� �����
}


long file_size (const char * name)
{
    assert(name);

    struct stat stbuf;
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


void Read_File (ONEGIN* file)
{
    assert(file);

    FILE* fp = fopen (file->name, "rb");
    assert(fp);

    long fsize = file->fsize;

    char* buffer_addr = file->buffer_addr = (char*) calloc(fsize + 1 , sizeof(char)); //������ ����� �������� ���������?(��) ������
    assert(buffer_addr);

    fread(buffer_addr, sizeof(char), fsize + 1, fp);

    fclose (fp);
    assert(fp);
}

void Check_argc (int argc)
{
    if (argc != 2)
    {
        fprintf (stderr, "Error: the file name was not received");
        exit(1);
    }
}

void Address_String (ONEGIN* file)
{
    char** str_addr = file->str_addr = (char**)calloc (file->string_quantity, sizeof(char**));
    assert(str_addr);

    char* buffer_addr = file->buffer_addr;
    long n_string = 1;
    str_addr[0] = buffer_addr;

    while(*buffer_addr != '#')
    {

        if (*buffer_addr == '\n')
        {
            str_addr[n_string] = (buffer_addr+1);
            n_string++;
        }
        buffer_addr++;
    }
    buffer_addr[file->fsize] = '\n';

}

void FREE (ONEGIN* file)
{
    free (file->buffer_addr);
    free (file->str_addr);

    assert (file->buffer_addr);
    assert (file->str_addr);
}

void Print_text (ONEGIN* file)
{
    char** str_addr = file->str_addr;
    long str_quan = file->string_quantity;
    for (int i = 0; i < str_quan; i++)
    {
        fputs (str_addr[i], stdout);
        putchar('\n');
    }
     putchar('\n');
}


void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common)
{
    assert(Compare_common);
    assert(data);

    #define DATA1_ (const char*)data + j * single_size
    #define DATA2_ (const char*)data + (j+1) * single_size

    for (size_t i = 1; i < quantity; i++)
        for (size_t j = 0; j < quantity - i; j++)
        {
            if (Compare_common (DATA1_, DATA2_) > 0)
            Swap (DATA1_, DATA2_);
        }
    #undef DATA1_
    #undef DATA2_
}

void Swap (const void* first, const void* second)
{
    assert (first);
    assert (second);

    char** real_first = (char**) first;
    char** real_second = (char**) second;

    char* temp = *real_first;
    *real_first = *real_second;
    *real_second = temp;
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

