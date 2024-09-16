#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

int main ()
{
    struct stat stbuf;

   stat("Demo.txt", &stbuf);
   int n = stbuf.st_size;
   printf("%d", n);


return 0;

}
