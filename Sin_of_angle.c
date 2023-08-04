#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,acc;
    char c;

    printf("Enter a degree in rad\n");
    scanf("%d",&x);
    printf("Enter the accuracy you want \n");
    scanf("%d",&acc);
    float tmp=x,ans=x;
    for(size_t i=1;i<=2*acc;i+=2)
        {
            tmp=tmp*(-1)*x*x/((i+1)*(i+2));

            ans+=tmp;
        }
        printf("sin(%d)=%f\n",x,ans);
        c=getch();
    return 0;
}
