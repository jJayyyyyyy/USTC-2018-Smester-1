/*
只考虑最短路径唯一的情况
*/
#include <iostream>
#include <vector>
#define INF 0x3fffffff
using namespace std;

struct Node{
	int vertex, distance;
	Node(int v, int d){
		vertex = v;
		distance = d;
	}
};

class BellmanFord{
public:
	int n;
	vector<vector<Node> > graph;
	vector<vector<int> > pre;
	vector<int> dist, ansPath;

	BellmanFord(){
	}

	BellmanFord(int numVertex){
		n = numVertex;
		graph.resize(n);
		dist.resize(n, INF);
	}

	void init(){
		graph.resize(n);
		pre.resize(n);
		dist.resize(n, INF);
	}

	// get shortest path d[] using BF algorithm
	void doBF(int src){
		fill(dist.begin(), dist.end(), INF);
		dist[src] = 0;
		// iteration = |V| - 1 = n - 1
		// 结点编号为 [0, n-1]
		for( int i = 0; i < n - 1; i++ ){
			// 把每个结点当作中间结点 mid, 尝试更新 mid 能够到达的结点的 dist[]
			for( int mid = 0; mid < n; mid++ ){
				for( Node node : graph[mid] ){
					int nextV = node.vertex;
					int distance = node.distance;
					if( dist[mid] + distance < dist[nextV] ){
						dist[nextV] = dist[mid] + distance;
					}
				}
			}
		}
	}

	// @return: false is good, true is bad
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
	// bool hasNegativeEdge;
	int n, m;
	vector<bool> vis;
	vector<int> dist, ansPath;
	vector<vector<int> > graph;
	vector<vector<int> > pre;

	Dijkstra(){
	}

	void init(){
		fill(vis.begin(), vis.end(), false);
		fill(dist.begin(), dist.end(), INF);
	}

	void doDijkstra(int src, int dest){
		init();
		dist[src] = 0;
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
			if( mid == -1 ){
				return;
			}

			// 设置 mid 为已访问结点
			// 以 mid 为中间结点, 更新 mid 能够到达的结点的 dist[]
			vis[mid] = true;
			for( int i = 0; i < n; i++ ){
				if( vis[i] == false && graph[mid][i] != INF ){
					if( dist[mid] + graph[mid][i] < dist[i] ){
						dist[i] = dist[mid] + graph[mid][i];
						pre[i].clear();
						pre[i].push_back(mid);
					}
				}
			}
		}
	}

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

	bool hasNegativeEdge(){
		size_t row = graph.size();
		size_t col = graph[0].size();
		for( int i = 0; i < row; i++ ){
			for( int j = 0; j < col; j++ ){
				if( graph[i][j] < 0 ){
					return false;
				}
			}
		}
		return true;
	}

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
