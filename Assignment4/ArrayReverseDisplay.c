#include <stdio.h>

int main()
{
    int numbers[4];
    printf("ENTER FOUR NUMBERS (pressing enter after each entry):\n");
    for(int count=0;count<4; ++count){
        scanf("%d",&numbers[count]);
    }
    printf("\n\nThe values stored into the array are : ");
    for(int count = 0 ; count<4; ++count){
        printf("%d  ",numbers[count]);
    }

    printf("\n\nThe values stored into the array in reverse are : ");
    for(int count = 3 ; count>-1; --count){
        printf("%d  ",numbers[count]);
    }
    printf("\n\n");
    return 0;
}
