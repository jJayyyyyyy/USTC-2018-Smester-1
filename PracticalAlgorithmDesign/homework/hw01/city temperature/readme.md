##	0. 简介

*	Ch2_1 所示程序主要用于练习链表操作，其过程如下

	*	首先从当前目录读取数据文件 `citytemp.dat`，从而构造一个个 `Node` 类型的结点
	*	然后按照预定规则进行插入排序，生成一个单链表 `L1`，其头结点为 `head`
	*	完成链表 `L1` 的创建后，首先遍历 `L1`，返回总的结点数 `cnt`
	*	接着，重新遍历 `L1`，并输出各个结点，同时对于中间结点，即第 `cnt/2` 个结点，输出附加信息 `" <-- mid "`
	*	然后，删除头结点 `head`，得到链表 `L2`，并遍历输出 `L2`
	*	这之后进入一个循环，每次删除 `head->next`, 得到新的链表 `Li`, 并遍历输出 `Li`
	*	退出循环后，再删除头结点 `head`，再次遍历链表并输出结点信息。由于此时链表为空，所以不会有输出信息
	*	退出程序

*	对原示例程序进行了重写, 包含以下改动

	*	开发环境: `Ubuntu 16.04`, `g++ 4.8.4`
	*	编程语言: `C++`
	*	重新命名变量和函数名
	*	使用 `fstream` 代替 `FILE` 指针
	*	使用 `string` 代替字符数组

<br>

##	1. 运行截图

![result1](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw01/city%20temperature/assets/result1.png)

![result2](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw01/city%20temperature/assets/result2.png)

![result3](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw01/city%20temperature/assets/result3.png)

![result4](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw01/city%20temperature/assets/result4.png)

<br>

##	2. 数据结构

*	结点数据结构

	```cpp
	struct Node {
		int temp;
		string city, state;
		Node * next;
	};
	```

	另外，为了方便结点之间的比较操作，这里进行了运算符的重载

	```cpp
	bool operator < (const Node & a) const {
		if( temp != a.temp ){
			return temp < a.temp;
		}else if( city != a.city ){
			return city < a.city;
		}else{
			return state < a.state;
		}
	}

	bool operator == (const Node & a) const {
		return (temp == a.temp && city == a.city && state == a.state);
	}
	```

<br>

##	3. 头文件和库函数

*	头文件

	```cpp
	#include <cstdlib>
	#include <fstream>
	#include <iostream>
	```

*	库函数

	*	`istream & getline (istream & is, string & str, char delim);`

		从 `is` 流中读取数据，以 `delim` 为分隔符，分段保存在 `str` 中。

		一般配合 `while` 进行读取，示例如下

		```cpp
		while ( getline(ifs, buffer) ){
			Node * node = new Node(buffer);
			head = ascInsert(head, node);
		}
		```

<br>

##	4. 子函数

*	`Node * ascInsert(Node * head, Node * & node);`

	用插入排序的方式，建立一个升序链表，同时去掉重复的结点，最后返回头结点

*	`int cntNode(Node * head);`

	遍历链表，返回当前链表中的结点数

*	`int showList(Node * head, int mid);`

	遍历链表，逐个打印结点信息，最后返回当前链表中的结点数

*	`Node * deleteHead(Node * head);`

	删除头结点 `head`，返回 `head->next` 作为新的头结点

*	`Node * deleteHeadNext(Node * head);`

	删除 `head->next`，返回头结点 `head` 

<br>

##	5. 流程图

![workflow](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw01/city%20temperature/assets/workflow.jpg)

<br>

##	参考链接

*	[cplusplus, getline()](http://www.cplusplus.com/reference/string/string/getline/)

*	[overload c++ operator](https://github.com/jJayyyyyyy/OJ/blob/master/tools/STL_usage.cpp)

*	[c++ 11, stoi](http://www.cplusplus.com/reference/string/stoi/)

*	[string, substr, find](http://www.cplusplus.com/reference/string/string/)

*	[ifstream](http://www.cplusplus.com/reference/fstream/ifstream/open/)

*	[Java annotation, for reference](https://blog.csdn.net/jcy1009015337/article/details/53819253)

<br>
