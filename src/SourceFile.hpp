
#ifndef SourceFile_hpp
#define SourceFile_hpp

#include <vector>
#include <stack>
#include <memory>

#include "statement/FunctionDefStatement.hpp"


class SourceFile
{
public:
    SourceFile();
    ~SourceFile();
    void assembly(std::ostream& os) const;
    void makeAbstractSyntaxTree(std::istream& input);
    void genAssembly(std::ostream& output);
    std::string getNewLabel() const;

public:
    std::vector<FunctionDefStatement*> m_functions;
    mutable int m_labelCount;
    std::stack<std::string> m_breakLabels;
    std::stack<std::string> m_continueLabels;
};

#endif

