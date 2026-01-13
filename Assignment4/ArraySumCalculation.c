#include <stdio.h>

int main()
{
    int sum=0;
    int numbers[3];

    printf("ENTER 3 NUMBERS (pressing enter after each entry):\n");
    for(int count=0;count<3; ++count){
        scanf("%d",&numbers[count]);
    }

    for(int count = 0 ; count<3; ++count){
        sum+=numbers[count];
    }

    printf("\n\nSum of all elements stored in the array is : %d\n\n",sum);

    return 0;
}
