#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include<algorithm>
using namespace std;
int intmax = 10000000;
class avltree
{
public:
	struct avlnode
	{
		int data;
		avlnode* left;
		avlnode* right;
		avlnode* pre;
		avlnode* next;
		int num;
		int height;
		avlnode()
		{
			left = NULL;
			right = NULL;
			pre = NULL;
			next = NULL;
			height = 0;
			num = 1;
		}
	};
	avlnode* root;
	size_t currentsize;
public:
	int max(int a, int b) { if (a < b) return b;else return a; }
	int min(int a, int b) { if (a < b) return a;else return b; }
	int h(avlnode* &p) { if (p == NULL) return 0; else return p->height; }
	avltree() :root(NULL), currentsize(0) {}
	void reclear(avlnode* &root)
	{
		if (root->left != NULL)
		{
			reclear(root->left);
		}
		if (root->right != NULL)
		{
			reclear(root->right);
		}
		delete root;
		root = NULL;
		currentsize = 0;
	}
	void clear() { if (root != NULL)reclear(root); };
	~avltree() { if (root != NULL) clear(); }
	avlnode* find(int elem)const
	{
		avlnode* tmp = root;
		while (tmp != NULL && tmp->data != elem)
		{
			if (elem< tmp->data) tmp = tmp->left;
			else tmp = tmp->right;
		}
		return tmp;
	}
	void updateheight(avlnode* & p)
	{
		if (p == NULL) return;
		p->height = max(h(p->left), h(p->right)) + 1;
	}
	void LL(avlnode* & root)
	{
		avlnode* tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		updateheight(root);
		updateheight(tmp);
		root = tmp;
	}
	void RR(avlnode* & root)
	{
		avlnode* tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		updateheight(root);
		updateheight(tmp);
		root = tmp;
	}
	void LR(avlnode* & root)
	{
		RR(root->left);
		LL(root);
	}
	void RL(avlnode* & root)
	{
		LL(root->right);
		RR(root);
	}

	void balance(avlnode* &root)
	{
		if (root == NULL) return;
		if (h(root->left) - h(root->right) > 1)
		{
			if (h(root->left->left) >= h(root->left->right))
				LL(root);
			else LR(root);
		}
		else if (h(root->right) - h(root->left) > 1)
		{
			if (h(root->right->right) >= h(root->right->left))
				RR(root);
			else RL(root);
		}
	}

	avlnode* insert(const int& x)
	{
		avlnode* storepre = NULL;
		avlnode* storenext = NULL;
		bool inserted = false;
		return reinsert(root, storepre, storenext, x, inserted);

	}

	void remove(const int& x)
	{
		avlnode* storeininode = NULL;
		reremove(storeininode, root, x);
	}

	avlnode* reinsert(avlnode* &root, avlnode*& thepre, avlnode*& thenext, const int & x, bool& inserted)
	{
		avlnode* tmp = NULL;
		if (root == NULL)
		{
			root = new avlnode;
			root->data = x;
			currentsize++;
			tmp = root;
			root->pre = thepre;
			root->next = thenext;
			if (root->pre != NULL) root->pre->next = root;
			if (root->next != NULL) root->next->pre = root;
			inserted = true;
		}
		else
			if (x<root->data)
				tmp = reinsert(root->left, thepre, root, x, inserted);
			else
				if (root->data<x)
					tmp = reinsert(root->right, root, thenext, x, inserted);
				else
				{
					root->num++;
					currentsize++;
					return root;
				}
		if (inserted)
		{
			updateheight(root);
			balance(root);
		}
		return tmp;
	}
	/*
	void reremove(avlnode*& ininode, avlnode* &root, const int & x)
	{
		if (root == NULL) return;// not found
		if (x<root->data)
			reremove(root, root->left, x);
		else if (root->data<x)
			reremove(root, root->right, x);
		else if (root->num > 1)
		{
			root->num--;
			currentsize--;
			return;
		}
		else if (root->left != NULL&&root->right != NULL)
		{
			avlnode* tmp = root->right;
			while (tmp->left != NULL)
			{
				tmp = tmp->left;
			}
			root->data = tmp->data;
			reremove(root, root->right, root->data);
		}
		else
		{

			if (root->pre != NULL) root->pre->next = root->next;
			if (root->next != NULL) root->next->pre = root->pre;
			avlnode* oldnode = root;
			root = (root->left != NULL) ? root->left : root->right;
			//	printf("deleted:           %d\n", oldnode->data->second);
			currentsize--;
			delete oldnode;
		}
		if (root != NULL)
		{
			updateheight(root);
			balance(root);
		}
	}*/

	void reremove(avlnode*& ininode, avlnode* &root, const int & x)
	{
		if (root == NULL) return;// not found
		if (x< root->data)
			reremove(root, root->left, x);
		else if (root->data < x)
			reremove(root, root->right, x);
		else if (root->num > 1)
		{
			root->num--;
			currentsize--;
			return;
		}
		else if (root->left != NULL&&root->right != NULL)
		{
			avlnode* tmp = root->right;
			avlnode* initmp = root->right;
			if (tmp->left != NULL) tmp = initmp->left;
			while (tmp->left != NULL)
			{
				initmp = initmp->left;
				tmp = tmp->left;
			}
			if (tmp == initmp)
			{
				avlnode* theroot = root;
				avlnode* tmpright = tmp->right;
				tmp->left = root->left;
				tmp->right = root;
				root = tmp;
				theroot->left = NULL;
				theroot->right = tmpright;
				reremove(root, root->right,theroot->data);
			}
			else {
				avlnode	* tmpright = tmp->right;
				avlnode* theroot = root;
				tmp->left = root->left;
				tmp->right = root->right;
				root = tmp;
				initmp->left = theroot;
				theroot->left = NULL;
				theroot->right = tmpright;
				reremove(root, root->right, theroot->data);
			}
		}
		else
		{
			if (root->pre != NULL) root->pre->next = root->next;
			if (root->next != NULL) root->next->pre = root->pre;
			avlnode* oldnode = root;
			root = (root->left != NULL) ? root->left : root->right;
			//	printf("deleted:           %d\n", oldnode->data->second);
			currentsize--;
			delete oldnode;
		}
		if (root != NULL)
		{
			updateheight(root);
			balance(root);
		}
	}
	void traverse()
	{
		if (root == NULL) return;
		avlnode* max = root;
		while (max->right != NULL) max = max->right;
		cout << "          now traverse:" << endl;
		cout << max->data << " * " << max->num << endl;
		while (max->pre != NULL)
		{
			max = max->pre;
			cout << max->data << " * " << max->num << endl;
		}
	}
	int query(int largenum)
	{
		avlnode* max = root;
		if (max == NULL) return 0;
		while (max->right != NULL) max = max->right;
		for (int i = max->num; i < largenum; i += max->num)
		{
			if (max->pre == NULL) return 0;
			max = max->pre;
		}
		return max->data;
	}
};

class disjointset
{
private:
	int size;
	int* parent;
public:
	disjointset(int i_size = 1000)
	{
		size = i_size;
		parent = new int[size];
		for (int i = 0; i < size; i++)
			parent[i] = -1;
	}
	int Find(int x)
	{
		if (parent[x] < 0) return x;
		return parent[x] = Find(parent[x]);
	}
	void Union(int root1, int root2)
	{
		if (parent[root1] > parent[root2])
		{
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else
		{
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
	int Unionelement(int elem1, int elem2)
	{
		int root1 = Find(elem1);
		int root2 = Find(elem2);
		if (parent[root1] == -intmax || parent[root2] == -intmax) return -1;
		if (root1 == root2) return -1;
		Union(root1, root2);
		return 1;
	}
	int removesubtree(int elem)
	{
		int found = Find(elem);
		if (parent[found] == -intmax) return -1;
		parent[found] = -intmax;
		return 1;
	}
	int querysize(int elem)
	{
		return -parent[Find(elem)];
	}
};


int n = 0;
int m = 0;
int x = 0;
int y = 0;
char flag;
int p = 0;
int sizex = 0;
int sizey = 0;
int main()
{
	//freopen("out.txt", "w", stdout);
	//freopen("新建文本文档.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	avltree avl;
	avl.insert(1);
	avl.root->num = n;
	avl.currentsize = n;
	disjointset ds(n);
	for (int i = 1; i <= m; i++)
	{
		if (scanf("%c%c", &flag, &flag) == EOF) break;
		switch (flag)
		{
		case 'C':
			scanf("%d%d", &x, &y);
			//cout << "now operate C " << x << " " << y << endl;
			if (x > n || x < 1 || y>n || y < 1) break;
			--x;--y;
			sizex = ds.querysize(x);
			sizey = ds.querysize(y);
			if (ds.Unionelement(x, y) != -1)
			{
				avl.remove(sizex);
				avl.remove(sizey);
				avl.insert(sizex + sizey);
			}
		////	cout << "after:" << endl;
		//	avl.traverse();
			break;
		case 'D':
			scanf("%d", &x);
			//cout << "now operate D " << x << endl;
			if (x > n || x < 1)break;
			--x;
			sizex = ds.querysize(x);
			if (ds.removesubtree(x) != -1)
				avl.remove(sizex);
			//cout << "after:" << endl;
		//	avl.traverse();
			break;
		case 'Q':
			scanf("%d", &p);
		//	cout << "now operate Q " << p << endl;
			if (p > avl.currentsize) cout << 0 << endl;
			else
			printf("%d\n", avl.query(p));
			break;
		default:
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}