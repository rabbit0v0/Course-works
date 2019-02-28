#include <iostream>
#include "matrix.hpp"
using namespace std;
using sjtu::matrix;
int main()
{
	const matrix<10> mat;
	mat[1][2] = 231;
	return 0;
}
