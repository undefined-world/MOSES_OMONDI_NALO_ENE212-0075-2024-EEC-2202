#include <stdio.h>
#include <string.h>

int main()
{
    char userName[100];
    printf("What is your name?  ");
    fgets(userName,sizeof(userName),stdin);
    printf("\n");
    printf("Your name is %s",userName);
    printf("\n");
    printf("Your name is %d characters long.",strlen(userName));
    printf("\n");
    return 0;
}
