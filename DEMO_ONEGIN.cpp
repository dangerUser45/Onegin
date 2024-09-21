#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

struct STRING
{
    char str_addr;
    char end_addr;
};

struct ONEGIN
{
    int n;
    STRING* str_data;
    char* xh;
};

void func (ONEGIN* file);


int main ()
{


    ONEGIN file;
    func (&file);

    free (file.str_data);
    return 0;
}

void func (ONEGIN* file)
{
    char n1 = 66;
    char n2 = 67;
    char n3 = 68;
    char n4 = 69;

    STRING* str_data = file->str_data = (STRING*)calloc (10, sizeof(STRING));

    str_data[0].str_addr = n1;
    str_data[0].end_addr = n2;
    str_data[1].str_addr = n3;
    str_data[1].end_addr = n4;

    str_data[9].str_addr = '#';
                         //file->str_data[0].str_addr = &n1;
                                                    //file->str_data[0].end_addr = &n2;
                                                    //
                                                    //file->str_data[1].str_addr = &n3;
                                                    //file->str_data[1].end_addr = &n4;



     printf("adr n1 = %c\n"
            "adr n2 = c\n"
            "adr n3 = %c\n"
            "adr n4 = %c\n", n1, n2, n3, n4);
    //printf ("file.str_data = %llu\n", file.str_data.str_addr);
    printf ("file.str_data[0].str_addr = %c\n", str_data[0].str_addr);
    printf ("file.str_data[0].end_addr = %c\n", str_data[0].end_addr);
    printf ("file.str_data[1].str_addr = %c\n", str_data[1].str_addr);
    printf ("file.str_data[1].end_addr = %c\n", str_data[9].str_addr);

    /*
    printf("sizeof(STRING) = %d\n", sizeof(STRING));
    printf("sizeof(ONEGIN) = %d\n", sizeof(ONEGIN));
    printf("sizeof(char*) = %ld\n", sizeof(char*));
    printf("sizeof(long) = %d", sizeof(long));
     */
}
