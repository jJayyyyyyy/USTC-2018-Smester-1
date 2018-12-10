/*
只考虑最短路径唯一的情况
*/
#include <iostream>
#include <vector>
#define INF 0x3fffffff
using namespace std;

// BF算法用到的邻接表的结点结构
struct Node{
	int vertex, distance;
	Node(int v, int d){
		vertex = v;
		distance = d;
	}
};

class BellmanFord{
public:
	// n 是结点总数
	int n;
	// graph 以邻接表形式保存了图的信息
	vector<vector<Node> > graph;
	// pre[i] 是结点 src 到结点 i 的最短路径上的 i 的前置结点
	vector<vector<int> > pre;
	// dist[i] 表示结点 src 到结点 i 的最短距离
	// ansPath 保存了 src 到某个结点的最短路径
	// ansPath 是各个结点复用的, 每次打印完最短路径后需要 ansPath.clear()
	vector<int> dist, ansPath;

	BellmanFord(){
	}

	// 构造函数
	BellmanFord(int numVertex){
		n = numVertex;
		graph.resize(n);
		dist.resize(n, INF);
	}

	// 初始化 graph, pre, dist
	void init(){
		graph.resize(n);
		pre.resize(n);
		dist.resize(n, INF);
	}

	// 使用 Bellman-Ford 算法寻找 src 到各个结点的最短路径 dist[]
	void doBF(int src){
		dist[src] = 0;
		// iteration = |V| - 1 = n - 1
		// 即循环次数 = n - 1
		// 结点编号为 [0, n-1]
		for( int i = 0; i < n - 1; i++ ){
			// 把每个结点当作中间结点 mid, 尝试更新 mid 能够到达的结点的 dist[]
			for( int mid = 0; mid < n; mid++ ){
				for( Node node : graph[mid] ){
					int nextV = node.vertex;
					int distance = node.distance;
					if( dist[mid] + distance < dist[nextV] ){
						// 如果通过 mid 可以更快到达结点 i, 那么就更新 dist[i]
						dist[nextV] = dist[mid] + distance;
					}
				}
			}
		}
	}

	// BF 算法无法处理含负边的环
	// return true 说明图中有负边环
	// return false 时可以正确处理
	bool hasNegativeCircle(){
		for( int mid = 0; mid < n; mid++ ){
			for( Node node : graph[mid] ){
				int nextV = node.vertex;
				int distance = node.distance;
				if( dist[mid] + distance < dist[nextV] ){
					return true;
				}else if( dist[mid] + distance == dist[nextV] ){
					pre[nextV].clear();
					pre[nextV].push_back(mid);
				}
			}
		}
		return false;
	}

	// 获取 src 到 dest 的路径
	void dfs(int src, int v){
		if( v == src ){
			ansPath.push_back(v);
			return;
		}

		for( int preV : pre[v] ){
			dfs(src, preV);
			ansPath.push_back(v);
		}
	}

	// 打印 src 到 dest 的路径
	void getPath(int src, int dest){
		ansPath.clear();
		dfs(src, dest);
		if( ansPath.size() > 0 ){
			cout<<ansPath[0];
			for( int i = 1; i < ansPath.size(); i++ ){
				cout<<"->"<<ansPath[i];
			}
		}
	}

	// 打印最短距离和最短路径
	void getPathAndDistance(int src, int dest){
		// cout<<"Shortest distance from src "<<src<<" to each node is as below:\n";
		cout<<"Path from "<<src<<" to "<<dest<<'\n';
		int distance = dist[dest];
		if( distance != INF ){
			getPath(src, dest);
			cout<<"\ndistance: "<<distance<<"\n\n";
		}else{
			cout<<"No Path";
			cout<<"\ndistance: INF\n\n";
		}
	}

	// 测试用例
	void test(){
		n = 6;
		init();

		graph[0].push_back(Node(2, 100));
		graph[0].push_back(Node(3, 30));
		graph[0].push_back(Node(4, 10));

		graph[1].push_back(Node(4, 5));

		graph[3].push_back(Node(2, 60));
		graph[3].push_back(Node(5, 20));

		graph[4].push_back(Node(5, 50));

		graph[5].push_back(Node(2, 10));

		int src = 0;
		doBF(src);

		if( hasNegativeCircle() == false ){
			for( int dest = 0; dest < n; dest++ ){
				getPathAndDistance(src, dest);
			}
		}else{
			cout<<"there is a negative circle\n";
		}
	}
};

class Dijkstra{
public:
	// 结点总数为 n, 编号范围 [0, n-1]
	int n;
	// vis[] 保存结点的访问状态
	// 若 vis[i] == false 则说明结点 i 尚未被访问
	vector<bool> vis;
	// dist[i] 表示结点 src 到结点 i 的最短距离
	// ansPath 保存了 src 到某个结点的最短路径
	// ansPath 是各个结点复用的, 每次打印完最短路径后需要 ansPath.clear()
	vector<int> dist, ansPath;
	// graph 保存了图上各个结点直接的连接关系
	vector<vector<int> > graph;
	// pre[i] 是结点 src 到结点 i 的最短路径上的 i 的前置结点
	vector<vector<int> > pre;

	// 构造函数为空
	Dijkstra(){
	}

	// 初始化
	// 将 vis 全部设为未访问 false
	// 将 dist 全部设为 INF, 即初始距离设为无穷大
	void init(){
		fill(vis.begin(), vis.end(), false);
		fill(dist.begin(), dist.end(), INF);
	}

	// 使用 Dijkstra 算法寻找 src -> dest 的最短路径
	void doDijkstra(int src, int dest){
		// 先进行初始化
		init();
		// 将原点 src 距离设为 0
		dist[src] = 0;
		// 如果目的结点 dest 还未被访问, 就继续循环
		while( vis[dest] == false ){
			int mid = -1;
			int minDist = INF;
			for( int i = 0; i < n; i++ ){
				// 从未访问结点集合中选出结点 mid , 使 dist[mid] 最小
				if( vis[i] == false && dist[i] < minDist ){
					mid = i;
					minDist = dist[i];
				}
			}
			// mid 初始值为 -1 如果在遍历未访问结点后 mid 仍为 -1, 则说明目标结点不可达
			if( mid == -1 ){
				return;
			}

			// 将 mid 置为已访问结点
			vis[mid] = true;
			// 以 mid 为中间结点, 更新 mid 能够到达的结点的 dist[]
			for( int i = 0; i < n; i++ ){
				if( vis[i] == false && graph[mid][i] != INF ){
					if( dist[mid] + graph[mid][i] < dist[i] ){
						// 如果通过 mid 可以更快到达结点 i, 那么就更新 dist[i]
						dist[i] = dist[mid] + graph[mid][i];
						// 并且将 i 的前置结点设为 mid
						pre[i].clear();
						pre[i].push_back(mid);
					}
				}
			}
		}
	}

	// 获取 src 到 dest 的路径
	void dfs(int src, int v){
		if( v == src ){
			ansPath.push_back(v);
			return;
		}

		for( int preV : pre[v] ){
			dfs(src, preV);
			ansPath.push_back(v);
		}
	}

	// 打印 src 到 dest 的路径
	void getPath(int src, int dest){
		ansPath.clear();
		dfs(src, dest);
		if( ansPath.size() > 0 ){
			cout<<ansPath[0];
			for( int i = 1; i < ansPath.size(); i++ ){
				cout<<"->"<<ansPath[i];
			}
		}
	}

	// 打印最短距离和最短路径
	void getPathAndDistance(int src, int dest){
		cout<<"Path from "<<src<<" to "<<dest<<'\n';
		int distance = dist[dest];
		if( distance != INF ){
			getPath(src, dest);
			cout<<"\ndistance: "<<distance<<"\n\n";
		}else{
			cout<<"No Path";
			cout<<"\ndistance: INF\n\n";
		}
	}

	// Dijkstra 算法无法处理有负边的图
	bool hasNegativeEdge(){
		size_t row = graph.size();
		size_t col = graph[0].size();
		for( int i = 0; i < row; i++ ){
			for( int j = 0; j < col; j++ ){
				if( graph[i][j] < 0 ){
					return true;
				}
			}
		}
		return false;
	}

	// 测试用例
	void test(){
		n = 6;
		vis.resize(n, false);
		dist.resize(n, INF);
		graph.resize(n, vector<int>(n, INF));
		pre.resize(n);

		graph[0][2] = 100;
		graph[0][3] = 30;
		graph[0][4] = 10;

		graph[1][4] = 5;

		graph[3][2] = 60;
		graph[3][5] = 20;

		graph[4][5] = 50;

		graph[5][2] = 10;
 
		if( hasNegativeEdge() == false ){
			int src = 0;
			for( int dest = 0; dest < n; dest++ ){
				doDijkstra(src, dest);
				getPathAndDistance(src, dest);
			}
		}else{
			cout<<"There is a negative edge\n";
		}
	}
};

int main(){
	cout<<"Bellman-Ford algorithm\n-----------------------\n";
	BellmanFord bf;
	bf.test();
	cout<<"\n\n\n";

	cout<<"Dijkstra algorithm\n---------------------------\n";
	Dijkstra dijkstra;
	dijkstra.test();
	cout<<"\n\n\n";

	return 0;
}