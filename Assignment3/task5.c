#include <stdio.h>

void swapNumbers(int* num1, int* num2){
    int tempHolder = *num1;
    *num1 = *num2;
    *num2 = tempHolder;
}

int main(){
    int a=34, b=72;
    printf("\nBEFORE swapNumbers() CALL:\n");
    printf("a = %d and b = %d \n\n",a,b);
    swapNumbers(&a, &b);
    printf("AFTER swapNumbers() CALL:\n");
    printf("a = %d and b = %d \n\n",a,b);
}