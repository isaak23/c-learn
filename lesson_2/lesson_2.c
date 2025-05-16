#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int number1;
int number2;
float number3;
float number4;

int main()
{
    scanf("%d %d",&number1,&number2);
    scanf("%f %f", &number3,&number4);
    
    int sumint = number1 + number2;
    int diffint = number1 -number2; 
    printf("%d %d" ,sumint,diffint);
    printf("\n");
    
    float sumfloat = number3 + number4;
    float difffloat = number3 - number4; 
    printf("%.1f %.1f" ,sumfloat,difffloat);
    
    return 0;
}