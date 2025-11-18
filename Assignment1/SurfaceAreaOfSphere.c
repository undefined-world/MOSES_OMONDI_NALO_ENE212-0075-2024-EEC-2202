#include <stdio.h>
#define PI 3.142

int main()
{
    float radius, surfaceArea;
    printf("\n");
    printf("Surface Area of a Sphere\n");
    printf("\n");
    printf("Enter the radius of the sphere: ");
    scanf("%f",&radius);
    printf("\n");
    printf("Surface Area = %.2f",4*PI*radius*radius);\
    printf("\n");
    return 0;
}
