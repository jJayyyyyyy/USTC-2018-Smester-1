时间: 20190107 ~ 20190113

##	新闻

*	[New year, new GitHub: Announcing unlimited free private repos and unified Enterprise offering](https://blog.github.com/2019-01-07-new-year-new-github/)

	GitHub 个人账号可以免费创建无限多个 private repo 了, 这是微软收购 GitHub 后给大家带来的一个福利

*	[VLC 下载量超过 30 亿](https://www.solidot.org/story?sid=59276)

*	[Observations of fast radio bursts at frequencies down to 400 megahertz](https://www.nature.com/articles/s41586-018-0867-7)

	有人认为这是外星人发出的信号

*	[在空中给无人机充电](https://www.solidot.org/story?sid=59261)

*	[英特尔的 10nm Ice Lake CPU](https://www.anandtech.com/show/13774/intels-keynote-at-ces-2019-10nm-ice-lake-lakefield-snow-ridge-cascade-lake)

	<br>

##	资源推荐

*	[C++ string::find complexity](https://stackoverflow.com/questions/8869605/c-stringfind-complexity/8869689)

	Q: Why the c++'s implemented string::find() doesn't use the KMP algorithm (and doesn't run in O(N + M)) and runs in O(N * M)?

	A: The C++ standard doesn't specify implementation details, and only specifies complexity requirements in some cases. The only complexity requirements on std::string operations are that size(), max_size(), operator[], swap(), c_str() and data() are all constant time. The complexity of anything else depends on the choices made by whoever implemented the library you're using.

	The most likely reason for choosing a simple search over something like KMP is to avoid needing extra storage. Unless the string to be found is very long, and the string to search contains a lot of partial matches, the time taken to allocate and free that would likely be much more than the cost of the extra complexity.

	Q: If the complexity of current substr is not O(N * M), what is that?

	A: That's the worst-case complexity, when the string to search contains a lot of long partial matches. If the characters have a reasonably uniform distribution, then the average complexity would be closer to O(N). So by choosing an algorithm with better worst-case complexity, you may well make more typical cases much slower.

*	[Visualizations of Data Structure and Algorithm](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)

	来自 Department of Computer Science of USFCA, 展示了常见数据结构和算法的可视化过程

	比如 [Red/Black Tree](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html), [Splay Tree](https://www.cs.usfca.edu/~galles/visualization/SplayTree.html) 的结点的插入删除等等

*	[online gif editor](https://ezgif.com/)

	在查看 [office 的这篇文档](https://support.office.com/zh-cn/article/%E5%90%91%E5%B9%BB%E7%81%AF%E7%89%87%E6%B7%BB%E5%8A%A0%E5%8A%A8%E6%80%81-gif-3a04f755-25a9-42c4-8cc1-1da4148aef01)时发现的一个在线编辑和制作 gif 动画的工具

*	[Trie by 花花](https://www.youtube.com/watch?v=f48wGD-MuQw)

	对应 [LeetCode P208 Implement Trie (Prefix Tree)](https://github.com/jJayyyyyyy/OJ/blob/master/LeetCode/201-300/P208_Implement_Trie_Prefix_Tree_*.cpp)

*	[suffix array by WilliamFiset](https://www.youtube.com/watch?v=zqKlL3ZpTqs)

	<br>

##	其他

*	[]

	<br>
