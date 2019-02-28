#ifndef DATALAB_VM_H
#define DATALAB_VM_H

#include <stack>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>


enum Opcode : std::uint32_t
{
	Move,
	Not, Neg, LogNot,
	Add, Sub,
	Multu,
	Divu, Modu,
	And, Or, Xor,
	Shl, Shr,
	Seq, Sne, Sgt, Sge, Slt, Sle,
	Branch,
	Jump,

	Label
};

template<typename Key, typename Value>
std::unordered_map<Value, Key> reverse_map(const std::unordered_map<Key, Value> &map)
{
	std::unordered_map<Value, Key> ret;
	for (auto &kv : map)
		ret[kv.second] = kv.first;
	return ret;
}

static const std::unordered_map<std::uint32_t, std::string> opcode2str = {
	{ Move,	"mov" },
	{ Not,	"not" },
	{ Neg,	"neg" },
	{ LogNot, "lognot" },
	{ Add,	"add" },
	{ Sub,	"sub" },
	{ Multu,	"mul" },
	{ Divu,	"div" },
	{ Modu,	"mod" },
	{ And,	"and" },
	{ Or,	"or" },
	{ Xor,	"xor" },
	{ Shl,	"shl" },
	{ Shr,	"shr" },
	{ Seq,	"seq" },
	{ Sne,	"sne" },
	{ Sgt,	"sgt" },
	{ Sge,	"sge" },
	{ Slt,	"slt" },
	{ Sle,	"sle" },
	{ Branch, "br" },
	{ Jump,	"j" },
};
static const std::unordered_map<std::string, std::uint32_t> str2opcode = reverse_map(opcode2str);

struct Operand
{
	enum { Reg, Imm } type;
	std::uint32_t val;
};

inline Operand Reg(std::uint32_t id) { return Operand{ Operand::Reg, id }; }
inline Operand Imm(std::uint32_t imm) { return Operand{ Operand::Imm, imm }; }

inline std::ostream &operator<<(std::ostream &out, Operand operand)
{
	if (operand.type == Operand::Reg)
		out << "$" << operand.val;
	else
		out << std::int32_t(operand.val);
	return out;
}
inline std::istream &operator>>(std::istream &in, Operand &operand)
{
	std::string str;
	in >> str;
	if (!str.empty() && str[0] == '$')
		operand = Reg(std::stoi(str.substr(1)));
	else
		operand = Imm(std::stoi(str));
	return in;
}

struct Instruction
{
	std::uint32_t dst;
	Opcode opcode;
	Operand src1, src2;

	Instruction() : dst(0), opcode(Move), src1(Reg(0)), src2(Reg(0)) {}
	Instruction(std::uint32_t dst, Opcode opcode, Operand src1) : dst(dst), opcode(opcode), src1(src1), src2(Reg(0)) {}
	Instruction(std::uint32_t dst, Opcode opcode, Operand src1, Operand src2) : dst(dst), opcode(opcode), src1(src1), src2(src2) {}
};

inline std::string ins2str(const Instruction &insn)
{
	std::stringstream ss;
	ss << opcode2str.find(insn.opcode)->second << "\t" << Reg(insn.dst) << " " << insn.src1 << " " << insn.src2;
	return ss.str();
}
inline Instruction str2ins(const std::string &str)
{
	Instruction insn;
	std::stringstream ss(str);
	std::string opcode;
	Operand dst;
	ss >> opcode >> dst >> insn.src1 >> insn.src2;
	insn.dst = dst.val;
	insn.opcode = Opcode(str2opcode.find(opcode)->second);
	return insn;
}

static std::stack<std::list<Instruction>> stkInsn;

inline void newInsn(Instruction insn)
{
	stkInsn.top().push_back(insn);
}

static std::uint32_t total;
static std::uint32_t cntLabel;

class Integer
{
	template<typename ...Args, std::size_t ...I>
	friend void compile_impl(std::ostream &out, std::function<Integer(Args...)> func, std::index_sequence<I...>);

public:
	Integer() : id(++total) {}
	Integer(const Integer &other) : id(++total) { newInsn(Instruction(id, Move, Reg(other.id))); }
	Integer(std::uint32_t other) : id(++total) { newInsn(Instruction(id, Move, Imm(other))); }

	Integer &operator=(const Integer &rhs)
	{
		if (this == &rhs)
			return *this;
		newInsn(Instruction(id, Move, Reg(rhs.id)));
		return *this;
	}
	Integer &operator=(std::uint32_t rhs)
	{
		newInsn(Instruction(id, Move, Imm(rhs)));
		return *this;
	}
	Integer operator~() const { return Integer(Instruction(0, Not, Reg(id))); }
	Integer operator-() const { return Integer(Instruction(0, Neg, Reg(id))); }
	Integer operator!() const { return Integer(Instruction(0, LogNot, Reg(id))); }

	Integer &operator++() { return OpAssignBinary(Add, 1); }
	Integer  operator++(int)
	{
		Integer ret(Instruction(0, Move, Reg(id)));
		OpAssignBinary(Add, 1);
		return ret;
	}
	Integer &operator--() { return OpAssignBinary(Sub, 1); }
	Integer  operator--(int)
	{
		Integer ret(Instruction(0, Move, Reg(id)));
		OpAssignBinary(Sub, 1);
		return ret;
	}

	Integer  operator+ (const Integer &rhs) const { return OpBinary(Add, rhs); }
	Integer  operator+ (std::uint32_t rhs)  const { return OpBinary(Add, rhs); }
	Integer &operator+=(const Integer &rhs) { return OpAssignBinary(Add, rhs); }
	Integer &operator+=(std::uint32_t rhs) { return OpAssignBinary(Add, rhs); }

	Integer  operator- (const Integer &rhs) const { return OpBinary(Sub, rhs); }
	Integer  operator- (std::uint32_t rhs)  const { return OpBinary(Sub, rhs); }
	Integer &operator-=(const Integer &rhs) { return OpAssignBinary(Sub, rhs); }
	Integer &operator-=(std::uint32_t rhs) { return OpAssignBinary(Sub, rhs); }

	Integer  operator* (const Integer &rhs) const { return OpBinary(Multu, rhs); }
	Integer  operator* (std::uint32_t rhs)  const { return OpBinary(Multu, rhs); }
	Integer &operator*=(const Integer &rhs) { return OpAssignBinary(Multu, rhs); }
	Integer &operator*=(std::uint32_t rhs) { return OpAssignBinary(Multu, rhs); }

	Integer  operator/ (const Integer &rhs) const { return OpBinary(Divu, rhs); }
	Integer  operator/ (std::uint32_t rhs)  const { return OpBinary(Divu, rhs); }
	Integer &operator/=(const Integer &rhs) { return OpAssignBinary(Divu, rhs); }
	Integer &operator/=(std::uint32_t rhs) { return OpAssignBinary(Divu, rhs); }

	Integer  operator% (const Integer &rhs) const { return OpBinary(Modu, rhs); }
	Integer  operator% (std::uint32_t rhs)  const { return OpBinary(Modu, rhs); }
	Integer &operator%=(const Integer &rhs) { return OpAssignBinary(Modu, rhs); }
	Integer &operator%=(std::uint32_t rhs) { return OpAssignBinary(Modu, rhs); }

	Integer  operator& (const Integer &rhs) const { return OpBinary(And, rhs); }
	Integer  operator& (std::uint32_t rhs)  const { return OpBinary(And, rhs); }
	Integer &operator&=(const Integer &rhs) { return OpAssignBinary(And, rhs); }
	Integer &operator&=(std::uint32_t rhs) { return OpAssignBinary(And, rhs); }

	Integer  operator| (const Integer &rhs) const { return OpBinary(Or, rhs); }
	Integer  operator| (std::uint32_t rhs)  const { return OpBinary(Or, rhs); }
	Integer &operator|=(const Integer &rhs) { return OpAssignBinary(Or, rhs); }
	Integer &operator|=(std::uint32_t rhs) { return OpAssignBinary(Or, rhs); }

	Integer  operator^ (const Integer &rhs) const { return OpBinary(Xor, rhs); }
	Integer  operator^ (std::uint32_t rhs)  const { return OpBinary(Xor, rhs); }
	Integer &operator^=(const Integer &rhs) { return OpAssignBinary(Xor, rhs); }
	Integer &operator^=(std::uint32_t rhs) { return OpAssignBinary(Xor, rhs); }

	Integer  operator<< (const Integer &rhs) const { return OpBinary(Shl, rhs); }
	Integer  operator<< (std::uint32_t rhs)  const { return OpBinary(Shl, rhs); }
	Integer &operator<<=(const Integer &rhs) { return OpAssignBinary(Shl, rhs); }
	Integer &operator<<=(std::uint32_t rhs) { return OpAssignBinary(Shl, rhs); }

	Integer  operator>> (const Integer &rhs) const { return OpBinary(Shr, rhs); }
	Integer  operator>> (std::uint32_t rhs)  const { return OpBinary(Shr, rhs); }
	Integer &operator>>=(const Integer &rhs) { return OpAssignBinary(Shr, rhs); }
	Integer &operator>>=(std::uint32_t rhs) { return OpAssignBinary(Shr, rhs); }

	Integer operator==(const Integer &rhs) const { return OpBinary(Seq, rhs); }
	Integer operator==(std::uint32_t rhs)  const { return OpBinary(Seq, rhs); }

	Integer operator!=(const Integer &rhs) const { return OpBinary(Sne, rhs); }
	Integer operator!=(std::uint32_t rhs)  const { return OpBinary(Sne, rhs); }

	Integer operator> (const Integer &rhs) const { return OpBinary(Sgt, rhs); }
	Integer operator> (std::uint32_t rhs)  const { return OpBinary(Sgt, rhs); }

	Integer operator< (const Integer &rhs) const { return OpBinary(Slt, rhs); }
	Integer operator< (std::uint32_t rhs)  const { return OpBinary(Slt, rhs); }

	Integer operator>=(const Integer &rhs) const { return OpBinary(Sge, rhs); }
	Integer operator>=(std::uint32_t rhs)  const { return OpBinary(Sge, rhs); }

	Integer operator<=(const Integer &rhs) const { return OpBinary(Sle, rhs); }
	Integer operator<=(std::uint32_t rhs)  const { return OpBinary(Sle, rhs); }

public:
	const std::uint32_t id;

private:
	Integer(Instruction insn) : id(++total)
	{
		insn.dst = id;
		newInsn(insn);
	}
	struct tag_setid {};
	Integer(std::uint32_t id, tag_setid) : id(id) { total = std::max(total, id); }

	Integer OpBinary(Opcode opcode, const Integer &rhs) const
	{
		return Integer(Instruction(0, opcode, Reg(id), Reg(rhs.id)));
	}
	Integer OpBinary(Opcode opcode, std::uint32_t rhs) const
	{
		return Integer(Instruction(0, opcode, Reg(id), Imm(rhs)));
	}
	Integer &OpAssignBinary(Opcode opcode, const Integer &rhs)
	{
		newInsn(Instruction(id, opcode, Reg(id), Reg(rhs.id)));
		return *this;
	}
	Integer &OpAssignBinary(Opcode opcode, std::uint32_t rhs)
	{
		newInsn(Instruction(id, opcode, Reg(id), Imm(rhs)));
		return *this;
	}
};


inline void if_(Integer cond, std::function<void()> bodyIf, std::function<void()> bodyElse = std::function<void()>())
{
	std::list<Instruction> insnIf, insnElse;
	stkInsn.emplace();
	bodyIf();
	insnIf = std::move(stkInsn.top());
	stkInsn.pop();
	if (bodyElse)
	{
		stkInsn.emplace();
		bodyElse();
		insnElse = std::move(stkInsn.top());
		stkInsn.pop();
	}

	std::uint32_t labelIf = ++cntLabel, labelEnd = ++cntLabel;

	newInsn(Instruction(0, Branch, Reg(cond.id), Imm(labelIf)));
	stkInsn.top().splice(stkInsn.top().end(), insnElse);
	newInsn(Instruction(0, Jump, Imm(labelEnd)));
	newInsn(Instruction(0, Label, Imm(labelIf)));
	stkInsn.top().splice(stkInsn.top().end(), insnIf);
	newInsn(Instruction(0, Label, Imm(labelEnd)));
}

struct loopInfo
{
	std::uint32_t labelContinue;
	std::uint32_t labelBreak;
};
static std::stack<loopInfo> stkLoopInfo;

inline void while_(std::function<Integer()> cond, std::function<void()> body)
{
	std::list<Instruction> insnCond, insnBody;

	std::uint32_t labelBody = ++cntLabel;
	std::uint32_t labelContinue = ++cntLabel, labelBreak = ++cntLabel;
	stkLoopInfo.push({ labelContinue, labelBreak });

	stkInsn.emplace();
	std::uint32_t condID = cond().id;
	insnCond = std::move(stkInsn.top());
	stkInsn.pop();

	stkInsn.emplace();
	body();
	insnBody = std::move(stkInsn.top());
	stkInsn.pop();

	stkLoopInfo.pop();

	newInsn(Instruction(0, Jump, Imm(labelContinue)));
	newInsn(Instruction(0, Label, Imm(labelBody)));
	stkInsn.top().splice(stkInsn.top().end(), insnBody);
	newInsn(Instruction(0, Label, Imm(labelContinue)));
	stkInsn.top().splice(stkInsn.top().end(), insnCond);
	newInsn(Instruction(0, Branch, Reg(condID), Imm(labelBody)));
	newInsn(Instruction(0, Label, Imm(labelBreak)));
}

inline void break_()
{
	newInsn(Instruction(0, Jump, Imm(stkLoopInfo.top().labelBreak)));
}

inline void continue_()
{
	newInsn(Instruction(0, Jump, Imm(stkLoopInfo.top().labelContinue)));
}

inline void removeLabel()
{
	std::vector<std::uint32_t> label2addr(cntLabel + 1);

	std::uint32_t curAddr = 0;
	for (auto iter = stkInsn.top().begin(); iter != stkInsn.top().end(); )
	{
		if (iter->opcode == Label)
		{
			label2addr[iter->src1.val] = curAddr;
			iter = stkInsn.top().erase(iter);
		}
		else
		{
			++curAddr;
			++iter;
		}
	}

	curAddr = 0;
	for (auto &insn : stkInsn.top())
	{
		if (insn.opcode == Jump)
			insn.src1 = Imm(label2addr[insn.src1.val] - (curAddr + 1));
		else if (insn.opcode == Branch)
			insn.src2 = Imm(label2addr[insn.src2.val] - (curAddr + 1));

		++curAddr;
	}
}

template<typename ...Args, std::size_t ...I>
void compile_impl(std::ostream &out, std::function<Integer(Args...)> func, std::index_sequence<I...>)
{
	while (!stkInsn.empty())
		stkInsn.pop();
	stkInsn.emplace();

	while (!stkLoopInfo.empty())
		stkLoopInfo.pop();

	cntLabel = 0;
	total = 0;

	std::uint32_t result = func(Integer(I + 1, Integer::tag_setid{})...).id;

	removeLabel();

	for (size_t i = 0; i < sizeof...(Args); i++)
		out << "input $" << i + 1 << std::endl;
	out << "output $" << result << std::endl;
	out << "begin" << std::endl;
	for (auto &insn : stkInsn.top())
		out << "\t" << ins2str(insn) << std::endl;
	out << "end" << std::endl;
}

template<typename ...Args>
void compile(std::ostream &out, std::function<Integer(Args...)> func)
{
	compile_impl(out, func, std::make_index_sequence<sizeof...(Args)>{});
}

class Program
{
public:
	class invalid_program : public std::exception
	{
	public:
		virtual const char *what() const noexcept override
		{
			return "Invalid Program";
		}
	};

	class runtime_error : public std::exception
	{
	public:
		runtime_error(const std::string &description) : description("Runtime Error: " + description) {}

		virtual const char *what() const noexcept override
		{
			return description.c_str();
		}

	protected:
		std::string description;
	};

public:
	Program(std::istream &in) : maxInsn(SIZE_MAX)
	{
		std::string line;
		bool flag = false;
		while (std::getline(in, line))
		{
			line = removeBlank(line);
			if (line.empty())
				continue;

			if (flag)
			{
				if (line == "end")
					return;
				insns.push_back(str2ins(line));
			}
			else
			{
				if (line == "begin")
					flag = true;
				else
				{
					std::string directive, argument;
					std::stringstream ss(line);
					ss >> directive >> argument;
					if (directive == "input" && !argument.empty() && argument[0] == '$')
					{
						input.push_back(std::stoi(argument.substr(1)));
					}
					else if (directive == "output" && !argument.empty() && argument[0] == '$')
					{
						output = std::stoi(argument.substr(1));
					}
					else
					{
						throw invalid_program();
					}
				}
			}
		}
		throw invalid_program();
	}

	void setInsnLimit(size_t limit) { maxInsn = limit; }
	bool checkOp(const std::set<Opcode> &avaliableOp)
	{
		for (auto &insn : insns)
		{
			if (!avaliableOp.count(insn.opcode))
				return false;
		}
		return true;
	}

	void setOpPenalty(std::map<Opcode, size_t> mapPenalty)
	{
		opPenalty = std::move(mapPenalty);
	}

	size_t getInsnCount() const { return cntInsn; }
	size_t getPenalty() const { return penalty; }

	std::uint32_t run(const std::vector<std::uint32_t> &args)
	{
		const std::uint32_t limitID = 100000;

		std::uint32_t maxID = output;
		for (std::uint32_t i : input)
			maxID = std::max(maxID, i);
		for (auto &insn : insns)
		{
			maxID = std::max(maxID, insn.dst);
			if (insn.src1.type == Operand::Reg)
				maxID = std::max(maxID, insn.src1.val);
			if (insn.src2.type == Operand::Reg)
				maxID = std::max(maxID, insn.src2.val);
		}

		if (maxID > limitID)
			throw runtime_error("Too many registers");

		reg.resize(maxID + 1);
		PC = 0;

		if (args.size() != input.size())
			throw runtime_error("Argument not match");

		for (size_t i = 0; i < args.size(); i++)
			reg[input[i]] = args[i];

		cntInsn = 0;
		penalty = 0;

		while (PC < insns.size())
		{
			if (cntInsn >= maxInsn)
				throw runtime_error("Instruction Limit Exceeded");
			penalty += opPenalty[insns[PC].opcode];
			execute(insns[PC]);
			++PC;
			++cntInsn;
		}

		return reg[output];
	}

protected:

	std::uint32_t getOperand(Operand operand)
	{
		if (operand.type == Operand::Reg)
			return reg[operand.val];
		else
			return operand.val;
	}

	void execute(const Instruction &insn)
	{
		std::uint32_t src1 = getOperand(insn.src1);
		std::uint32_t src2 = getOperand(insn.src2);
		std::uint32_t &dst = reg[insn.dst];
		switch (insn.opcode)
		{
		case Move:
			dst = src1;
			break;
		case Not:
			dst = ~src1;
			break;
		case Neg:
			dst = -std::int32_t(src1);
			break;
		case LogNot:
			dst = !src1;
			break;
		case Add:
			dst = src1 + src2;
			break;
		case Sub:
			dst = src1 - src2;
			break;
		case Multu:
			dst = src1 * src2;
			break;
		case Divu:
			if (src2 == 0)
				throw runtime_error("Divided by zero");
			dst = src1 / src2;
			break;
		case Modu:
			if (src2 == 0)
				throw runtime_error("Divided by zero");
			dst = src1 % src2;
			break;
		case And:
			dst = src1 & src2;
			break;
		case Or:
			dst = src1 | src2;
			break;
		case Xor:
			dst = src1 ^ src2;
			break;
		case Shl:
			dst = src1 << src2;
			break;
		case Shr:
			dst = src1 >> src2;
			break;
		case Seq:
			dst = src1 == src2;
			break;
		case Sne:
			dst = src1 != src2;
			break;
		case Sgt:
			dst = src1 > src2;
			break;
		case Sge:
			dst = src1 >= src2;
			break;
		case Slt:
			dst = src1 < src2;
			break;
		case Sle:
			dst = src1 <= src2;
			break;
		case Branch:
			if (src1)
				PC += int32_t(src2);
			break;
		case Jump:
			PC += int32_t(src1);
			break;
		default:
			throw runtime_error("Invalid Instruction");
		}
	}

protected:
	static std::string removeBlank(const std::string &str)
	{
		std::string ret;
		for (char c : str)
		{
			if (c == '#')
				break;
			if (!ret.empty() || (c != ' ' && c != '\t'))
				ret.push_back(c);
		}
		while (!ret.empty() && (ret.back() == ' ' || ret.back() == '\t' || ret.back() == '\r' || ret.back() == '\n'))
			ret.pop_back();
		return ret;
	}


protected:
	std::vector<std::uint32_t> input;
	std::uint32_t output;
	std::vector<Instruction> insns;

	std::vector<std::uint32_t> reg;
	size_t PC;
	size_t maxInsn;

	std::map<Opcode, size_t> opPenalty;
	size_t penalty;
	size_t cntInsn;
};

#endif
