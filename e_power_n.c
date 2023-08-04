#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,acc;
    char c;

    printf("Enter number\n");
    scanf("%d",&x);
    printf("Enter the accuracy you want \n");
    scanf("%d",&acc);
    float tmp=1,ans=1;
    for(size_t i=1;i<=acc;i++)
        {
            tmp=tmp*x/i;

            ans+=tmp;
        }
    printf("e power(%d)=%f\n",x,ans);
    c=getch();
    return 0;
}
