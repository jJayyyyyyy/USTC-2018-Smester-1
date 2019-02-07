##	类型转换

```cpp
#include <iostream>
using std::cout;

int main()
{
	double a = 3.2;
	int b = static_cast<int>(a);	// truncated, 截断
	cout << b << '\n';	// 3
	return 0;
}
```