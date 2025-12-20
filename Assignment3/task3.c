#include <stdio.h>

int main(){

    int count = 10;
    int *pCount = &count;
    *pCount = 22;
    printf("\n count = %d\n", count);
    return 0;
}