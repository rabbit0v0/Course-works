#include <iostream>
#include "vm.h"


Integer Example1(Integer a, Integer b)
{
    return a + b;
}

Integer Example2(Integer a)
{
    if_(a == 0, [&]()
        {
            a = 1;
        }, [&]() /* else */
        {
            a = 0;
        });
    return a;
}

Integer Example3(Integer a, Integer n)
{
    Integer result = 1;
    while_([&]() { return n > 0; }, [&]()
           {
               result *= a;
               --n;
           });
    return result;
}

Integer Example4(Integer a, Integer b)
{
    Integer sum = 0;
    Integer i = a;
    while_([&]() { return i <= b; }, [&]()
           {
               if_(i % 2 == 1, [&]()
                   {
                       ++i;
                       continue_();
                   });
               sum += i;
               ++i;
           });
    return sum;
}

//////////////////////////////////////

/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *
 *	A = 4, B = 8
 *   Rating: 1
 */
Integer bitAnd(Integer x, Integer y)////////////////////right/////////////////
{
    return ~((~x)|(~y));
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 3, B = 6
 *   Rating: 2
 */
Integer getByte(Integer x, Integer n) //////////////////////right//////////////////
{
    Integer tmp;
    tmp = ((x >> (((Integer)-4 + n) << 3)) & 0xFF);
    return tmp;
}

/*
 * logicalShift - shift x to the right by n, using a arithmetic shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0xf8765432
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 10, B = 20
 *   Rating: 6
 */
Integer arithmeticShift(Integer x, Integer n)
{
    return (x >> n);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 25, B = 128
 *   Rating: 8
 */
Integer bitCount(Integer x)//////////////////right//////////////
{
    Integer sum = 0;
    for (int i = 0; i < 32; ++i){
        sum += (x & 1);
        x = x >> 1;
    }
    return sum;
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *
 *	A = 6, B = 24
 *   Rating: 6
 */
Integer bang(Integer x)
{
    Integer tmp = x + 1;
    Integer res = tmp / x;
    return res;
}

/*
 * divpwr2 - Compute int(x)/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 16, B = 32
 *   Rating: 6
 */
Integer divpwr2(Integer x, Integer n)
{
    Integer res = x;
    res = res >> n;
    return res;
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 3, B = 6
 *   Rating: 1
 */
Integer negate(Integer x)/////////////right//////////////////////////////
{
    Integer res = (~x);
    res += 1;
    return res;
}

/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 5, B = 10
 *   Rating: 4
 */
Integer isPositive(Integer x)
{
    return (x > 0);
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 15, B = 36
 *   Rating: 6
 */
Integer isLessOrEqual(Integer x, Integer y)
{
    return (x <= y);
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *	A = 32, B = 100
 *   Rating: 8
 */
Integer ilog2(Integer x)
{
    Integer sum = 0;
    for (int i = 0; i < 32; ++i){
        x >> 1;
        sum += (x > 0);
    }
    return sum;
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer operations and if, while
 *
 *	A = 6, B = 20
 *   Rating: 6
 */
Integer float_neg(Integer f)
{
    Integer res = f;
    res = -res;
    return res;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Legal ops: Any integer operations and if, while
 *
 *	A = 50, B = 150
 *   Rating: 8
 */
Integer float_i2f(Integer x)
{
    return 2;
}

/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer operations and if, while
 *
 *	A = 15, B = 90
 *   Rating: 8
 */
Integer float_twice(Integer f)
{
    return 2;
}

/*
 * float_sqrt - Return bit-level equivalent of expression sqrtf(f) for
 *   floating point argument f.
 *	The relative error fabs(ans-sqrtf(f))/sqrtf(f) should not be larger than 1e-3
 *	Can assume that 0 <= f <= 1e6
 *   Legal ops: Any integer operations and if, while
 *
 *	A = 300, B = 2000
 *   Rating: 15
 */
Integer float_sqrt(Integer f)
{
    return 2;
}

/*
 * divide - Compute int(x)/n
 *  Round toward zero
 *   Example: divide(-6) / 3 = -2
 *   Legal ops: Any integer operations and if, while
 *
 *	A = 10, B = 72
 *   Rating: 5 * 3
 */
Integer divide(Integer x, std::int32_t n)
{
    Integer res = 0, tmp = (Integer)n;
    res = x / tmp;
    return res;
}

//////////////////////////////////////

template<typename ...Args>
void testcase(std::ostream &out, const std::string &description, std::function<Integer(Args...)> func)
{
    out << "# " << description << std::endl;
    compile(out, func);
    out << std::endl;
}

template<typename ...Args>
void testcase(std::ostream &out, const std::string &description, Integer (*func)(Args...))
{
    testcase(out, description, std::function<Integer(Args...)>(func));
}

int main()
{
    testcase(std::cout, "bitAnd",			bitAnd);
    testcase(std::cout, "getByte",			getByte);
    testcase(std::cout, "arithmeticShift",	arithmeticShift);
    testcase(std::cout, "bitCount",			bitCount);
    testcase(std::cout, "bang",				bang);
    testcase(std::cout, "divpwr2",			divpwr2);
    testcase(std::cout, "negate",			negate);
    testcase(std::cout, "isPositive",		isPositive);
    testcase(std::cout, "isLessOrEqual",	isLessOrEqual);
    testcase(std::cout, "ilog2",			ilog2);
    testcase(std::cout, "float_neg",		float_neg);
    testcase(std::cout, "float_i2f",		float_i2f);
    testcase(std::cout, "float_twice",		float_twice);
    testcase(std::cout, "float_sqrt",		float_sqrt);
    
    for (int i = 0; i < 3; i++)
    {
        std::int32_t divisor;
        std::cin >> divisor;
        testcase(std::cout, "divide_" + std::to_string(divisor), std::function<Integer(Integer)>(std::bind(divide, std::placeholders::_1, std::uint32_t(divisor))));
    }
    
    return 0;
}
