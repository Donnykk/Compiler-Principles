all: calc expr

calc.tab.c calc.tab.h:	calc.y
	bison -d calc.y

calc: calc.tab.c calc.tab.h
	gcc -o calc calc.tab.c 

expr.tab.c expr.tab.h:	expr.y
	bison -d expr.y

expr: expr.tab.c expr.tab.h
	gcc -o expr expr.tab.c 
