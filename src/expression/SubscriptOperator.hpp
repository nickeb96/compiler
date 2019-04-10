
#ifndef SubscriptOperator_hpp
#define SubscriptOperator_hpp

#include "PostfixOperator.hpp"


class SubscriptOperator: public PostfixOperator, public LValue
{
public:
    SubscriptOperator(Expression* p_left = nullptr, Expression* p_index = nullptr):
    PostfixOperator("[]")
    {
        m_left = p_left;
        m_index = p_index;
    }

    virtual ~SubscriptOperator()
    {
        delete m_index;
    }

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_left->toString() + std::string("[") + m_index->toString() + std::string("]");

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const;

protected:
    Expression* m_index;
};

#endif

