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
		Node* subLR = subL->_right;
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
		//针对左子树的折线
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
		//针对右子树的折线
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
		else if (bf == 0)//有三个节点时的特殊情况
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
			cout << "平衡因子失常" << endl;
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







