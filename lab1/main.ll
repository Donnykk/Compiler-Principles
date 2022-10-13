@a = constant float 2.000000e+00, align 4   ; 全局变量,浮点数a
@str =constant [24 x i8] c"Please enter 1 inputs:\0A\00", align 1   ; 预定义str字符串
@str1 = constant [3 x i8] c"%d\00", align 1
@str2 = constant [4 x i8] c"%d\0A\00", align 1

define i32 @func(i32 %0, i32 %1, i32 %2) #0 {   ; 定义func()函数
  %4 = alloca i32, align 4   ; 分配空间，对齐方式为4字节
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, i32* %4, align 4   ; 存入对应参数值
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %7 = load i32, i32* %4, align 4
  %8 = load i32, i32* %5, align 4
  %9 = add nsw i32 %7, %8
  %10 = load i32, i32* %6, align 4
  %11 = add nsw i32 %9, %10   ; 以上为运算a+b+c
  ret i32 %11
}

define i32 @main() #0 {   ; main函数
  %1 = alloca i32, align 4
  %2 = alloca [2 x i32], align 4   ; 2位数组
  store i32 0, i32* %1, align 4   ; 将 0（i32）存入 %1（i32*）
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @str, i64 0, i64 0))   ; 调用printf输出
  %4 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0   ; 根据指针获得b[0]（inbounds为越界检查）
  %5 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @str1, i64 0, i64 0), i32* %4)   ; 调用scanf输入
  %6 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0
  %7 = load i32, i32* %6, align 4
  %8 = icmp slt i32 %7, 0   ; 比较%7与0大小
  br i1 %8, label %9, label %10   ; %8的值如果为真，执行 label%9，否则执行 label%10

9:                                               
  store i32 0, i32* %1, align 4
  br label %30   ; 跳转到return 0

10:                                      
  br label %11   ;继续运行

11:                                            ; while语句中判断语句
  %12 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0
  %13 = load i32, i32* %12, align 4
  %14 = icmp sgt i32 %13, 0   ; 判断%13与0大小
  br i1 %14, label %15, label %20   

15:                                             
  %16 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0   ; 运算while循环内运算语句
  %17 = load i32, i32* %16, align 4
  %18 = sub nsw i32 %17, 1   ; b[0] = b[0] - 1
  %19 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0
  store i32 %18, i32* %19, align 4
  br label %11   ; 返回while的判断语句

20:                                               
  %21 = call i32 @func(i32 1, i32 2, i32 1)   ; b[1] = func(1, 2, 1)
  %22 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 1   ; 获取b[1]
  store i32 %21, i32* %22, align 4
  %23 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 0
  %24 = load i32, i32* %23, align 4
  %25 = add nsw i32 2, %24   ; a+b[0]
  %26 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i64 0, i64 1
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %25, %27   ; a+b[0]+b[1]
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @str2, i64 0, i64 0), i32 %28)
  store i32 0, i32* %1, align 4
  br label %30

30:                                             
  %31 = load i32, i32* %1, align 4
  ret i32 %31   ; return 0
}

declare i32 @printf(i8*, ...) #1

declare i32 @__isoc99_scanf(i8*, ...) #1
