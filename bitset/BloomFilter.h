#pragma once


#include "BitSet_.h"

namespace ck
{
	struct HashFunc1
	{
		//BKDR Hash
		size_t operator()(const string& str)
		{
			size_t seed = 131; // 31 131 1313 13131 131313 etc..
			size_t hash = 0;
			for (size_t i = 0; i < str.length(); i++)
			{
				hash = (hash * seed) + str[i];
			}
			return hash;
		}
	};
	struct HashFunc2
	{
		//FNV Hash
		size_t operator()(const string& str)
		{
			size_t fnv_prime = 0x811C9DC5;
			size_t hash = 0;
			for (std::size_t i = 0; i < str.length(); i++)
			{
				hash *= fnv_prime;
				hash ^= str[i];
			}

			return hash;
		}
	};
	struct HashFunc3
	{
		//APH Hash
		size_t operator()(const string& str)
		{
			unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
			unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
			unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
			unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
			unsigned int hash = 0;
			unsigned int test = 0;

			for (std::size_t i = 0; i < str.length(); i++)
			{
				hash = (hash << OneEighth) + str[i];

				if ((test = hash & HighBits) != 0)
				{
					hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
				}
			}

			return hash;
		}
	};
	template<size_t N, class K=string ,class Hash1 = HashFunc1, class Hash2 = HashFunc2, class Hash3 = HashFunc3>
	class BloomFilter
	{
	public:
		void set(const K& key)
		{
			
			size_t x1 = Hash1()(key)%len;
			size_t x2 = Hash2()(key) % len;
			size_t x3 = Hash3()(key) % len;
			_bs.set(x1);
			_bs.set(x2);
			_bs.set(x3);
		}
		bool test(const K& key)
		{
			//����һ����������е�ֵ
			size_t x1 = Hash1()(key) % len;
			if (!_bs.test(x1))
			{
				return false;
			}
			size_t x2 = Hash2()(key) % len;
			if (!_bs.test(x2))
			{
				return false;
			}
			size_t x3 = Hash2()(key) % len;
			if (!_bs.test(x3))
			{
				return false;
			}
			return true;//����λ��ȫ�����ڲ���˵������
		}
	private:
		BitSet<6*N>_bs;
		size_t len = 6 * N;//λͼ�Ĵ�С���Ծ�����������Ч�ʣ�Խ���ϣ��ͻ����ԽС�����и���Խ�ͣ�
	};
	void TestBloomFilter()
	{
		/*BloomFilter<100> bf;
		bf.Set("����");
		bf.Set("����");
		bf.Set("ţħ��");
		bf.Set("�캢��");

		cout << bf.Test("����") << endl;
		cout << bf.Test("����") << endl;
		cout << bf.Test("ţħ��") << endl;
		cout << bf.Test("�캢��") << endl;
		cout << bf.Test("�����") << endl;
		cout << bf.Test("������") << endl;
		cout << bf.Test("��˽�") << endl;*/
		BloomFilter<100> bf;
		size_t N = 100;
		std::vector<std::string> v1;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
			url += std::to_string(1234 + i);
			v1.push_back(url);
		}

		for (auto& str : v1)
		{
			bf.set(str);
		}

		for (auto& str : v1)
		{
			cout << bf.test(str) << endl;
		}
		cout << endl << endl;

		std::vector<std::string> v2;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
			url += std::to_string(6789 + i);
			v2.push_back(url);
		}

		size_t n2 = 0;
		for (auto& str : v2)
		{
			if (bf.test(str))
			{
				++n2;
			}
		}
		cout << "�����ַ���������:" << (double)n2 / (double)N << endl;

		std::vector<std::string> v3;
		for (size_t i = 0; i < N; ++i)
		{
			//std::string url = "https://www.baidu.com/s?wd=ln2&rsv_spt=1&rsv_iqid=0xc1c7784f000040b1&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_dl=tb&rsv_enter=1&rsv_sug3=8&rsv_sug1=7&rsv_sug7=100&rsv_sug2=0&rsv_btype=i&prefixsug=ln2&rsp=5&inputT=4576&rsv_sug4=5211";
			//std::string url = "https://zhidao.baidu.com/question/1945717405689377028.html?fr=iks&word=ln2&ie=gbk&dyTabStr=MCw0LDMsMiw2LDEsNSw3LDgsOQ==";
			std::string url = "https://www.cnblogs.com/-clq/archive/2012/01/31/2333247.html";


			url += std::to_string(6789 + i);
			v3.push_back(url);
		}

		size_t n3 = 0;
		for (auto& str : v3)
		{
			if (bf.test(str))
			{
				++n3;
			}
		}
		cout << "�������ַ���������:" << (double)n3 / (double)N << endl;

	}
}

