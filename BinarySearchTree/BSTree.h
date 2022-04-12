#pragma once

#include <iostream>
#include <algorithm>
using namespace std;

template<class K=int>
struct BSTreeNode
{
	BSTreeNode(const K&key=K())//给定默认的
		:left(nullptr)
		,right(nullptr)
		,val(key)
	{}
	BSTreeNode* left;
	BSTreeNode* right;
	K val;
};

template <class K>
class BSTree
{
public:
	typedef BSTreeNode<K> Node;
	BSTree()
		:_root(nullptr)
	{}

	//bool insert(const K& key);
	//bool Erase(const K& key);
	//Node* find(const K& key);
	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root);
	}
	const BSTree<K>& operator=(const BSTree<K>& t)
	{
		if (this != &t)
		{
			_root = _Copy(t._root);
		}
		return *this;
	}
	const BSTree<K>& operator=(const BSTree<K> t)
	{
		::swap(_root, t._root);
		return *this;
	}

	~BSTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
	Node* _find(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (key > root->val)
		{
			_find(root->right,key);
		}
		else if (key < root->val)
		{
			_find(root->left,key);
		}
		else
		{
			return root;
		}
	}
	Node* find(const K& key)
	{
		return _find(_root, key);
	}
	/*Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur!=nullptr)
		{
			if (key < cur->val)
			{
				cur = cur->left;
			}
			else if (key > cur->val)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}*/

	bool _Insert(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		if (key < root->val)//key小于当前节点的值,去左边找
		{
			_Insert(root->left, key);
		}
		else if (key > root->val)
		{
			_Insert(root->right, key);
		}
		else
		{
			return false;
		}
	}
	bool Insert(const K& key)//找到位置然后插入
	{
		return _Insert(_root, key);
	}
	//bool Insert(const K&key)//找到位置然后插入 非递归写法
	//{
	//	if (_root == nullptr)
	//	{
	//		_root = new Node(key);
	//		return true;
	//	}
	//	Node* parent = nullptr;
	//	Node* cur = _root;
	//	while (cur!=nullptr)
	//	{
	//		if (key < cur->val)//插入的数比当前数小 往左子树放
	//		{
	//			parent = cur;
	//			cur = parent->left;
	//		}
	//		else if (key > cur->val)//插入的数比当前数大 往右子树放
	//		{
	//			parent = cur;
	//			cur = parent->right;
	//		}
	//		else
	//		{
	//			return false;
	//		}
	//	}
	//	Node* newnode = new Node(key);
	//	if (key < parent->val)//当前值小于父亲的值 放在父亲的左边
	//	{
	//		parent->left =newnode;
	//	}
	//	else//当前值大于父亲的值 放在父亲的右边
	//	{
	//		parent->right = newnode;
	//	}
	//	return true;
	//}

	bool Erase(const K& key)
	{
		//先找到再删
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (key > cur->val)
			{
				parent = cur;
				cur = parent->right;
			}
			else if (key < cur->val)
			{
				parent = cur;
				cur = parent->left;
			}
			else//找到了
			{
				if (cur->left == nullptr)
				{
					if (key < parent->val)
					{
						parent->left = cur->right;
					}
					else
					{
						parent->right = cur->right;
					}
					delete cur;
				}
				else if (cur->right == nullptr)
				{
					if (key < parent->val)//在父亲的左边，是父亲的左孩子
					{
						parent->left = cur->left;
					}
					else
					{
						parent->right = cur->left;
					}
					delete cur;
					return true;
				}
				else//左右子树都不为空
					//替代法：用右子树最小的（右子树最左边的叶子）去替代或者用左子树最大的（左子树最右边的叶子）去替代
					//这里选择用右子树最左边的去替代要删除的结点，去替代别人的结点没有左子树，转为第一种去做
				{
					//找到右子树最左边的结点
					Node* minRight = cur->right;
					Node* minRightParent = cur;
					while (minRight->left != nullptr)
					{
						minRightParent = minRight;
						minRight = minRightParent->left;
					}
					cur->val = minRight->val;
					//去删除minRight
					minRightParent->left = minRight->right;//minRight左子树为空
					delete minRight;
					return true;
				}
			}
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	
private:	
	Node* _root;
	void _Destroy(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		_Destroy(node->left);
		_Destroy(node->right);
		delete node;
	}
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		Node* newnode = new Node(root->val);
		newnode->left = _Copy(root->left);
		newnode->right = _Copy(root->right);
		return newnode;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->left);
		cout << root->val << " ";
		_InOrder(root->right);
	}
};

void test1()
{
	BSTree<int> bst;	
	bst.Insert(1);
	bst.Insert(2);
	bst.Insert(3);
	bst.Insert(4);
	bst.InOrder();
}

void test2()
{
	BSTree<int> bst;
	bst.Insert(1);
	bst.Insert(2);
	bst.Insert(3);
	bst.Insert(4);
	if (bst.find(1) != nullptr)
	{
		cout << "存在1" << endl;
	}
	else
	{
		cout << "不存在1" << endl;
	}
	if (bst.find(5) != nullptr)
	{
		cout << "存在5" << endl;
	}
	else
	{
		cout << "不存在5" << endl;
	}
}

void test3()
{
	BSTree<int> bst;
	bst.Insert(4);
	bst.Insert(2);
	bst.Insert(1);
	bst.Insert(3);
	//bst.Erase(1);
	bst.InOrder();
}
