#ifndef SJTU_OOP_MATRIX
#define SJTU_OOP_MATRIX
/*
	Include relevant header files here.
*/
#include <iostream>
#include <cstddef>
using std :: istream;
using std :: ostream;

namespace sjtu
{
	//Consider why we use a template here, tell me about your thoughts in the email.
	template <int n, typename type_real = double>
	class matrix
	{
	public:
		type_real ** p;

	/*
		Add your own codes here.
		You are required to manually manage the memory.
		STL is banned.
		Static array is banned.
		Use a pointer and operator "new" or malloc to implement the function of an array.
		You are permitted to define a private class here.
	*/
	public:
		matrix()
		{
			p = new type_real * [n + 1];
			for (int i = 1; i <= n; ++i){
				p[i] = new type_real[n + 1];
			}
			//Write your own codes here to construct a static-sized matrix.
		}
		matrix(const matrix & src)
		{
			p = new type_real * [n + 1];
			for (int i = 1; i <= n; ++i){
				p[i] = new type_real[n + 1];
			}
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					p[i][j] = src.p[i][j];
				}
			}
			//Write your own codes here to copy-construct a static-sized matrix.
		}
		matrix & operator=(const matrix & src)
		{
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					p[i][j] = src.p[i][j];
				}
			}
			return *this;
			//Write your own codes here to implement a assignment operator for your matrix class
		}
		type_real & operator()(size_t i, size_t j)
		{
			if (i < 1 || i > n || j < 1 || j > n){
				throw ("ioob");
			}
			return p[i][j];
			//Write your own codes to return the i-line, j-col element.
			//ATTENTION: 1 - based.
			//Use exception-throw to deal with overflows.
		}
		const type_real & operator()(size_t i, size_t j) const/* Is here supposed to be a keyword? Then what is it? */
		{
			if (i < 1 || i > n || j < 1 || j > n){
				throw ("ioob");
			}
			return p[i][j];
			//Write your own codes to return the i-line, j-col element.
			//ATTENTION: 1 - based.
			//Use exception-throw to deal with overflows.
		}
		type_real * & operator[](size_t i)
		{
			if (i < 1 || i > n){
				throw ("ioob");
			}
			 return p[i];
		}

		const type_real * & operator[](size_t i) const
		{
			if (i < 1 || i > n){
				throw ("ioob");
			}
			 return p[i];
		}
		/*
			Try to figure out the differences between the two operator() implementations.
			Tell me about your thoughts in the E-mail where you send this file to me.
		*/
		
		/*Design two functions to support usages like:
			matrix_a[i][j]
				which equals to matrix_a(i, j)
		*/
		size_t size() const
		{
			return n;
			// Return the size of the matrix.
		}
		matrix operator+(const matrix & rhs) const/* Is here supposed to be a keyword? Then what is it? */
		{
			matrix <n, type_real> q;
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					q.p[i][j] = p[i][j] + rhs.p[i][j];
				}
			}
			return q;
			//Write your own codes to implement a naive matrix addition.
			//It shall be avaliable for constant matrices.
		}
		matrix operator-(const matrix & rhs) const/* Is here supposed to be a keyword? Then what is it? */
		{
			matrix <n, type_real> q;
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					q.p[i][j] = p[i][j] - rhs.p[i][j];
				}
			}
			return q;
			//Write your own codes to implement a naive matrix subtraction.
			//It shall be avaliable for constant matrices.
		}
		
		/*
			Implement the functions of stream-based input/output.
			Learn more at:http://cn.bing.com/search?q=%E6%B5%81%E8%BE%93%E5%85%A5%E8%BE%93%E5%87%BA+%E9%87%8D%E8%BD%BD&go=%E6%8F%90%E4%BA%A4&qs=n&form=QBLH&pq=%E6%B5%81%E8%BE%93%E5%85%A5%E8%BE%93%E5%87%BA+%E9%87%8D%E8%BD%BD&sc=1-8&sp=-1&sk=&cvid=0313FD30AE76426F8AC06BB269B88C9A
			
		*/
		friend istream & operator>>(istream & fin, matrix & rhs)
		{
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					fin >> rhs.p[i][j];
				}
			}
			return fin;
			//Write your own codes here.
		}
		friend ostream & operator<<(ostream & fout, const matrix & rhs)
		{
			for (int i = 1; i <= n; ++i){
				for (int j = 1; j <= n; ++j){
					fout << rhs.p[i][j] << ' ';
				}
				fout << '\n';
			}
			return fout;
			//Write your own codes here.
		}
		
		~matrix()
		{
			for (int i = 1; i <= n; ++i){
				delete [] p[i];
			}
			delete [] p;
			//Destruct your matrix.
			//Be sure to prevent any memory leaks from happening.
		}
	};
}
#endif
