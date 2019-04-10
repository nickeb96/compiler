
#ifndef IntegerLiteral_hpp
#define IntegerLiteral_hpp

#include "LiteralExpression.hpp"


class IntegerLiteral: public LiteralExpression, public RValue
{
public:
    IntegerLiteral(std::string const& p_str = ""):
    LiteralExpression(p_str)
    {
    }

    virtual ~IntegerLiteral() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

