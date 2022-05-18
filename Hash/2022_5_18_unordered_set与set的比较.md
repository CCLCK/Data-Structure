[TOC]

## 🌴测试代码

下面这段代码可以比较unordered_set和set增删查的性能

以下数据都是在VS2022 release版本下测的

```c++
#include <iostream>
#include <set>
#include <unordered_set>
#include <stdlib.h>
#include <vector>
#include <time.h>
using namespace std;
#define N 10000000
void test()
{
	srand(time(0));
	vector<int>v;
	v.reserve(N);
	for (int i = 0; i < N; i++)
	{
		v.push_back(rand());
	}

	set<int>s;
	unordered_set<int>us;
//------------------------------------------
	//set insert time
	clock_t begin1 = clock();
	for (int i = 0; i < N; i++)
	{
		s.insert(v[i]);
	}
	clock_t end1 = clock();

	//unorde_set insert time
	clock_t begin2 = clock();
	for (int i = 0; i < N; i++)
	{
		us.insert(v[i]);
	}
	clock_t end2 = clock();
	cout << "set insert: " << end1 - begin1 << endl;
	cout << "unordered_set insert: " << end2 - begin2 << endl << endl;
//------------------------------------------
	//set find time
	clock_t begin3 = clock();
	for (auto e : v)
	{
		s.find(e);
	}
	clock_t end3 = clock();

	clock_t begin4 = clock();
	for (auto e : v)
	{
		us.find(e);
	}
	clock_t end4 = clock();
	cout << "set find: " << end3 - begin3 << endl;
	cout << "unordered_set find: " << end4 - begin4 << endl << endl;
//------------------------------------------

	//set erase time
	clock_t begin5 = clock();
	for (auto e : v)
	{
		s.erase(e);
	}
	clock_t end5 = clock();

	//unordered_set erase time
	clock_t begin6 = clock();
	for (auto e : v)
	{
		us.erase(e);
	}
	clock_t end6 = clock();

	cout << "set earse: " << end5- begin5 << endl;
	cout << "unordered_set erase: " << end6 - begin6 << endl << endl;
}

int main()
{
	test();

	return 0;
}
```

## 🌴比较

### 🌵N=1000

![image-20220518221326635](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221326635.png)

### 🌵N=10000

![image-20220518221357690](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221357690.png)

### 🌵N=100000

![image-20220518221424418](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221424418.png)

### 🌵N=1000000

![image-20220518221507808](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221507808.png)

### 🌵N=10000000

![image-20220518221535054](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221535054.png)

### 🌵N=100000000

![image-20220518221729424](https://pic-1304888003.cos.ap-guangzhou.myqcloud.com/img/image-20220518221729424.png)

## 🌴小结

可以看到unordered_set在增删查方面的性能都比set好，但是为什么我们不用unordered_set去代替set呢？因为set还有一个特点就是有序！而在底层方面，unordered_set底层是哈希，set是红黑树。

所以处理无序数据时建议用unordered_set，如果需要有序那就选set