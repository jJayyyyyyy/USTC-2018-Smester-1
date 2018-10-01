#include <vector>
#include <iostream>
#include <ctime>	// http://www.cplusplus.com/reference/ctime/time/
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <climits>			// http://www.cplusplus.com/reference/climits/
#define u8 unsigned char
#define u32 unsigned int
#define u64 unsigned long long
#define maxNonce ULLONG_MAX
using namespace std;

// https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
string int2hex(u64 num){
	stringstream ss;
	ss<<setw(16)<<setfill('0')<<hex<<num;
	return ss.str();
}

// TODO
// string s = "000000000000000100000000000000000000000000000000";
// strHexTargetHash = strBin2StrHex(s, 32);
// strHexTargetHash = "0100000000000000000000000000000000000000000000000000000000000000";
// 0000 0000 (b) -> 00
// 0000 0001 (b) -> 01
// 0000 0010 (b) -> 02
string strBin2StrHex(string num, size_t size){
	stringstream ss;
	for( size_t i = 0; i < size; i += 8 ){
		string strPiece = num.substr(i, 8);
		u32 intPiece = (u32)strtoul(strPiece.c_str(), NULL, 2);
		ss<<hex<<setw(2)<<setfill('0')<<intPiece;
	}
	return ss.str();
}

// https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
// https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions
// https://www.xorbin.com/tools/sha256-hash-calculator
string getsha256(string str){
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}

// 将字节数组，转换成字符串
// 举例
// 41 -> 0x41 -> 65 -> A
// 字节数组用字符串表示，是为了方便打印查看 hash 
string byteArr2str(string strByteArray){
	stringstream ss;
	for( int i = 0; i < strByteArray.size(); i += 2 ){
		string strhex = strByteArray.substr(i, 2);
		// https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
		// http://www.cplusplus.com/reference/cstdlib/strtoul/?kw=strtoul
		ss<<(u8)strtoul(strhex.c_str(), NULL, 16);
	}
	string s = ss.str();
	return s;
}

const size_t targetBits = 8;

struct Block{
	u64 nonce;
	u64 timeStamp;
	string msg;
	string prevHash;		// byte array 的字符串形式
	string currHash;		// byte array 的字符串形式
	string strHexTargetHash;
	Block * next;

	Block(string _msg, string pH){
		msg = _msg;
		prevHash = pH;

		// 测试一致性
		// 对 go 做同样处理，使两者的 timestamp 都为 0，控制变量
		// 最后的结果应该是一样的
		timeStamp = 0;
		// 实际应用时，取消下面 3 行的注释
		// time_t timer;
		// time(&timer);
		// timeStamp = (u64)timer;

		if( targetBits > 0 && targetBits < 256 ){
			// 如果 targetBit = 4, 则 target <<= 252
			// 得到 target = 000100000...000 (binary)
			// 若   hash   < 000100000...000 (binary)
			// 则   hash  == 0000xxxxx...xxx
			// 即 hash 前4位为 0, 即为有效 hash
			strHexTargetHash = string(255, '0');
			strHexTargetHash.insert(targetBits - 1, "1");
			strHexTargetHash = strBin2StrHex(strHexTargetHash, 256);
		}

		mining();

		next = NULL;
	}

	void mining(){
		cout<<"Mining the block containing \""<<msg<<"\"\n";
		for( u64 tmpNonce = 0; tmpNonce < maxNonce; tmpNonce++ ){
			string data = prepareData( tmpNonce );
			string tmpHash = getsha256(data);

			// https://wizardforcel.gitbooks.io/golang-stdlib-ref/content/81.html#Int.Cmp
			if( tmpHash < strHexTargetHash ){
				// 小于，则前 targetBits 位都是0, 即符合要求
				cout<<tmpHash<<"\n\n";
				currHash = tmpHash;
				nonce = tmpNonce;
				break;
			}
		}
	}

	string prepareData(u64 tmpNonce){
		// prototype 中, timestamp 是 strconv.FormatInt(b.TimeStamp, 10)
		// 这里变成了 hex
		string data = byteArr2str(prevHash) + msg +
					byteArr2str(int2hex(timeStamp)) +
					byteArr2str(int2hex(targetBits)) +
					byteArr2str(int2hex(tmpNonce));
		return data;
	}

	bool validate(){
		string data = prepareData(nonce);
		string tmpHash = getsha256(data);
		return tmpHash < strHexTargetHash;
	}
};

struct BlockChain{
	Block *head, *tail;
	int size;

	BlockChain(){
		head = new Block("Genesis Block", "");
		tail = head;
		size = 1;
	}

	int addBlock(string msg){
		tail->next = new Block(msg, tail->currHash);
		tail = tail->next;
		size++;
	}
};

int main(int argc, char *argv[]){
	BlockChain * bc = new BlockChain();
	bc->addBlock("send 1 BTC to Ivan");
	bc->addBlock("send 2 more BTC to Ivan");

	cout<<"\n\n\n";
	Block * p = bc->head;
	for( size_t i = 0; i < bc->size; i++ ){
		cout<<"prev hash: "<<p->prevHash<<'\n';
		cout<<"curr msg: "<<p->msg<<'\n';
		cout<<"curr Hash: "<<p->currHash<<'\n';
		cout<<"PoW: "<<p->validate()<<"\n\n\n";
		p = p->next;
	}

	return 0;
}

// TODO
// 3. 数据库(或者自己写保存文件)
// 4. 命令行
// 5. Python
