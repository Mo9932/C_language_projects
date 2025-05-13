#ifndef _FFT_H
#define _FFT_H

#define pi  (3.14159265358979323846)

typedef struct{
    float Real ;
    float Img ;
}Complex_t;

void Complex_mul(Complex_t *res, Complex_t num1, Complex_t num2);

void fft_subgroup(Complex_t *res, Complex_t *data_arr, Complex_t *roots, int input_num, int arr_len);

void Ifft_subgroup(Complex_t *res, Complex_t *data_arr, Complex_t *roots, int input_num, int arr_len);

Complex_t* fft_data(Complex_t *data_arr, int size);

Complex_t* Ifft_data(Complex_t *data_arr,int size);


#endif //_FFT_H