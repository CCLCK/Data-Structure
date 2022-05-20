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

namespace open_hash
{


}

