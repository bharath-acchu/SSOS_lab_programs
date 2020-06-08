/******************************************************************************
 Design,develop and implement YACC/C program to construct Predictive/LL(1) Parsing Table for the grammer rules:
                                          A->aBa
                                          B->bB|#
 Use this table to parse the sentence abba$
                            
*******************************************************************************/
#include<stdio.h>
#include<string.h>


/*
 FIRST(A)={a}
 FIRST(B)={b#}
 FOLLOW(A)={$}
 FOLLOW(B)={a}
 
 Parser Table Entry
 
 M[A,a]=A->aBa
 M[B,a]=B->#
 M[B,b]=B->bB
 */

struct FT
{
	char nonT;
	char set[20];
};
typedef struct FT FIRST_FOLLOW_SET;
FIRST_FOLLOW_SET first[10],follow[10];
/*char Parser_Table[2][3][10]={{"A->aBa","",""},
							 {"B->#","B->bB",""},
							};*/
char Parser_Table[2][3][10];							
char termminal_list[3]={"ab$"};
int n; // number of productions 
char stack[50];
int top=-1;
char *strrev(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}
int getFollowIndex(char x)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(follow[i].nonT==x)
			break;
	}
	return i;
}
int getTerminalIndex(char x)
{
	int i;
	for(i=0;i<strlen(termminal_list);i++)
	{
		if(termminal_list[i]==x)
			break;
	}
	return i;
}
void push(char x)
{
	stack[++top]=x;
}
void pop()
{
	stack[top]='\0';
	top--;
}
void check_input(char expr[30],int n_expr)
{
	int i,j,row,col;
	char prod[20],*token,ch,StackTop,temp[2],rprod[20];
	temp[1]='\0';
	for(i=0;expr[i]!='$';)
	{
		ch=expr[i];
		StackTop=stack[top];
		temp[0]=StackTop;
		if(strstr(termminal_list,temp)!=NULL || StackTop =='$' )
		{
			if(strstr(termminal_list,temp)!=NULL )
			{
				pop();
				i++;
			}
			else
			{
				printf("\nError in the Stack Symbol Not Matching");
				printf("\n%s Not Accepted",expr);
				return;
			}
		}
		else
		{
			if(strstr(termminal_list,temp)==NULL)
			{
				row=getFollowIndex(StackTop);
				col=getTerminalIndex(ch);
				strcpy(prod,Parser_Table[row][col]);
				printf("\nM[%d,%d]  M[%c,%c] = %s",row,col,StackTop,ch,prod);
				if(strstr(prod,"err")!=NULL)
				{
					printf("\nError : No Entry in the Table");
					printf("\n%s Not Accepted",expr);
					return;
				}
				else
				{
					strcpy(rprod,strrev(prod));
					token=strtok(rprod,">");
					if(strstr(rprod,"#")!=NULL)
					{
						pop();
					}
					else
					{
						pop();
						for(j=0;j<strlen(token);j++)
							push(token[j]);
					}
				}
			}
		}
	}
	if(expr[i]==stack[top])
		printf("\n ch = %c StackTop = %c  %s is Accepted",expr[i],stack[top],expr);
	else
		printf("\n ch = %c StackTop = %c  %s is Not Accepted",expr[i],stack[top],expr);
}
void init()
{
	stack[0]='\0';
	top=-1;
}
int main()
{
	char production[10][20],Ind_prod[30][20],inputString[30];
	int i,j,n_Ind=0,ch;
	char t,T;
	printf("\n Enter the number of production\n");
	scanf("%d",&n);
	fflush(stdin);
	for(i=0;i<n;i++)
	{
		printf("Enter the %d production\t",i);
		scanf("%s",production[i]);
		fflush(stdin);
	}
	printf("\n The production entered\t");
	for(i=0;i<n;i++)
		printf("\n %s",production[i]);

	printf("\n First Set\n");
	for (i=0;i<n;i++)
	{
		first[i].nonT=production[i][0];
		printf("Enter First(%c)\t",first[i].nonT);
		scanf("%s",first[i].set);
		fflush(stdin);
	}
	printf("\n Follow Set\n");
	for (i=0;i<n;i++)
	{
		follow[i].nonT=first[i].nonT;
		printf("Enter Follow(%c)\t",follow[i].nonT);
		scanf("%s",follow[i].set);
		fflush(stdin);
	}
	printf("\n If no entry please enter err in the table\n");
	for(i=0;i<2;i++)
	for (j=0;j<3;j++)
	{
		T=first[i].nonT;
		t=termminal_list[j];
		printf("M[%d,%d] M[%c,%c]=\t",i,j,T,t) ;
		scanf("%s",Parser_Table[i][j]);
		fflush(stdin);
	}
	while(1)
	{
		init();
		push('$');
		push(production[0][0]);
		printf("\nStack %s",stack);
		printf("\nEnter the input \t");
		scanf("%s",inputString);
		strcat(inputString,"$");
		printf("InputString %s",inputString);
		check_input(inputString,strlen(inputString));
		printf("\n Press 1 to Continue 0 to Exit\t");
		scanf("%d",&ch);
		fflush(stdin);
		if(ch==0)
			break;
	}
}
	






 

