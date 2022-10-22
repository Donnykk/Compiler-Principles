编译原理课程大作业仓库
lab1 lab2为预备工作
ult_lab为编译器实现


注：
汇编文件生成可执行文件：
arm-linux-gnueabihf-gcc main.S -o main

运行可执行文件：
qemu-arm -L /usr/arm-linux-gnueabihf/ ./main

bison：
    $ bison -d calc.y
    $ flex calc.l
    $ gcc calc.tab.c lex.yy.c -o calc -lm
    $ ./calc