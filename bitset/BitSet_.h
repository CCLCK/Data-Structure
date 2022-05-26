#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace ck
{
	template<size_t N>//N个数
	class BitSet
	{	
	public:
		BitSet()
		{
			_bits.resize(N / 8 + 1);//开这么多个字节
		}
		void set(size_t x)//第x位置为1
		{
			if (!test(x))//如果这一位是0，置为1的话++
			{
				_cnt++;
			}
			size_t integer = x / 8;//第几个字节
			size_t rem = x % 8;//字节的第几个位置
			_bits[integer] |= (1 << rem);
		
		}
		void reset(size_t x)//第x位置为0
		{
			if (test(x))//如果这一位是1，置为0的话--
			{
				_cnt--;
			}
			size_t integer = x / 8;//第几个字节
			size_t rem = x % 8;//字节的第几个位置
			_bits[integer] &= (~(1 << rem));
		}
		bool test(size_t x)
		{
			size_t integer = x / 8;//第几个字节
			size_t rem = x % 8;//字节的第几个位置
			return ((_bits[integer] >> rem) & 1) ? true : false;
		}
		void flip(size_t x)//翻转
		{
			if (test(x))//1
			{
				reset(x);
			}
			else//0
			{
				set(x);
			}
		}
		size_t size() const
		{
			return N;
		}
		size_t count()
		{
			return _cnt;
		}
		bool any()
		{
			if (_cnt)
			{
				return true;
			}
			return false;
		}
		bool none()
		{
			return !any();
		}
		bool all()
		{
			if (_cnt == N)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		template<size_t T>
		friend ostream& operator<<(ostream& out, const BitSet<T>& bs);
	
	private:

		vector<char>_bits;
		size_t _cnt = 0;//被设置为1的个数
	};
	template<size_t T>//模板参数不能取名为N
	ostream& operator<<(ostream& out, const BitSet<T>& bs)
	{
		//从后往前是低位到高位，库里面是这样的
		int len = bs.size() / 8 ;
		char tmp;
		tmp = bs._bits[len];
		for (int i = bs.size() % 8 - 1; i >= 0; i--)
		{
			if ((tmp >> i) & 1)
			{
				cout << '1';
			}
			else
			{
				cout << '0';
			}
		}
		for (int i = len-1; i >=0; i--)
		{
			tmp = bs._bits[i];
			for (int j = 7; j >=0; j--)
			{
				if ((tmp >> j) & 1)
				{
					cout << '1';
				}
				else
				{
					cout << '0';
				}
			}
		}

		//从前往后是低位到高位（人看起来合适）
		//for (int i=0;i<len;i++)
		//{
		//	tmp = bs._bits[i];
		//	for (int i =0;i<8;i++)
		//	{
		//		if ((tmp >> i) & 1)
		//		{
		//			cout << '1';
		//		}
		//		else
		//		{
		//			cout << '0';
		//		}
		//	}
		//}		
		//tmp = bs._bits[len];
		//for (int i = 0; i < bs.size() % 8; i++)
		//{
		//	if ((tmp >> i) & 1)
		//	{
		//		cout << '1';
		//	}
		//	else
		//	{
		//		cout << '0';
		//	}
		//}
		
		return out;
	}

	void test_bitset()
	{
		BitSet<10> bits;
		bits.set(1);
		bits.set(9);
		cout << bits.count() << endl;
		bits.reset(1);
		cout << bits.count() << endl;

		cout << bits << endl;
		
		/*cout << bits.none() << endl;
		bits.set(4);
		cout << bits.none() << endl;
		cout << bits.any() << endl;
		cout << bits.all() << endl;*/


		/*bits.set(4);
		cout << bits.test(4) << endl;
		bits.flip(4);
		cout << bits.test(4) << endl;
		bits.flip(4);
		cout << bits.test(4) << endl;*/

		/*bits<0xffffffff>bits;
		cout << endl;*/
	}
	/*1. 给定100亿个整数，设计算法找到只出现一次的整数？
	100亿个整数不代表要开一百亿位大小的空间，有些可能重复了几次，所以开int大小的即可。
	整两个位图 00 01 10 11 第一个位图代表第一位 第二个位图表示第二位  初始状态都是00 来了一个数后将其置为01  再来就置为10  再去遍历
	*/

	template<size_t N>
	class FindOnceVal
	{
	public:
		void set(size_t x)
		{
			bool flag1 = _bs1.test(x);
			bool flag2 = _bs2.test(x);
			if (flag1 == false && flag2 == false)//00->01
			{
				_bs2.set(x);
			}
			else if (flag1 == false && flag2 == true)//01->10
			{
				_bs1.set(x);
				_bs2.reset(x);
			}
			//10->11...不用再处理了
		}
		bool check(size_t x)
		{
			if (!_bs1.test(x) && _bs2.test(x))//01
			{
				return true;
			}
			return false;
		}
		void print()
		{
			for (size_t i = 0; i < N; i++)
			{
				if (check(i))
				{
					printf("%d\n",i);
				}
			}
		}
	private:
		BitSet<N>_bs1;
		BitSet<N>_bs2;
	};
	void TestFindOnceVal()
	{
		int a[] = { 1, 20, 30, 43, 5, 4, 1, 43, 43, 7, 9, 7, 7, 0 };
		FindOnceVal<100> fov;
		for (auto e : a)
		{
			fov.set(e);
		}
		fov.print();
	}

	/*位图应用变形：1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数   在第一题的基础上稍作改动即可*/

	/*给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？
	两个位图，分别去映射两个文件，再去遍历即可
	*/

	/*给一个超过100G大小的log file, log中存着IP地址, 设计算法找到出现次数最多的IP地址？ 与上题条件相同，
如何找到top K的IP？*/
	/*哈希切割  运用哈希算法将IP分类（切割），比如把IP转成字符串，再映射成整形，这就是一种哈希算法 100G给分成100个文件，即100个小类，
	每一个文件去计数，比如就用map<string,int> 然后记录下最大的，再将map清空  
	第二个文件出来的最大次数再与第一个得到的最大次数进行比较
	如果要topK 建一个小堆即可  如果出现一个文件还是过大，那换一种哈希算法在进行切割
	*/
	
}
