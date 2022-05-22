#pragma once


#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

template<class K>
struct HashFunc
{
	const K& operator()(const K& key) 
	{
		return key;
	}
};
template<>
struct HashFunc <string>
{
	size_t operator()(const string& key)
	{
		size_t value = 0;
		for (auto e : key)
		{
			value = value * 13 + (size_t)e;//*131是BKDR发明的字符串哈希算法，*131等数效率更高
		}
		return value;
	}
};
namespace close_hash
{
	
	enum Status//定义一下结点的状态，方便查找
	{
		EMPTY,
		EXIST,
		DELETE
	};
	
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		Status _status = EMPTY;
	};

	//特别处理string
	
	template<class K,class V,class Hash=HashFunc<K>>
	class HashTable
	{
	public:
		HashData<K, V>* Find(const K& key)
		{
			if (_tables.size() == 0)
			{
				return nullptr;
			}
		
			Hash hash;
			size_t start = hash(key) % _tables.size();
			size_t i = 0;
			size_t index = start + i;
			while (_tables[index]._status != EMPTY)
			{
				if (_tables[index]._kv.first == key
					&& _tables[index]._status == EXIST)
				{
					return &_tables[index];
				}
				else
				{
					++i;
					//index = start + i; // 线性探测
					index = start + i * i; // 二次探测
					index %= _tables.size();
				}
			}
		
			return nullptr;
		}
		bool Insert(const pair<K, V>& kv)
		{
			Hash hash;
			if (Find(kv.first))//原来的表中存在
			{
				return false;
			}
			if (_tables.size()==0||_n*10/_tables.size()>=7)
				//负载因子在0.7的时候扩容 不然可能导致死循环
			{
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				
				HashTable<K, V, Hash>NewHT;//搞一个vector出来行吗？可以，但是hashtable更方便
				NewHT._tables.resize(newsize);
				for (auto& e : _tables)//这种传引用 不传引用得多拷贝一次
				{
					NewHT.Insert(e._kv);
				}
				_tables.swap(NewHT._tables);//交换之后NewHT就被销毁了
			}
			size_t start = hash(kv.first) % _tables.size();
			size_t i = 0;
			size_t index = start + i;
			//进行线性探测或二次探测
			while (_tables[index]._status==EXIST)//不等于空就一直往后走
			{
				//index++;//由于负载因子在0.7时扩容了所以不会死循环.
				i++;
				//index = start + i 线性探测
				index = start+i*i;
				index %= _tables.size();
			}
			//找到位置了
			
			_tables[index]._status = EXIST;
			_tables[index]._kv = kv;
			_n++;
			return true;
		}
		bool Erase(const K& key)
		{
			
			/*	Hash hs;
				size_t index = hs(key) % _tables.size();
				while (_tables[index]._status==EXIST)
				{
					if (_tables[index]._kv.first == key)
					{
						_tables[index]._status = DELETE;
						return true;
					}
					index++;
					index %= _tables.size();
				}
				return false;*/
			HashData<K, V>* ret = Find(key);
			if (ret == nullptr)
			{
				return false;
			}
			else
			{
				ret->_status = DELETE;
				return true;
			}
		}
		
	private:
		vector<HashData<K,V>>_tables;
		size_t _n = 0;
	};
	void test1()
	{
		//int a[] = { 5, 3, 100, 9999, 333, 14, 26, 34, 5};
		int a[] = { 5, 7, 28, 35, 48,1,2,3,4,5,6 };
		HashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Erase(3);
		cout << ht.Find(3) << endl;
	}
	void test2()
	{
		HashTable<string, string, HashFunc<string>>ht;
		ht.Insert(make_pair("sort", "排序"));
		ht.Insert(make_pair("entity", "实体"));
		ht.Insert(make_pair("object", "对象"));
		ht.Insert(make_pair("buffer", "缓冲"));
		ht.Erase("sort");
		cout << ht.Find("sort") << endl;

	}

}

//namespace open_hash
namespace HashBucket
{
	template<class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode* _next;
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
	};
	template<class K,class V,class Hash=HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K,V> Node;
	public:

		Node* Find(const K& key)//Find函数返回值一般都是指针，通过指针访问这个自定义类型的成员
		{
			Hash hash;
			if (_tables.size() == 0)//表的大小为0，防止取余0
			{
				return nullptr;
			}
			size_t index = hash(key) % _tables.size();//找到桶号
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}


		size_t GetNextPrime(size_t prime)
		{
			const int PRIMECOUNT = 28;
			static const size_t primeList[PRIMECOUNT] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			//ul表示unsigned long
			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}

			return primeList[i];
		}

		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))//有相同的key直接返回false
			{
				return false;
			}
			//if(_n==0||_n==_tables.size())
			Hash hash;
			if (_n == _tables.size())//最开始_n为0，而_tables.size()也为0所以可以简化为一行代码
			{
				//增容
				//size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				size_t newSize = GetNextPrime(_tables.size());
				vector<Node*>newTables;
				newTables.resize(newSize, nullptr);
				for (int i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;//记录下一个位置
						size_t index = hash(cur->_kv.first) % newTables.size();
						cur->_next = newTables[index];//cur当头
						newTables[index] = cur;//更新vector里的头
						cur = next;
					}
				}
				_tables.swap(newTables);//把新表的数据放入旧表中
			}

			size_t index = hash(kv.first) % _tables.size();//算出桶号
			//头插
			Node* newNode = new Node(kv);
			newNode->_next = _tables[index];
			_tables[index]=newNode;
			++_n;//别忘记更新有效数据的个数
			return true;
		}
		bool Erase(const K& key)
		{ 
			//if (!Find(key))//找不到这个元素 
			// 这么写也可以，但是后面删除的过程中会顺带遍历整个桶
			//{
			//	return false;
			//}
			if (_tables.size() == 0)//哈希表为空
			{
				return false;
			}
			Hash hash;
			size_t index = hash(key) % _tables.size();
			Node* cur = _tables[index];
			Node* prev = nullptr;//记录前一个位置
			while (cur)
			{
				if (cur->_kv.first == key)//找到这个元素了
				{
					if(cur==_tables[index])//元素是头结点
					{
						_tables[index] = cur->_next;
						
					}
					else//不是头结点
					{
						prev->_next = cur->_next;
					}
					delete cur;
					cur = nullptr;
					_n--;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
		~HashTable()//哈希桶采用的链表结构 需要释放每个链表
		{
			for (int i=0;i<_tables.size();i++)
			{
				Node* cur = _tables[i];
				if (cur == nullptr)
				{
					continue;
				}
				else
				{
					cur = cur->_next;
				}
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
			_n = 0;
		}
		HashTable() {};

	private:
		vector<Node*>_tables;//存的是链表首元素的指针
		size_t _n=0;//有效数据
	};
	void TestHashTable1()
	{
		HashTable<int, int> ht;
		int a[] = { 4, 44, 14, 5, 2, 22, 12, 5, 8, 10, 15 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(11, 11));

		ht.Erase(22);
		ht.Erase(2);
		ht.Erase(100);
		HashTable<int, int> ht2(ht);

	}
}

