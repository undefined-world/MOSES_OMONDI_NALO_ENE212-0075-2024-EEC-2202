#include <stdio.h>

int main()
{
    int _2DArray[6][4];

    printf("\n Please provide input for 6 rows and 4 columns:\n\n");
    for(int row=0;row<6;++row){
        printf("ENTER 4 COLUMN INTEGER VALUES FOR ROW %d (press enter after each entry)\n",row+1);
        for(int column = 0; column<4;++column){
            scanf("%d",&_2DArray[row][column]);
        }
    }

    printf("\n\nTHIS IS THE 2D ARRAY YOU ENTERED:\n");
    printf("[\n");
    for(int row=0;row<6;++row){
        printf("  [ ");
        for(int column = 0; column<4;++column){
            printf("%d ",_2DArray[row][column]);
        }
        printf("]\n");
    }
    printf("]\n\n");

    return 0;
}
