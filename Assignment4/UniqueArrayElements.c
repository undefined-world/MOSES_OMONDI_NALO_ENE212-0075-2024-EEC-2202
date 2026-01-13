#include <stdio.h>

int main()
{
    int numbers[4];
    bool uniqueExist=false;
    printf("ENTER FOUR NUMBERS (pressing enter after each entry):\n");
    for(int count=0;count<4; ++count){
        scanf("%d",&numbers[count]);
    }

    printf("\n\nThe unique elements found in the array are: ");
    for(int count = 0 ; count<4; ++count){
        bool isRepeated=false;
        for(int count2 = 0 ; count2<4; ++count2){
            if(count != count2){
                if(numbers[count]==numbers[count2]){
                    isRepeated=true;
                }
            }
        }
        if(!isRepeated){
            printf("%d  ",numbers[count]);
            uniqueExist=true;
        }
    }

    if(!uniqueExist){
        printf("none (ALL ELEMENTS IN THE ARRAY ARE DUPLICATED)");
    }
    printf("\n\n");

    return 0;
}
