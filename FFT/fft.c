
#include "stdlib.h"
#include <stdio.h>
#include "math.h"
#include "fft.h"
#include "BIT_MATH.h"



void Complex_mul(Complex_t *res, Complex_t num1, Complex_t num2){
    res->Real = num1.Real*num2.Real - num1.Img*num2.Img;
    res->Img = num1.Real*num2.Img + num1.Img*num2.Real;
}

void fft_subgroup(Complex_t *res, Complex_t *data_arr, Complex_t *roots, int input_num, int arr_len){
    
    int index_counter =0;


    for (int i = 0; i < input_num/2; i++)
    {
        Complex_mul(res+i+(input_num/2),roots[i*((arr_len/2)/(input_num/2))],data_arr[i+(input_num/2)]) ;
    }

    for (index_counter; index_counter < input_num/2; index_counter++)
    {
        res[index_counter].Real = data_arr[index_counter].Real + res[index_counter+(input_num/2)].Real;
        res[index_counter].Img = data_arr[index_counter].Img + res[index_counter+(input_num/2)].Img;
    }
    
    for (int i =0 ; index_counter < input_num , i < input_num/2; index_counter++,i++)
    {
        res[index_counter].Real = data_arr[i].Real - res[index_counter].Real;
        res[index_counter].Img = data_arr[i].Img - res[index_counter].Img;
    }
    
    for(int i = 0 ; i <input_num ; i++){
        data_arr[i] = res[i] ;
    }
    
    
}
void Ifft_subgroup(Complex_t *res, Complex_t *data_arr, Complex_t *roots, int input_num, int arr_len){
    
    int index_counter =0;


    for (index_counter; index_counter < input_num/2; index_counter++){
        res[index_counter].Real = data_arr[index_counter].Real + data_arr[index_counter+(input_num/2)].Real;
        res[index_counter].Img = data_arr[index_counter].Img + data_arr[index_counter+(input_num/2)].Img;
    }
    
    for (int i =0 ; index_counter < input_num , i < input_num/2; index_counter++,i++){
        res[index_counter].Real = data_arr[i].Real - data_arr[index_counter].Real;
        res[index_counter].Img = data_arr[i].Img - data_arr[index_counter].Img;
    }

    if(input_num!=2){
        for (int i = 0; i < input_num/2; i++){
            Complex_mul(res+i+(input_num/2),roots[i*((arr_len/2)/(input_num/2))],data_arr[i+(input_num/2)]) ;
        }
    }


    for(int i = 0 ; i <input_num ; i++){
        data_arr[i] = res[i] ;
    }
    
}


Complex_t* fft_data(Complex_t *data_arr,int size){


    unsigned char tmp_size = logf(size)/logf(2) + 1;

    int arr_len =1;

    int input = 1 ;

    unsigned  int count = 0 ;

    int bit = 1 ;
    //2^tmp_size

    for(int i =0 ; i<tmp_size ;i++){
        arr_len *=2 ;
    }

    Complex_t * res = malloc(sizeof(Complex_t)*arr_len);
    Complex_t * data_tmp = malloc(sizeof(Complex_t)*arr_len);
    Complex_t * roots =malloc(sizeof(Complex_t)*arr_len/2);

    for (int i = 0; i < arr_len/2; i++)
    {
        roots[i].Real=cosf((-2*pi*i)/arr_len);
        roots[i].Img=sinf((-2*pi*i)/arr_len);
    }

    for (int i = 0; i < arr_len; i++)
    {
        if(i <= size)
            data_tmp[i] = data_arr[i] ;      
        else{
            data_tmp[i].Real = 0;
            data_tmp[i].Img  = 0;
        }
    }

    for (int i = 0; i < arr_len; i++)
    {
        res[i] = data_tmp[count] ;
        TOG_BIT(count,tmp_size-1);
        if(i!=0){
            bit = 1 ;
            for (int j = 1; j < tmp_size; j++)
            {
                bit*=2 ;
                if(i%(bit)==0)
                    TOG_BIT(count,tmp_size-1-j);
            }
        }       

    }

    for (int i = 0; i < arr_len; i++)
    {
        data_tmp[i] = res[i] ;
    }

    for (int i = 0; i < tmp_size; i++)
    {
        input*= 2 ;
        for (int j = 0; j < pow(2,tmp_size-1-i); j++)
        {
            fft_subgroup(&res[j*input],&data_tmp[j*input],roots,input,arr_len);
        }   
    }

    free(roots);
    free(data_tmp);

    return res ;
    
}

Complex_t* Ifft_data(Complex_t *data_arr,int size){


    unsigned char tmp_size = logf(size)/logf(2) + 1;

    int arr_len =1;

    int input = arr_len ;

    unsigned  int count = 0 ;

    int bit = 1 ;
    //2^tmp_size

    for(int i =0 ; i<tmp_size ;i++){
        arr_len *=2 ;
    }

    Complex_t * res = malloc(sizeof(Complex_t)*arr_len);
    // Complex_t * data_tmp = malloc(sizeof(Complex_t)*arr_len);
    Complex_t * roots =malloc(sizeof(Complex_t)*arr_len/2);

    for (int i = 0; i < arr_len/2; i++)
    {
        roots[i].Real=cosf((2*pi*i)/arr_len);
        roots[i].Img=sinf((2*pi*i)/arr_len);
    }

    // for (int i = 0; i < arr_len; i++)
    // {
    //     data_tmp[i] = data_arr[i] ;      
    // }

    int iterrator =1;

    for (int i = 0; i < tmp_size; i++)
    {
        for (int j = 0; j < iterrator ; j++)
        {
            Ifft_subgroup(&res[j*input],&data_arr[j*input],roots,input,arr_len);
        }

        input/= 2 ; 
        iterrator*=2;  
    }

    for(int i =0 ; i<arr_len ; i++){
        data_arr[i].Real /= arr_len ;
        data_arr[i].Img /= arr_len ;
    }
    
    for (int i = 0; i < arr_len; i++)
    {
        res[i] = data_arr[count] ;
        TOG_BIT(count,tmp_size-1);
        if(i!=0){
            bit = 1 ;
            for (int j = 1; j < tmp_size; j++)
            {
                bit*=2 ;
                if(i%(bit)==0)
                    TOG_BIT(count,tmp_size-1-j);
            }
        }       

    }

    // for (int i = 0; i < arr_len; i++)
    // {
    //     data_tmp[i] = res[i] ;
    // }

    free(roots);

    return res ;
    
}


