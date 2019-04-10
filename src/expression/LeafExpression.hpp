
#ifndef LeafExpression_hpp
#define LeafExpression_hpp

#include "Expression.hpp"


class LeafExpression: public Expression
{
protected:
    virtual ~LeafExpression() = default;

public:
    virtual std::string toString(tribool withParenthesis = indeterminate) const = 0;
    virtual void assembly(std::ostream& os) const = 0;
};

#endif

