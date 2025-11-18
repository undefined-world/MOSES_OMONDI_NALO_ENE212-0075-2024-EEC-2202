#include <stdio.h>

int main()
{
    float operand1, operand2;
    //Prompt user to enter two numbers
    printf("Enter two numbers, pressing ENTER after each entry:\n");
    scanf("%f%f",&operand1,&operand2);

    //Perform multiplication on the two numbers
    printf("\n");
    printf("%.2f * %.2f = %.2f\n",operand1,operand2, operand1*operand2);

    //Perform division on the two numbers
    printf("%.2f / %.2f = %.2f\n",operand1,operand2,operand1/operand2);

    //Perform modulo operation on the two numbers
    printf("%d %% %d = %d\n",(int)operand1,(int)operand2,(int)operand1%(int)operand2);

    //Add the two numbers
    printf("%.2f + %.2f = %.2f\n",operand1,operand2,operand1+operand2);

    //Subtract the two numbers
    printf("%.2f - %.2f = %.2f\n",operand1,operand2,operand1-operand2);

    return 0;
}
