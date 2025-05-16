#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LEN 50

int main() 
{
    char c;
    char str[MAX_LEN];
    char sen[MAX_LEN];
    scanf("%c", &c);
    scanf("%s",&str);
    scanf("\n");
    scanf("%[^\n]%*c", &sen);
    
    printf("%c",c);
    printf("\n");
    printf("%s",str);
    printf("\n");
    printf("%s",sen);
    return 0;
}
