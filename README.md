# MIT-6.006-Introduction-to-Algorithms 算法导论
##### 课程地址：

- ※[推荐]※ youtube上的 [youtube.com](https://www.youtube.com/watch?v=HtSuA80QTyo&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&ab_channel=MITOpenCourseWare)
- B站上的 [【MIT公开课】6.006 算法导论（完结·中英字幕·机翻）_哔哩哔哩_bilibili](https://www.bilibili.com/video/av84549127?spm_id_from=333.788.b_636f6d6d656e74.7)
- MIT课程介绍官网 [Introduction to Algorithms | Electrical Engineering and Computer Science | MIT OpenCourseWare](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/)

##### 课程说明：

- MIT的6.046存在两个版本：2005，2015，前者无算法基础要求，后者要求先学过6.006，即本repo, 6.046（2015）在6.006的基础上又延伸了很多，如果只为算法入门的话，6.006完全足够
- 6.006只有2011年版本的，可以把它理解为 6.046（2005）的 *升级版+精简版* 

##### 我的笔记：

- [MIT-6.006算法导论 (notion.site)](https://mucz.notion.site/MIT-6-006-c0d7fa39f4054b64b14eed04e7554163)

##### 文件说明：

- 本repo整理了MIT官网上提供的文档，加了一些自己的笔记和测试代码
- 文件夹前的编号是为了正确显示lec和ps的顺序，顺序参考了课程页面
  - 比如：上完lec02和lec03之后开始做ps02
- `lec` ：讲义 or ppt ，与视频正课编号一致
- `ps `：problem set 也就是题
- **`xxx.cpp xxx.c xxx.py` 课上提到的问题、算法、数据结构的实现**



##### 目录：

| LEC #                           | TOPICS                                                       | KEY DATES                                 | PS key words                              |
| :------------------------------ | :----------------------------------------------------------- | :---------------------------------------- | ----------------------------------------- |
| **Unit 1: Introduction**        |                                                              |                                           |                                           |
| 1                               | Algorithmic thinking, peak finding                           | Problem set 1 out                         | **Asymptotic Practice & 2D Peek-Finding** |
| 2                               | Models of computation, Python cost model, document distance  |                                           |                                           |
| **Unit 2: Sorting and Trees**   |                                                              |                                           |                                           |
| 3                               | Insertion sort, merge sort<br />`Sort.c`                     | Problem set 1 due <br />Problem set 2 out | **Asymptotic Practice of Tree& Heap**     |
| 4                               | Heaps and heap sort<br />`Heap.py` `HeapSort.c`              |                                           |                                           |
| 5                               | Binary search trees, BST sort                                |                                           |                                           |
| 6                               | AVL trees, AVL sort<br />`BBST.cpp`                          | Problem set 2 due                         |                                           |
| 7                               | Counting sort, radix sort, lower bounds for sorting and searching<br />`CountingSort.c` | Problem set 3 out                         | **Augmented AVL Trees** **&** **BBST**    |
| **Unit 3: Hashing**             |                                                              |                                           |                                           |
| 8                               | Hashing with chaining                                        |                                           |                                           |
| 9                               | Table doubling, Karp-Rabin<br />`StringMatching.cpp`<br />`HashTable.cpp` `SimpleHashTable.cpp` | Problem set 3 due <br />Problem set 4 out | **Hash Table**                            |
| 10                              | Open addressing, cryptographic hashing<br />`HasTableOA.cpp` | Problem set 4 due                         |                                           |
| **Quiz 1**                      |                                                              |                                           |                                           |
| **Unit 4: Numerics**            |                                                              |                                           |                                           |
| 11                              | *Integer arithmetic, Karatsuba multiplication*               | Problem set 5 out                         |                                           |
| 12                              | *Square roots, Newton's method*                              |                                           |                                           |
| **Unit 5: Graphs**              |                                                              |                                           |                                           |
| 13                              | Breadth-first search (BFS)                                   |                                           |                                           |
| 14                              | Depth-first search (DFS), topological sorting                | Problem set 5 due <br />Problem set 6 out |                                           |
| **Unit 6: Shortest Paths**      |                                                              |                                           |                                           |
| 15                              | Single-source shortest paths problem                         |                                           |                                           |
| 16                              | Dijkstra                                                     |                                           |                                           |
| 17                              | Bellman-Ford                                                 |                                           |                                           |
| 18                              | Speeding up Dijkstra                                         | Problem set 6 due                         |                                           |
| **Quiz 2**                      |                                                              |                                           |                                           |
| **Unit 7: Dynamic Programming** |                                                              |                                           |                                           |
| 19                              | Memoization, subproblems, guessing, bottom-up; Fibonacci, shortest paths | Problem set 7 out                         |                                           |
| 20                              | Parent pointers; text justification, perfect-information blackjack<br />`BlackJack.cpp` |                                           |                                           |
| 21                              | String subproblems, psuedopolynomial time; parenthesization, edit distance, knapsack<br />`EditDistance.cpp`<br />`LongestCommonSubsequence.cpp` |                                           |                                           |
| 22                              | Two kinds of guessing; piano/guitar fingering, Tetris training, Super Mario Bros. | Problem set 7 due                         |                                           |
| **Unit 8: Advanced Topics**     |                                                              |                                           |                                           |
| 23                              | Computational complexity                                     |                                           |                                           |
| 24                              | Algorithms research topics                                   |                                           |                                           |

