
#ifndef FunctionDefStatement_hpp
#define FunctionDefStatement_hpp

#include <vector>

#include "Statement.hpp"
#include "BlockStatement.hpp"
#include "VariableDefStatement.hpp"

class SourceFile;


class FunctionDefStatement: public Statement
{
public:
    FunctionDefStatement();
    virtual ~FunctionDefStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

    void setBody(Statement* body);

public: // change back to protected
    std::string m_name;
    std::vector<VariableDefStatement*> m_parameters;
    std::string m_returnType;
    BlockStatement* m_body;
    SourceFile* m_sourceFile;
};

#endif

