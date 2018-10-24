/**
 * city_temperature.cpp, 本程序主要用于练习链表操作
 * 
 * 首先从当前目录读取数据文件 citytemp.dat，从而构造一个个 Node 结点
 * 然后按照预定规则进行插入排序，生成一个单链表L1，其头结点为 head
 * 完成链表 L1 的创建后，首先遍历 L1，返回总的结点数 cnt
 * 接着，重新遍历 L1，并输出各个结点，同时对于中间结点，即第 cnt/2 个结点，输出附加信息 " <-- mid "
 * 然后，删除头结点 head，得到链表 L2，并遍历输出L2
 * 这之后进入一个循环，每次 删除 head->next, 得到新的链表 Li, 并遍历输出 Li
 * 退出循环后，再删除头结点 head，再次遍历链表并输出结点信息。由于此时链表为空，所以不会有输出信息
 * 退出程序
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

/**
 * 结点的数据结构, 每个结点包含如下信息
 * temp: 城市温度
 * city: 城市名
 * state: 城市所属的州名
 * next: 指向下一个结点的指针
 */
struct Node {
	int temp;
	string city, state;
	Node * next;
	Node(int mtemp, string mcity, string mstate) : temp(mtemp), city(mcity), state(mstate), next(NULL) {}
	Node(string buffer){
		size_t comma = buffer.find(',');
		if( comma != string::npos ){
			temp = stoi(buffer.substr(0, 3));
			city = buffer.substr(3, comma-3);
			state = buffer.substr(comma+2, 2);
		}
		next = NULL;
	}
	
	// 重载 < 运算符，用于插入排序
	bool operator < (const Node & a) const {
		if( temp != a.temp ){
			return temp < a.temp;
		}else if( city != a.city ){
			return city < a.city;
		}else{
			return state < a.state;
		}
	}
	
	// 重载 == 运算符，用于去掉重复结点
	bool operator == (const Node & a) const {
		return (temp == a.temp && city == a.city && state == a.state);
	}
};

/**
 * 由于题目要求链表进行升序排列，所以建立链表的过程相当于插入排序
 * @param head: 链表头结点
 * @param node: 待插入的结点
 * @return: 返回头结点
 * 从头结点开始遍历，首先找到第一个大于 node 的结点 now
 * 将 node 插入 now 之前
 */
Node * ascInsert(Node * head, Node * & node){
	if( head == NULL ){
		return node;
	}
	
	Node *pre = head, *now = head;
	while( now != NULL ){
		// 从头结点开始遍历，首先找到第一个大于 node 的结点 now
		if( *node < *now ){
			break;
		}
		pre = now;
		now = now->next;
	}
	
	// 将 node 插入 now 之前
	if( *node == *pre ){
		delete node;
	}else{
		pre->next = node;
		node->next = now;
	}
	return head;
}

/**
 * 统计链表结点个数
 * @param head: 链表头结点
 * @return: 总结点个数
 */
int cntNode(Node * head){
	int cnt = 0;
	while( head != NULL ){
		head = head->next;
		cnt++;
	}
	return cnt;
}

/**
 * 遍历链表，并打印结点信息. 对于第 mid 个结点，再输出附加信息 " <--mid"
 * @param head: 链表头结点
 * @param mid: mid = ttlcnt / 2，其中 ttlcnt 是总结点数
 * @return: 返回总结点数
 */
int showList(Node * head, int mid){
	int cnt = 0;
	while( head != NULL ){
		if( cnt == mid ){
			cout<<cnt<<": "<<(head->temp)<<' '<<(head->city)<<' '<<(head->state)<<" <-- mid\n";
		}else{
			cout<<cnt<<": "<<head->temp<<' '<<head->city<<' '<<head->state<<'\n';
		}
		head = head->next;
		cnt++;
	}
	return cnt;
}

/**
 * 删除头结点
 * @param head: 链表头结点
 * @return: 新的链表头结点
 */
Node * deleteHead(Node * head){
	if( head != NULL ){
		Node * p = head->next;
		delete head;
		return p;
	}else{
		return NULL;
	}
}

/**
 * 删除 head->next
 * @param head: 链表头结点
 * @return: 链表头结点
 */
Node * deleteHeadNext(Node * head){
	if( head == NULL || head->next == NULL ){
		return head;
	}

	Node * p = head->next;
	head->next = p->next;
	delete p;
	return head;
}

/**
 * 主函数
 * @param argc: 命令行参数的个数 
 * @param argv: 命令行参数数组
 * 首先，若 argc != 2 则参数个数不正确，退出程序
 * 文件名 filename = argv[1]
 * 接着，使用 ifstream 文件流，读取 filename 文件
 * 使用 getline() 逐行读取 ifs，每一行存入 buffer，并以此构造新结点 node，再插入链表，完成 ifs 的读取后，关闭文件流
 */
int main(int argc, char *argv[]){
	// 首先，若 argc != 2 则参数个数不正确，退出程序
	if ( argc != 2 ){
		cerr<<"Usage: citytemp filename.ext\n";
		return EXIT_FAILURE;
	}
	// 文件名 filename = argv[1]
	string filename(argv[1]);
	ifstream ifs;

	// 接着，使用 ifstream 文件流，读取 filename 文件
	try{
		ifs.open(filename, ifstream::in);
	}catch(exception e){
		cerr<< "Exception opening/reading/closing file\n";
	}

	Node * head = NULL;
	int nodeCnt = 0;
	string buffer;
	// 使用 getline() 逐行读取 ifs，每一行存入 buffer，并以此构造新结点 node，再插入链表 L1
	while ( getline(ifs, buffer) ){
		Node * node = new Node(buffer);
		head = ascInsert(head, node);
	}
	ifs.close();	// 关闭文件流

	// 首先遍历 L1，返回总的结点数 cnt
	cout<<"cnt nodes: ";
	int cnt = cntNode(head);
	cout<<cnt<<'\n';

	// 遍历 L1，并输出各个结点，同时对于中间结点，即第 cnt/2 个结点，输出附加信息 " <-- mid "
	cout<<"show linked list\n";
	cnt = showList(head, (cnt - 1) / 2);

	// 删除头结点 head，得到链表 L2，并遍历输出L2
	cout<<"\n\nDelete Head\n";
	head = deleteHead(head);
	cnt--;
	cnt = showList(head, (cnt - 1) / 2);

	// 进入一个循环，每次 删除 head->next, 得到新的链表 Li, 并遍历输出 Li
	while( head != NULL && head->next != NULL ){
		cout<<"\n\nDelete head->next\n";
		head = deleteHeadNext(head);
		cnt--;
		cnt = showList(head, (cnt - 1) / 2);
	}
	
	// 退出循环后，再删除头结点 head，再次遍历链表并输出结点信息。由于此时链表为空，所以不会有输出信息
	cout<<"\n\nDelete Head\n";
	head = deleteHead(head);
	cnt--;
	cnt = showList(head, (cnt - 1) / 2);

	return 0;
}
