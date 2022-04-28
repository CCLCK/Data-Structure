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
			//插在左边
			cur_parent->_left = cur;
			cur->_parent = cur_parent;//三叉链还得注意父亲
		}
		else
		{
			//擦在右间
			cur_parent->_right =cur;
			cur->_parent = cur_parent;
		}

		//处理平衡因子
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
				//继续往上调整
				cur = cur_parent;
				cur_parent = cur->_parent;
			}
			else if (cur_parent->_bf == 2 || cur_parent->_bf == -2)
			{
				//为+-2就是不平衡
				if (cur_parent->_bf == -2 && cur->_bf == -1)
				{
					//右旋
					RotateR(cur_parent);
				}
				else if (cur_parent->_bf == 2 && cur->_bf == 1)
				{
					//左旋
					RotateL(cur_parent);
				}
				else if (cur_parent->_bf == -2 && cur->_bf == 1)
				{
					//左右双旋
					RotateLR(cur_parent);
				}
				else if (cur_parent->_bf == 2 && cur->_bf == -1)
				{
					//右左双旋
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
		Node* subLR = parent->_right;
		//subLR可能为空
		//subL可能为根节点
		//subL上面还有结点
		//更新平衡因子
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
			//十分重要的一点 别忘了更新父亲
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
		RotateL(parent);
		RotateR(parent);
	}
	void RotateRL(Node* parent)
	{
		RotateR(parent);
		RotateL(parent);
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
	
private:
	Node* _root;
};

void TestAVLTree()
{
	AVLTree<int, int> t1;
	t1.Insert(make_pair(1, 1));
	t1.Insert(make_pair(2, 2));
	t1.Insert(make_pair(3, 3));
	t1.Insert(make_pair(4, 4));
	t1.Insert(make_pair(5, 5));
	t1.Insert(make_pair(6, 6));
	t1.InOrder();
}







