#pragma once


#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
using namespace std;

enum Color
{
	RED,
	BLACK
};
template<class K,class V>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;

	pair<K, V>_kv;
	int _col;

	RBTreeNode(const pair<K,V>&kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{}
	~RBTreeNode()
	{
		_left = nullptr;
		_right = nullptr;
		_parent = nullptr;
		_col = BLACK;
	}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(nullptr)
	{}

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kv.first < (cur->_kv).first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > (cur->_kv).first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else//������ֵͬ
			{
				return false;
			}
		}
		cur = new Node(kv);
		if ((cur->_kv).first < (parent->_kv).first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//��ʼ����������
		while (parent && parent->_col == RED)
		{
			_root->_col = BLACK;
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)//���������� Ϊ���ж���ֱ�߻�������  һ�������ֿ���
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)//uncle������Ϊ��
				{
					grandfather->_col = RED;
					parent->_col = uncle->_col = BLACK;
					cur = grandfather;
					parent = cur->_parent;
				}
				else //uncle�����ڻ���uncleΪ��
				{
					if (parent->_left == cur)//ֱ��
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//����
					{
						RotateL(parent);
						RotateR(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break;
				}
			}
			else//�������Һ���
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;//����
				}
				else//uncle�����ڻ�uncleΪ��
				{
					if (parent->_right == cur)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//����
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		subL->_right = parent;//subL������Ϊ�� ��תʱƽ�����ӿ϶�Ϊ2��-2 ���ýڵ�����һ��һ������
		parent->_parent = subL;
		if(parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
		
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << (root->_kv).first << " ";
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool CheckRED(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}

		//���Ӳ�һ�����ڣ����Լ���ɫ���ĸ����Ƿ�Ϊ��
		if (root->_col == RED)
		{
			if ((root->_parent)->_col == RED)
			{
				cout << "�����ĺ�ɫ���" << endl;
				return false;
			} 
			//���ﲻ��ֱ��return  true ��Ϊ��Ҫ���������������Ƿ���������ĺ���
		}

		return CheckRED(root->_left)
			&& CheckRED(root->_right);

	}

	bool CheckBlackNums(Node* root,int blackNums,int benchmark)
	{
		if (root == nullptr)
		{
			if (blackNums == benchmark)
			{
				return true;
			}
			else
			{
				cout << "ÿ��·���Ϻ�ɫ�ڵ㲻һ��" << endl;
				return false;
			}
			
		}
		if (root->_col == BLACK)
		{
			blackNums++;
		}
		return CheckBlackNums(root->_left,blackNums,benchmark) && CheckBlackNums(root->_right, blackNums, benchmark);

	}

	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			cout << "���ڵ�Ϊ��ɫ" << endl;
			return false;
		}
		int benchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				benchmark++;
			}
			cur = cur->_left;
		}
		int blacknum = 0;
		return CheckRED(_root)
			&& CheckBlackNums(_root, blacknum, benchmark);
	}

	bool Erase(const pair<K,V>&kv)
	{
		Node* cur = _root;
		while (cur)
		{
			if ( (cur->_kv).first>kv.first )
			{
				cur = cur->_left;
			}
			else if ((cur->_kv).first < kv.first)
			{
				cur = cur->_right;
			}
			else//�ҵ���
			{
				break;
			}
		}
		if (cur==nullptr)
		{
			return false;
		}
		if (cur == _root&&cur->_right==nullptr&&cur->_left!=nullptr)//ֱ��ɾ���� ��������Ϊ��
		{
			_root = cur->_left;
			_root->_col = BLACK;
			delete cur;
			cur = nullptr;
			return true;
		}
		if (cur == _root && cur->_right != nullptr && cur->_left == nullptr)//ֱ��ɾ���� ��������Ϊ��
		{
			_root = cur->_right;
			_root->_col = BLACK;
			delete cur;
			cur = nullptr;
			return true;
		}

		Node* realDel = nullptr;
		Node* parent = cur->_parent;

		if (cur->_right == nullptr && cur->_left == nullptr)//Ҷ��
		{
			if (cur->_col == RED)//��ɫҶ��ֱ��ɾ
			{
				if (parent->_left == cur)
				{
					parent->_left = nullptr;
				}
				else
				{
					parent->_right = nullptr;
				}
				delete cur;
				cur = nullptr;
			}
			else//��ɫҶ��
			{
				realDel = cur;//��¼����������
			}
		}
		else if (cur->_right == nullptr&&cur->_left!=nullptr)//ֻ��������
		{
			if (cur->_col == BLACK)//�Ϻ��º�ĺ�ɫ��֧
			{
				
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
					cur->_left->_parent = parent;
				}
				else
				{
					parent->_right = cur->_left;
					cur->_left->_parent = parent;

				}
				cur->_left->_col = BLACK;
				delete cur;
				cur = nullptr;
			}
			else//����Ϊ������������� ����оʹ�ӡ
			{
				cout << "������ֻ���������ĵ�֧�����������ɫ���Ǻ�ɫ" << endl;
			}
		
		}
		else if (cur->_left == nullptr&&cur->_right!=nullptr)//ֻ��������
		{
			if (cur->_col == BLACK)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
					cur->_right->_parent = parent;
				}
				else
				{
					parent->_right = cur->_right;
					cur->_right->_parent = parent;
				}
				cur->_right->_col = BLACK;
				
				delete cur;
				cur = nullptr;
			}
			else//����Ϊ�������������
			{
				cout << "������ֻ���������ĵ�֧�����������ɫ���Ǻ�ɫ" << endl;
			}
		}
		else//����������
		{
			Node* minRight = cur->_right;
			Node* minRightParent=cur ;
			while (minRight->_left)
			{
				minRightParent = minRight;
				minRight = minRight->_left;
			}
		
			cur->_kv = minRight->_kv;
			if (minRight->_col == RED&&minRight->_right==nullptr)//û�����������滻������Ǻ�ɫҶ��
			{
				if (minRightParent->_left == minRight)
				{
					minRightParent->_left = nullptr;
				}
				else
				{
					minRightParent->_right = nullptr;
				}
				delete minRight;
				minRight = nullptr;
			}
			else if (minRight->_col == BLACK && minRight->_right != nullptr)//�����������Ҳ���Ҷ��
			{
				if (minRightParent->_left == minRight)
				{
					minRightParent->_left = minRight->_right;
					minRight->_right->_parent = minRightParent;
				}
				else
				{
					minRightParent->_right = minRight->_right;
					minRight->_right->_parent = minRightParent;
				}
				minRight->_right->_col = BLACK;
				delete minRight;
				minRight = nullptr;
			}
			else if(minRight->_col==BLACK&&minRight->_right==nullptr)//��ɫҶ��
			{
				realDel = minRight;//��¼����������
			}
			else//����Ϊ�������������
			{
				cout << "�����˲�����Ҫ������" << endl;
			}
		}
		if (realDel == nullptr)
		{
			return true;
		}
		//ɾ����ɫҶ��
		/*
			1.��ɫҶ��Ϊ��ʱ 
			2.�ֵ�ֶ��ȫ��  --> ������
			3.�ֵ�Ϊ�� ֶ�Ӳ�ȫ��-->��ֱ��/����
			4.�ֵ�Ϊ�� ��ת�����2
		*/
		if (realDel == _root)
		{
			cout << "��ɾ����" << endl;
			_root = nullptr;
			return true;
		}
		//���Ǹ��ڵ� ��ɫҶ�ӿ϶��и���
		Node* del = realDel;//��¼��ɾ���Ľ��  
		while (realDel != _root && realDel->_col==BLACK)
		{
			Node* DelParent = realDel->_parent;
			Node* sibling;
			if (DelParent->_left == realDel)
			{
				sibling = DelParent->_right;
			}
			else
			{
				sibling = DelParent->_left;
			}
			if (sibling == nullptr)
			{
				sibling= new Node(make_pair(-999, 0));
				sibling->_col = BLACK;
			}
			Node* nephew_left = sibling->_left;
			Node* nephew_right = sibling->_right;
			if (nephew_left == nullptr)
			{
				nephew_left = new Node(make_pair(-999,0));
				nephew_left->_col = BLACK;
			}
			if (nephew_right == nullptr)
			{
				nephew_right= new Node(make_pair(-999,0));
				nephew_right->_col = BLACK;
			}
			if (sibling->_col == BLACK && nephew_right->_col == BLACK && nephew_left->_col == BLACK)
			{
				//�ֵ�ֶ��ȫ��
				if (DelParent->_col == RED)
				{
					//����Ϊ��
					DelParent->_col = BLACK;
					sibling->_col = RED;
					break;
				}
				else
				{
					//����Ϊ��
					sibling->_col = RED;
					realDel = realDel->_parent;
				}

			}
			else if (sibling->_col == BLACK && (!(nephew_right->_col == BLACK && nephew_left->_col == BLACK)))
			{
				//�ֵ�Ϊ�� ֶ�Ӳ�ȫ��

				if (DelParent->_right == sibling && nephew_right->_col == RED)
				{
					//ֱ��
					sibling->_col = DelParent->_col;
					DelParent->_col = BLACK;
					RotateL(DelParent);
					nephew_right->_col = BLACK;
					
				}
				else if (DelParent->_left == sibling && nephew_left->_col == RED)
				{
					//ֱ��
					sibling->_col = DelParent->_col;
					DelParent->_col = BLACK;
					RotateR(DelParent);
					nephew_left->_col = BLACK;
				}
				else if (DelParent->_left==sibling&&nephew_right->_col==RED)
				{
					//����
					RotateL(sibling);
					nephew_right->_col = BLACK;
					sibling->_col = RED;
					nephew_left = sibling;
					sibling = nephew_right;
					RotateR(DelParent);
					sibling->_col = DelParent->_col;
					DelParent->_col = BLACK;
					nephew_left->_col = BLACK;
				}
				else if (DelParent->_right==sibling&&nephew_left->_col==RED)
				{
					//����
					RotateR(sibling);
					nephew_left->_col = BLACK;
					sibling->_col = RED;
					nephew_right = sibling;
					sibling = nephew_left;
					RotateL(DelParent);
					sibling->_col = DelParent->_col;
					DelParent->_col = BLACK;
					nephew_right->_col = BLACK;
				}
				else
				{
					assert(false);
				}
				break;
			}
			else if (sibling->_col == RED)
			{
				//�ֵ�Ϊ��
				if (DelParent->_left == sibling && sibling->_col == RED)
				{
					RotateR(DelParent);
					sibling->_col = BLACK;
					DelParent->_col = RED;
				}
				else if (DelParent->_right == sibling && sibling->_col == RED)
				{
					RotateL(DelParent);
					sibling->_col = BLACK;
					DelParent->_col = RED;
				}
			}
			else
			{
				assert(false);
			}
		}
		Node* delParent = del->_parent;
		
		if (delParent->_left == del)//������Ķ���Ҷ��
		{
			delParent->_left = del->_right;
		
			/*if (del->_right)
			{
				cout << "del->_right�ǿ�" << endl;
				del->_right->_parent = delParent;
			}*/
			delete del;
			del = nullptr;
		}
		else
		{
			delParent->_right = del->_right;
		
		/*	if (del->_right)
			{
				cout << "del->_right�ǿ�" << endl;
				del->_right->_parent = delParent;
			}*/

			delete del;
			del = nullptr;
		}
		return true;
	}
	
private:
	Node* _root;
};


void test1()//�������
{
	RBTree<int,int> rb;
	//rb.Insert(make_pair(4, 1));
	//rb.Insert(make_pair(2, 2));
	//rb.Insert(make_pair(6, 3));
	//rb.Insert(make_pair(1, 4));
	//rb.Insert(make_pair(3, 5));
	//rb.Insert(make_pair(5, 6));
	//rb.Insert(make_pair(15, 7));
	//rb.Insert(make_pair(7, 8));
	//rb.Insert(make_pair(16, 9));
	//rb.Insert(make_pair(14, 10));
	rb.Insert(make_pair(27, 1));
	rb.Insert(make_pair(4, 1));
	rb.Insert(make_pair(12, 1));
	rb.Insert(make_pair(66, 1));
	rb.Insert(make_pair(95, 1));
	rb.Insert(make_pair(82, 1));
	rb.Insert(make_pair(56, 1));
	rb.Insert(make_pair(59, 1));
	rb.Insert(make_pair(73, 1));
	rb.Insert(make_pair(19, 1));

	rb.InOrder();
	cout << rb.IsBalance() << endl;
}

void test2()//���������������
{
	RBTree<int, int> rb;
	const int n = 1000000;
	vector<int>v;
	v.reserve(n);
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		v.push_back(rand());
	}
	for (auto e : v)
	{
		
		rb.Insert(make_pair(e, e));
	}
	cout << rb.IsBalance() << endl;
}


void test3()//����ɾ������
{
	RBTree<int, int> rb;
	rb.Insert(make_pair(27, 1));
	rb.Insert(make_pair(4, 1));
	rb.Insert(make_pair(12, 1));
	rb.Insert(make_pair(66, 1));
	rb.Insert(make_pair(95, 1));
	rb.Insert(make_pair(82, 1));
	rb.Insert(make_pair(56, 1));
	rb.Insert(make_pair(59, 1));
	rb.Insert(make_pair(73, 1));
	rb.Insert(make_pair(19, 1));
	
	rb.Erase(make_pair(19, 1));
	rb.Erase(make_pair(27, 1));
	rb.Erase(make_pair(4, 1));
	rb.Erase(make_pair(59, 1));
	rb.Erase(make_pair(82, 1));

	cout << rb.IsBalance() << endl;

}



void test4()//���ɾ������
{
	RBTree<int, int> rb;
	const int n =10000;
	vector<int>v;
	v.reserve(n);
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		v.push_back(rand());
	}
	for (auto e : v)
	{
		//cout << e << " " << endl;
		rb.Insert(make_pair(e, e));
	}
	for (auto e : v)
	{
		
		rb.Erase(make_pair(e, e));
		if (rb.IsBalance() == 0)
		{
			cout << "����ɾ�����ɹ�" << endl;
		}
	}
	cout << "ɾ���ɹ�" << endl;
	
}

void test5()//�����������
{
	RBTree<int, int> rb;
	rb.Insert(make_pair(24, 1));
	rb.Insert(make_pair(70, 1));
	rb.Insert(make_pair(42, 1));
	rb.Insert(make_pair(50, 1));
	rb.Insert(make_pair(89, 1));
	rb.Insert(make_pair(52, 1));
	rb.Insert(make_pair(48, 1));
	rb.Insert(make_pair(5, 1));
	rb.Insert(make_pair(24, 1));
	rb.Insert(make_pair(3, 1));

	rb.Erase(make_pair(24, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(70, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(42, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(50, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(89, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(52, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(48, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(5, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(24, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(3, 1));
	cout << rb.IsBalance() << endl;
}

void test6()//�����������
{
	RBTree<int, int> rb;
	rb.Insert(make_pair(12, 1));
	rb.Insert(make_pair(88, 1));
	rb.Insert(make_pair(11, 1));
	rb.Insert(make_pair(29, 1));
	rb.Insert(make_pair(41, 1));
	rb.Insert(make_pair(73, 1));
	rb.Insert(make_pair(96, 1));
	rb.Insert(make_pair(49, 1));
	rb.Insert(make_pair(26, 1));
	rb.Insert(make_pair(18, 1));

	rb.Erase(make_pair(12, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(88, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(11, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(29, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(41, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(73, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(96, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(49, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(26, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(18, 1));
	cout << rb.IsBalance() << endl;
}


void test7()//�����������
{
	RBTree<int, int> rb;
	rb.Insert(make_pair(34, 1));
	rb.Insert(make_pair(81, 1));
	rb.Insert(make_pair(91, 1));
	rb.Insert(make_pair(52, 1));
	rb.Insert(make_pair(78, 1));
	rb.Insert(make_pair(20, 1));
	rb.Insert(make_pair(61, 1));
	rb.Insert(make_pair(1, 1));
	rb.Insert(make_pair(10, 1));
	rb.Insert(make_pair(12, 1));

	rb.Erase(make_pair(34, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(81, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(91, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(52, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(78, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(20, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(61, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(1, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(10, 1));
	cout << rb.IsBalance() << endl;
	rb.Erase(make_pair(12, 1));
	cout << rb.IsBalance() << endl;
	
}
