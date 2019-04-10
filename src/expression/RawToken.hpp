
#ifndef RawToken_hpp
#define RawToken_hpp

#include <cctype>
#include <cassert>

#include "Expression.hpp"


class RawToken: public Expression
{
public:
    RawToken(std::string const& p_token = "")
    {
        m_token = p_token;
    }

    virtual ~RawToken() = default;

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        return m_token;
    }

    virtual void assembly(std::ostream& os) const
    {
        assert("CANNOT GENERATE ASSEMBLY FROM RAW TOKEN");
    }

    bool isIntegerLiteral() const
    {
        for (int i = 0; i < m_token.length(); ++i)
        {
            if (!std::isdigit(m_token[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool isIdentifier() const
    {
        for (int i = 0; i < m_token.length(); ++i)
        {
            if (!std::isalpha(m_token[i]) && m_token[i] != '_')
            {
                return false;
            }
        }
        return true;
    }

    bool isOperator() const
    {
        return m_token == "*" || m_token == "+" || m_token == "=";
    }

protected:
    std::string m_token;
};

#endif

