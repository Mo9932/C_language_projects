#include "MNF.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for implementing and chosing the activation function for output leyer and the hidden leyers
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************



float randf(void){
    return (float)rand()/(float)RAND_MAX;
}

float sigmf(float x){
    return 1/(1 + expf(-x)) ; 
}

float leku(float x){
    return (x >= 0) ? x : ((float)x/nunlinearity_factor) ;
}

float relu(float x){
    return (x > 0) ? x : 0 ;
}


void nn_set_activ(uint_8 first,uint_8 second){
    

    switch(first){
        case SIGMOID:   
            activ_f[0] = mat_sigmf;
            back_prob_f = nn_sig_backprob ;
        break;

        case LEKU:   
            activ_f[0] = mat_leku;
            back_prob_f = nn_rel_lek_backprob ;
        break;

        case RELU:
            activ_f[0] = mat_relu;
            back_prob_f = nn_rel_backprob ;
        break;
    }
    switch(second){
        case SIGMOID: 
            activ_f[1] = mat_sigmf;
        break;

        case LEKU:
            activ_f[1] = mat_leku;
        break;

        case RELU:
            activ_f[1] = mat_relu;
        break;
    }
}



//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for oprations on matrixes
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************


void mat_fill(MAT m,float x){

    for(int i=0 ; i < m.rows ; i++){
        for(int j=0 ; j < m.cols ; j++){
            MAT_AT(m,i,j) = x ;
        }
    }
}

void mat_rand(MAT m , float ll ,float ul){
    for(int i=0 ; i < m.rows ; i++){
        for(int j=0 ; j < m.cols ; j++){
            MAT_AT(m,i,j) = randf()*(ul-ll)+ll ;
        }
    }
}

void matdot(MAT dst , MAT src1 , MAT src2){
    for(int i=0; i< dst.rows;i++){
        for(int j=0; j< dst.cols;j++){
            MAT_AT(dst,i,j) = 0 ;
            for(int k=0;k<src1.cols ; k++)
                MAT_AT(dst,i,j) += MAT_AT(src1,i,k)*MAT_AT(src2,k,j);
        }
    }
}
void matsum(MAT dst , MAT src){
    for(int i=0 ; i< dst.rows ; i++){
        for(int j=0 ; j<dst.cols; j++){
            MAT_AT(dst,i,j) += MAT_AT(src,i,j);
        }
    }
}

void matsub(MAT dst, MAT src){
    for(int i=0 ; i< dst.rows ; i++){
        for(int j=0 ; j<dst.cols; j++){
            MAT_AT(dst,i,j) -= MAT_AT(src,i,j);
        }
    }
}

MAT mat_alloc(int row ,int col){
    MAT m ;
    m.rows= row ;
    m.cols= col ;
    m.ptr = malloc(sizeof(*m.ptr)*row*col);

    return m;
}

void mat_print(MAT m, char *name){

    printf("%s = [\n",name);
    for(int i=0 ; i<m.rows ; i++){
        for(int j=0 ; j<m.cols ; j++){
            printf("%f  ",MAT_AT(m,i,j));
        }
        printf("\n");
    }
    printf("]\n");
}

void mat_sap(MAT dst, MAT src,int entry){

    for(int i=0 ; i < dst.rows ; i++){
        for(int j=0 ; j < dst.cols ; j++){
            MAT_AT(dst,i,j) = MAT_AT(src,i,j+entry);
        }
    }

}

void mat_row(MAT *dst, MAT src,int row){
    
    dst->ptr = &MAT_AT(src,row,0);
}

void mat_leku(MAT m){
    for(int i=0 ; i < m.rows ; i++){
        for(int j=0 ; j < m.cols ; j++){
            MAT_AT(m,i,j) = relu(MAT_AT(m,i,j));
        }
    }
}
void mat_sigmf(MAT m){
    for(int i=0 ; i < m.rows ; i++){
        for(int j=0 ; j < m.cols ; j++){
            MAT_AT(m,i,j) = sigmf(MAT_AT(m,i,j));
        }
    }
}
void mat_relu(MAT m){
    for(int i=0 ; i < m.rows ; i++){
        for(int j=0 ; j < m.cols ; j++){
            MAT_AT(m,i,j) = relu(MAT_AT(m,i,j));
        }
    }
}



//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for initiating the data
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************


MAT data_init(MAT m,int row,int col,float *data){
    m.rows = row ;
    m.cols = col ;
    m.ptr = data ;
    return m ;
}

MAT data_sap(MAT m,MAT data,int col,int entry){
    m.rows = data.rows ;
    m.cols = col ;
    m = mat_alloc(m.rows,m.cols);
   
    mat_sap(m,data,entry);
    
    return m;
}


//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for operations on the nural
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

nn nn_init(int *arr,int size){
    nn tmp ;

    int mat_size=0 ;

    for(int i=0 ; i < size; i++){
        mat_size += sizeof(mat_alloc(1,1)) ;
    }

    tmp.nn_size = size;

    tmp.b = malloc(mat_size);

    tmp.w = malloc(mat_size-1);

    tmp.a = malloc(mat_size+1);


    for(int i=0 ; i < size ; i++){
        tmp.w[i] = mat_alloc(arr[i],arr[i+1]);
    }
    for(int i=0 ; i < size-1 ; i++){
        tmp.b[i] = mat_alloc(1,arr[i+1]);
    }
    for(int i=0 ; i < size ; i++){
        tmp.a[i] = mat_alloc(1,arr[i]);
    }

    return tmp ;
}

void nn_print(nn m ,char *name){

    printf("%s =[\n",name);
    for(int i =0 ; i < m.nn_size-1 ; i++){
        MAT_PRINT(m.w[i]);
    }
    printf("--------------------------------------\n");
    for(int i =0 ; i < m.nn_size-1 ; i++){
        MAT_PRINT(m.b[i]);
    }
    printf("--------------------------------------\n");

    for(int i =0 ; i < m.nn_size ; i++){
        MAT_PRINT(m.a[i]);
    }
    printf("--------------------------------------\n");

    printf("]\n");
}

void nn_rand(nn m,float ll,float ul){
    for(int i =0 ; i < m.nn_size-1 ; i++){
        mat_rand(m.w[i],ll,ul);
    }
   
    for(int i =0 ; i < m.nn_size-1 ; i++){
        mat_rand(m.b[i],ll,ul);
    }
   
}

float nn_cost(nn m,MAT ti,MAT to){
    
    float out , d , c =0 ;

    for(int i =0 ;i< ti.rows ;i++){
        out = MAT_AT(to , i , 0);
        nn_forward(m,ti,i);
        d = out - MAT_AT(m.a[m.nn_size-1], 0 , 0);
        c += d*d ;
    }

    return c/ti.rows;
}

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for back_probagation functions
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

void nn_zero(nn m){
     for(int i =0 ; i < m.nn_size-1 ; i++){
        mat_fill(m.w[i],0);
    }
   
    for(int i =0 ; i < m.nn_size-1 ; i++){
        mat_fill(m.b[i],0);
    }
   
}

void nn_sig_backprob(nn dst ,nn src ,MAT ti,MAT to){
   
    float a , er ,la ,lw ;
    
    nn_zero(dst);
    for(int j=0 ; j < ti.rows ; j++){
        nn_forward(src,ti,j);

        for(int i=0 ; i < dst.nn_size ;i++){
            mat_fill(dst.a[i],0) ;
        }

        for(int i = 0 ;i < to.cols ;i++){
            MAT_AT(dst.a[dst.nn_size-1],0,i) = MAT_AT(src.a[src.nn_size-1],0,i) - MAT_AT(to,j,i) ;
        }
    
        for(int l = dst.nn_size-1 ; l > 0 ; l--){
            for(int i =0 ; i < dst.a[l].cols ; i++){
                a = MAT_AT(src.a[l],0,i) ;
                er = MAT_AT(dst.a[l],0,i) ;
                MAT_AT(dst.b[l-1] , 0 , i) += 2*er*(1-a)*a ;
                for(int w = 0 ; w < src.a[l-1].cols ; w++){
                    la = MAT_AT(src.a[l-1],0,w);
                    lw = MAT_AT(src.w[l-1],w,i);

                    MAT_AT(dst.w[l-1],w,i) += 2*er*a*(1-a)*la; 
                    MAT_AT(dst.a[l-1],0,w) += 2*er*a*(1-a)*lw; 
                }
            }
        }
    }

    for(int i=0 ; i < dst.nn_size-1;i++){
        for(int j=0 ; j < dst.w[i].rows ; j++){
            for(int k =0 ; k < dst.w[i].cols ; k++){
                MAT_AT(dst.w[i],j,k) /= ti.rows ;
            }
        }
        for(int j=0 ; j < dst.b[i].rows ; j++){
            for(int k =0 ; k < dst.b[i].cols ; k++){
                MAT_AT(dst.b[i],j,k) /= ti.rows ;
            }
        }
    }
}

void nn_rel_lek_backprob(nn dst ,nn src ,MAT ti,MAT to){

    float a , er ,la ,lw ;
    
    nn_zero(dst);
    for(int j=0 ; j < ti.rows ; j++){
        nn_forward(src,ti,j);

        for(int i=0 ; i < dst.nn_size ;i++){
            mat_fill(dst.a[i],0) ;
        }

        for(int i = 0 ;i < to.cols ;i++){
            MAT_AT(dst.a[dst.nn_size-1],0,i) = MAT_AT(src.a[src.nn_size-1],0,i) - MAT_AT(to,j,i) ;
        }
       
        for(int l = dst.nn_size-1 ; l > 0 ; l--){
            for(int i =0 ; i < dst.a[l].cols ; i++){
                a = MAT_AT(src.a[l],0,i) ;
                er = MAT_AT(dst.a[l],0,i) ;
                if(l == dst.nn_size-1){   
                    
                    MAT_AT(dst.b[l-1] , 0 , i) += 2*er*(1-a)*a ;
                }
                else{
                    MAT_AT(dst.b[l-1] , 0 , i) += 2*er ;
                }
                for(int w = 0 ; w < src.a[l-1].cols ; w++){
                    la = MAT_AT(src.a[l-1],0,w);
                    lw = MAT_AT(src.w[l-1],w,i);
                   if(l == dst.nn_size-1){
                        MAT_AT(dst.w[l-1],w,i) += 2*er*a*(1-a)*la; 
                        MAT_AT(dst.a[l-1],0,w) += 2*er*a*(1-a)*lw; 
                   }
                   else{
                        MAT_AT(dst.w[l-1],w,i) += 2*er*la;
                        if( la > 0 ) 
                            MAT_AT(dst.a[l-1],0,w) += 2*er*lw; 
                        else if(la < 0)
                            MAT_AT(dst.a[l-1],0,w) -= er*lw/nunlinearity_factor;
                   }
                }
            }
        }
    }

    for(int i=0 ; i < dst.nn_size-1;i++){
        for(int j=0 ; j < dst.w[i].rows ; j++){
            for(int k =0 ; k < dst.w[i].cols ; k++){
                MAT_AT(dst.w[i],j,k) /= ti.rows ;
            }
        }
        for(int j=0 ; j < dst.b[i].rows ; j++){
            for(int k =0 ; k < dst.b[i].cols ; k++){
                MAT_AT(dst.b[i],j,k) /= ti.rows ;
            }
        }
    }
}

void nn_rel_backprob(nn dst ,nn src ,MAT ti,MAT to){

    float a , er ,la ,lw ;
    
    nn_zero(dst);
    for(int j=0 ; j < ti.rows ; j++){
        nn_forward(src,ti,j);

        for(int i=0 ; i < dst.nn_size ;i++){
            mat_fill(dst.a[i],0) ;
        }

        for(int i = 0 ;i < to.cols ;i++){
            MAT_AT(dst.a[dst.nn_size-1],0,i) = MAT_AT(src.a[src.nn_size-1],0,i) - MAT_AT(to,j,i) ;
        }
       
        for(int l = dst.nn_size-1 ; l > 0 ; l--){
            for(int i =0 ; i < dst.a[l].cols ; i++){
                a = MAT_AT(src.a[l],0,i) ;
                er = MAT_AT(dst.a[l],0,i) ;
                if(l == dst.nn_size-1){   
                    
                    MAT_AT(dst.b[l-1] , 0 , i) += 2*er*(1-a)*a ;
                }
                else{
                    MAT_AT(dst.b[l-1] , 0 , i) += 2*er ;
                }
                for(int w = 0 ; w < src.a[l-1].cols ; w++){
                    la = MAT_AT(src.a[l-1],0,w);
                    lw = MAT_AT(src.w[l-1],w,i);
                   if(l == dst.nn_size-1){
                        MAT_AT(dst.w[l-1],w,i) += 2*er*a*(1-a)*la; 
                        MAT_AT(dst.a[l-1],0,w) += 2*er*a*(1-a)*lw; 
                   }
                   else{
                        MAT_AT(dst.a[l-1],0,w) += 2*er*lw; 
                        MAT_AT(dst.w[l-1],w,i) += 2*er*la;
                        // if( la > 0 ) 
                        // else if(la < 0)
                        //     MAT_AT(dst.a[l-1],0,w) -= er*lw/nunlinearity_factor;
                   }
                }
            }
        }
    }

    for(int i=0 ; i < dst.nn_size-1;i++){
        for(int j=0 ; j < dst.w[i].rows ; j++){
            for(int k =0 ; k < dst.w[i].cols ; k++){
                MAT_AT(dst.w[i],j,k) /= ti.rows ;
            }
        }
        for(int j=0 ; j < dst.b[i].rows ; j++){
            for(int k =0 ; k < dst.b[i].cols ; k++){
                MAT_AT(dst.b[i],j,k) /= ti.rows ;
            }
        }
    }
}


//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for training
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

void nn_forward(nn m , MAT input ,int row){
    
    mat_row(&m.a[0],input ,row);
    for(int i=0 ; i < m.nn_size-1 ;i++){
        matdot(m.a[i+1],m.a[i],m.w[i]);
        matsum(m.a[i+1],m.b[i]);
        if(i == m.nn_size-2)
            activ_f[1](m.a[i+1]);
        else
            activ_f[0](m.a[i+1]);
    }
}

void nn_learn(nn dst,nn src,float rate){

    for(int i=0 ; i<src.nn_size-1;i++){
        for(int j=0 ; j<src.w[i].rows;j++){
            for(int k=0 ; k<src.w[i].cols;k++){
                MAT_AT(dst.w[i],j,k) -= rate*MAT_AT(src.w[i],j,k) ;
            }
        }
        for(int j=0 ; j<src.b[i].rows;j++){
            for(int k=0 ; k<src.b[i].cols;k++){
                MAT_AT(dst.b[i],j,k) -= rate*MAT_AT(src.b[i],j,k) ;
            }
            
        }
    }
}



void nn_train(nn nural,nn grade,MAT ti,MAT to ,float rate,int train_count){
    for(int i =0 ; i < train_count;i++){
        back_prob_f(grade,nural,ti,to);
        nn_learn(nural,grade,rate);
        if(i%10000==0)printf("cost = %f\n",nn_cost(nural,ti,to));
    }
}

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for testing the nural network
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

void nn_forward_dir(nn m){
    for(int i=0 ; i < m.nn_size-1 ;i++){
        matdot(m.a[i+1],m.a[i],m.w[i]);
        matsum(m.a[i+1],m.b[i]);
        if(i == m.nn_size-2)
            activ_f[1](m.a[i+1]);
        else
            activ_f[0](m.a[i+1]);
    }
}


//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

/*
    this section is for finishing the work with the nural network
*/

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************


void nn_free(nn g){
    free(g.w);
    free(g.b);
    free(g.a);
}
