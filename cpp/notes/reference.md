##	Reference, &

*	必须初始化指向的对象

	```cpp
	void f1()
	{
		int x;
		int & xref = x;    // ok
		int & yref;        // error
	}
	```

*	不能改变指向的对象

	```cpp
	void f2()
	{
		int x = 1;
		int y = 2;
		int & xref = x;    // ok
		xref = y;          // ok, 这是复制值
		xref = 3;          // 但是 xref 还是指向 x, 并不会指向 y

		cout << x << '\n'; // x == 3
		cout << y << '\n'; // y == 2
	}
	```

*	const reference

	```cpp
	void f3()
	{
		int x = 1;
		int const & xref = x;

		x = 2;       // ok, x == 2, xref == 2
		xref = 3;    // error, assignment of read-only reference ‘xref’
	}
	```