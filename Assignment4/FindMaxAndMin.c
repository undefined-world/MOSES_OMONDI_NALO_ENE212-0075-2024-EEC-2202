#include <stdio.h>

int main()
{
    int numbers[4];
    int highest,lowest;

    printf("ENTER FOUR NUMBERS (pressing enter after each entry):\n");
    for(int count=0;count<4; ++count){
        scanf("%d",&numbers[count]);
    }

    highest=numbers[0];
    lowest=numbers[0];

    for(int count = 1 ; count<4; ++count){
        if(numbers[count]> highest){
            highest=numbers[count];
        }
    }
    for(int count = 1 ; count<4; ++count){
        if(numbers[count]< lowest){
            lowest=numbers[count];
        }
    }

    printf("\nMaximum element is : %d\n",highest);
    printf("Minimum element is : %d\n\n",lowest);

    return 0;
}
