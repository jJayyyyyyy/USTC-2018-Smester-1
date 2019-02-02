##	模板

*	强类型语言, 变量/对象的类型是确定的

	为了解决严格性与灵活性的矛盾, 增加函数的通用性, 有以下几种方法

	*	宏函数

	*	重载

	*	模板

	下面我们就来简单介绍一下模板

*	例1, 写一个通用的 `swap()`

	```cpp
	#include <iostream>

	// 标识符 tmplate <class ... > 是固定的写法, 注意没有分号
	// 相当于定义了一个 ElemType 类型
	// 也可以理解为这些标识符扮演了【占位符】的角色 (via Essential C++ )
	template <class ElemType>
	void swap(ElemType & a, ElemType & b)
	{
		ElemType tmp = a;
		a = b;
		b = tmp;
	}

	int main()
	{
		int a = 1, b = 2;
		swap(a, b);		// swap 既可以接受 int 类型参数
		std::cout<<a<<' '<<b<<'\n';

		double c = 3.0, d = 4.0;
		swap(c, d);		// swap 也可以接受 double 类型参数
		std::cout<<c<<' '<<d<<'\n';
		return 0;
	}
	```

*	例2, 写一个通用的 `stack`

	```
	#include <iostream>

	template <class ElemType>
	class stack
	{
	private:
		#define MAXSIZE 4
		int now;
		ElemType stk[MAXSIZE];
	public:
		stack(): now(0) {}

		void push(ElemType val)
		{
			if( now < MAXSIZE )
			{
				stk[now++] = val;
			}
		}

		ElemType top()
		{
			return stk[now - 1];
		}

		void pop()
		{
			if( now > 0 )
			{
				stk[--now] = 0;
			}
		}
	};

	int main()
	{
		// 模板的真正类型由实例化时的 <...> 指定
		stack<int> s1;       // 既可以存放 int 类型的元素
		stack<double> s2;    // 也可以存放 double 类型的元素
		return 0;
	}
	```
