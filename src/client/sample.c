#include "sample.h"

void sample_cont(ui_t* options)
{
    printf("----------------------------\n");
    printf("Starting continuous sampling:\n");
    char buf[1024];
    int n;
    while (1) 
    {
        memset(buf, 0, 1024);
        n = read(options->fd, buf, 1024);
        printf("%s", buf);
    }
}

void sample_buf(ui_t* options)
{
    printf("Sample buffered not implemented yet\n");
}