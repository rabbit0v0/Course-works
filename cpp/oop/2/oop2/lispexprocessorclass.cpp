#include "lispexprocessorclass.hpp"

//Here is nothing for you to actually write, but please cons-
//ider why the variable is declared in this source file inst-
//ead of in the header file?

LisPeXProcessorClass LisPeXProcessor;



LisPeXProcessorClass::LisPeXProcessorClass()
{
    /*
     * Implement an appropriate construction function to initia-
     * lize the function transmission table.
     */
    table["define"] = new ProcessorTitleDeclarer("define", *this);
    table["document"] = new ProcessorDocument();
    table["align"] = new ProcessorAlign();
    table["section"] = new ProcessorSection();
    table["subsection"] = new ProcessorSubsection();
    table["subsubsection"] = new ProcessorSubsubsection();
    table["textbf"] = new ProcessorTextbf();
    table["newparagraph"] = new ProcessorParagraph();
    table["endpage"] = new ProcessorNewpage();
    table["endline"] = new ProcessorNextline();
    
}

void LisPeXProcessorClass::append_expr(const std::string & expr)
{
    int pos = 0;
    while (pos < expr.length())
    {
        switch (expr[pos])
        {
        case '(':
            ++pos;
            lexeme.push_back(Token({left_b, ""}));
	    break;
        case ')':
            ++pos;
            lexeme.push_back(Token({right_b, ""}));
	    break;
        case '\"':
            ++pos;
            lexeme.push_back(get_literal(expr, pos));
	    break;
        case ' ': case '\t':
            ++pos;
	    break;
        default:
            lexeme.push_back(get_identifier(expr, pos));
        }
    }
}
void print_package_ref(ostream & fout)
{
    fout << "\\documentclass[12pt, a4paper]{article}" << endl
         << "\\usepackage{ctex}" << endl
         << "\\usepackage{amsmath}" << endl
         << "\\usepackage{amsfonts}" << endl
         << "\\usepackage{latexsym}" << endl
         << "\\usepackage[margin=1in]{geometry}" << endl
         << "\\usepackage{color}" << endl
         << "\\definecolor{bgGray}{RGB}{36, 36, 36}" << endl
         << "\\usepackage{supertabular}" << endl
         << "\\usepackage{fontspec}" << endl
         << "\\newfontfamily\\courier{Courier}" << endl
         << "\\usepackage{xcolor}" << endl;
}
string LisPeXProcessorClass::evaluate(ostream & fout, int & pos)
{
    deque<string> arg;
    if (pos >= lexeme.size())
	return "";
    switch (lexeme[pos].type)
    {
    case left_b:
        return evaluate(fout, ++pos);
	break;
    case identifier: {
		string _title = lexeme[pos++].value;
        while (pos < lexeme.size() && lexeme[pos].type != right_b)
            arg.push_back(evaluate(fout, pos));
        while (pos < lexeme.size() && lexeme[pos].type == right_b)
            ++pos;
		return table[_title] -> proc(fout, arg);
    } break;
    case literal:
        return lexeme[pos++].value;
	break;
    case right_b:
        return "";
	break;
    }
    throw std::exception();
}

LisPeXProcessorClass::Token LisPeXProcessorClass::get_identifier(const std::string & expr, int & pos)
{
    Token ret_v;
    ret_v.type = identifier;
    string & val(ret_v.value);
    bool cont = true;
    while (pos < expr.length() && cont)
    {
        switch (expr[pos])
        {
        case  '\"': case ' ': case '\t':
            cont = false; ++pos;
	    break;
        case '(': case ')':
            cont = false;
	    break;
        default:
            val += expr[pos++];
        }
    }
    return ret_v;
}

LisPeXProcessorClass::Token LisPeXProcessorClass::get_literal(const std::string & expr, int & pos)
{
    Token ret_v;
    ret_v.type = literal;
    string & val(ret_v.value);
    bool cont = true;
    while (pos < expr.length() && cont)
    {
        switch (expr[pos])
        {
        case '\\':
            ++pos;
            switch (expr[pos])
            {
            case 't':
                val += '\t';
		break;
            case 'n':
                val += '\n';
		break;
            case '\\': case '\'': case '\"':
                val += expr[pos];
		break;
            }
            ++pos;
	    break;
        case  '\"':
            cont = false; ++pos;
	    break;
        default:
            val += expr[pos++];
        }
    }
    return ret_v;
}

void LisPeXProcessorClass::compile(std::istream & fin, std::ostream & fout)
{
    print_package_ref(fout);
    string ins;
    while (!fin.eof())
    {
        getline(fin, ins);
        append_expr(ins);
    }
    int pos = 0;
    //for (auto i = lexeme.begin(); i != lexeme.end(); ++i) std::cerr << *i << endl;
    while (pos < lexeme.size())
	fout << evaluate(fout, pos);
}
