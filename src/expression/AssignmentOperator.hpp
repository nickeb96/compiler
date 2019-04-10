
#ifndef AssignmentOperator_hpp
#define AssignmentOperator_hpp

#include "BinaryOperator.hpp"


class AssignmentOperator: public BinaryOperator, public RValue
{
public:
    AssignmentOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("=")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~AssignmentOperator() = default;

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = true;

        if (withParenthesis)
            rtn += "(";

        rtn += m_left->toString(false) + " " + m_operator + " " + m_right->toString(false);

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const;
};

#endif

