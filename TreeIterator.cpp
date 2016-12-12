/*************************************************************************
	> File Name: TreeIterator.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月12日 星期一 19时18分33秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <iostream>
#include <cassert>
#include <cstdio>
#include <stack>
#include <queue>

using namespace std;

template<class T>
class BinaryTree
{
public:
	struct BinaryTreeNode
	{
		BinaryTreeNode *leftchild;
		BinaryTreeNode *rightchild;
		T data;
		BinaryTreeNode():leftchild(NULL), rightchild(NULL), data(T()) {}
	};
protected:
	typedef BinaryTreeNode *BPNode;
	BPNode root;
	T EndMark;
public:
	static BPNode _BuyNode()
	{
		BPNode s = new BinaryTreeNode();
		return s;
	}
	static void _FreeNode(BPNode ptr)
	{
		delete(ptr);
	}
	BPNode CreateBinaryTree(const T *&src)
	{
		if(src == NULL) return NULL;
		BinaryTreeNode *ptr = NULL;
		if(*src != EndMark)
		{
			ptr = _BuyNode();
			ptr->data = *src;
			
			ptr->leftchild = CreateBinaryTree(++src);
			ptr->rightchild = CreateBinaryTree(++src);
		}
		
		return ptr;
	}
	static void DestroyTree(BPNode& root)
	{
		if(root != NULL)
		{
			DestroyTree(root->leftchild);
			DestroyTree(root->rightchild);
			_FreeNode(root);
		}
	}
	
	static int Size(BPNode root)
	{
		if(root == NULL) return 0;
		return Size(root->leftchild) + Size(root->rightchild) + 1;
	}
	
	static int Max(int a, int b)
	{
		return a > b ? a : b;
	}
	
	static int Depth(BPNode root)
	{
		if(root == NULL) return 0;
		return Max(Depth(root->leftchild), Depth(root->rightchild))+1;
	}
	
	static BPNode FindValue(BPNode root, const T &val)
	{
		if(root == NULL || val == EndMark)
		{
			return NULL;
		}
		if(root->data == val) return root;
		
		BPNode ptr = NULL;
		ptr = FindValue(root->leftchild);
		if(ptr == NULL)
		{
			ptr = FindValue(root->rightchild);
		}
		
		return ptr;
	}
	
	static BPNode CopyBinaryTree(const BPNode &src)
	{
		if(src == NULL) return NULL;
		
		BPNode p = _BuyNode();
		p->data = src->data;
		p->leftchild = CopyBinaryTree(src->leftchild);
		p->rightchild = CopyBinaryTree(src->rightchild);
		
		return p;
	}
	
	static BPNode FindParent(const BPNode root, const BPNode &child)
	{
		if(root == NULL || root->leftchild == child || root->rightchild == child)
		{
			return root;
		}
		
		BPNode p = NULL;
		p = FindParent(root->leftchild, child);
		if(p == NULL)
		{
			p = FindParent(root->rightchild, child);
		}
		
		return p;
	}
	
	static void InOrder(const BPNode root)
	{
		if(root != NULL)
		{
			InOrder(root->leftchild);
			cout << root->data << " ";
			InOrder(root->rightchild);
		}
	}
	
	static void PastOrder(const BPNode root)
	{
		if(root != NULL)
		{
			PastOrder(root->leftchild);		
			PastOrder(root->rightchild);
			cout << root->data << " ";
		}
	}
	static void PastOrder2(BPNode root)    
	{
		stack<BPNode> s;
		BPNode cur;                     
		BPNode pre=NULL;                 
		s.push(root);
		while(!s.empty())
		{
			cur=s.top();
			if((cur->leftchild==NULL&&cur->rightchild==NULL)||
			   (pre!=NULL&&(pre==cur->leftchild||pre==cur->rightchild)))
			{
				cout<<cur->data<<" "; 
				s.pop();
				pre=cur; 
			}
			else
			{
				if(cur->rightchild!=NULL)
					s.push(cur->rightchild);
				if(cur->leftchild!=NULL)    
					s.push(cur->leftchild);
			}
		}    
	}

	static void PreOrder(const BPNode root)
	{
		if(root != NULL)
		{
			cout << root->data << " ";
			PreOrder(root->leftchild);
			PreOrder(root->rightchild);
		}
	}

	static void PreOrder2(const BPNode root)
	{
		if(root == NULL) return;
		
		stack<BPNode> st;
		BPNode pcur = root;
		
		while(pcur != NULL || !st.empty())
		{
			while(pcur != NULL)
			{
				cout << pcur->data << " ";
				st.push(pcur);
				pcur = pcur->leftchild;
			}
			
			if(!st.empty())
			{
				pcur = st.top(); st.pop();
			
				pcur = pcur->rightchild;
			}
			
		}
	}
	static void InOrder2(const BPNode root)
	{
		if(root == NULL) return ;

		BPNode pcur = root;
		stack<BPNode> st;

		while(pcur != NULL || !st.empty())
		{
			while(pcur != NULL)
			{
				st.push(pcur);
				pcur = pcur->leftchild;
			}
			
			pcur = st.top(); st.pop();
			cout << pcur->data << " ";
			
			pcur = pcur->rightchild;
		}
	}
public:
	BinaryTree(const T &x):root(NULL), EndMark(x) {}
	BinaryTree(const BinaryTree<T> &bt):EndMark(bt.EndMark)
	{
		CopyBinaryTree(root, bt.root);
	}
	BinaryTree<T>& operator=(const BinaryTree<T> &bt)
	{
		if(&bt != this)
		{
			EndMark = bt.EndMark;
			DestroyTree(root);
			root = CopyBinaryTree(bt.root);
		}
		
		return *this;
	}
	~BinaryTree()
	{
		Clear();
	}
	void CreateTree(const T *src)
	{
		if(src != NULL)
		{
			root = CreateBinaryTree(src);
		}
	}
	void Clear()
	{
		DestroyTree(root);
	}
	int Size() const
	{
		retrun Size(root);
	}
	int Depth() const{
		return Depth(root);
	}
	void InOrder() const
	{
		InOrder(root);
	}
	void InOrder2() const
	{
		InOrder2(root);
	}
	void PastOrder() const
	{
		PastOrder(root);
	}
	void PastOrder2() const
	{
		PastOrder2(root);
	}
	void PreOrder() const
	{
		PreOrder(root);
	}
	void PreOrder2() const
	{
		PreOrder2(root);
	}
	BPNode FindParent(const BPNode &child) const
	{
		return FindParent(root, child);
	}
	BPNode FindValue(const T &val) const
	{
		return FindValue(root, val);
	}
	BPNode GetRoot() const
	{
		return root;
	}
};


template<class T>
class TreeIterator
{
public:
	TreeIterator(BinaryTree<T> &bt):tree(bt), _Ptr(NULL) {}
	T& operator*()
	{
		return _Ptr->data;
	}
	const T& operator*() const
	{
		return _Ptr->data;
	}
	bool IsDone() const
	{
		return _Ptr == NULL;
	}
	virtual void First() = 0;
	virtual void operator++() = 0;
protected:
	BinaryTree<T> &tree;
	typename BinaryTree<T>::BinaryTreeNode *_Ptr;
};

template<class T>
class InIterator : public TreeIterator<T>
{
public:
	InIterator(BinaryTree<T> &root):TreeIterator(root){}
	void First()
	{
		_Ptr = tree.GetRoot();
		while(!IsDone())
		{
			mst.push(_Ptr);
			if(_Ptr->leftchild == NULL)
			{
				operator++();
				return ;
			}
			_Ptr = _Ptr->leftchild;
		}
	}
	void operator++()
	{
		typename BinaryTree<T>::BinaryTreeNode* pcur = NULL;
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		pcur = _Ptr = mst.top(); mst.pop();
		pcur = pcur->rightchild;
		while(pcur != NULL)
		{
			mst.push(pcur);
			pcur = pcur->leftchild;
		}
	}
private:
	stack<typename BinaryTree<T>::BinaryTreeNode*> mst;
};

template<class T>
class PastIterator : public TreeIterator<T>
{
public:
	PastIterator(BinaryTree<T> &bt):TreeIterator(bt){}
	void First()
	{
		_Ptr = tree.GetRoot();
		while(!IsDone())
		{
			mst.push(_Ptr);
			if(_Ptr->leftchild == NULL)
			{
				operator++();
				return ;
			}
			_Ptr = _Ptr->leftchild;
		}
	}
	void operator++()
	{
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		typename BinaryTree<T>::BinaryTreeNode* pcur = NULL;
		static typename BinaryTree<T>::BinaryTreeNode* tag = NULL;
		
		_Ptr = pcur = mst.top(); mst.pop();
		pcur = pcur->rightchild;
		if(pcur == NULL || pcur == tag)
		{
			tag = _Ptr;
		}
		else
		{
			mst.push(_Ptr);
			while(pcur != NULL)
			{
				mst.push(pcur);
				if(pcur->leftchild == NULL)
				{
					_Ptr = pcur;
					pcur = tag;
					operator++();
					break;
				}
				
				pcur = pcur->leftchild;
			}
		}
	}
private:
	stack<typename BinaryTree<T>::BinaryTreeNode*> mst;
};

template<class T>
class PreIterator : public TreeIterator<T>
{
public:
	PreIterator(BinaryTree<T> &bt):TreeIterator(bt) {}
	void First()
	{
		_Ptr = tree.GetRoot();
		if(_Ptr != NULL)
		{
			mst.push(_Ptr);
			operator++();
		}
	}
	
	void operator++()
	{
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		typename BinaryTree<T>::BinaryTreeNode* pcur = NULL;
		pcur = _Ptr = mst.top(); mst.pop();
		if(pcur->rightchild != NULL)
		{
			mst.push(pcur->rightchild);
		}
		if(pcur->leftchild != NULL)
		{
			mst.push(pcur->leftchild);
		}
	}
	
private:
	stack<typename BinaryTree<T>::BinaryTreeNode*> mst;
};

template<class T>
class StkNode
{
public:
	StkNode(typename BinaryTree<T>::BinaryTreeNode* bt = NULL):pnode(bt), popnum(0) {}
	typename BinaryTree<T>::BinaryTreeNode* pnode;
	int                                  popnum;
};

template<class T>
class PastIterator2 : public TreeIterator<T>
{
public:
	PastIterator2(BinaryTree<T> &bt):TreeIterator(bt) {}
	void First()
	{
		_Ptr = tree.GetRoot();
		if(_Ptr != NULL)
		{
			mst.push(StkNode<T>(_Ptr));
			operator++();
		}
	}
	void operator++()
	{
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		while(1)
		{
			StkNode<T> node = mst.top();
			mst.pop();
			if(++node.popnum == 3)
			{
				_Ptr = node.pnode;
				return ;
			}
			mst.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				mst.push(StkNode<T>(node.pnode->leftchild));
			}
			else if(node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				mst.push(StkNode<T>(node.pnode->rightchild));
			}
		}
	}
private:
	stack<StkNode<T> > mst;
};

template<class T>
class InIterator2 : public TreeIterator<T>
{
public:
	InIterator2(BinaryTree<T>& bt):TreeIterator(bt) {}
	void First()
	{
		_Ptr = tree.GetRoot();
		if(_Ptr != NULL)
		{
			mst.push(StkNode<T>(_Ptr));
			operator++();
		}
	}
	void operator++()
	{
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		StkNode<T> node = mst.top();
		mst.pop();
		
		if(++node.popnum == 2)
		{
			_Ptr = node.pnode;
			if(_Ptr->rightchild != NULL)
			{
				mst.push(StkNode<T>(_Ptr->rightchild));
			}
			
			return ;
		}
		
		if(node.popnum == 1 && node.pnode->leftchild != NULL)
		{
			mst.push(StkNode<T>(node.pnode->leftchild));
		}
	}
private:
	stack<StkNode<T> > mst;
};

template<class T>
class PreIterator2 : public TreeIterator<T>
{
public:
	PreIterator2(BinaryTree<T> &bt):TreeIterator(bt) {}
	void First()
	{
		_Ptr = tree.GetRoot();
		if(_Ptr != NULL)
		{
			mst.push(StkNode<T>(_Ptr));
			operator++();
		}
	}
	
	void operator++()
	{
		if(mst.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		StkNode<T> node = mst.top(); mst.pop();
		_Ptr = node.pnode;
		
		if(_Ptr->rightchild != NULL)
		{
			mst.push(StkNode<T>(_Ptr->rightchild));
		}
		if(_Ptr->leftchild != NULL)
		{
			mst.push(StkNode<T>(_Ptr->leftchild));
		}
	}
private:
	stack<StkNode<T> > mst;
};

template<class T>
class LevelIterator : public TreeIterator<T>
{
public:
	LevelIterator(BinaryTree<T> &bt):TreeIterator(bt) {}
	void First()
	{
		_Ptr = tree.GetRoot();
		if(_Ptr != NULL)
		{
			qu.push(_Ptr);
			operator++();
		}
	}
	void operator++()
	{
		if(qu.empty())
		{
			_Ptr = NULL;
			return ;
		}
		
		_Ptr = qu.front(); qu.pop();
		if(_Ptr->leftchild != NULL)
		{
			qu.push(_Ptr->leftchild);
		}
		if(_Ptr->rightchild != NULL)
		{
			qu.push(_Ptr->rightchild);
		}
	}
private:
	queue<typename BinaryTree<T>::BinaryTreeNode*> qu;
};

template<class T>
void PrintTreeInterator(TreeIterator<T> &tr)
{
	tr.First();
	while(!tr.IsDone())
	{
		cout << *tr << " ";
		++tr;
	}
}

int main()
{
	char *str = "ABC##DE#j##F##G#H##";
	BinaryTree<char> myt('#');
	myt.CreateTree(str);
	myt.PreOrder2();
	cout << endl;
	
	/*myt.InOrder();
	cout << endl;
	BinaryTree<char> yout('#');
	yout = myt;
	yout.InOrder();
	cout << endl;*/

	InIterator<char> ii(myt);
	PastIterator<char> pi(myt);
	PreIterator<char> pp(myt);
	LevelIterator<char> li(myt);
	
	PreIterator2<char> ppi2(myt);
	PrintTreeInterator(pp);
	cout << endl;

	myt.InOrder2();
	cout << endl;
	PrintTreeInterator(ii);
	cout << endl;

	myt.PastOrder2();
	cout << endl;
	PrintTreeInterator(pi);
	cout << endl;
	/*InIterator<char> ii2(myt);
	PrintTreeInterator(ii2);
	cout << endl;*/
	/*PastIterator2<char> pi2(myt);
	PrintTreeInterator(pi2);
	cout << endl;
	myt.PastOrder();
	cout << endl;*/
	/*PrintTreeInterator(ii);
	cout << endl;*/
	//PrintTreeInterator(pp);
	//cout << endl;
	//cout << "-----------------" << endl;

	//myt.PreOrder();
	//cout << endl;
	//PrintTreeInterator(pp);
	//cout << endl;
	//cout << "-----------------" << endl;

	//PrintTreeInterator(li);
	//cout << endl;
	//cout << "------------------" << endl;
	return 0;
}
