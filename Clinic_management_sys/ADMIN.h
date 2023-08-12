#include "STD_TYPES.h"

typedef struct rev
{
	u8 id;
	struct rev* next;
}rev;

typedef struct patient
{
	u32 id;
	u8 age;
	s8 gender;
	struct rev* slot;
	struct patient *next;
	s8 name[];
}patient;


void add_p(patient* head)
{
	patient* ptr=head;
	patient* tmp1=head;
	patient* tmp=malloc(sizeof(patient));
	tmp->next=NULL;
	tmp->slot=NULL;
	
	printf("enter the name:");
	scanf("%s",&tmp->name);
	
	printf("enter the age:");
	scanf("%u",&tmp->age);
	printf("enter the gender M or F:");
	scanf(" %c",&tmp->gender);
	printf("enter the ID:");
	scanf("%u",&tmp->id);
	
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	ptr->next=tmp;
	
	while(tmp1->next!=NULL)
	{
		while(tmp->id==tmp1->id)
		{
			printf("this ID is alrady existed\n enter another one:");
			scanf("%u",&tmp->id);
		}
		tmp1=tmp1->next;
	}
	
}

void edit_p(patient*p,u32 tmp)
{
	patient*ptr=p;
	while(ptr!=NULL)
	{
		if(tmp==ptr->id)
		{
			printf("name: %s\n",ptr->name);
			printf("age: %u\n",ptr->age);
			printf("gender: %c\n",ptr->gender);
			printf("edit the name:");
			scanf("%s",&ptr->name);
			printf("edit the age:");
			scanf("%u",&ptr->age);
			printf("edit the gender M or F:");
			scanf(" %c",&ptr->gender);
			break;
		}
		ptr=ptr->next;
	}
}

void print_list(patient* head)
{
	u8 count=0;
	
	patient* ptr=head;
	ptr=ptr->next;
	printf("-------------------------------------\n");
	while(ptr!=NULL)
	{
		printf("\tname: %s \n",ptr->name);
		printf("\tage: %u \n",ptr->age);
		printf("\tgender: %c \n",ptr->gender);
		printf("\tID: %u \n",ptr->id);
		printf("-------------------------------------\n");
		ptr=ptr->next;
		count++;
	}
	if(count==0)
	{
		printf("this list is empty\n");
		printf("-------------------------------------\n");
	}
}

void add_slot(rev* p,u8 x)
{
	rev* ptr1=p;
	u8 count=0;
	
	while(ptr1->next!=NULL)
	{
		ptr1=ptr1->next;
		count++;
	}
	
	if(count!=5)
	{
		rev* ptr=p;
		rev* tmp=malloc(sizeof(rev));
		tmp->id=x;
		tmp->next=NULL;
		while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=tmp;
	}
	
}
void print_slot(rev* head)
{
	u8 count=0;
	
	rev* ptr=head;
	rev* ptr1=head;
	rev* ptr2=head;
	rev* ptr3=head;
	rev* ptr4=head;
	printf("-------------------------------------\n");
	while(ptr!=NULL)
	{
		if(count==0)
		{
			ptr=ptr->next;
			count++;
		}
		else
		{
			switch((ptr->id)+1)
			{
				case 1:
					printf("\tslot(%u):from 2pm to 2:30pm\n",(ptr->id)+1);
					printf("-------------------------------------\n");
					break;
			}
			count++;
			ptr=ptr->next;
		}
	}
	count=0;
	while(ptr1!=NULL)
	{
		if(count==0)
		{
			ptr1=ptr1->next;
			count++;
		}
		else
		{
			switch((ptr1->id)+1)
			{
				case 2:
					printf("\tslot(%u):from 2:30pm to 3pm\n",(ptr1->id)+1);
					printf("-------------------------------------\n");
					break;
			}
			count++;
			ptr1=ptr1->next;
		}
	}
	count=0;
	while(ptr2!=NULL)
	{
		if(count==0)
		{
			ptr2=ptr2->next;
			count++;
		}
		else
		{
			switch((ptr2->id)+1)
			{
				case 3:
					printf("\tslot(%u):from 3:30pm to 4pm\n",(ptr2->id)+1);
					printf("-------------------------------------\n");
					break;
			}
			count++;
			ptr2=ptr2->next;
		}
	}
	count=0;
	while(ptr3!=NULL)
	{
		if(count==0)
		{
			ptr3=ptr3->next;
			count++;
		}
		else
		{
			switch((ptr3->id)+1)
			{
				case 4:
					printf("\tslot(%u):from 4pm to 4:30pm\n",(ptr3->id)+1);
					printf("-------------------------------------\n");
					break;
			}
			count++;
			ptr3=ptr3->next;
		}
	}
	count=0;
	while(ptr4!=NULL)
	{
		if(count==0)
		{
			ptr4=ptr4->next;
			count++;
		}
		else
		{
			switch((ptr4->id)+1)
			{
				case 5:
					printf("\tslot(%u):from 4:30pm to 5pm\n",(ptr4->id)+1);
					printf("-------------------------------------\n");
					break;
			}
			count++;
			ptr4=ptr4->next;
		}
	}
	if(count==1)
	{
		printf("this list is empty\n");
		printf("-------------------------------------\n");
	}
	
}
void print_p(patient* head,u8 tmp)
{
	u8 count=0;
	patient*ptr=head;
	while(ptr!=NULL)
	{
		if(tmp==ptr->id)
		{
			count++;
			printf("name: %s\n",ptr->name);
			printf("age: %u\n",ptr->age);
			printf("gender: %c\n",ptr->gender);
			break;
		}
		ptr=ptr->next;
	}
	if(count==0)
		printf("\tno such ID\n");
	printf("-------------------------------------\n");

}
void print_p_res(patient* head,u32 tmp)
{
	patient*ptr=head;
	while(ptr!=NULL)
	{
		if(tmp==ptr->id)
		{
			printf("name: %s\n",ptr->name);
			printf("age: %u\n",ptr->age);
			printf("gender: %c\n",ptr->gender);
			switch(ptr->slot->id)
			{
				case 0:
					printf("\tfrom 2pm to 2:30pm\n");
					printf("-------------------------------------\n");
					break;
				case 1:
					printf("\tfrom 2:30pm to 3pm\n");
					printf("-------------------------------------\n");
					break;
				case 2:
					printf("\tfrom 3pm to 3:30pm\n");
					printf("-------------------------------------\n");
					
					break;
				case 3:
					printf("\tfrom 4pm to 4:30p\n");
					printf("-------------------------------------\n");
					break;
				case 4:
					printf("\tfrom 4:30pm to 5pm\n");
					printf("-------------------------------------\n");
					break;
				default:
					printf("\tno reservation\n");
					break;
			}
			break;
		}
		ptr=ptr->next;
	}
}
void delet_slot(rev* slot,u8 id1)
{
	rev* ptr=slot;
	rev* tmp=slot;
	rev* tmp1=slot;
	
	if(slot->next!=NULL)	
		while(ptr->next!=NULL)
		{
			tmp=tmp1->next;
			
			if(tmp->id==id1)
			{
				ptr->next=tmp->next;
				free(tmp);
				tmp->next=NULL;
				break;
			}
			else if(tmp->id!=id1)
				ptr=ptr->next;
			
			tmp1=ptr;
		}
}

void delet_p_res(patient*p,u8 z)
{
	patient*ptr=p;
	ptr=ptr->next;
	
	while(ptr!=NULL)
	{
		if(ptr->slot!=NULL)
		{
			if(ptr->slot->id==z)
			{	
				ptr->slot=NULL;
				break;
			}
		}
		ptr=ptr->next;
	}
}

void add_res(rev*x,u8 y,patient*p,u8 z,rev* head)
{
	u8 count=0;
	
	rev*ptr1=x;
	patient*ptr=p;
	
	while(ptr!=NULL)
	{
		if(z==ptr->id)
		{
			count++;
			break;
		}
		ptr=ptr->next;
	}
	if(count==1)
	{
		while(ptr1!=NULL)
		{
			if((y-1)==ptr1->id)
			{
				break;
			}
			ptr1=ptr1->next;
		}
		if(ptr->slot==NULL)
		{
			ptr->slot=ptr1;
			add_slot(head,y-1);
			delet_slot(x,y-1);
		}
		else if(ptr->slot!=NULL)
		{
			printf("\tthis patient has alrady reserved\n");
		}
	}	
	else
		printf("\tinvalid reservation\n");
	printf("-------------------------------------\n");

}

void print_unslot(rev* head,patient* pt)
{
	u8 count=0;
	patient* p=pt;
	patient* p1=pt;
	patient* p2=pt;
	patient* p3=pt;
	patient* p4=pt;
	
	rev* ptr=head;
	rev* ptr1=head;
	rev* ptr2=head;
	rev* ptr3=head;
	rev* ptr4=head;
	
	ptr=ptr->next;
	p=p->next;
	
	ptr1=ptr1->next;
	p1=p1->next;
	
	ptr2=ptr2->next;
	p2=p2->next;
	
	ptr3=ptr3->next;
	p3=p3->next;
	
	ptr4=ptr4->next;
	p4=p4->next;
	
	printf("-------------------------------------\n");
	while(ptr!=NULL)
	{
		
		switch((ptr->id)+1)
		{
			case 1:
				printf("\tslot(%u):from 2pm to 2:30pm\t",(ptr->id)+1);
				while(p!=NULL)
				{
					if(p->slot!=NULL)
						if(p->slot->id==ptr->id)
						{
							count++;
							printf("ID: %u\n",p->id);
							printf("-------------------------------------\n");
							break;
						}
					p=p->next;
				}
				break;
		}
		ptr=ptr->next;
	}
	
	while(ptr1!=NULL)
	{
		
		switch((ptr1->id)+1)
		{
			case 2:
				printf("\tslot(%u):from 2:30pm to 3pm\t",(ptr1->id)+1);
				while(p1!=NULL)
				{
					if(p1->slot!=NULL)
						if(p1->slot->id==ptr1->id)
						{
							count++;
							printf("ID: %u\n",p1->id);
							printf("-------------------------------------\n");
							break;
						}
					p1=p1->next;
				}
				break;
		}
		ptr1=ptr1->next;
	}
	
	while(ptr2!=NULL)
	{
		
	
		switch((ptr2->id)+1)
		{
			case 3:
				printf("\tslot(%u):from 3:30pm to 4pm\t",(ptr2->id)+1);
				while(p2!=NULL)
				{
					if(p2->slot!=NULL)
						if(p2->slot->id==ptr2->id)
						{
							count++;
							printf("ID: %u\n",p2->id);
							printf("-------------------------------------\n");
							break;
						}
					p2=p2->next;
				}
				break;
		}
		ptr2=ptr2->next;
	
	}

	while(ptr3!=NULL)
	{
		

		switch((ptr3->id)+1)
		{
			case 4:
				printf("\tslot(%u):from 4pm to 4:30pm\t",(ptr3->id)+1);
				while(p3!=NULL)
				{
					if(p3->slot!=NULL)
						if(p3->slot->id==ptr3->id)
						{
							count++;
							printf("ID: %u\n",p3->id);
							printf("-------------------------------------\n");
							break;
						}
					p3=p3->next;
				}
				break;
		}
		ptr3=ptr3->next;
	
	}
	
	while(ptr4!=NULL)
	{
		
		switch((ptr4->id)+1)
		{
			case 5:
				printf("\tslot(%u):from 4:30pm to 5pm\t",(ptr4->id)+1);
				while(p4!=NULL)
				{
					if(p4->slot!=NULL)
						if(p4->slot->id==ptr4->id)
						{
							count++;
							printf("ID: %u\n",p4->id);
							printf("-------------------------------------\n");
							break;
						}
					p4=p4->next;
				}
				break;
		}
		count++;
		ptr4=ptr4->next;
	
	}
	if(count==0)
	{
		printf("this list is empty\n");
		printf("-------------------------------------\n");
	}
	
}


