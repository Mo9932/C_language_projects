#include <stdio.h>

void rev_arr(int* arr,int size); 

 void main()
 {
	 int arr[10];
	 int size;
	 size=sizeof(arr)/sizeof(int);
	 
	 printf("enter 10 values\n");
	 
	 for(int i=0;i<10;i++)
	 {
		 printf("enter number: ");
		 scanf("%d",&arr[i]);
	 }
	 
	 rev_arr(arr,size);
	 
	 for(int i=0;i<10;i++)
	 {
		 printf("arr[%d]=\t%d\n",i,arr[i]);
	 }
 }
 
 void rev_arr(int* arr,int size)
 {
	 int tmp;
	 
	 for(int i=0;i<size/2;i++)
	 {
		tmp=arr[i]	;
		arr[i]=arr[(size-1)-i];
		arr[(size-1)-i]=tmp;	 
	 }
 }