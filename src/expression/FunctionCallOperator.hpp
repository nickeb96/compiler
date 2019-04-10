
#ifndef FunctionCallOperator_hpp
#define FunctionCallOperator_hpp

#include <vector>

#include "PostfixOperator.hpp"


class FunctionCallOperator: public PostfixOperator, public RValue
{
public:
    FunctionCallOperator(Expression* p_left = nullptr):
    PostfixOperator("()")
    {
        m_left = p_left;
    }

    virtual ~FunctionCallOperator()
    {
        for (Expression* expression : m_arguments)
        {
            delete expression;
        }
    }

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_left->toString(false) + "(";

        bool firstPass = true;
        for (Expression* expression : m_arguments)
        {
            if (!firstPass)
            {
                rtn += ", ";
            }
            firstPass = false;
            rtn += expression->toString(false);
        }

        rtn += ")";

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const;

    void appendArgument(Expression* expression)
    {
        m_arguments.push_back(expression);
    }

private:
    std::vector<Expression*> m_arguments;
};

#endif

