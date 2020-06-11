%{
   #include<stdio.h>
   #include<stdlib.h>
   #include<ctype.h>
   int yylex();
   int yyerror();
   int valid = 1;
%}
%token num
%left '+''-'
%left '*''/'
%left '('')'

%%
exp:e		{if (valid) printf("value of exp is %d\n", $1); exit(0);}
e: e'+'e	{ $$ = $1 + $3;}
e: e'-'e	{ $$ = $1 - $3;}
e: e'*'e	{ $$ = $1 * $3;}
e: e'/'e	{ if( $3 == 0) {printf("Divide by zero error\n"); exit(0);} 
		else $$ = $1 / $3; }
e: '('e')'		{ $$ = $2;}
e: num		{ $$ = $1 ;}
e: '-'e		{$$= -$2;}

%%




int main()
{
	printf("Enter the expression\n");
	yyparse();
	printf("Invalid\n");
}
	
int yyerror()
{
	valid = 0;
}
int yywrap()
{
	return 1;
}

