
#ifndef BinaryOperator_hpp
#define BinaryOperator_hpp

#include "OperatorExpression.hpp"


class BinaryOperator: public OperatorExpression
{
protected:
    BinaryOperator(std::string const& p_operator):
    OperatorExpression(p_operator)
    {
        m_left = nullptr;
        m_right = nullptr;
    }

public:
    virtual ~BinaryOperator()
    {
        delete m_left;
        delete m_right;
    }

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = true;

        if (withParenthesis)
            rtn += "(";

        rtn += m_left->toString() + " " + m_operator + " " + m_right->toString();

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const = 0;

protected:
    Expression* m_left;
    Expression* m_right;
};

#endif

