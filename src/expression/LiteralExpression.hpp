
#ifndef LiteralExpression_hpp
#define LiteralExpression_hpp

#include "LeafExpression.hpp"


class LiteralExpression: public LeafExpression
{
protected:
    LiteralExpression(std::string const& p_str = "")
    {
        m_str = p_str;
    }

public:
    virtual ~LiteralExpression() = default;

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_str;

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const = 0;

protected:
    std::string m_str;
};

#endif

