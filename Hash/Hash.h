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
			value = value * 13 + (size_t)e;//*131��BKDR�������ַ�����ϣ�㷨��*131����Ч�ʸ���
		}
		return value;
	}
};
namespace close_hash
{
	
	enum Status//����һ�½���״̬���������
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

	//�ر���string
	
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
					//index = start + i; // ����̽��
					index = start + i * i; // ����̽��
					index %= _tables.size();
				}
			}
		
			return nullptr;
		}
		bool Insert(const pair<K, V>& kv)
		{
			Hash hash;
			if (Find(kv.first))//ԭ���ı��д���
			{
				return false;
			}
			if (_tables.size()==0||_n*10/_tables.size()>=7)
				//����������0.7��ʱ������ ��Ȼ���ܵ�����ѭ��
			{
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				
				HashTable<K, V, Hash>NewHT;//��һ��vector�������𣿿��ԣ�����hashtable������
				NewHT._tables.resize(newsize);
				for (auto& e : _tables)//���ִ����� �������õö࿽��һ��
				{
					NewHT.Insert(e._kv);
				}
				_tables.swap(NewHT._tables);//����֮��NewHT�ͱ�������
			}
			size_t start = hash(kv.first) % _tables.size();
			size_t i = 0;
			size_t index = start + i;
			//��������̽������̽��
			while (_tables[index]._status==EXIST)//�����ڿվ�һֱ������
			{
				//index++;//���ڸ���������0.7ʱ���������Բ�����ѭ��.
				i++;
				//index = start + i ����̽��
				index = start+i*i;
				index %= _tables.size();
			}
			//�ҵ�λ����
			
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
		ht.Insert(make_pair("sort", "����"));
		ht.Insert(make_pair("entity", "ʵ��"));
		ht.Insert(make_pair("object", "����"));
		ht.Insert(make_pair("buffer", "����"));
		ht.Erase("sort");
		cout << ht.Find("sort") << endl;

	}

}

namespace open_hash
{


}

