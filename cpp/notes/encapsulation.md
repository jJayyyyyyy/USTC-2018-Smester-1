##	封装

*	main.cpp

	```
	#include "Rectangle.h"
	#include <iostream>
	using std::cout;

	int main()
	{
		Rectangle r1;
		Rectangle r2{};
		Rectangle r3{4, 7};
		cout << r2.area() << ' ' << r3.area() << '\n';
		cout << r3.perimeter() << '\n';

		r2.resize(5, 5);
		r3.resize(1, 2);

		cout << r2.area() << ' ' << r3.area() << '\n';
		cout << r3.perimeter() << '\n';

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
		int get_height() { return _height; }

		void resize(int new_width, int new_height)
		{
			_width = new_width;
			_height = new_height;
		}

		// definition 可以放在 .h
		int area()
		{
			return _width * _height;
		}

		// 也可以把 declaration 放在 .h, 而把 definition 放到 cpp
		int perimeter();
	};
	```

*	Rectangle.cpp

	```
	#include "Rectangle.h"

	int Rectangle::perimeter()
	{
		return ( _width + _height ) * 2;
	}
	```

	<br>

##	参考链接

*	https://www.youtube.com/watch?v=FjKka2HDonw
