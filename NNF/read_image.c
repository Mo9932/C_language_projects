#include <stdio.h>
#include <time.h>
#include <math.h>
#include "MNF.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#define Y (2)
#define X (4*Y)
#define PI (22.0/7)




int main(){
    srand(time(NULL));  
    int width,hight,channels;
    uint_8 *image = stbi_load("img_1.jpg", &width, &hight, &channels, 0);
    printf("width is: %d, hight is: %d,number of channels: %d\n",width,hight,channels);

    float data[width*hight*(X+1)];
    

    for(int i=0;i<hight;i++){    
        for(int j=0;j<width;j++){
            int plus =0 ;
            float in1 = PI*((float)(2*j)/(width-1)-1);
            float in2 = PI*((float)(2*i)/(hight-1)-1);


            for(int k=1 ; k<=(Y);k++){
                data[(i*width+j)*(X+1)+plus++] = sinf(k*in1) ;
                data[(i*width+j)*(X+1)+plus++] = cosf(k*in1) ;
            }
            for(int k=1 ; k<=(Y);k++){
                data[(i*width+j)*(X+1)+plus++] = sinf(k*in2) ;
                data[(i*width+j)*(X+1)+plus++] = cosf(k*in2) ;
            }

            data[(i*width+j)*(X+1)+plus] = (float)image[i*width+j]/255;
        }
    }

  

    float rate = 1 ;
    int train_count =3*10000;
    MAT td ,ti,to;
    td=data_init(td,width*hight,(X+1),data);
    ti = data_sap(ti,td,(X),0);
    to = data_sap(to,td,1,(X));

    nn nural, grade ;
    
    int arch[]={X,4,4,6,1};
    nural = NN_INIT(arch);
    grade = NN_INIT(arch);

    nn_set_activ(SIGMOID,SIGMOID);

    nn_rand(nural,-5,5);
    printf("cost before = %f\n",nn_cost(nural,ti,to));
    nn_train(nural,grade,ti,to ,rate ,train_count);
    printf("cost after = %f\n",nn_cost(nural,ti,to));

    int new_width =600;
    int new_hight =600;
   uint_8 new_image[new_width*new_hight];

    for(int i=0;i<new_hight;i++){    
        for(int j=0;j<new_width;j++){

            float in1 = PI*((float)(2*j)/(new_width-1)-1);
            float in2 = PI*((float)(2*i)/(new_hight-1)-1);
            int plus =0 ; 
            for(int k=1 ; k<=Y ; k++){
                NN_INPUT(nural,plus++,sinf(k*in1));
                NN_INPUT(nural,plus++,cosf(k*in1));
            }
            for(int k=1 ; k<=Y ; k++){
                NN_INPUT(nural,plus++,sinf(k*in2));
                NN_INPUT(nural,plus++,cosf(k*in2));
            }

            nn_forward_dir(nural);
            new_image[i*new_width+j] = (uint_8)(NN_OUTPUT(nural,0)*255);
            
        }
    }
    printf("Number of learning iterations = %i \nwith %f learning rate\n",train_count,rate);

    stbi_write_jpg("new_image_relu_1.jpg",new_width,new_hight,1,new_image,100);
    stbi_image_free(image);
    nn_free(nural);
    nn_free(grade);


    return 0;
}