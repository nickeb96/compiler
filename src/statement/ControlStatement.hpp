
#ifndef ControlStatement_hpp
#define ControlStatement_hpp

#include "Statement.hpp"

class SourceFile;


class ControlStatement: public Statement
{
public:
    ControlStatement(Statement* parentStatement);
    virtual ~ControlStatement();
    virtual std::string toString(int depth = 0) const = 0;
    virtual void assembly(std::ostream& os) const = 0;

    void setCondition(Expression* expression);

protected:
    Expression* m_condition;
    SourceFile* m_sourceFile;
};

#endif

