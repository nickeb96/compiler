
#ifndef IfElseStatement_hpp
#define IfElseStatement_hpp

#include "ControlStatement.hpp"


class IfElseStatement: public ControlStatement
{
public:
    IfElseStatement(Statement* parentStatement);
    virtual ~IfElseStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

    void setIfBody(Statement* body);
    void setElseBody(Statement* body);

protected:
    Statement* m_ifBody;
    Statement* m_elseBody;
};

#endif

