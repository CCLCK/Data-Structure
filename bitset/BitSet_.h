#pragma once
#include <vector>
#include <iostream>
using namespace std;

namespace ck
{
	
	
	
	template<size_t N>//N个数
	class BitSet
	{
		
		friend class reference;
	public:
		BitSet()
		{
			_bits.resize(N / 8 + 1);//开这么多个字节
		}
		void set(size_t x)//第x位置为1
		{
			size_t integer = x / 8;//第几个字节
			size_t rem = x % 8;//字节的第几个位置
			_bits[integer] |= (1 << rem);
			_cnt++;
		}
		void reset(size_t x)//第x位置为0
		{
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
		template<size_t N>
		friend ostream& operator<<(ostream& out, const BitSet<N>& bs);
	
	private:

		vector<char>_bits;
		size_t _cnt = 0;//被设置为1的个数
	};
	template<size_t N>//模板参数不能取名为N
	ostream& operator<<(ostream& out, const BitSet<N>& bs)
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

	};
}





















