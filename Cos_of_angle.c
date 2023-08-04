#include <stdio.h>
#include <stdlib.h>

int main()
{   int x,acc;
    char c;

    float y;

    printf("Enter an angle in degrees\n");
    scanf("%d",&x);
    printf("Enter the accuracy you want \n");
    scanf("%d",&acc);
    float tmp=1,ans=1;

    y=x*3.14/180;

    for(size_t i=1;i<=2*acc;i+=2)
        {
            tmp=tmp*(-1)*y*y/((i+1)*i);

            ans+=tmp;
        }
        printf("cos(%d)=%f\n",x,ans);
        c=getch();

    return 0;
}
