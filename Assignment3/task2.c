#include <stdio.h>

int main(){
    int num = 10;
    int *ptr= &num;
    printf("\nnum = %d\n\n", num);
    printf("*ptr = %d\n\n", *ptr);
    printf("ptr = %d\n\n", ptr);

    return 0;
}