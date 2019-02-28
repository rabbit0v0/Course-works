#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include<algorithm>
using namespace std;


template <class elem, class compare = std::less<int>>
class cpile
{
public:
	elem* data;
	int currentsize;
	int maxsize;
	compare cmp;
public:
	cpile(int size = 10)
	{
		data = new elem[size];
		currentsize = 0;
		maxsize = size;
	}
	~cpile()
	{
		delete[] data;
	}

	void doublespace()
	{
		elem* p = new elem[2 * maxsize];
		for (int i = 0; i <= currentsize; i++)
		{
			p[i] = data[i];
		}

		delete[] data;
		data = p;
		maxsize *= 2;
	}
	void enqueue(elem input)
	{
		if (currentsize >= maxsize - 1) doublespace();
		int hole = ++currentsize;
		for (;hole > 1 && cmp(input , data[hole / 2]);hole /= 2)//
		{
			data[hole] = data[hole / 2];
		}
		data[hole] = input;
	}

	void percolatedown(int hole)
	{
		elem tmp = data[hole];
		int child = 0;
		for (;hole * 2 <= currentsize;hole = child)
		{
			child = hole * 2;
			if (child < currentsize&& cmp(data[child + 1] , data[child]))//
				child++;
			if (cmp(data[child] , tmp)) data[hole] = data[child];//
			else break;
		}
		data[hole] = tmp;
	}
	elem dequeue()
	{
		elem tmp = data[1];
		data[1] = data[currentsize];
		percolatedown(1);
		currentsize--;
		return tmp;
	}
	void pilesort(elem a[], int n, bool stol = true)
	{
		for (int i = 0; i < n; i++)
		{
			enqueue(a[i]);
		}
		if (stol)
		{
			for (int i = 0; i < n; i++)
			{
				a[i] = dequeue();
			}
		}
		else
		{
			for (int i = n - 1; i >= 0; i--)
			{
				a[i] = dequeue();
			}
		}
	}
};


struct ch
{
	int num1;
	int num2;
};

class cmp1
{
public:
	bool operator() (ch x, ch y)
	{
		return x.num1 < y.num1;
	}
};

ch c[10];



int main()
{
	for (int i = 0; i < 10; i++)
	{
		c[i].num1 = i;
	}
	cpile<ch,cmp1> chips;
	chips.pilesort(c, 10);



	return 0;
}