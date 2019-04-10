
#ifndef OperatorExpression_hpp
#define OperatorExpression_hpp

#include "Expression.hpp"


class OperatorExpression: public Expression
{
protected:
    OperatorExpression(std::string const& p_operator):
    m_operator(p_operator)
    {
    }

public:
    virtual ~OperatorExpression() = default;
    virtual std::string toString(tribool withParenthesis = indeterminate) const = 0;
    virtual void assembly(std::ostream& os) const = 0;

protected:
    const std::string m_operator;
};

#endif

