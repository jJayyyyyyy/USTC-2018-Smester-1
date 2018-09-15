/*
16bit 编码

TODO1:
为了方便对照与课件实例进行对照, 这里采用了 16bit 编码(有点浪费空间, 且对于较短的输入并没有起到压缩的效果)
想办法实现课上说的 12bit 编码

TODO2:
如果解码字典满了, 进行清空等相应处理
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#define u16 u_int16_t
using namespace std;

class MyLZW{
public:
	unordered_map<string, u16> mEn;
	string mDe[1024];				// 解码查表
	
	vector<u16> compress(string input){
		u16 i = 0;
		for( i = 0; i < 256; i++ ){
			string w(1, i);
			mEn[w] = i;
		}
		
		string w = "";
		vector<u16> output;
		input += '\0';
		for( char k : input ){
			string wk = w + k;
			if( mEn.find(wk) != mEn.end() ){
				w = wk;
			}else if( mEn.find(w) != mEn.end() ){
				// add wk to the dictionary (so wk is stored);
				u16 codeWK = mEn[w];
				mEn[wk] = i++;
				// output the code for w;
				output.push_back(codeWK);
				// w = k;
				w = k;
			}
		}
		return output;
	}
	
	string decompress(vector<u16> input){
		u16 i = 0;
		for( i = 0; i < 256; i++ ){
			string w(1, i);
			mDe[i] = w;
		}
		
		string output = "";
		string k, w;
		bool isFirst = true;
		for( u16 code : input ){
			// entry = dictionary entry for k;
			k = mDe[code];
			// output entry;
			output += k;
			// add w + entry[0] to dictionary;
			if( isFirst ){
				isFirst = false;
			}else{
				mDe[i++] = w + k[0];
			}
			// w = entry;
			w = k;
		}
		return output;
	}
};

int main(){
	MyLZW lzw;
	
	// 输入
	// ^WED^WE^WEE^WEB^WET
	// 期望输出
	// 94 87 69 68 256 69 260 261 257 66 260 84
	string s1 = "^WED^WE^WEE^WEB^WET";
	vector<u16> ans = lzw.compress(s1);
	for( u16 num : ans ){
		cout<<num<<' ';
	}
	cout<<'\n';
	
	// 输入
	// 94 87 69 68 256 69 260 261 257 66 260 84
	// 期望输出
	// ^WED^WE^WEE^WEB^WET
	string s2 = lzw.decompress(ans);
	cout<<s2<<'\n';
	
	cout<<(s1 == s2)<<'\n';
	
	return 0;
}

/*
 
^WED^WE^WEE^WEB^WET + EOF = 20 * 8

^WED<256>E<260><261><257>B<260>T
94 87 69 68 256 69 260 261 257 66 260 84 = 12 * 16



或者把 u16 换成 u8
256 -> 128

^WED^WE^WEE^WEB^WET + EOF = 20 * 8
94 87 69 68 128 69 132 133 129 66 132 84 = 12 * 8


这样, 压缩前的长度还是 160 bit
压缩后是 12 * 8 = 96 bit
*/
