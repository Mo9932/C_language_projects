/*  // MNNF stands for : Mohamed`s nural_network framework 
    // This is a framework to help in implementing a full connected nural networc
    // It gives you the abliti to chose different activation functions in the hidden leyers and the output leyer

    //***********************-----Usable functions-----***************************
    // 1- MAT data_init(MAT m,int row,int col,float *data);
    // 2- MAT data_sap(MAT m,MAT data,int col,int entry);
    // 3- void nn_set_activ(uint_8 first,uint_8 second)
    // 4- void nn_rand(nn m,float ll, float ul);
    // 5- void nn_train(nn nural,nn grade,MAT ti,MAT to ,float rate ,int train_count);
    // 6- float nn_cost(nn m,MAT ti,MAT to);
    // 7- NN_INPUT(m,i,j);
    // 8- void nn_forward_dir(nn m);
    // 9- NN_OUTPUT(m,i);


    // First in clude the frame work in your project #include "MFNN.h"

    // You can prepare the training data as following 

    // 1- the training moddel accepts the input and the output data as a 2D matrixes 
    // 2- create the data array as 1D array , each training sample is a row of training input and then the output as following [in,in,in,out,                                                                                                                                
                                                                                                                                in,in,in,out,
                                                                                                                                in,in,in,out ]
    // 03- I provide a MAT structur that have a number of rows and cols and the first adress of the 1D array of data
    // 04- creat three elements of MAT type  as following  MAT train_data, train_input, train_output;                                                                                                                           
    // 05- use the function data_int to initiate the training data -> train_data = data_int(train_data,row_num,col_num,data_array);
    // 06- use the function data_sap to saperate the input and the output data to 2 different matrixes -> train_input = data_sap(train_input,train_data,input_col_num,0);
                                                                                                          train_output = data_sap(train_output, train_data, output_col_num, input_col_num);
    // 07- creat the architecture of the nural network as 1D array first element is input number, last element is output number, add many elements you want each one is a hidde leyer with number of nurals = element
           int arch[]={input_leyer,5,11,.....,output_leyer};

    // 08- creat 2 element of nn type -> nn nural, grade; the actual nural and the other one to help in training
    // 09- initiate the nural and the grade using the function NN_INIT() -> nural = NN_INIT(the_architecture) ;  = grade_INIT(the_architecture) ;
    // 10- use the function nn_arnd() to randomaize the nural -> nn_rand(nural,lower_limit,uper_limit);
    // 11- use the function nn_set_activ() to chose the activation of the nural -> nn_set_activ(hidden_leyers_activation,output_leyers_activation);


    //********* the activation supported for now {SIGMOID,RELU,LEKU}******************


    // 12- use the function nn_train() to train the nural -> nn_train(nural, grade, train_input, train_output, learning_rate, train_count);
    // 13- use the function nn_cost() to see the current cost of the nural -> printf("%f",nn_cost(nural,train_input,train_output));--- the lower the cost the better the nural ---
    // 14- use the function NN_INPUT() to input a test sample to the nural -> NN_INPUT(nural,input_index,value) ;
    // 15- use the function nn_forward_dir() to test the nural -> nn_forward_dir(nural);
    // 16- use the function NN_OUTPUT() to test the nural -> NN_OUTPUT(nural,output_index);


    // note the nural may performe better with different activations and may not work with RELU and LEKU for hidden leyers but sigmoid always converge


*/




#ifndef MNF_H
#define MNF_H

#define SIGMOID 0
#define LEKU    1
#define RELU    2
#define nunlinearity_factor 10

typedef struct {
    int cols ;
    int rows ;
    int stride ;
    float *ptr ;
}MAT;



typedef struct {
    int nn_size ;
    MAT *w ;
    MAT *b ;
    MAT *a ;
}nn ;

typedef unsigned char      uint_8  ;
typedef unsigned short     uint_16 ;
typedef unsigned int       uint_32 ;
typedef unsigned long int  uint_64 ;

#define MAT_AT(m,i,j)   m.ptr[(i)*m.cols+(j)]
#define MAT_PRINT(m)    mat_print(m , #m)
#define NN_INIT(m)       nn_init(m , (sizeof(m)/sizeof(m[0])))
#define NN_PRINT(m)       nn_print(m , #m)
#define NN_INPUT(m,i,j)     MAT_AT(m.a[0],0,(i))=(j)
#define NN_OUTPUT(m,i)     MAT_AT(m.a[m.nn_size-1],0,(i))


float randf(void);
float sigmf(float x);
float leku(float x);
float relu(float x);


void (*activ_f[2])(MAT) ;
void (*back_prob_f)(nn,nn,MAT,MAT) ;
void nn_set_activ(uint_8 first,uint_8 second);

nn nn_init(int *arr,int size);
void nn_print(nn m ,char *name);
void nn_rand(nn m,float ll, float ul);
float nn_cost(nn m,MAT ti,MAT to);
void nn_forward(nn m ,MAT input,int row);
void nn_forward_dir(nn m);
void nn_diff(nn dst ,nn src ,MAT ti,MAT to,float eps);
void nn_backprob(nn dst ,nn src ,MAT ti,MAT to);
void nn_sig_backprob(nn dst ,nn src ,MAT ti,MAT to);
void nn_rel_lek_backprob(nn dst ,nn src ,MAT ti,MAT to);
void nn_rel_backprob(nn dst ,nn src ,MAT ti,MAT to);
void nn_learn(nn dst ,nn src ,float rate);
void nn_zero(nn src);
void nn_train(nn nural,nn grade,MAT ti,MAT to ,float rate ,int train_count);

void mat_rand(MAT m , float ll ,float ul);
void mat_fill(MAT m,float x);
void matdot(MAT dst , MAT src1 , MAT src2);
void matsum(MAT dst , MAT src);
MAT mat_alloc(int row ,int col);
void mat_print(MAT m , char *name);
void matsub(MAT dst, MAT src);
void mat_sigmf(MAT m);
void mat_leku(MAT m);
void mat_relu(MAT m);

void mat_row(MAT *dst, MAT src,int row);
void mat_sap(MAT dst, MAT src,int entry);

MAT data_init(MAT m,int row,int col,float *data);
MAT data_sap(MAT m,MAT data,int col,int entry);

void nn_free(nn g);


#endif //MNF