## SYSTEM SOFTWARE AND OPERATING SYSTEM LAB PROGRAMS (17CSL67)

### REQUIRED SOFTWARES
* flex
* bison


### How to install?

type ` sudo apt-get install flex`

enter your password

type `sudo apt-get install bison`

enter your password

Boom!!! you are done .

### How to run lex programs ?
1. write the lex program in a file and save it as file.l (where file is the name of the file).
2. open the terminal and navigate to the directory where you have saved the file.l  (e.x cd Desktop)
3. type  lex filename.l
4. then type  cc lex.yy.c 
5. then type  ./a.out

### How to run lex and yacc combine ?
1. write lex program in a file file.l and yacc in a file file.y
2. open the terminal and navigate to the directory where you have saved the files.
3. type lex filename.l
4. type yacc filename.y
5. type cc lex.yy.c y.tab.h 
6. type ./a.out
