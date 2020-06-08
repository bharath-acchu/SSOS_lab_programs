%{
  #include<stdio.h>
  int id=0,optr=0,p=0;
%}
%%
[0-9]+	{ id++;printf("Identifier is %s\n",yytext);}
[+*]	{ optr++;printf("The operator is %s\n",yytext);}
[(]	p++;
[)]	p--;
%%
int main()
{
	printf("Enter an expression\n");
	yylex();
	if(id==optr+1 && optr>=1 && p==0)
	{
		printf("This is valid expression\n");
		printf("Count of operator is %d\n and Count of identifier is %d\n",optr,id);
	}
	else
	     printf("Invalid expression\n");
}
int yywrap()
{
	return 1;
}
