#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define FILENAME "Lab1test_utf8.DAT"
using namespace std;

struct Node{
	string id;
	string name;
	int age;
	Node * next;

	Node(string line){
		size_t comma1 = line.find(',');
		size_t comma2 = line.rfind(',');
		id = line.substr(0, comma1);
		name = line.substr(comma1+1, comma2-comma1-1);
		age = stoi(line.substr(comma2+1), NULL, 10);
		next = NULL;
	}

	Node(int usage, string usid, string usname){
		age = usage;
		id = usid;
		name = usname;
		next = NULL;
	}

	void print(){
		cout<<id<<'\t'<<name<<'\t'<<age<<'\n';
	}
};

struct NodeArray{
	vector<Node> stuArray;

	NodeArray(){
		initArray();
	}

	// get input from filename
	void initArray(){
		ifstream ifs;
		string filename = FILENAME;
		ifs.open(filename, ifstream::in);
		string line;
		while( getline(ifs, line) ){
			Node stu(line);
			stuArray.push_back(stu);
		}

		ifs.close();
	}

	void printAll(){
		for( Node stu : stuArray ){
			stu.print();
		}
	}

	void printAt(size_t index){
		if( isValidIndex(index) ){
			stuArray[index].print();
		}
	}

	// get input from stdin
	void insert(size_t index){
		if( isValidIndex(index) ){
			cout<<"请按照 [学号,姓名,年龄] 的格式输入学生信息\n";
			string line;
			cin>>line;

			// TODO: 判断输入合法性

			Node stu(line);
			stuArray.insert(stuArray.begin()+index, stu);
		}
	}

	void del(size_t index){
		if( isValidIndex(index) ){
			stuArray.erase(stuArray.begin()+index);
		}
	}

	bool isValidIndex(size_t index){
		if( index >= 0 && index < stuArray.size() ){
			return true;
		}else{
			cout<<"下标越界!\n";
			return false;
		}
	}
};

int main(){
	NodeArray arr;
	arr.printAll();
	while(true){
		cout<<"请输入操作和下标, 如 P1, I2, D3. 输入 q 退出程序\n";
		string usinput;
		cin>>usinput;
		char option = usinput[0];
		size_t index = 0;
		if( option == 'q' ){
			break;
		}else if( usinput.size() == 1 ){
			cout<<"请重新输入\n";
		}else{
			index = (size_t) stoi(usinput.substr(1), NULL, 0);
			if( option == 'P' ){
				arr.printAt(index);
			}else if( option == 'D' ){
				arr.del(index);
			}else if( option == 'I' ){
				arr.insert(index);
			}
		}

		cout<<"\n\n完成操作后的数组数据如下\n";
		arr.printAll();
		cout<<"\n\n";
	}

	return 0;
}

