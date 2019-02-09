##	const

const 是一个 qualifier, 限定词, 修饰符

在实现 member function 的时候, 如果它不会改变对象, 要写好 `const`, 这是对 compiler 的一个 promise

*	main.cpp

	```
	#include "Rectangle.h"

	int main()
	{
		Rectangle const rec{ 3, 4 };

		int width = rec.get_width();
		// error, 需要在 get_width() 的定义中增加 const
		// int get_width() const { return _width; }

		int area = rec.area();
		// error, 需要在 area() 的定义中增加 const
		// int area() const { ... }

		int perimeter = rec.perimeter();
		// error, 需要在 area() 的定义和原型声明中增加 const
		// int perimeter() const;
		// int Rectangle::perimeter() const { ... }

		return 0;
	}
	```

*	Rectangle.h

	```
	class Rectangle
	{
	private:
		int _width;
		int _height;

	public:
		Rectangle()
			: _width { 1 }, _height { 1 }
		{ }

		Rectangle(int width, int height)
			: _width { width }, _height { height }
		{ }

		int get_width() { return _width; }
		// int get_width() const { return _width; }
		// 表示 const 不会修改 this 指向的对象

		int get_height() { return _height; }

		int area()
		// int area() const
		{
			return _width * _height;
		}

		int perimeter();
		// int perimeter() const;
	};
	```

*	Rectangle.cpp

	```
	#include "Rectangle.h"

	int Rectangle::perimeter()
	// int Rectangle::perimeter() const
	{
		return ( _width + _height ) * 2;
	}
	```

	<br>

##	参考链接

*	https://www.youtube.com/watch?v=FjKka2HDonw

	33:00
