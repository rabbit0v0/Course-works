#ifndef LISPEXPROCESSORCLASS_HPP
#define LISPEXPROCESSORCLASS_HPP
#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
using std::istream;
using std::ostream;
using std::unordered_map;
using std::string;
using std::deque;
#define endl '\n'
class LisPeXProcessorClass;
extern LisPeXProcessorClass LisPeXProcessor;

class LisPeXProcessorClass
{
public:
    enum TokenType
    {
        // "(", ")"    ,  func name, const str
        left_b, right_b, identifier, literal
    };

    struct Token
    {
        TokenType type;
        string value;
        friend ostream & operator<<(ostream & fout, const Token & opt)
        {
            switch (opt.type)
            {
            case left_b:
                fout << "<left bracket>";
            break;
            case right_b:
                fout << "<right bracket>";
            break;
            case identifier:
                fout << "<identifier " << opt.value << ">";
            break;
            case literal:
                fout << "<literal \"" << opt.value << "\">";
            break;
            }
            return fout;
        }
    };
    
private:
    class ProcessorBase
    {
	/* Is there supposed to be something? */
    protected:
        string title = "";
    public:
        ProcessorBase(const string & _title)
            :title(_title)/*Initialization list shall be correctly defined here.*/
        {}
        virtual string proc(ostream & fout, deque<string> & arg) = 0;
        virtual ~ProcessorBase(){}
    };
    //Declarations of processors.
    class ProcessorPairedStructure;
	class ProcessorUnpairedStructure;
    class ProcessorTitleDeclarer;

    /*
     * Give the correct definition of the p-
     * rocessor classes.
     * You are required to implement the vi-
     * rtual member function for a non-abst-
     * ract class.
     * Both classes are derived from Proces-
     * sorBase.
     * For paired structure, the output for-
     * mat shall be like this:
     * \begin{<title string>}
     * ......(parameter strings)
     * \end{<title string>}
     * For unpaired structure, the output f-
     * ormat shall be like this:
     * \<title string>{parameterstring1}{pa-
     * rameterstring2}...
     *
     */
    class ProcessorPairedStructure :public ProcessorBase /* Inheritance shall be correctly defined here. */
    {
    public:
        ProcessorPairedStructure(const string & _title)
            :ProcessorBase(_title) /* Initialization list shall be correctly defined here.*/
        {
            /*Do we need to write something here?*/
        }
        string proc(ostream & fout, deque<string> & arg)
        {
            string q = "\\begin{";
            q += title;
            q += "}\n";
            int i = 0;
            while (i < arg.size()){
                q += arg[i];
                q += "\n";
                ++i;
            }
            q += "\\end{";
            q += title;
            q += "}\n";
            return q;
            /* Implement the processing function for paired structure.
             * Format:
             * \begin{title}
             * para1
             * para2
             * para3
             * para4
             * ......
             * \end{title}
             */
        }
    };
    class ProcessorUnpairedStructure :public ProcessorBase /* Inheritance shall be correctly defined here. */
    {
    public:
        ProcessorUnpairedStructure(const string & _title)
            :ProcessorBase(_title) /* Initialization list shall be correctly defined here.*/
        {
            /*Do we need to write something here?*/
        }
        string proc(ostream & fout, deque<string> & arg)
        {
            string q = "\\";
            q += title;
            int i = 0;
            while (i < arg.size()){
                q += "{";
                q += arg[i];
                q += "}";
                i++;
            }
            q += "\n";
            return q;
            /* Implement the processing function for paired structure.
             * Format:
             * \title{para1}{para2}......
             */
        }
    };
    class ProcessorTitleDeclarer : public ProcessorBase /* Inheritance shall be correctly defined here. */
    {
        LisPeXProcessorClass & LisPeXProcessor;
    public:
        ProcessorTitleDeclarer(const string & _title, LisPeXProcessorClass & _LisPeXProcessor)
            : ProcessorBase(_title), LisPeXProcessor(_LisPeXProcessor)/* Initialization list shall be correctly defined here.*/
        {}
        string proc(ostream & fout, deque<string> & arg)
        {
            //Consider why we can do this.
            //This will help you to finish the job.
            if (arg[0] == "paired")
                LisPeXProcessor.table[arg[1]] = new ProcessorPairedStructure(arg[1]);
            else
                LisPeXProcessor.table[arg[1]] = new ProcessorUnpairedStructure(arg[1]);
            return "";
        }
    };
    friend class ProcessorTitleDeclarer;
    deque<Token> lexeme;
    unordered_map<string, ProcessorBase *> table;
    string evaluate(ostream & fout, int & pos);
    Token get_identifier(const string & expr, int & pos);
    Token get_literal(const string & expr, int & pos);
public:
    LisPeXProcessorClass();
    void append_expr(const string & expr);
    void compile(istream & fin, ostream & fout);
 
    
    class ProcessorDocument : public ProcessorPairedStructure
    {
    public:
        ProcessorDocument()
        :ProcessorPairedStructure("document")
        {}
    };
  
    class ProcessorAlign : public ProcessorPairedStructure
    {
    public:
        ProcessorAlign()
        :ProcessorPairedStructure("align")
        {}
    };
    
    class ProcessorSection : public ProcessorUnpairedStructure
    {
    public:
        ProcessorSection()
        :ProcessorUnpairedStructure("section")
        {}
    };
    
    class ProcessorSubsection : public ProcessorUnpairedStructure
    {
    public:
        ProcessorSubsection()
        :ProcessorUnpairedStructure("subsection")
        {}
    };
    
    class ProcessorSubsubsection : public ProcessorUnpairedStructure
    {
    public:
        ProcessorSubsubsection()
        :ProcessorUnpairedStructure("subsubsection")
        {}
    };
    
    class ProcessorTextbf : public ProcessorUnpairedStructure
    {
    public:
        ProcessorTextbf()
        :ProcessorUnpairedStructure("textbf")
        {}
    };
    
    class ProcessorParagraph : public ProcessorUnpairedStructure
    {
    public:
        ProcessorParagraph()
        :ProcessorUnpairedStructure("par")
        {}
        
    };
    
    class ProcessorNewpage : public ProcessorUnpairedStructure
    {
    public:
        ProcessorNewpage()
        :ProcessorUnpairedStructure("newpage")
        {}
    };
    
    class ProcessorNextline : public ProcessorUnpairedStructure
    {
    public:
        ProcessorNextline()
        :ProcessorUnpairedStructure("\\")
        {}
    };
    
    ~LisPeXProcessorClass(){
        unordered_map<string, ProcessorBase*> :: iterator l;
        l = table.begin();
        while (l != table.end()){
            delete l++ -> second;
        }
    }
};

#endif // LISPEXPROCESSORCLASS_HPP

    