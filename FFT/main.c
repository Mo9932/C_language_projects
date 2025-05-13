#include <stdio.h>
#include "math.h"

#include "BIT_MATH.h"

#include "edale_song.h"

#include "fft.h"

Complex_t data[1024] =  {0};
Complex_t *res = NULL;



int main(void){


    for (int i = 0; i < 1024; i++)
    {
    
        data[i].Real = sinf(((float)i/1024)*2*pi)  + 1;
        // data[i].Real = 0 ;
        // data[i+1].Real = 100 ;
        // data[i+2].Real = 0 ;
        // data[i+3].Real = -100 ;

    }

    
    // for (int i = 0; i < 1024; i++)
    // {
    //     printf("%f \n",data[i].Real);
    // }

    res = fft_data(data,1023);

    for (int i = 0; i < 1024; i++)
    {
        printf("%f \n",data[i].Real);
    }

    res1 = Ifft_data(res,1023);

    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < 1024; i++)
    {
        // res1[i].Real =  sqrtf(res1[i].Real*res1[i].Real+res1[i].Img*res1[i].Img) ;
        printf("%f ",res1[i].Real);
        // printf("%f",res1[i].Img);
        printf("\n");

        // if(i == 512) 
    }

    // for (int i = 0; i < 1024; i++)
    // {
    //     res[i].Real =  sqrtf(res[i].Real*res[i].Real+res[i].Img*res[i].Img) ;

    //     printf("%f\n",res[i].Real);
    //     // printf("i \n");
    // }





    return 0 ;
}