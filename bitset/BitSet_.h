#pragma once
#include <vector>
#include <iostream>
using namespace std;

namespace ck
{
	
	
	
	template<size_t N>//N����
	class BitSet
	{
		
		friend class reference;
	public:
		BitSet()
		{
			_bits.resize(N / 8 + 1);//����ô����ֽ�
		}
		void set(size_t x)//��xλ��Ϊ1
		{
			size_t integer = x / 8;//�ڼ����ֽ�
			size_t rem = x % 8;//�ֽڵĵڼ���λ��
			_bits[integer] |= (1 << rem);
			_cnt++;
		}
		void reset(size_t x)//��xλ��Ϊ0
		{
			size_t integer = x / 8;//�ڼ����ֽ�
			size_t rem = x % 8;//�ֽڵĵڼ���λ��
			_bits[integer] &= (~(1 << rem));
		}
		bool test(size_t x)
		{
			size_t integer = x / 8;//�ڼ����ֽ�
			size_t rem = x % 8;//�ֽڵĵڼ���λ��
			return ((_bits[integer] >> rem) & 1) ? true : false;
		}
		void flip(size_t x)//��ת
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
		size_t _cnt = 0;//������Ϊ1�ĸ���
	};
	template<size_t N>//ģ���������ȡ��ΪN
	ostream& operator<<(ostream& out, const BitSet<N>& bs)
	{
		//�Ӻ���ǰ�ǵ�λ����λ����������������
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

		//��ǰ�����ǵ�λ����λ���˿��������ʣ�
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
	/*1. ����100�ڸ�����������㷨�ҵ�ֻ����һ�ε�������
	100�ڸ�����������Ҫ��һ����λ��С�Ŀռ䣬��Щ�����ظ��˼��Σ����Կ�int��С�ļ��ɡ�
	������λͼ 00 01 10 11 ��һ��λͼ�����һλ �ڶ���λͼ��ʾ�ڶ�λ  ��ʼ״̬����00 ����һ����������Ϊ01  ��������Ϊ10  ��ȥ����
	*/

	template<size_t N>
	class FindOnceVal
	{

	};
}





















