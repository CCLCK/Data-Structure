#pragma once

#include <iostream>
#include <algorithm>
using namespace std;

template<class K=int>
struct BSTreeNode
{
	BSTreeNode(const K&key=K())//����Ĭ�ϵ�
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
		if (key < root->val)//keyС�ڵ�ǰ�ڵ��ֵ,ȥ�����
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
	bool Insert(const K& key)//�ҵ�λ��Ȼ�����
	{
		return _Insert(_root, key);
	}
	//bool Insert(const K&key)//�ҵ�λ��Ȼ����� �ǵݹ�д��
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
	//		if (key < cur->val)//��������ȵ�ǰ��С ����������
	//		{
	//			parent = cur;
	//			cur = parent->left;
	//		}
	//		else if (key > cur->val)//��������ȵ�ǰ���� ����������
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
	//	if (key < parent->val)//��ǰֵС�ڸ��׵�ֵ ���ڸ��׵����
	//	{
	//		parent->left =newnode;
	//	}
	//	else//��ǰֵ���ڸ��׵�ֵ ���ڸ��׵��ұ�
	//	{
	//		parent->right = newnode;
	//	}
	//	return true;
	//}

	bool Erase(const K& key)
	{
		//���ҵ���ɾ
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
			else//�ҵ���
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
					if (key < parent->val)//�ڸ��׵���ߣ��Ǹ��׵�����
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
				else//������������Ϊ��
					//�����������������С�ģ�����������ߵ�Ҷ�ӣ�ȥ������������������ģ����������ұߵ�Ҷ�ӣ�ȥ���
					//����ѡ��������������ߵ�ȥ���Ҫɾ���Ľ�㣬ȥ������˵Ľ��û����������תΪ��һ��ȥ��
				{
					//�ҵ�����������ߵĽ��
					Node* minRight = cur->right;
					Node* minRightParent = cur;
					while (minRight->left != nullptr)
					{
						minRightParent = minRight;
						minRight = minRightParent->left;
					}
					cur->val = minRight->val;
					//ȥɾ��minRight
					minRightParent->left = minRight->right;//minRight������Ϊ��
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
		cout << "����1" << endl;
	}
	else
	{
		cout << "������1" << endl;
	}
	if (bst.find(5) != nullptr)
	{
		cout << "����5" << endl;
	}
	else
	{
		cout << "������5" << endl;
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
