#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    float ans=1,tmp=1,y=3.141;


    FILE *fp;

    fp= fopen("io.txt","w");

    fprintf(fp,"cos(%.3f)=%d",y,1);


    for(size_t i=1;i<=22;i+=2)
        {
            tmp=tmp*(-1)*y*y/((i+1)*i);
            fprintf(fp,"+(%.2f)",tmp);
            ans+=tmp;
        }

    fprintf(fp,"=:%f\n",ans);

    fclose(fp);

    FILE *fp1;
    char buffer[128];
    fp1=fopen("io.txt","r");
    fgets(buffer,128,fp1);

    printf("buffer:%s\n",buffer);
    fclose(fp1);


    return 0;
}
