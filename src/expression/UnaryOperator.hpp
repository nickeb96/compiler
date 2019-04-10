
#ifndef UnaryOperator_hpp
#define UnaryOperator_hpp

#include "OperatorExpression.hpp"


class UnaryOperator: public OperatorExpression
{
protected:
    UnaryOperator(std::string const& p_operator):
    OperatorExpression(p_operator)
    {
        m_right = nullptr;
    }

public:
    virtual ~UnaryOperator()
    {
        delete m_right;
    }

    virtual void assembly(std::ostream& os) const = 0;

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_operator + m_right->toString();

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

protected:
    Expression* m_right;
};

#endif

