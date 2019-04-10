
#ifndef SingleStatement_hpp
#define SingleStatement_hpp

#include "Statement.hpp"
#include "../expression/Expression.hpp"


class SingleStatement: public Statement
{
public:
    SingleStatement(Statement* p_parentStatement);
    virtual ~SingleStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

    void setExpression(Expression* expression);

protected:
    Expression* m_expression;
};

#endif

