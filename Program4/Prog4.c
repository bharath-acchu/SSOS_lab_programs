/******************************************************************************

   Design,develop and implement YACC/C Program to demonstrate shift Reduce parsing technique for the grammar rules
                                 E->E+T | T 
                                 T->T*F | F 
                                 F->(E) | id 
   and parse the sentence : id+id*id

*******************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char inputsymbols[30];
int n;
char sy_stack[20],ind_prod[30][20];
int stack[20];
char action_T[]="a+*()$";
char goto_nt[]="ETF";
char set_of_terminal[]={"#abcdefghijklmnopqrstuvwxyz+-/*()"};
int top=-1,sy_top=-1;
char action[12][9][6]={{"s5","","","s4","",""},
			{"","s6","","","","Acc"},
			{"","r2","s7","","r2","r2"},
			{"","r4","r4","","r4","r4"},
			{"s5","","","s4","",""},
			{"","r6","r6","","r6","r6"},
			{"s5","","","s4","",""},
			{"s5","","","s4","",""},
			{"","s6","","","s11",""},
			{"","r1","s7","","r1","r1"},
			{"","r3","r3","","r3","r3"},
			{"","r5","r5","","r5","r5"},
			};
int Goto[12][3]={{1,2,3},
		{-1,-1,-1},
		{-1,-1,-1},
		{-1,-1,-1},
		{8,2,3},
		{-1,-1,-1},
		{-1,9,3},
		{-1,-1,10},
		{-1,-1,-1},
		{-1,-1,-1},
		{-1,-1,-1},
		{-1,-1,-1},
		};
int getterminalindex(char x)
{
	int i;
	for(i=0;i<strlen(action_T);i++)
	{
		if(action_T[i]==x)
			break;
		}
	return i;
}
char *strrev(char *str)
{
	int i=strlen(str)-1,j=0;
	char ch;
	while(i>j)
	{
		ch=str[i];
		str[i]=str[j];
		str[j]=ch;
		i--;
		j++;
	}
	return str;
}
int getgotoindex(char x)
{			
	int i;
	for(i=0;i<strlen(goto_nt);i++)
	{
		if(goto_nt[i]==x)
			break;
		}
	return i;
}

void push(int x)
{
	stack[++top]=x;
}
void pop(int n)
{
	
	int i;
	for(i=0;i<n;i++)
		top--;
}
void disp(int j,char inputstring[30])
{
	int i;
	for(i=0;i<=top;i++)
		printf("%3d",stack[i]);
	if(i==2)
		printf("		");
	else if(i==3)
		printf("	");
	else
		printf("	");
	for(i=0;i<=sy_top;i++)
		printf("%c",sy_stack[i]);
	printf("\t\t\t");
	for(i=j;i<strlen(inputstring);i++)
		printf("%c",inputstring[i]);
	printf("\t\t\t");
}
void sy_push(char x)
{
	sy_stack[++sy_top]=x;
}
void sy_pop(int n)
{
	int i;
	for(i=0;i<n;i++)
		sy_top--;
}
void processinput(char inputstring[30])
{
	int i=0,j,m,col,s,l,prod_no,t,st,buf[60],num;
	char ch,ac[3],*token,prod[20],rprod[20],temp[3];
	for(i=0;i<strlen(inputstring);i++)
	{
		ch=inputstring[i];
		while(1)
		{
			s=stack[top];
			buf[0]='\0';
			col=getterminalindex(ch);
			if(action[s][col][0]=='s')
			{
				strcpy(ac,action[s][col]);
				if(strlen(ac)==3)
				{
					temp[0]=ac[1];
					temp[1]=ac[2];
					temp[2]='\0';
					num=atoi(temp);
					push(num);
				}
				else
					push(ac[1]-'0');
				sy_push(ch);
				i++;
				disp(i,inputstring);
				printf("shift\n");
				ch=inputstring[i];
				continue;
			}
			else if(action[s][col][0]=='r')
			{
				strcpy(ac,action[s][col]);
				prod_no=ac[1]-'0';
				prod_no--;
				strcpy(prod,ind_prod[prod_no]);
				strcpy(rprod,strrev(prod));
				
				token=strtok(rprod,">");
				pop(strlen(token));
				t=stack[top];
				col=getgotoindex(ind_prod[prod_no][0]);
				st=Goto[t][col];
				sy_pop(strlen(token));
				sy_push(ind_prod[prod_no][0]);
				push(st);
				disp(i,inputstring);
				printf("reduce %s%s\n",ac,ind_prod[prod_no]);
			}
			else if(action[s][col][0]=='A')
			{
				disp(i,inputstring);
				printf("Accept parsing");
				break;
			}
			else
			{
				printf("error");
				return;
			}
		}
	}
}
void init()
{
	top=-1;
	sy_top=-1;
}
int main()
{
	char production[10][20],inputstring[30];
	int i,j,n_ind=0,ch;
	n=6;
	for(i=0;i<n;i++)
	{
		printf("enter the %d production\t",i);
		scanf("%s",production[i]);
		strcpy(ind_prod[i],production[i]);
	}
	printf("\n the prod enterd\t");
	for(i=0;i<n;i++)
		printf("\n %s",production[i]);
	n_ind=n;
	for(i=0;i<n_ind;i++)
		printf("\n%d %s",i,ind_prod[i]);
	while(1)
	{
		init();
		printf("\nenter the i/p\t");
		scanf("%s",inputstring);
		strcat(inputstring,"$");
		push(0);
		printf("\nstack\t\tsymbol\t\t\tinput\t\t\taction");
		printf("\n______\t\t______\t\t\t_____\t\t\t______\n");
		processinput(inputstring);
		printf("\n______\t\t______\t\t\t_____\t\t\t______\n");
		printf("\n press 1 to contine 0 to exit\t");
		scanf("%d",&ch);
		fflush(stdin);
		if(ch==0)
			break;
	}
}

