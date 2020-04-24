#include <stdio.h>
#include <stdlib.h>

struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};
struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};
void insert(struct nodeStudent **ns, int i, int m)
{
	struct nodeStudent *temp, *tmp, *t;
	
	temp=*ns;
	
	if(*ns==NULL)
	{
		*ns=malloc(sizeof(struct nodeStudent));
		(*ns)->studentID=i;
		(*ns)->midterm=m;
		(*ns)->next=NULL;
	}
	else
	{
		if((*ns)->midterm<m)
		{
			t=malloc(sizeof(struct nodeStudent));
			t->studentID=i;
			t->midterm=m;
			t->next=(*ns);
			*ns=t;
		}
		else
		{
			while(temp!=NULL && temp->midterm>=m)
			{
				tmp=temp;
				temp=temp->next;
			}
		
			t=malloc(sizeof(struct nodeStudent));
			t->studentID=i;
			t->midterm=m;
			t->next=temp;
			tmp->next=t;
		}			
	}
}

void printAll(struct nodeClass *temp)
{
	while(temp!=NULL)
	{
		printf("%d %.1f\n",temp->classID, temp->classMidtermAverage);
		
		struct nodeStudent *tempNs=temp->studentPtr;
		while(tempNs!=NULL)
		{
			printf("%d %d\n",tempNs->studentID,tempNs->midterm);
			tempNs=tempNs->next;
		}
		temp=temp->next;
		printf("\n");
	}
}

void printClassList(struct nodeClass *temp, int p)
{
	while(temp!=NULL)
	{
		if(temp->classID==p)
		{
			printf("%d %.1f\n",temp->classID, temp->classMidtermAverage);
		
			struct nodeStudent *tempNs=temp->studentPtr;
			while(tempNs!=NULL)
			{
				printf("%d %d\n",tempNs->studentID,tempNs->midterm);
				tempNs=tempNs->next;
			}
			printf("\n");
		}
		temp=temp->next;
	}
}
int main()
{
	struct nodeClass *headClass, *temp;
	int c=1, count=99;
	int id, midterm;
	struct nodeStudent *temps;
	int cToPrint;
	
	headClass=malloc(sizeof(struct nodeClass));
	headClass->classID=1;
	headClass->classMidtermAverage=0.0;
	headClass->next=NULL;
	headClass->studentPtr=NULL;
	temp=headClass;
	
	while(c<4)
	{
		temp->next=malloc(sizeof(struct nodeClass));
		temp=temp->next;
		temp->classID=++c;
		temp->classMidtermAverage=0.0;
		temp->next=NULL;
		temp->studentPtr=NULL;
	}
	
	temp=headClass;
	
	scanf("%d%d",&id,&midterm);
	
	while(id!=-1)
	{
		if(id<77000)
			insert(&(headClass->studentPtr),id,midterm);
		else if(id<88000)
			insert(&(headClass->next->studentPtr),id,midterm);
		else if(id<99000)
			insert(&(headClass->next->next->studentPtr),id,midterm);
		else
			insert(&(headClass->next->next->next->studentPtr),id,midterm);
		
		scanf("%d%d",&id,&midterm);
	}
	
	printf("\n");
	
	printAll(headClass);
	
	while(temp!=NULL)
	{
		struct nodeStudent *tempNs=temp->studentPtr;
		c=0;
		while(tempNs!=NULL)
		{
			tempNs=tempNs->next;
			c++;
		}
		temp=temp->next;
		if(count>c)
			count=c;
	}
	
	temp=headClass;
	while(temp!=NULL)
	{
		struct nodeStudent *tempNs=temp->studentPtr;
		int total=0;
		c=1;
	
		while(tempNs!=NULL && c<count)
		{
			total=total+tempNs->midterm;
			tempNs=tempNs->next;
			c++;
		}
		total=total+tempNs->midterm;
		
		struct nodeStudent *tempDel1=tempNs->next;
		
		while(tempDel1!=NULL)
		{
			struct nodeStudent *tempDel2;
			tempDel2=tempDel1;
			tempDel1=tempDel1->next;
			free(tempDel2);
		}
		tempNs->next=NULL;
		temp->classMidtermAverage=(double)total/count;
		temp=temp->next;
	}
	
	temp=headClass;
	while(temp!=NULL)
	{
		printf("%d %.1f\n",temp->classID, temp->classMidtermAverage);
		temp=temp->next;
	}
	printf("\n");
	
	printAll(headClass);
	
	printf("Enter class id:");
	scanf("%d",&cToPrint);

	printClassList(headClass,cToPrint);
	return 0;
}