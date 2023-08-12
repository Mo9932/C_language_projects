#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "ADMIN.h"


void main()
{
	u32 pass;
	u8 count=1,state,tmp,tmp1,count1=0;
	
	patient *queue=malloc(sizeof(patient));
	queue->next=NULL;
	
	rev *slot=malloc(sizeof(rev));
	slot->next=NULL;
	
	rev *un_slot=malloc(sizeof(rev));
	un_slot->next=NULL;
	
	for(int i=0;i<5;i++)
	{
		add_slot(slot,i);
	}
	
	while(1)
	{
		printf("chose the mode:\n");
		printf("enter 1 fore Admin mode\nenter 2 fore User mode\nenter 3 to exit\n");
		
		scanf("%u",&tmp);
		
		
		//ADMIN mode starts here
		
		if(tmp==1)
		{
			printf("enter the password: ");
			scanf("%u",&pass);
			while(pass!=1234)
			{
				if(count==3)
				{
					printf("out of tries\n");
					break;
				}
				else 
				{
					printf("wrong password\n try again: ");
					scanf("%u",&pass);
					count++;
				}
			}
			if(pass==1234)
				while(1)
				{
					if(count1==0)
					{
						printf("---------------------Welcome-------------------\n");
						count1++;
					}
					
					printf("\tto add pationt enter 1\n");
					printf("\tto edit pationt enter 2\n");
					printf("\tto add and edit reservation enter 3\n");
					printf("\tto cancel reservation enter 4\n");
					printf("\tto print queue enter 5\n");
					printf("\tto print reservation enter 6\n");
					printf("\tto print unavailable reservation enter 7\n");
					printf("\tto print patient records enter 8\n");
					printf("\tto exit enter 9\n");
					printf("\tyour choise: ");
					scanf("%u",&state);
					printf("-----------------------------------------------\n");

					switch(state)
					{
						case 1:
							add_p(queue);
							break;
						case 2:
							printf("enter the patient ID:");
							scanf("%u",&tmp);
							edit_p(queue,tmp);
							break;
						case 3:
							printf("enter the patient ID:");
							scanf("%u",&tmp1);
							print_p(queue,tmp1);
							printf("the available reservations are:\n ");
							print_slot(slot);
							printf("chose your reservation number:");
							scanf("%u",&tmp);
							add_res(slot,tmp,queue,tmp1,un_slot);	
							break;
						case 4:
							printf("the unavailable reservations are:\n");
							print_slot(un_slot);
							printf("enter the number of reservation you want to free:");
							scanf("%u",&tmp);
							delet_slot(un_slot,tmp-1);
							add_slot(slot,tmp-1);
							delet_p_res(queue,tmp-1);
							break;
						case 5:
							printf("patient list:\n");
							print_list(queue);
							break;
						case 6:
							printf("the available reservations are:\n");
							print_slot(slot);
							break;
						case 7:
							printf("the unavailable reservations are:\n");
							print_unslot(un_slot,queue);
							break;
						case 8:
							printf("enter the patient ID:");
							scanf("%u",&tmp1);
							print_p(queue,tmp1);
							break;
						case 9:
							printf("thank you\n");
							break;
						default:
							printf("wrong input\n");
							break;
					}
					if(state==9)
						break;
				}
		}
			//ADMIN mode ends here
			
			
			// USER mode starets here
		else if(tmp==2)	
		{
			while(1)
			{
				if(count1==0)
				{
					printf("---------------------Welcome-------------------\n");
					count1++;
				}
				printf("\tto print your recordes enter 1\n");
				printf("\tto view today`s reservations enter 2\n");
				printf("\tto exit enter 3\n");
				printf("\tyour choise: ");
				scanf("%u",&state);
				printf("-----------------------------------------------\n");
				
				switch(state)
				{
					case 1:
						printf("please enter your ID:");
						scanf("%u",&tmp);
						print_p(queue,tmp);
						break;
					case 2:
						printf("today`s reservations are:\n");
						print_unslot(un_slot,queue);
						break;
					case 3:
						printf("thank you\n");
						break;
					default:
						printf("wrong input\n");
						break;
				}
				if(state==3)
				break;
			}
		}
		else if(tmp==3)
		{
			printf("thank you\n");
			break;
		}
		else
			printf("\twrong input\n");
	}
	
	
		
		
		// USER mode ends here
		
		
}

