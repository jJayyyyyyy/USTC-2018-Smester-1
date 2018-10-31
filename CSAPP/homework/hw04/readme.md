##	程序设计与计算机系统第六章作业

6.25, 6.29, 6.34, 6.38. 6.41

*	6.25

	| Cache | m  |  C   | B  | E   | S   | t  | s | b |
	|:------|:---|:-----|:---|:----|:----|:---|:--|:--|
	| 1     | 32 | 1024 | 4  | 4   | 64  | 24 | 6 | 2 |
	| 2     | 32 | 1024 | 4  | 256 | 1   | 30 | 0 | 2 |
	| 3     | 32 | 1024 | 8  | 1   | 128 | 22 | 7 | 3 |
	| 4     | 32 | 1024 | 8  | 128 | 1   | 29 | 0 | 3 |
	| 5     | 32 | 1024 | 32 | 1   | 32  | 22 | 5 | 5 |
	| 6     | 32 | 1024 | 32 | 4   | 8   | 24 | 3 | 5 |

	<br>

*	6.29

	*	A

		| 12 | 11 | 10 | 9  | 8  | 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0  |
		|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|
		|    | CT | CT | CT | CT | CT | CT | CT | CT | CI | CI | C0 | C0 |

	*	B

		| Operation | Address | Hit? | Read value (or unknown) |
		|:----------|:--------|:-----|:------------------------|
		| Read      | 0x834   | Miss | -                       |
		| Write     | 0x836   | Hit  | unknown                 |
		| Read      | 0xFFD   | Hit  | 0xC0                    |

	<br>

*	6.34

	*	dest array

		|      | col0 | col1 | col2 | col3 |
		|------|------|------|------|------|
		| row0 | Miss | Miss | Miss | Miss |
		| row1 | Miss | Miss | Miss | Miss |
		| row2 | Miss | Miss | Miss | Miss |
		| row3 | Miss | Miss | Miss | Miss |

	*	src array

		|      | col0 | col1 | col2 | col3 |
		|------|------|------|------|------|
		| row0 | Miss | Miss | Hit  | Miss |
		| row1 | Miss | Hit  | Miss | Hit  |
		| row1 | Miss | Miss | Hit  | Miss |
		| row1 | Miss | Hit  | Miss | Hit  |

	<br>

*	6.38

	*	A

		外循环 16 次, 内循环 16 次, 每次写 4 次, 所以一共写 `16x16x4 = 1024` 次

	*	B

		因为 `sizeof(int) == 4`, 所以 `sizeof(point_color) == 16`

		又因为 `cache` 的块大小为 `B = 32B`

		由于 `cache` 初始为空, 所以第一步 `square[0][0].c = 0` 肯定是 `Miss`. 然后会在 `cache` 中存入 `32/16 = 2` 个 `point_color`

		这样, 在这次内循环中接下来的

		```
		square[0][0].m = 0
		square[0][0].y = 0
		square[0][0].k = 0
		```

		以及下次内循环中的

		```
		square[0][1].c = 0
		square[0][1].m = 0
		square[0][1].y = 0
		square[0][1].k = 0
		```

		数据都被加载到 `cache` 里面了, 所以使用的时候都是 `Hit`

		因此每 `8` 次写入过程会有 `1` 次 `Miss`

		总的写入次数是 `16x16x4=1024`, 即一共有 `1024/8=128` 次 `Miss`

	*	C

		由上题的分析可以得到 `MissRate = 1/8`

	<br>

*	6.41

	同 6.38, 因为 `sizeof(char) == 1`, 所以 `sizeof(pixel) == 4`, 

	又因为 `cache` 的块大小为 `B = 4B`

	由于 `cache` 初始为空, 所以第一步 `buffer[0][0].r = 0;` 肯定是 `Miss`

	然后会在 `cache` 中存入 `4/4 = 1` 个 `pixel`

	这样, 在这次内循环中接下来的

	```
	buffer[0][0].g = 0
	buffer[0][0].b = 0
	buffer[0][0].a = 0
	```

	都被加载到了 `cache`, 所以使用的时候都是 `Hit`

	下一次循环又重复这样的过程. 因此可以得到 `MissRate = 1/4`

	<br>