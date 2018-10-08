##	Java 第2次作业

1.	Survey sorting methods, make a summary and submit your PPT slides.
Implement the QuickSort(快速排序） in Java to Sort one dimensional array

	```java
	package hw02;

	public class Test {
		private int[] a = {0, 4, 5, 3, 2, 1};
		
		int partQuickSort(int left, int right) {
			int i = left, j = right;
			int key = a[i];
			while( i < j ) {
				while( i < j && a[j] > key ) {
					j--;
				}
				
				if( i < j ) {
					a[i++] = a[j];
				}
				
				while( i < j && a[i] < key ) {
					i++;
				}
				
				if( i < j ) {
					a[j--] = a[i];
				}
			}
			
			int mid = i;
			a[mid] = key;
			
			return mid;
		}
		
		void quickSort(int left, int right) {
			if( left < right ) {
				int mid = partQuickSort(left, right);
				quickSort(left, mid-1);
				quickSort(mid+1, right);
			}
		}
		
		void printArray() {
			for(int n : a) {
				System.out.printf("%d ", n);
			}
			System.out.println();
		}
		
		public static void main(String[] args) {
			Test test = new Test();
			test.printArray();
			test.quickSort(0, test.a.length-1);
			test.printArray();
		}
	}
	```

	<br>

2.	Compile the following code to see if there is any error. Explain the reason.

	```java
	public class TestAccess {
	}

	class T {
		private int i = 0;
				int j = 0;
		protected int k = 0;
		public int m = 0;
		
		public void m() {
			i = 9;
		}
	}

	class TT {
		public void m() {
			T t = new T();
			System.out.println(t.i);	// error, i是私有成员变量, not visible, 需要通过 getter() 访问
		}
	}
	```

	<br>

3.	What will be the output of the following program? Explain the reason

	```java
	public class TestOverriding {
		public static void main(String aga[]){
		Test t =new Fest();
			t.tests();
		}
	}

	class Test{
		void tests(){
			System.out.println("Test class : tests");
		}
	}

	class Fest extends Test{
		// error, 非 static 不能在重载为 static，反之亦然
		static void tests(){
			System.out.println("Fest class : tests");
		}
	}
	```

	<br>

4.	What will be the output of the following program? Explain the reason

	```java
	public class Test {
		public int aMethod(){
			// error, 非 static 方法中不能声明 static 变量
			static int i = 0;
			i++;
			return i;
		}
		public static void main(String args[]) {
			Test test = new Test();
			test.aMethod();
			int j = test.aMethod();
			System.out.println(j);
		}
	}
	```

	<br>

5.	What will be the output of the program? Explain the reason.

	```java
	class Super {
		public int i = 0;
		public Super(String text){
			i = 1;
		} 
	} 
	class Sub extends Super {
		public Sub(String text) {
			// 如果没有显式地用 super(text) 完成父类的构造函数
			// 则会隐式地调用无参数的 super()
			// 所以这里有两种解决方案
			// 1. 去掉父类构造函数的参数
			// 2. 不改变父类构造函数，在子类构造函数中显式调用 super(text);

			i = 2;
		}

		public static void main(String args[]) {
			Sub sub = new Sub("Hello"); 
			System.out.println(sub.i); 
		} 
	}
	```

	<br>

6.	Which statement can be inserted at line 7 to creates an instance of Bar?

	```java
	class Foo {
		class Bar{ }
	}

	class Test {
		public static void main (String [] args)   {
			Foo f = new Foo();
			/* Line 7: Missing statement ? */
			// 内部类的实例化
			Foo.Bar b = f.new Bar();
		}
	}
	```

	<br>

7.	Compile and run the following code snippet, and explain the results by analyzing memory allocation.

	```java
	public class Cat {
		private static int sid = 0;
		private String name;
		int id;
		Cat(String name) {
			this.name = name;  
			id = sid++;
		}
		public void info(){
			// 注意这里输出的是 id 而不是 sid
			System.out.println("My name is "+name+" No."+id);
		}
		public static void main(String arg[]){
			Cat.sid = 100;				// sid == 100, mimi.id == 100
			Cat mimi = new Cat("mimi");		// sid == 101
			mimi.sid = 2000;			// sid == 2000, mimi.id == 100
			Cat pipi = new Cat("pipi");		// sid == 2001, mimi.id == 100, pipi.id == 2000
			mimi.info(); 
			pipi.info();
		}
	}
	```

	一个static变量单独划分一块存储空间，不与具体的对象绑定在一起，该存储空间被类的各个对象所共享。static变量值在方法区加载一次，而非static在创建对象时会加载很多次。每次创建都会拷贝一份。

8.	Debug the code on page 35 of the third lecture notes(Slides, PPT), locate the bugs and fix the bugs. Submit a report.

	```java
	// void public method() -> public void method()
	public void method() {
		int i = 1, j = 0;			// j 需要初始化
		float f1 = (float) 0.1;			// 浮点数默认为double, 需要 cast 成 为(float)
		float f2 = 123;
		double d1 = 2e20, d2=124;
		byte b1 = 1, b2 = 2, b3 = (byte) 129;	// byte 1字节, 129 超出范围了
		j = j + 10;
		i = i / 10;
		i = (int) (i * 0.1);			// double 需要 cast 成为 (int)
		char c1 = 'a', c2 = 125;
		byte b = (byte) (b1 - b2);		// byte 1字节,  负数超出范围了, 需要 cast
		char c = (char) (c1 + c2 - 1);		// char unicode 编码, 直接加减需要 cast
		float f3 = f1 + f2;
		float f4 = f1 + f2 * (float)0.1;	// 同第 2 行
		double d = d1 * i + j;			// 自动转换成 double
		float f = (float)(d1*5 + d2);
	}
	```