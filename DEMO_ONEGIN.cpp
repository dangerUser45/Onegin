#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

int main ()
{
    char* ch = (char*) calloc (3, sizeof(char));
    int* in = (int*) calloc (3, sizeof(int));
    printf("ch[0]%%c = %c\n"
           "ch[1]%%d = %d\n"
           "in[0]%%c = %c\n"
           "in[0]%%d = %d\n", ch[0], ch[0], in[0], in[0]);
    free(ch);
    free (in);
    return 0;
}
