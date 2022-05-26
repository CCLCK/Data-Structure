#pragma once


#pragma once
#include <string>
#include "bitset.h"

namespace bit
{
	struct HashStr1
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			// BKDR
			for (size_t i = 0; i < s.size(); ++i)
			{
				hash *= 131;
				hash += s[i];
			}

			return hash;
		}
	};

	struct HashStr2
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			// SDBMHash
			for (size_t i = 0; i < s.size(); ++i)
			{
				hash *= 65599;
				hash += s[i];
			}

			return hash;
		}
	};

	struct HashStr3
	{
		size_t operator()(const string& s)
		{
			size_t hash = 0;
			// RSHash
			size_t magic = 63689;
			for (size_t i = 0; i < s.size(); ++i)
			{
				hash *= magic;
				hash += s[i];
				magic *= 378551;
			}

			return hash;
		}
	};

	// N表示最多插入N个值
	template<size_t N,
		class K = string,
		class Hash1 = HashStr1,
		class Hash2 = HashStr2,
		class Hash3 = HashStr3>
		class BloomFilter
	{
	public:
		bool Test(const K& key)
		{
			size_t index1 = Hash1()(key) % len;
			if (_bs.test(index1) == false)
			{
				return false;
			}

			size_t index2 = Hash2()(key) % len;
			if (_bs.test(index2) == false)
			{
				return false;
			}

			size_t index3 = Hash3()(key) % len;
			if (_bs.test(index3) == false)
			{
				return false;
			}

			return true; // 在是不准确的，这里可能是存在误判的
		}

		void Set(const K& key)
		{
			size_t index1 = Hash1()(key) % len;
			size_t index2 = Hash2()(key) % len;
			size_t index3 = Hash3()(key) % len;
			/*	cout<< index1<<endl;
				cout << index2 << endl;
				cout << index3 << endl<<endl;*/

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}

		// 一般情况不支持删除，why?->多个值可能会标记一个位，删除可能会影响其他key
		// 如果非要支持删除的话，标记不再使用一个比特位，可以使用多个比特位，进行计数多少个值映射的这个比特位
		// 但是这种方法是杀敌一千，自损八百的做法，因为消耗的更多的空间。
		//bool Reset(const K& key);
	private:
		bit::bitset<6 * N> _bs;
		size_t len = 6 * N;
	};

	/*void TestBloomFilter()
	{*/
	/*string s1("abcd");
	string s2("bcad");
	string s3("aadd");

	cout << HashStr1()(s1) << endl;
	cout << HashStr2()(s1) << endl; 

	cout << HashStr1()(s2) << endl;
	cout << HashStr2()(s2) << endl;
	cout << HashStr3()(s2) << endl << endl;

	cout << HashStr1()(s3) << endl;
	cout << HashStr2()(s3) << endl;
	cout << HashStr3()(s3) << endl << endl;*/
	//}

	void TestBloomFilter()
	{
		/*BloomFilter<100> bf;
		bf.Set("张三");
		bf.Set("李四");
		bf.Set("牛魔王");
		bf.Set("红孩儿");

		cout << bf.Test("张三") << endl;
		cout << bf.Test("李四") << endl;
		cout << bf.Test("牛魔王") << endl;
		cout << bf.Test("红孩儿") << endl;
		cout << bf.Test("孙悟空") << endl;
		cout << bf.Test("二郎神") << endl;
		cout << bf.Test("猪八戒") << endl;*/


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
			bf.Set(str);
		}

		for (auto& str : v1)
		{
			cout << bf.Test(str) << endl;
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
			if (bf.Test(str))
			{
				++n2;
			}
		}
		cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;

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
			if (bf.Test(str))
			{
				++n3;
			}
		}
		cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;

	}
}