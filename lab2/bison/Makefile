all: calc expr calc_plus

calc.tab.c calc.tab.h:	calc.y
	bison -d calc.y

calc: calc.tab.c calc.tab.h
	gcc -o calc calc.tab.c 

expr.tab.c expr.tab.h:	expr.y
	bison -d expr.y

expr: expr.tab.c expr.tab.h
	gcc -o expr expr.tab.c 

calc_plus.tab.c calc_plus.tab.h:	calc_plus.y
	bison -d calc_plus.y

calc_plus: calc_plus.tab.c calc_plus.tab.h
	gcc -o calc_plus calc_plus.tab.c 