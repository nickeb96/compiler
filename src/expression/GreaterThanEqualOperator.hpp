
#ifndef GreaterThanEqualOperator_hpp
#define GreaterThanEqualOperator_hpp

#include "BinaryOperator.hpp"


class GreaterThanEqualOperator: public BinaryOperator, public RValue
{
public:
    GreaterThanEqualOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator(">=")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~GreaterThanEqualOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

