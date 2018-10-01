##	区块链原型

*	区块链的英文是 `BlockChain`，顾名思义，我们的原型其实就是一个链表 `Chain`，每个结点都是一个块 `Block`

*	数据结构

	```cpp
	struct Block{
		string timeStamp;	// 时间戳, 记录区块生成的时间
		string prevHash;	// 前一个区块的 hash, 是一个以字符串形式保存的字节数组 byte array
		string currhash;	// 当前区块的 hash, 是一个以字符串形式保存的字节数组 byte array
		string msg;		// 区块中存储的实际交易
		Block * next;
	};

	struct BlockChain{
		Block *head, *tail;
		size_t size;
	}
	```

<br>

##	搭建过程

*	首先创建一个区块链，并添加一个创世区块 `Genesis Block`

	由于这个 `block` 是第一个块，所以其 `prevHash` 为空。另外，它的 `msg` 就是字符串 `Genesis Block`

	接下来我们就可以进行 `sha256(data)` 了

	```cpp
	string data = byte2str(prevHash) + msg + timeStamp;
	currhash = getsha256(data);
	```

	以上就是创世区块的创建过程

*	接着，我们使用 `addBlock(string msg)` 来添加新的区块。`msg` 是我们的交易信息，如 `send 1 BTC to Ivan`

	剩下的工作和之前一样，就是构造 `data` 并进行 `currhash = sha256(data)`

	如此循环即可在区块链中添加新的区块

<br>

##	参考链接

*	[ctime](http://www.cplusplus.com/reference/ctime/time/)

*	[generate-sha256-with-openssl-and-c](https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c)

*	[how-to-use-openssls-sha256-functions](https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions)

*	[sha256-hash-calculator](https://www.xorbin.com/tools/sha256-hash-calculator)

*	[converting-a-hex-string-to-a-byte-array](https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array)

*	[cplusplus reference, strtoul](http://www.cplusplus.com/reference/cstdlib/strtoul/?kw=strtoul)
