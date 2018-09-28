#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define List_Size 100/*分配空间的大小*/


typedef struct{
	int elem[List_Size]; /*存储空间*/
	int len;      /*实际长度*/
}SqListStatic;//顺序表静态定义的方案三：（通用性最强，类似STL:vector）

typedef struct{
	int *elem;       /*顺序表的存储空间*/
	int len;            /*实际长度*/
	int ListSize; /*当前分配的空间大小*/
} SqlistDyn;

int g1=0, g2=0, g3=0;


int main(int argc, char *argv[])
{
	static int s1=0,s2,s4,s3=0;
	const char *pc="12345";
	int v1=0,v2=0,*q=&v2,v3,*p=&v3,v4,v5, *r,*q11=&v2;
	int Sqlist1[100],*s=&Sqlist1,*u=Sqlist1,*v=&Sqlist1[0];//顺序表静态定义的方案一
	int Sqlist2[List_Size];//顺序表静态定义的方案
	SqListStatic Sqlist3;
	SqlistDyn Sqlist4;
	int v6;
	//int v7;

	//for (v1=1;v1<=100;v1++)
	//	Sqlist1[v1-1]=v1;

	printf("\n=====理解*p、p和&p的关联：假设定义int v3,*p=&v3;======\n");
	printf("局部变量v3的内存地址为：0x%08x;\t局部变量v3=0x%08x;\n",&v3,v3);
	printf("*p=0x%08x;\tp=0x%08x;\t&p=0x%08x\n\n",*p,p,&p); 

	printf("\n=====理解*q、q和&q的关联：假设定义int v2=0,*q=&v2;======\n");
	printf("局部变量v2的内存地址为：0x%08x;\t局部变量v2=0x%08x;\n",&v2,v2);
	printf("*q=0x%08x;\tq=0x%08x;\t&q=0x%08x\n\n",*q,q,&q);
	q =(int*) malloc(40);
	printf("执行'q =(int*) malloc(40);'后：局部变量q的内存地址和取值变为：\n");
	printf("*q=0x%08x;\tq=0x%08x;\t&q=0x%08x\n\n",*q,q,&q);

	q11 =(int*) malloc(40);
	printf("执行'q11 =(int*) malloc(40);'后：局部变量q11的内存地址和取值变为：\n");
	printf("*q11=0x%08x;\tq11=0x%08x;\t&q11=0x%08x\n\n",*q11,q11,&q11);

	printf("\n=====理解*s、s和&s的关联：假设定义int Sqlist1[100],*s=&Sqlist1,*u=Sqlist1,*v=&Sqlist1[0];====\n");
	printf("局部变量Sqlist1的内存地址为：0x%08x;\t局部变量Sqlist1=0x%08x\n;",&Sqlist1,Sqlist1);
	printf("*s=0x%08x;\ts=0x%08x;\t&s=0x%08x\n\n",*s,s,&s);
	printf("*u=0x%08x;\tu=0x%08x;\t&u=0x%08x\n\n",*u,u,&u);
	printf("*v=0x%08x;\tv=0x%08x;\t&v=0x%08x\n\n",*v,v,&v);

	printf("\n====执行'r=Sqlist1;'前后：局部变量r的内存地址和取值========\n");
	printf("局部变量r的内存地址为：0x%08x;\t局部变量r=0x%08x\n",&r,r);
	r=Sqlist1;	
	printf("\n             ===》\n");
	printf("局部变量r的内存地址为：0x%08x;\t局部变量r=0x%08x\n",&r,r);	

	printf("\n\n====打印各局部变量的内存地址和取值====\n");
	printf("局部变量v1的内存地址为：0x%08x;\t局部变量v1=0x%08x;\n",&v1,v1);
	printf("局部变量v2的内存地址为：0x%08x;\t局部变量v2=0x%08x;\n",&v2,v2);
	printf("局部变量q的内存地址为：0x%08x;\t局部变量q=0x%08x;\n",&q,q);
	printf("局部变量v3的内存地址为：0x%08x;\t局部变量v3=0x%08x;\n",&v3,v3);
	printf("局部变量p的内存地址为：0x%08x;\t局部变量p=0x%08x;\n",&p,p);
	printf("局部变量v4的内存地址为：0x%08x;\t局部变量v4=0x%08x;\n",&v4,v4);
	printf("局部变量v5的内存地址为：0x%08x;\t局部变量v5=0x%08x;\n",&v5,v5);
	printf("局部变量r的内存地址为：0x%08x;\t局部变量r=0x%08x;\n",&r,r);
	printf("局部变量s的内存地址为：0x%08x;\t局部变量s=0x%08x;\n",&s,s);
	printf("局部变量u的内存地址为：0x%08x;\t局部变量u=0x%08x;\n",&u,u);
	printf("局部变量v的内存地址为：0x%08x;\t局部变量v=0x%08x;\n",&v,v);
	printf("局部变量pc的内存地址为：0x%08x;\t局部变量pc=%s;\n",&pc,pc);
	printf("局部变量Sqlist1的内存地址为：0x%08x;\t局部变量Sqlist1=0x%08x;\n",&Sqlist1,Sqlist1);
	printf("局部变量Sqlist2的内存地址为：0x%08x;\t局部变量Sqlist2=0x%08x;\n",&Sqlist2,Sqlist2);
	printf("局部变量Sqlist3的内存地址为：0x%08x;\t局部变量Sqlist3=0x%08x;\n",&Sqlist3,Sqlist3);
	printf("局部变量Sqlist4的内存地址为：0x%08x;\t局部变量Sqlist4=0x%08x;\n",&Sqlist4,Sqlist4);
	printf("局部变量v6的内存地址为：0x%08x;\t局部变量v6=0x%08x;\n",&v6,v6);
	//printf("局部变量v7的内存地址为：0x%08x;\t局部变量v7=0x%08x;\n",&v7,v7);
	

	printf("\n\n====InitSqList函数的传入参数的内存地址和取值====\n");
	printf("局部变量Sqlist4的内存地址为：0x%08x;\t局部变量Sqlist4=0x%08x;\n",&Sqlist4,Sqlist4);
	InitSqList(&Sqlist4);	 
	printf("执行'InitSqList(&Sqlist4);'后：局部变量Sqlist4的内存地址和取值变为：\n");
	printf("局部变量Sqlist4的内存地址为：0x%08x;\t局部变量Sqlist4=0x%08x;\n",&Sqlist4,Sqlist4);


	printf("\n\n====打印各全局变量(已初始化)的内存地址，其中s========\n");
	printf("全局变量g1的内存地址为：0x%08x;\tg1=0x%08x\n",&g1,g1);//打印各全局变量的内存地址
	printf("全局变量g2的内存地址为：0x%08x;\tg2=0x%08x\n",&g2,g2);//打印各全局变量的内存地址
	printf("全局变量g3的内存地址为：0x%08x;\tg3=0x%08x\n",&g3,g3);//打印各全局变量的内存地址


	printf("\n\n====打印各静态变量的内存地址，其中s1,s3已初始化======\n");
	printf("静态变量s1的内存地址为：0x%08x;\ts1=0x%08x\n",&s1,s1);
	printf("静态变量s3的内存地址为：0x%08x;\ts3=0x%08x\n",&s3,s3);
	printf("静态变量s2的内存地址为：0x%08x;\ts2=0x%08x\n",&s2,s2);
	printf("静态变量s4的内存地址为：0x%08x;\ts4=0x%08x\n",&s4,s4);



	printf("\n\n====add函数的传入参数的内存地址和取值====\n");
	printf("局部变量v1的内存地址为：0x%08x;\t局部变量v1=0x%08x;\n",&v1,v1);
	printf("局部变量v2的内存地址为：0x%08x;\t局部变量v2=0x%08x;\n",&v2,v2);
	v4=add(v1,v2);
	
	

	printf("\n\n====打印程序初始程序main地址=====\n");
	printf("main函数的入口地址为: 0x%08x\n\n", main);
	printf("\n\n====打印main函数的参数地址=====\n");
	printf("argc的内存地址为：0x%08x;\targc: 0x%08x\n\n",&argc,argc);
	printf("argv的内存地址为：0x%08x;\targv=0x%08x\n\n",&argv,argv);
	printf("argv[0]的内存地址为：0x%08x;\n\n",&argv[0],argv[0]);
	printf("argv[1]的内存地址为：0x%08x;\n\n",&argv[1],argv[1]);
	printf("argv[2]的内存地址为：0x%08x;\n\n",&argv[2],argv[2]);



	printf("\n\n====打印子函数起始地址========\n");
	printf("InitSqList函数的入口地址为: 0x%08x\n\n",(int)(const void*)InitSqList);
	printf("add函数的入口地址为: 0x%08x\n\n",(int)(const void*)add);

	system("pause");
	return 1;
}


int InitSqList(SqlistDyn *L)//构造一个空的顺序表L
{
	L->elem=(int *) malloc(List_Size *sizeof(int));
	if (L->elem==NULL)
		exit(EXIT_FAILURE);
	L->len=0;
	L->ListSize =List_Size;
	printf("InitSqList函数调用中....\n");
	printf("观察子函数两个输入参数a,b的栈地址\n");
	printf("InitSqList函数中malloc分配的堆地址为：0x%08x\n;",L->elem);
	printf("InitSqList函数中指针变量L的内存地址为：0x%08x;\t局部变量L=0x%08x\n;",&L,L);
	return 1;
}

int add(int a, int b)
{
	printf("add函数调用中....\n");
	printf("观察子函数两个输入参数a,b的栈地址\n");
	printf("add函数中传入的参数a的内存地址为：0x%08x;\t局部变量a=0x%08x\n;",&a,a);
	printf("add函数中传入的参数b的内存地址为：0x%08x;\t局部变量b=0x%08x\n;",&b,b);
	return (a+b);
	
}