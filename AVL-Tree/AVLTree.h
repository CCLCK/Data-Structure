#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

template<class K, class V>

struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V>_kv;
	int _bf;

	AVLTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* cur = _root;
		Node* cur_parent = nullptr;
		while (cur)
		{
			if (kv.first < (cur->_kv).first)
			{
				cur_parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > (cur->_kv).first)
			{
				cur_parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		if (kv.first < (cur_parent->_kv).first)
		{
			//�������
			cur_parent->_left = cur;
			cur->_parent = cur_parent;//����������ע�⸸��
		}
		else
		{
			//�����Ҽ�
			cur_parent->_right =cur;
			cur->_parent = cur_parent;
		}

		//����ƽ������
		while (cur_parent)
		{
			if (cur_parent->_left==cur)
			{
				(cur_parent->_bf)--;
			}
			else
			{
				(cur_parent->_bf)++;
			}
			if (cur_parent->_bf == 0)
			{
				break;
			}
			else if (cur_parent->_bf == 1 || cur_parent->_bf == -1)
			{
				//�������ϵ���
				cur = cur_parent;
				cur_parent = cur->_parent;
			}
			else if (cur_parent->_bf == 2 || cur_parent->_bf == -2)
			{
				//Ϊ+-2���ǲ�ƽ��
				if (cur_parent->_bf == -2 && cur->_bf == -1)
				{
					//����
					RotateR(cur_parent);
				}
				else if (cur_parent->_bf == 2 && cur->_bf == 1)
				{
					//����
					RotateL(cur_parent);
				}
				else if (cur_parent->_bf == -2 && cur->_bf == 1)
				{
					//����˫��
					RotateLR(cur_parent);

				}
				else if (cur_parent->_bf == 2 && cur->_bf == -1)
				{
					//����˫��
					RotateRL(cur_parent);
				}
				else
				{
					assert(false);
				}
				break;
			}
			
		}
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//subLR����Ϊ��
		//subL����Ϊ���ڵ�
		//subL���滹�н��
		//����ƽ������
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (parent == _root)
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
			//ʮ����Ҫ��һ�� �����˸��¸���
			subL->_parent = ppNode;
		}
		subL->_bf = parent->_bf = 0;
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
		subR->_bf = parent->_bf = 0;
	}
	void RotateLR(Node* parent)
	{
		//���������������
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;	
		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1)
		{
			parent->_bf = 1;
			subLR->_bf = subL->_bf = 0;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			subLR->_bf = parent->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}
	void RotateRL(Node* parent)
	{
		//���������������
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = subRL->_bf = 0;
		}
		else if (bf == 0)//�������ڵ�ʱ���������
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
		else
		{
			assert(false);
		}
		
	}
	void InOrder()
	{
		_Inorder(_root);
		cout << endl;
	}
	void _Inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Inorder(root->_left);
		cout << (root->_kv).first << " ";
		_Inorder(root->_right);
	}
	int Height(Node* root)
	{
		return _Height(root);
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int LHeight = _Height(root->_left) ;
		int RHeight = _Height(root->_right) ;
		return ((LHeight > RHeight) ? LHeight+1 : RHeight+1) ;
	}

	
	bool IsBalance()
	{
		
		return _IsBalance(_root);
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int LHeight = Height(root->_left);
		int RHeight = Height(root->_right);
		if (root->_bf != (RHeight - LHeight))
		{
			cout << "ƽ������ʧ��" << endl;
			return false;
		}
		return abs(LHeight - RHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
		
	}
private:
	Node* _root;
};

void TestAVLTree()
{
	AVLTree<int, int> t1;
	t1.Insert(make_pair(4, 1));
	t1.Insert(make_pair(2, 2));
	t1.Insert(make_pair(6, 3));
	t1.Insert(make_pair(1, 4));
	t1.Insert(make_pair(3, 5));
	t1.Insert(make_pair(5, 6));
	t1.Insert(make_pair(15, 7));
	t1.Insert(make_pair(7, 8));
	t1.Insert(make_pair(16, 9));
	t1.Insert(make_pair(14, 10));
	t1.InOrder();

	cout << t1.IsBalance() << endl;
}







