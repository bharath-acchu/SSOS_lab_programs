%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    int yyerror();
%}
%token A B
%%
input:S '\n'	{printf("Successful grammar\n");exit(0);}
S: A S1 B |B
S1: ;|A S1
%%
int main()
{
	printf("Enter a string\n");
	yyparse();
}
int yyerror()
{
	printf("Error\n");
	exit(0);
}
