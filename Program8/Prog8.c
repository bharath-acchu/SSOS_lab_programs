/*******************************************************************************************************************************************************
	Design, develop and implement a C/C++/Java program to implement Banker’s algorithm. Assume suitable input required to demonstrate the results.

************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int alloc[10][10],max[10][10],need[10][10];
int avail[10],work[10],p,r,j,i,v=0;
bool finish[10];
bool check(int i)
{
	for(int j=0;j<r;j++)
	{
		if(need[i][j]>work[j])
			return false;
	}
	return true;
}
int main()
{
	printf("Enter the number of processes and resources\n");
	scanf("%d %d",&p,&r);
	int seq[p];
	printf("Enter the allocation values\n");
	for(int i=0;i<p;i++)
		for(j=0;j<r;j++)
			scanf("%d",&alloc[i][j]);
	printf("Enter the max values\n");
	for(int i=0;i<p;i++)
		for(j=0;j<r;j++)
			scanf("%d",&max[i][j]);	
	for(int i=0;i<p;i++)
		for(j=0;j<r;j++)
			need[i][j]=max[i][j]-alloc[i][j];
	printf("Enter the available matrix\n");
	for(i=0;i<r;i++)
	{
		scanf("%d",&avail[i]);
		work[i]=avail[i];
	}
	//Safety algorithm
	for(int i=0;i<p;i++)
	{
		finish[i]=false;
	}

	while(v<p)
	{
		bool allocated=false;
		for(int i=0;i<p;i++)
		{
			if(!finish[i] && check(i))
			{
				for(int k=0;k<r;k++)
					work[k]=work[k]+alloc[i][k];
				allocated=finish[i]=true;
				seq[v]=i;
				v++;
			}
			
		}
		if(!allocated)
				break;
		
	}	
	for(i=0;i<p;i++)
	{
		if(finish[i]==false)
		{
			printf("All processes not safely allocated\n");
			exit(0);
		}
	}
	printf("Processes safely allocated with the sequence \n");
	for(i=0;i<v;i++)
		printf("%d\t",seq[i]);
}












