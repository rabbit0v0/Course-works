#include <iostream>
#include <random>
#include <set>
#include <cassert>
#include <cmath>
#include "vm.h"

std::uint32_t bitAnd(std::uint32_t a, std::uint32_t b)
{
	return a & b;
}

std::uint32_t getByte(std::uint32_t a, std::uint32_t n)
{
	assert(n <= 3);
	return *(reinterpret_cast<std::uint8_t *>(&a) + n);
}

std::uint32_t arithmeticShift(std::uint32_t a, std::uint32_t b)
{
	return std::int32_t(a) >> b;
}

std::uint32_t bitCount(std::uint32_t x)
{
	int count = 0;
	for (int i = 0; i <= 31; i++)
		if (x & (1 << i))
			count++;
	return count;
}

std::uint32_t bang(std::uint32_t x)
{
	return !x;
}

std::uint32_t divpwr2(std::uint32_t x, std::uint32_t n)
{
	assert(n <= 30);
	return std::int32_t(x) / (1 << n);
}

std::uint32_t negate(std::uint32_t x)
{
	return -std::int32_t(x);
}

std::uint32_t isPositive(std::uint32_t x)
{
	return std::int32_t(x) > 0;
}

std::uint32_t isLessOrEqual(std::uint32_t x, std::uint32_t y)
{
	return std::int32_t(x) <= std::int32_t(y);
}

std::uint32_t ilog2(std::uint32_t x)
{
	std::uint32_t result = 0;
	for (; x > 1; x >>= 1)
		result++;
	return result;
}

std::uint32_t float_neg(std::uint32_t f)
{
	if (std::isnan(*reinterpret_cast<float *>(&f)))
		return f;
	float ans = -*reinterpret_cast<float *>(&f);
	return *reinterpret_cast<std::uint32_t *>(&ans);
}

std::uint32_t float_i2f(std::uint32_t x)
{
	float ans = float(std::int32_t(x));
	return *reinterpret_cast<std::uint32_t *>(&ans);
}

std::uint32_t float_twice(std::uint32_t f)
{
	if (std::isnan(*reinterpret_cast<float *>(&f)))
		return f;
	float ans = 2 * (*reinterpret_cast<float *>(&f));
	return *reinterpret_cast<std::uint32_t *>(&ans);
}

std::uint32_t float_sqrt(std::uint32_t f)
{
	float ans = sqrtf(*reinterpret_cast<float *>(&f));
	return *reinterpret_cast<std::uint32_t *>(&ans);
}

std::uint32_t divide(std::uint32_t x, std::int32_t y)
{
	return std::int32_t(x) / y;
}

std::mt19937 gen(0x19260817);

typedef std::function<std::uint32_t()> funcRand;

std::uint32_t default_rand()
{
	std::uniform_int_distribution<std::uint32_t> dist;
	return dist(gen);
}

template<std::uint32_t a, std::uint32_t b>
std::uint32_t rand_range()
{
	std::uniform_int_distribution<std::uint32_t> dist(a, b);
	return dist(gen);
}

template<typename ...Args, std::size_t ...I>
double judge_impl(
	std::istream &in, 
	const std::string &name, 
	std::function<std::uint32_t(Args...)> func, 
	size_t argA, size_t argB,
	double rating,
	const std::set<Opcode> &avaliableOpcode,
	const std::vector<funcRand> &funcRand, 
	std::function<bool(std::uint32_t, std::uint32_t)> funcCheck,
	std::index_sequence<I...>)
{
	static const std::map<Opcode, size_t> opPenalty = {
		{Move, 0}, 
		{Not, 1}, {Neg, 2}, {LogNot, 1},
		{Add, 2}, {Sub, 2}, 
		{Multu, 4}, {Divu, 64}, {Modu, 64},
		{And, 1}, {Or, 1}, {Xor, 1},
		{Shl, 1}, {Shr, 1},
		{Seq, 2}, {Sne, 2}, {Sgt, 2}, {Sge, 2}, {Slt, 2}, {Sle, 2},
		{Branch, 1},
		{Jump, 0}
	};

	std::cout << "Testing " << name << ": " << std::endl;

	std::vector<std::uint32_t> args(sizeof...(Args));
	

	try
	{
		Program program(in);
		if (!program.checkOp(avaliableOpcode))
		{
			std::cout << "\tForbidden Operation" << std::endl << std::endl;
			return 0;
		}
		program.setInsnLimit(100000);
		program.setOpPenalty(opPenalty);

		const int times = 10;
		size_t penalty = 0;
		size_t cntInsn = 0;
		for (int i = 0; i < times; i++)
		{
			for (size_t i = 0; i < funcRand.size(); i++)
				args[i] = funcRand[i]();
			for (size_t i = funcRand.size(); i < args.size(); i++)
				args[i] = default_rand();

			std::uint32_t result = program.run(args);
			std::uint32_t ans = func(args[I]...);

			std::cout << std::dec << "\t#" << i + 1 << ": ( ";
			for (auto i : args)
				std::cout /*<< std::hex*/ << i << " ";
			std::cout << ") result=" << result << ", ans=" << ans << std::endl;
			//std::cout << std::dec;

			bool correct = false;
			if (funcCheck)
				correct = funcCheck(result, ans);
			else
				correct = result == ans;

			if (!correct)
			{
				std::cout << "\tWrong Answer" << std::endl << std::endl;
				return 0;
			}

			cntInsn += program.getInsnCount();
			penalty += program.getPenalty();
		}

		double score;

		if (penalty <= argA * times)
			score = rating;
		else if (penalty >= argB * times)
			score = 0.1 * rating;
		else
			score = 0.1 * rating + double(argB * times - penalty) / (argB * times - argA * times) * 0.9 * rating;

		std::cout << "\tPASS" << std::endl;
		std::cout << "\tAvg. Instruction: " << cntInsn / 10.0 << std::endl;
		std::cout << "\tAvg. Penalty: " << penalty / 10.0 << std::endl;
		std::cout << "\tScore: " << score << std::endl;
		std::cout << std::endl;
		
		return score;
	}
	catch (std::exception &e)
	{
		std::cout << "\tRuntime Error: " << e.what() << std::endl << std::endl;
		return 0;
	}
}

template<typename ...Args>
double judge(
	std::istream &in,
	const std::string &name,
	std::function<std::uint32_t(Args...)> func,
	size_t argA, size_t argB,
	double rating,
	const std::set<Opcode> &avaliableOpcode,
	const std::vector<funcRand> &funcRand = std::vector<std::function<std::uint32_t()>>(),
	std::function<bool(std::uint32_t, std::uint32_t)> funcCheck = std::function<bool(std::uint32_t, std::uint32_t)>())
{
	return judge_impl(in, name, func, argA, argB, rating, avaliableOpcode, funcRand, funcCheck,
		std::make_index_sequence<sizeof...(Args)>{});
}

template<typename ...Args>
double judge(
	std::istream &in,
	const std::string &name,
	std::uint32_t(*func)(Args...),
	size_t argA, size_t argB,
	double rating,
	const std::set<Opcode> &avaliableOpcode,
	const std::vector<funcRand> &funcRand = std::vector<std::function<std::uint32_t()>>(),
	std::function<bool(std::uint32_t, std::uint32_t)> funcCheck = std::function<bool(std::uint32_t, std::uint32_t)>())
{
	return judge(in, name, std::function<std::uint32_t(Args...)>(func), argA, argB, rating, avaliableOpcode, funcRand, funcCheck);
}

int main()
{
	std::istream &in = std::cin;

	double score = 0;

	const std::set<Opcode> basicOpcode = { Move, Not, LogNot, And, Or, Xor, Add, Shl, Shr };
	const std::set<Opcode> fullOpcode = { Move, Not, Neg, LogNot, Add, Sub, Multu, Divu, Modu, And, Or, Xor, Shl, Shr, Seq, Sne, Sgt, Sge, Slt, Sle, Branch, Jump };

	score += judge(in, "bitAnd", bitAnd, 4, 8, 1, { Move, Not, Or  });
	score += judge(in, "getByte", getByte, 3, 6, 2, basicOpcode, { default_rand, rand_range<0, 3> } );
	score += judge(in, "arithmeticShift", arithmeticShift, 10, 20, 6, basicOpcode, { default_rand, rand_range<0, 31> });
	score += judge(in, "bitCount", bitCount, 25, 128, 8, basicOpcode);
	score += judge(in, "bang", bang, 6, 24, 6, { Move, Not, And, Or, Xor, Add, Shl, Shr }, std::vector<funcRand>{ []() -> std::uint32_t {
		static bool zero = false;
		if (!zero)
		{
			zero = true;
			return 0;
		}
		return default_rand();
	}});
	score += judge(in, "divpwr2", divpwr2, 16, 32, 6, basicOpcode, { default_rand, rand_range<0, 30> });
	score += judge(in, "negate", negate, 3, 6, 1, basicOpcode);
	score += judge(in, "isPositive", isPositive, 5, 10, 4, basicOpcode, std::vector<funcRand>{ []() -> std::uint32_t {
		static bool zero = false;
		if (!zero)
		{
			zero = true;
			return 0;
		}
		return default_rand();
	}});

	int same = 0;
	std::uint32_t tmp = default_rand();
	auto rand_tmp = [&same, tmp]() -> std::uint32_t
	{
		if (same < 2)
		{
			same++;
			return tmp;
		}
		return default_rand();
	};
	score += judge(in, "isLessOrEqual", isLessOrEqual, 15, 36, 6, basicOpcode, { rand_tmp, rand_tmp });
	score += judge(in, "ilog2", ilog2, 32, 100, 8, basicOpcode, std::vector<funcRand>{ []() -> std::uint32_t {
		std::uniform_real_distribution<double> dist(1, 31);
		double result = exp2(dist(gen)) - 1;
		return std::uint32_t(result);
	}});
	score += judge(in, "float_neg", float_neg, 6, 20, 6, fullOpcode, std::vector<funcRand>{ []() -> std::uint32_t {
		static bool nan = false;
		float result;
		if (!nan)
		{
			nan = true;
			result = NAN;
		}
		else
		{
			std::uniform_real_distribution<float> dist(-1e10f, 1e10f);
			result = dist(gen);
		}
		return *reinterpret_cast<std::uint32_t *>(&result);
	}});
	score += judge(in, "float_i2f", float_i2f, 50, 150, 8, fullOpcode);
	score += judge(in, "float_twice", float_twice, 15, 90, 8, fullOpcode, std::vector<funcRand>{ []() -> std::uint32_t
	{
		static bool nan = false;
		if (!nan)
		{
			nan = true;
			float tmp = NAN;
			return *reinterpret_cast<std::uint32_t *>(&tmp);
		}
		return default_rand();
	}});
	score += judge(in, "float_sqrt", float_sqrt, 300, 2000, 15, fullOpcode, std::vector<funcRand>{ []() -> std::uint32_t {
		std::uniform_real_distribution<float> dist(0, 1e6);
		float result = dist(gen);
		return *reinterpret_cast<std::uint32_t *>(&result);
	}}, [](std::uint32_t result, std::uint32_t ans) {
		const float eps = 1e-3f;
		float fresult = *reinterpret_cast<float *>(&result);
		float fans = *reinterpret_cast<float *>(&ans);
		return fabs(fans - fresult) < eps * fresult;
	});

	const std::int32_t divisors[] = { -1926, 2017, 817 };
	for (std::int32_t divisor : divisors)
	{
		score += judge(in, "divide_" + std::to_string(divisor), 
			std::function<std::uint32_t(std::uint32_t)>(std::bind(divide, std::placeholders::_1, divisor)),
			10, 72, 5, fullOpcode);
	}

	std::cout << "Final Score: " << score << std::endl;
	return 0;
}