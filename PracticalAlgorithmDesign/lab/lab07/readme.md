##	实用算法第七次实验

*	图的最短路径

	设起点 `src = V0`, 求 `src` 到各个结点的最短距离

	![graph](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/lab/lab07/assets/graph.png)

*	Bellman-Ford 算法

*	Dijkstra 算法

	<br>

##	Bellman-Ford 算法

*	TODO: 简介

*	参考代码

	```cpp
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
	```

*	参考视频

	[Bellman-Ford in 5 minutes](https://www.youtube.com/watch?v=obWXjtg0L64&list=PL2h_VWy7-njuvpg8szurNzxh14j39kyWK&index=6)

	<br>

##	Dijkstra 算法

*	TODO: 简介

*	参考代码

	```cpp
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
	```

*	参考视频

	[Dijkstra Algorithm](https://www.youtube.com/watch?v=gdmfOwyQlcI&list=PL2h_VWy7-njuvpg8szurNzxh14j39kyWK&index=5)

	<br>

##	参考资料

*	[Dijkstra Algorithm](https://www.youtube.com/watch?v=gdmfOwyQlcI&list=PL2h_VWy7-njuvpg8szurNzxh14j39kyWK&index=5)

*	[Bellman-Ford in 5 minutes](https://www.youtube.com/watch?v=obWXjtg0L64&list=PL2h_VWy7-njuvpg8szurNzxh14j39kyWK&index=6)

*	[算法笔记](https://book.douban.com/subject/26827295/)

*	[OJ 模板: Dijkstra, BF](https://github.com/jJayyyyyyy/OJ/blob/master/tools/Question4.md)
