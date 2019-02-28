#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "matrix.hpp"
using namespace std;
using sjtu::matrix;
bool mission_complete = true;
void TestDynamicSpace()
{
	matrix<10000> mat;
	cout << "Testing the usage of pointers instead of static members: ";
	if (sizeof(mat) > 5 * (sizeof(double*)))
	{
		mission_complete = false;
		cout << "Incorrect." << endl;
	} else {
		cout << "Correct." << endl;
	}
}
bool TestBasic()
{
	matrix<10> src;
	double data[11][11];
	bool passed = true;
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			data[i][f] = double(rand() % 10000) / 100.0;
			src(i, f) = data[i][f];
			if (src(i, f) != data[i][f])
				passed = false;
		}
	}
	bool except1flag = false;
	try
	{
		src[213][3] = 233;
	}
	catch(...)
	{
		except1flag = true;
	}
	passed = passed && except1flag;
	except1flag = false;
	try
	{
		src(213, 3) = 233;
	}
	catch(...)
	{
		except1flag = true;
	}
	passed = passed && except1flag;
	return passed;
}

void TestCopyConstructor()
{
	bool passed = true;
	cout << "Testing copy constructor: ";
	matrix<10> * srcptr = new matrix<10>();
	matrix<10> & src(*srcptr);
	double data[11][11];
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			data[i][f] = double(rand() % 10000) / 100.0;
			src(i, f) = data[i][f];
			if (src(i, f) != data[i][f])
				passed = false;
		}
	}
	const matrix<10> cp1(src);
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (src(i, f) != cp1(i, f))
				passed = false;
	matrix<10> cp2(src);
	delete srcptr;
	// To ensure that you used deep copy.
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (cp2(i, f) != cp1(i, f))
				passed = false;
	if (passed)
	{
		cout << "Correct." << endl;
	} else {
		cout << "Incorrect." << endl;
		mission_complete = false;
	}
}
void TestAssignmentOperator()
{
	bool passed = true;
	cout << "Testing assignment operator: ";
	matrix<10> * srcptr = new matrix<10>();
	matrix<10> & src(*srcptr);
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			src(i, f) = rand() % 233;
		}
	}
	const matrix<10> cp1(src);
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (src(i, f) != cp1(i, f))
				passed = false;
	matrix<10> cp2;
	cp2 = src;
	delete srcptr;
	// To ensure that you used deep copy.
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (cp2(i, f) != cp1(i, f))
				passed = false;
	if (passed)
	{
		cout << "Correct." << endl;
	} else {
		cout << "Incorrect." << endl;
		mission_complete = false;
	}
}
void TestBracketAccessment()
{
	bool passed = true;
	cout << "Testing accessment through brackets operator: ";
	matrix<10> src;
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			src(i, f) = rand() % 233;
		}
	}
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (src[i][f] != src(i, f))
			{
				passed = false;
				break;
			}
	if (passed)
	{
		cout << "Correct." << endl;
	} else {
		cout << "Incorrect." << endl;
		mission_complete = false;
	}
}
void TestLinearOperation()
{
	bool passed = true;
	cout << "Testing linear operation: ";
	matrix<10, int> rhs, lhs;
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			rhs(i, f) = rand() % 10000;
			lhs(i, f) = rand() % 10000;
		}
	}
	matrix<10, int> res;
	res = lhs + rhs;

	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (rhs[i][f] + lhs[i][f] != res[i][f])
				passed = false;
	res = lhs - rhs;
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
			if (lhs[i][f] - rhs[i][f] != res[i][f])
				passed = false;
	if (passed)
	{
		cout << "Correct." << endl;
	} else {
		cout << "Incorrect." << endl;
		mission_complete = false;
	}
}
void TestInputOutputConsistency()
{
	bool passed = true;
	cout << "Testing stream input / output consistency: ";
	stringstream fout;
	matrix<10> src, cp;
	double data[11][11];
	for (int i = 1; i <= 10; ++i)
	{
		for (int f = 1; f <= 10; ++f)
		{
			data[i][f] = double(rand() % 10000) / 100.0;
			src(i, f) = data[i][f];
			if (src(i, f) != data[i][f])
				passed = false;
		}
	}
	fout << src;
	fout >> cp;
	for (int i = 1; i <= 10; ++i)
		for (int f = 1; f <= 10; ++f)
		{
			if (data[i][f] != cp[i][f])
				passed = false;
		}
	if (passed)
	{
		cout << "Correct." << endl;
	} else {
		cout << "Incorrect." << endl;
		mission_complete = false;
	}
}
void ShowCongratulations()
{
	cout << "Congratulations! You have passed all basic tests. Use valgrind to make sure there are no memory leaks in your matrix. Have fun!" << endl;
}

int main()
{
	srand(20200613LL);
	if (TestBasic())
	{
		TestDynamicSpace();
		TestCopyConstructor();
		TestAssignmentOperator();
		TestBracketAccessment();
		TestLinearOperation();
		TestInputOutputConsistency();
		if (mission_complete)
			ShowCongratulations();
	} else {
		cout << "Basic function test failed." << endl;
	}
	return 0;
}
