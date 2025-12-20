#include <stdio.h>

void passByValue(int num){
    ++num;
}
void passByReference(int* num){
    ++*num;
}

int main(){
    int num = 99;
    printf("\nBEFORE ANY CALL:\n");
    printf("num = %d\n\n",num);
    passByValue(num);
    printf("\nAFTER passByValue() CALL:\n");
    printf("num = %d\n\n",num);
    passByReference(&num);
    printf("\nAFTER passByReference() CALL:\n");
    printf("num = %d\n\n",num);

    return 0;
}