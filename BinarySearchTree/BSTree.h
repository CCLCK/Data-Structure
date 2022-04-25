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
	bool EraseR(const K& key)
	{
		//找到再删
		return _EraseR(_root, key);
	}
	

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
					if (cur == _root)
					{
						_root = cur->right;
					}
					else
					{
						if (key < parent->val)
						{
							parent->left = cur->right;
						}
						else
						{
							parent->right = cur->right;
						}
					}
					delete cur;
					return true;
				}
				else if (cur->right == nullptr)
				{
					if (cur == _root)
					{
						_root = _root->left;
					}
					else
					{
						if (key < parent->val)//在父亲的左边，是父亲的左孩子
						{
							parent->left = cur->left;
						}
						else
						{
							parent->right = cur->left;
						}
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

					if (minRightParent->left = minRight)
					{
						minRightParent->left = minRight->right;
					}
					else if (minRightParent->right = minRight)
					{
						minRightParent->right = minRight->right;
					}
					//minRightParent->left = minRight->right;//minRight左子树为空  不能这么写 如果只有三个节点呢？ 所以必须判断是在父亲节点的左边还是右边！
					delete minRight;
					return true;
				}
			}
		}
		return false;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	
private:	
	bool _EraseR(Node*& root, const K& key)//递归必须传引用 传引用,即传实参相当于多了个parent指针
	{
		if (root == nullptr)
		{
			return false;
		}
		if (key < root->val)
		{
			_EraseR(root->left, key);
		}
		else if (key > root->val)
		{
			_EraseR(root->right, key);
		}
		else//找到了准备去删
		{
			if (root->left == nullptr)
			{
				Node* tmp = root;
				root = root->right;
				delete tmp;
				return true;
			}
			else if (root->right == nullptr)
			{
				Node* tmp = root;
				root = root->left;
				delete tmp;
				return true;
			}
			else
			{
				Node* minRight = root->right;
				Node* minRightParent = root;
				while (minRight->left)
				{
					minRightParent = minRight;
					minRight = minRightParent->left;
				}
				root->val = minRight->val;
				if (minRightParent->left == minRight)
				{
					minRightParent->left = minRight->right;
				}
				else
				{
					minRightParent->right = minRight->right;
				}
				delete minRight;
				minRight = nullptr;
				return true;
			}
		}

	}
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
	Node* _find(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (key > root->val)
		{
			_find(root->right, key);
		}
		else if (key < root->val)
		{
			_find(root->left, key);
		}
		else
		{
			return root;
		}
	}
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
	bst.Erase(1);
	bst.Erase(2);
	bst.Erase(3);
	bst.Erase(4);
	bst.Insert(3);
	bst.InOrder();
}


void test4()
{
	BSTree<int> bst;
	bst.Insert(4);
	bst.Insert(2);
	bst.Insert(1);
	bst.Insert(3);
	bst.EraseR(1);
	bst.EraseR(2);
	bst.EraseR(3);
	bst.EraseR(4);
	bst.Insert(3);
	bst.InOrder();
}