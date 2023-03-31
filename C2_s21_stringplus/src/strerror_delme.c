#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
{
    for(int i=0; i<134; i++)
        printf("sys_errlist[%d] = \"%s\"\n", i, strerror(i));
    return 0;
}
