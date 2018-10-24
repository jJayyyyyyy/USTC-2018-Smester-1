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

struct NodeList{
	Node *head, *tail;
	size_t len;

	NodeList(){
		head = NULL;
		tail = NULL;
		len = 0;
		initList();
	}

	// get input from filename
	void initList(){
		ifstream ifs;
		string filename = FILENAME;
		ifs.open(filename, ifstream::in);
		string line;

		getline(ifs, line);
		head = new Node(line);
		tail = head;
		len++;
		while( getline(ifs, line) ){
			insertTail(line);
		}
		ifs.close();
	}

	void printAll(){
		Node * p = head;
		while( p != NULL ){
			p->print();
			p = p->next;
		}
	}

	Node * findAt(size_t index){
		if( isValidIndex(index) ){
			Node * p = head;
			for( size_t i = 0; i < index; i++ ){
				p = p->next;
			}
			return p;
		}
		return NULL;
	}

	void printAt(size_t index){
		if( isValidIndex(index) ){
			Node * p = findAt(index);
			p->print();
		}
	}

	void insertTail(string & line){
		tail->next = new Node(line);
		tail = tail->next;
		len++;
	}

	// get input from stdin
	void insert(size_t index){
		if( isValidIndex(index) ){
			cout<<"请按照 [学号,姓名,年龄] 的格式输入学生信息\n";
			string line;
			cin>>line;

			// TODO: 判断输入合法性

			Node *node = new Node(line);
			if( index == 0 ){
				node->next = head;
				head = node;
			}else{
				Node * p = findAt(index-1);
				node->next = p->next;
				p->next = node;
			}
		}
	}

	void del(size_t index){
		if( isValidIndex(index) ){
			Node * p;
			if( index == 0 ){
				p = head;
				head = head->next;
			}else{
				Node *node = findAt(index-1);
				p = node->next;
				node->next = p->next;
			}
			len--;
			free(p);
		}
	}

	bool isValidIndex(size_t index){
		if( index >= 0 && index < len ){
			return true;
		}else{
			cout<<"下标越界!\n";
			return false;
		}
	}
};

int main(){
	NodeList * li = new NodeList();
	li->printAll();
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
				li->printAt(index);
			}else if( option == 'D' ){
				li->del(index);
			}else if( option == 'I' ){
				li->insert(index);
			}
		}

		cout<<"\n\n完成操作后的数组数据如下\n";
		li->printAll();
		cout<<"\n\n";
	}

	free(li);
	return 0;
}

