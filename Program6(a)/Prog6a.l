%{
  #include<stdio.h>
  int c=0;
%}
%%
[/][/][0-9a-zA-Z \t]*	{c++;printf(" ");}
[/][*][0-9a-zA-Z \n\t]*[*][/]	{c++;printf(" ");}
%%
int main(int argc,char *argv[])
{
	yyin=fopen(argv[1],"r");
	yyout=fopen(argv[2],"w");
	yylex();
	printf("The number of comment lines is %d\n",c);
}
int yywrap()
{
	return 1;
}

