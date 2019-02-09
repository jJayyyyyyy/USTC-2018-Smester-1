##	初始化 和 构造函数

*	demo

	```cpp
	#include <iostream>

	class Rectangle
	{
	public:
		int _width;         // 单下划线开头, 当成私有变量
		int _height;
	};

	class Circle
	{
	private:
		int _radius_;        // 私有变量

	public:
		Circle(int radius);
		{
			_radius_ = radius;
		}
	};

	class Line
	{
	private:
		int _length_;

	public:
		Line()
		{
			_length_ = 1;
		}
	}

	class Triangle
	{
	private:
		int _perimeter_;

	public:
		Triangle()
			: _perimeter_ {}
		{}

		Triangle(int perimeter)
			: _perimeter_ {perimeter}
		{}
	}

	int main()
	{
		int x;                // 未初始化, Debug 时是 0xcccccccc, 但 Release 不会
		int y{};              // 初始化为默认值 0
		int z{1};             // 初始化为 1


		Rectangle r1;         // 未初始化
		Rectangle r2{ };      // r2._width = 0, r2._height = 0
		Rectangle r3{ 2, 3 }; // r3._width = 2, r3._height = 3


		Circle c1{};          // error, 只有一个带参数的构造函数, 不能进行默认初始化, 需要一个不带参数的构造函数 Circle(){}
		Circle c2{ 2 };       // error, 私有变量不能这样初始化, 需要使用 setter 或者 构造函数
		Circle c3(3);         // ok, 使用构造函数, radius == 3
		Circle c4({});        // ok, radius = 0

		Line l1{};            // length == 1, 而不是 0

		return 0;
	}
	```

	`{}` 和 `()` 很像

	<br>

##	参考链接

*	https://www.youtube.com/watch?v=FjKka2HDonw

*	更详细完整的例子可以参考 `encapsulation.md`