#include "TxLib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>


struct ONEGIN
{
    long fsize, string_quantity;
    char* buffer_addr;
    char** str_addr;
    const char* name;
};

void File_Common (ONEGIN* file);
long file_size (const char* name);
void Strings_Number (ONEGIN* file);
void Read_File (ONEGIN* file);
void Check_fsize (long fsize);
void Check_argc (int argc);
void Address_String (ONEGIN* file);
void FREE (ONEGIN* file);
void Print_text (ONEGIN* file);


int main (int argc, char* argv[])
{
    Check_argc (argc);
    ONEGIN file;
    file.name = argv[1];

    File_Common (&file);
    FREE (&file);
    Print_text (&file);
    printf("You go to end of main ");
    return 0;
}


void File_Common (ONEGIN* file)
{
    assert(file);

    long fsize = file->fsize = file_size (file->name);                   //узнал размер файла в символах

    Check_fsize (fsize);                                                 //проверил не пустой ли файл
    Read_File (file);                                                    //прочитал файл и перекопировал всё в буфер

    Strings_Number (file);
    Address_String (file);                            //посчитал кол-во строк
}


long file_size (const char* name)
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
        /*
        printf("/%c\\", *buffer_addr);
        //*/
        buffer_addr++;
    }
    /*
    printf("buffer_addr = %p, file->buffer_addr = %p\n", buffer_addr, file->buffer_addr);
    printf("\n");
    printf("string_quantity = %ld\n", string_quantity);
    */

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


    char* buffer_addr = file->buffer_addr = (char*) calloc(fsize + 1 , sizeof(char)); //создал буфер размером двоичного?(да) текста
    assert(buffer_addr);

    fread(buffer_addr, sizeof(char), fsize + 1, fp);                                  //заполнил массив

    fclose (fp);
    assert(fp);

     /*

     printf("file->fsize = %ld\n", file->fsize);
     printf("buffer_addr = %p, file->buffer_addr = %p\n", buffer_addr, file->buffer_addr);
     printf("buffer_addr[0] = /%c\\\n", buffer_addr[0]);
     printf("\nbuffer_addr[%ld] = /%c\\\n", fsize-1, buffer_addr[fsize-1]);
     printf("\nbuffer_addr[%ld] = /%c\\\n", fsize,  buffer_addr[fsize]);
    */
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
    char** str_addr = file->str_addr = (char**)calloc (file->string_quantity, sizeof(int));
    assert(str_addr);

    char* buffer_addr = file->buffer_addr;
    long n_string = 1;
    str_addr[0] = buffer_addr;

    /*
          printf("Buf_ad = %llu\n", buffer_addr);
          printf("Str_Ad = %llu\n", str_addr[0]);

    */
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

     /*
    for (int i = 0; i < n_string; i++)
    {
        printf("str_addr[i] = %llu\n", str_addr[i]);
    }
    //
        printf("buffer_addr[0] = %llu\n", file->buffer_addr);
        printf("buffer_addr[1] = %llu\n", (file->buffer_addr)+1);

     printf("n_string = %ld\n", n_string);
     */
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
}

/*void Self_Sort (ONEGIN* file)
{
    string_quantity = file->string_quantity
    for (int i = 1; i < string_quantity; i++)
        for (int j = 0; j < string_quantity - i; j++)
            if (strcompare (&text[j * ROWS_QUANTITY], &text[(j + 1) * ROWS_QUANTITY]))
                swap_string(&text[j * ROWS_QUANTITY], &text[(j + 1) * ROWS_QUANTITY]);

}

void Swap (void* a, void* b)
{
    char* temp = calloc ()
}  */
