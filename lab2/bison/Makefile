all: calc

calc.tab.c calc.tab.h:	calc.y
	bison -d calc.y

calc: calc.tab.c calc.tab.h
	gcc -o calc calc.tab.c 

clean:
	rm calc calc.tab.c calc.tab.h calc.output
