#define _CRT_SECURE_NO_WARNINGS 1


#include "Hash.h"


//#define N 100000000
//void test()
//{
//	srand(time(0));
//	vector<int>v;
//	v.reserve(N);
//	for (int i = 0; i < N; i++)
//	{
//		v.push_back(rand());
//	}
//
//	set<int>s;
//	unordered_set<int>us;
////------------------------------------------
//	//set insert time
//	clock_t begin1 = clock();
//	for (int i = 0; i < N; i++)
//	{
//		s.insert(v[i]);
//	}
//	clock_t end1 = clock();
//
//	//unorde_set insert time
//	clock_t begin2 = clock();
//	for (int i = 0; i < N; i++)
//	{
//		us.insert(v[i]);
//	}
//	clock_t end2 = clock();
//	cout << "set insert: " << end1 - begin1 << endl;
//	cout << "unordered_set insert: " << end2 - begin2 << endl << endl;
////------------------------------------------
//	//set find time
//	clock_t begin3 = clock();
//	for (auto e : v)
//	{
//		s.find(e);
//	}
//	clock_t end3 = clock();
//
//	clock_t begin4 = clock();
//	for (auto e : v)
//	{
//		us.find(e);
//	}
//	clock_t end4 = clock();
//	cout << "set find: " << end3 - begin3 << endl;
//	cout << "unordered_set find: " << end4 - begin4 << endl << endl;
////------------------------------------------
//
//	//set erase time
//	clock_t begin5 = clock();
//	for (auto e : v)
//	{
//		s.erase(e);
//	}
//	clock_t end5 = clock();
//
//	//unordered_set erase time
//	clock_t begin6 = clock();
//	for (auto e : v)
//	{
//		us.erase(e);
//	}
//	clock_t end6 = clock();
//
//	cout << "set earse: " << end5- begin5 << endl;
//	cout << "unordered_set erase: " << end6 - begin6 << endl << endl;
//}

int main()
{
	//test();
	//test1();
	//close_hash::test1();
	//close_hash::test2();
	
	//unordered_set<int>us;
	//us.insert(1);
	//us.insert(2);
	//us.insert(1);
	//unordered_set<int>us2(us);

	//cout << us2.size() << endl;

	HashBucket::TestHashTable1();
	return 0;
}


