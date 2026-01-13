#include <stdio.h>

const int BUFFER_SIZE=5;
int writeIndex = 0;
int oldestIndex=0;

void insertDataValue(int data[],int newValue){
    static bool bufferFilledAtleastOnce=false;
    int newValueIndex=writeIndex%BUFFER_SIZE;
    data[newValueIndex]=newValue;

    if(bufferFilledAtleastOnce) oldestIndex=newValueIndex+1;
    if(newValueIndex==(BUFFER_SIZE-1)){
        oldestIndex=0;
        if(!bufferFilledAtleastOnce) bufferFilledAtleastOnce= true;
    }
    writeIndex++;
}


void printOldestToNewest(int data[]){
    int printRange;
    if(writeIndex<BUFFER_SIZE) printRange=writeIndex;
    else printRange=BUFFER_SIZE;
    printf("\n\nOLDEST TO NEWEST: ");

    //print data from the oldest index to the last data value
    for(int count=oldestIndex;count<printRange;++count){
        printf("%d  ",data[count]);
    }

    //print newly inserted values if any
    if(oldestIndex!=0){
        for(int count = 0;count<oldestIndex; ++count){
            printf("%d  ",data[count]);
        }
    }
    printf("\n\n");
}


int main()
{
    int data[BUFFER_SIZE];
    int userInput;
    bool firstEntry=true;
    int printRange;
    printf("\nBUFFER SIZE = %d\n\n",BUFFER_SIZE);
    while(true){
        if(firstEntry){
            printf("Enter integer data value: ");
            firstEntry=false;
        }
        else{
            printf("\nEnter integer data value (ENTER -1 IF YOU ARE DONE): ");
        }
        scanf("%d",&userInput);
        if(userInput==-1) break;
        else{
            insertDataValue(data,userInput);
        }

        if(writeIndex<BUFFER_SIZE) printRange=writeIndex;
        else printRange=BUFFER_SIZE;
        printf("\nBUFFER : [");
        for(int count = 0 ; count<printRange; ++count){
            printf("%d  ",data[count]);
        }
        printf("]\n");
    }
    printOldestToNewest(data);

    return 0;
}
