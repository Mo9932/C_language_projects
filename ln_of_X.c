#include <stdio.h>
#include <stdlib.h>

float exp(float,int);

int main()
{
    char c;
    int acc,r;
    float x=0,y=0;
    float ans=0 ,tmp=0;

    printf("ln ");
    scanf("%d",&r);
    printf("enter two values\"positive and negative\" to start solving\n");
    scanf("%f %f",&x,&y);

    printf("enter the accuracy you want\n");
    scanf("%d",&acc);


    for(size_t i=0;i<acc;i++)
    {
        ans=exp(tmp,acc)-r;

        if(ans==0)
             break;

        else if(ans<0)
           {
               y=tmp;
               tmp=(x+y)/2;
           }
        else
            {
                x=tmp;
                tmp=(x+y)/2;
            }
    }
    printf("the answer is %f\n",tmp);

    c = getch();
    return 0;
}
float exp(float x,int acc)
{
    float tmp=1,ans=1;
    for(size_t i=1;i<acc;i++)
    {
        tmp=tmp*x/i;
        ans+=tmp;
    }
    return ans;
}
