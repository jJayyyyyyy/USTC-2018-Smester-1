##	名字空间 namespace

```cpp
#include <iostream>
using std::cout;

namespace space1
{
	int val = 1;
}

namespace space2
{
	int val = 2;
}

int main()
{
	int val{ space1::val };
	cout << val << '\n';	// 1
	val = space2::val;
	cout << val << '\n';	// 2
	return 0;
}
```