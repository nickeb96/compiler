
#ifndef PostfixOperator_hpp
#define PostfixOperator_hpp

#include "OperatorExpression.hpp"


class PostfixOperator: public OperatorExpression
{
protected:
    PostfixOperator(std::string const& p_operator):
    OperatorExpression(p_operator)
    {
        m_left = nullptr;
    }

public:
    virtual ~PostfixOperator()
    {
        delete m_left;
    }

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_left->toString() + m_operator;

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const = 0;

protected:
    Expression* m_left;
};

#endif

