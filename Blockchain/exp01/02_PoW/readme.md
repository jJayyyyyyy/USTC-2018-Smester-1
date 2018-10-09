##	PoW, 工作量证明

*	`PoW` 的英文是 `Proof of Work`，即工作量证明。我们在上一节已经完成了区块链的原型，不过，向整条链中加入区块太容易了。

	> 区块链和比特币的其中一个核心就是，要想加入新的区块，必须先完成一些非常困难的工作。

	因此，本节引入的 `PoW` 就是一些 `困难的工作`

*	数据结构

	```cpp
	struct Block{
		u64 nonce;
		u64 timeStamp;
		string msg;
		string prevHash;
		string currHash;
		string strHexTargetHash;
		Block * next;
	};
	```

	本节新加入的数据是 `nonce`, `strHexTargetHash`, 此外 `timeStamp` 的类型也由上一节的 `string` 变成了本节的 `u64`

<br>

##	Nonce

*	> Wikipedia: In cryptography, a nonce is an arbitrary number that can be used just once.
	>
	> 百度百科: Nonce 是 Number once 的缩写，在密码学中，Nonce 是一个只被使用一次的任意或非重复的随机数字，在各类验证协议的通信应用中确保验证信息不被重复使用以对抗重放攻击(Replay Attack)

*	增加了 `PoW` 之后，我们对 `validHash` 就有了限制，即，`validHash` 的二进制形式的前 `targetBits` 位必须是 `0`

	```
	data = prevHash + msg + timestamp + targetBits + nonce
	hash = sha256(data)
	validHash = validate(hash)
	```

	由于 `prevHash`, `targetBits` 都是确定的值，而当我们在某个时间点准备创建新的 `block` 时，`timestamp` 也就确定了。于是，只有改变 `nonce` 才能改变 `data` ，进而改变 `sha256(data)` 的结果

	所以，我们需要对输入量中的 `nonce` 进行遍历搜索，再进行 `sha256(data)` ，试图找到一个符合要求的 `validHash`

	这个过程就是挖矿, `mining`，挖矿比较耗时耗力，是你的工作量证明, `Proof of Work`

<br>

##	挖矿流程

*	本节总体流程和第一节 `Prototype` 一致，不过我们将对其中的 `getHash()` 进行扩展，增加 `PoW` 的内容

*	设置 `targetBits` 和 `strHexTargetHash`

	刚才已经说过，挖矿的过程，就是找到一个 `hash` 值，它的二进制形式的前 `targetBits` 位都是 `0`

	假设 `targetBits = 8`(数字越大越难耗时)，那么符合要求的最大 `hash` 值是

	```
	0000 0000 1111 1111 .... 1111
	前8位是0，后248位是1
	```

	有多种方式可以来判断新的 `hash` 是否满足要求，不过为了更方便地进行数据表示(打印)，我们把 `hash` 值用字符串的方式进行存储，即 `strBinHash`

	结合这一点，最方便的判断 `hash` 是否满足要求的方法就是，我们要设置一个长度 `256` 的 `strBinTargetHash`，且

	```
	strBinTargetHash = "0000 0001 0000 0000 .... 0000"
	strBinTargetHash.size() = 256
	```

	即 strBinTargetHash[7] = '1'，其他全都是 '0'

	这样，只要 `strBinHash < strBinTargetHash`，那么 `strBinHash` 就是一个合格的 `hash`

	为了缩小存储空间，在字符串中我们还可以用16进制代替二进制，

	```
	strHexTargetHash = "01 00 .. 00 .. 00"
	strHexTargetHash.size() = 32
	```

	同样的，只要 `strHexHash < strHexTargetHash`，那么 `strHexHash` 就是一个合格的 `hash`

*	`prepareData()`

	准备数据 data ，用于接下来的 `sha256(data)`

	```cpp
	string data = byteArr2str(prevHash) +
		msg +
		byteArr2str(int2hex(timeStamp)) +
		byteArr2str(int2hex(targetBits)) +
		byteArr2str(int2hex(tmpNonce));
	```

	需要注意的是，这次实验的 [第一节](https://github.com/Jeiwan/blockchain_go/blob/part_1/block.go) 和 [第二节](https://github.com/Jeiwan/blockchain_go/blob/part_2/proofofwork.go#L38)，对于 `timestamp` 的处理方法是不一样的。为了描述两者的区别，假设现在是 `time.Now().Unix()` 的第 `1538269222` 秒，假设现在是 `Genesis Block`，并且先不考虑 `targetBit` 和 `nonce`

	*	按照第一节(prototype)的方法，将会得到

		```cpp
		u64 timestamp = 1538269222;
		string strDecTimeStamp = to_string(timestamp);

		// 将要进行sha256的字符串是 "Genesis Block1538269222"
		string data = "Genesis Block" + strTimeStamp;

		string strHexhash = sha256(data);
		// 结果是
		// 6e64873ff5d89cfa2c7d8701dbd203c2f95a642732d668b7dd3a2589cfc23d5f
		```

	*	如果按照第二节(pow)的方法，将会得到

		```cpp
		u64 timestamp = 1538269222;
		string strHexTimeStamp = "000000005bb02026";
		string strTs = byte2str("000000005bb02026");

		// 将要进行sha256的字符串是 "Genesis Block" + strTS
		string data = "Genesis Block" + strTs;

		string strHexhash = sha256(data);
		// 结果是
		// b84530cce8354d338b65715104ff23bf84b26c8d112909029303095d5d0a7f05
		```

		其中 `string strTs` 是这么来的，首先把 `10进制` 整数 `1538269222` 变成 `16进制` 的 `5bb02026`, 再把它当作字符串并在前面补 `0`，得到 `"000000005bb02026"`，接着按照 `2个字符` 一组，每组再解读成 `16进制` 的整数，

		```
		0x00, 0x00, 0x00, 0x00, 0x5b, 0xb0, 0x20, 0x26
		```

		再根据 `extended ASCII` 进行解读，得到

		```
		'\0', '\0', '\0', '\0', '[', '°', ' ', '&'
		```

		即 `"[° &"`，

	*	总结一下就是，两个小节中将要进行 `sha256` 的字符串分别是

		```
		"Genesis Block1538269222"	// 第1节
		"Genesis Block[° &"		// 第2节
		```

		目前还没有研究比特币的实现是按照哪种方式将 `timestamp` 变成字符串的。

*	计算并验证新的 `hash` 是否满足要求

	```cpp
	for( u64 tmpNonce = 0; tmpNonce < maxNonce; tmpNonce++ ){
		string data = prepareData( tmpNonce );
		string tmpHash = getsha256(data);

		if( tmpHash < strHexTargetHash ){
			// 小于，则前 targetBits 位都是0, 即符合要求
			cout<<tmpHash<<"\n\n";
			currHash = tmpHash;
			nonce = tmpNonce;
			break;
		}
	}
	```

<br>

##	运行结果

*	为了方便对照，我们手动把 `go` 和 `c++` 代码中的 `timeStamp` 设为 `0`，于是可以得到如下结果

	```
	Mining the block containing "Genesis Block"
	0095fc432755e954f7e692a8d87f2a2c90ccd4f9105f0f7d92eb862a64882e51

	Mining the block containing "send 1 BTC to Ivan"
	00545df96cd7e392f83e03740f12a2481593c45a12c456c80d40ab9b5a146480

	Mining the block containing "send 2 more BTC to Ivan"
	00203c07d82584fff3b977968e37cdff451e0a2913a4ee8c487932cbc5359b98



	prev hash: 
	curr msg: Genesis Block
	curr Hash: 0095fc432755e954f7e692a8d87f2a2c90ccd4f9105f0f7d92eb862a64882e51
	PoW: 1


	prev hash: 0095fc432755e954f7e692a8d87f2a2c90ccd4f9105f0f7d92eb862a64882e51
	curr msg: send 1 BTC to Ivan
	curr Hash: 00545df96cd7e392f83e03740f12a2481593c45a12c456c80d40ab9b5a146480
	PoW: 1


	prev hash: 00545df96cd7e392f83e03740f12a2481593c45a12c456c80d40ab9b5a146480
	curr msg: send 2 more BTC to Ivan
	curr Hash: 00203c07d82584fff3b977968e37cdff451e0a2913a4ee8c487932cbc5359b98
	PoW: 1
	```

	后续使用时，把 `timeStamp` 重新设为当前时间戳即可

<br>

##	参考链接

*	[工作量证明](https://liuchengxu.gitbook.io/blockchain/bitcoin/proof-of-work)

*	[Nonce, Wikipedia](https://en.wikipedia.org/wiki/Cryptographic_nonce)

*	[Nonce, 百度百科](https://baike.baidu.com/item/Nonce/2525414)

*	[Extended ASCII](https://www.ascii-code.com/)

*	[SHA-256 hash calculator](https://www.xorbin.com/tools/sha256-hash-calculator)

*	[Integer to hex string in C++](https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c)
