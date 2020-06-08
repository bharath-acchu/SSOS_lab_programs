/*********************************************************************************************************************************************************************

 Design, develop and implement a C/Java program to generate the machine code using Triples for the statement A = -B * (C +D) whose intermediate       code in three- address form:
                            T1 = -B
                            T2 = C + D
                            T3 = T1 + T2 
                             A = T3




**********************************************************************************************************************************************************************/

#include<stdio.h>
#include<string.h>
void main()
{
	char icode[10][30],opr;
	char op1[5],op2[5],res[5];
	int i=0,n,j,k;
	printf("\n enter the no. of intermediate statements\n");
	scanf("%d",&n);
	printf("enter the set of intermediate code\n");
	for(i=0;i<n;i++)
	{
		scanf("%s",icode[i]);
	}
	printf("\n");
	
	for(i=0;i<n;i++)
	{
		j=0;k=0;
		while(icode[i][j]!='=')
		{
			res[k]=icode[i][j];
			j=j+1;
			k=k+1;
		}
		res[j]='\0';
		k=0;
		j++;
		
		if(icode[i][j]=='-')
		{
			j++;
			while(icode[i][j]!='\0')
			{
				op1[k]=icode[i][j];
				j++;
				k++;
			}
			op1[k]='\0';
			printf("\nLOAD R1,%s\n",op1);
			printf("NEG R1\n");
			printf("STORE %s,R1\n",res);
		}

		else
		{
			k=0;
			while(icode[i][j]!='\0' && icode[i][j]!='+' && icode[i][j]!='-' && icode[i][j]!='*')
			{
				op1[k]=icode[i][j];
				j++;k++;
			}
			op1[k]='\0';
			if(icode[i][j]=='\0')
			{
				printf("\n LOAD R1,%s\n",op1);
				printf("STORE %s,R1\n",res);
				continue;
			}
			else
			{
				opr=icode[i][j];
				k=0;j++;
				while(icode[i][j]!='\0')
				{
					op2[k]=icode[i][j];
					j++;k++;
				}
				op2[k]='\0';
			}
			switch(opr)
			{
				case '+':
							printf("\nLOAD R2,%s\n",op1);
							printf("LOAD R3,%s\n",op2);
							printf("ADD R2,R3\n");
							printf("STORE %s,R2\n",res);
							break;
				case '-':
							printf("\nLOAD R2,%s\n",op1);
							printf("LOAD R3,%s\n",op2);
							printf("SUB R2,R3\n");
							printf("STORE %s,R2\n",res);
							break;
				case '*':
							printf("\nLOAD R1,%s\n",op1);
							printf("LOAD R2,%s\n",op2);
							printf("MUL R1,R2\n");
							printf("STORE %s,R1\n",res);
							break;

				default:printf("\n Invalid statement\n");
			}
		}
	}
}
	

