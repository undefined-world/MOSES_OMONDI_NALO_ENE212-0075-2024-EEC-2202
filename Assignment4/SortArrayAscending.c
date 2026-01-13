#include <stdio.h>
#include <string.h>

void pseudoDelete(int numbers[], int position, int lastIndex){
    for(int count = position; count < lastIndex; ++count){
        numbers[count] = numbers[count + 1];
    }
}
int main()
{
    int numbers[5];
    int sortedNumbers[5];
    int currentSortIndex=0;
    int lastIndex=4;

    printf("ENTER FIVE NUMBERS (pressing enter after each entry):\n");
    for(int count=0;count<5; ++count){
        scanf("%d",&numbers[count]);
    }

    while(lastIndex>0){
        int lowest=numbers[0];
        int indexOfLowest=0;
        for(int count=1; count<=lastIndex;++count){
            if(numbers[count]< lowest){
                lowest=numbers[count];
                indexOfLowest=count;
            }
        }
        sortedNumbers[currentSortIndex]=lowest;
        pseudoDelete(numbers,indexOfLowest,lastIndex);
        ++currentSortIndex;
        --lastIndex;
    }
    //Add the element remaining at index 0 in numbers array to the sortedNumbers array
    sortedNumbers[currentSortIndex]=numbers[0];

    printf("\n\nElements of array in sorted ascending order: ");
    for(int count =0;count<5;++count){
        printf("%d  ",sortedNumbers[count]);
    }
    printf("\n\n");

    return 0;
}
