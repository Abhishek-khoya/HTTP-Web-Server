#include<stdio.h>
int notFound()
{
    int errorCode=404;
    FILE *f;
    f=fopen("index.html","r");
    if(f==NULL)
    {
        printf("index.html not found\n");
    }
    f=fopen("index.htm","r");
    if(f==NULL)
    {
        printf("index.htm not found");
    }
    return errorCode;
}
int main()
{
    notFound();
    return 0;
}