
#ifndef LessThanEqualOperator_hpp
#define LessThanEqualOperator_hpp

#include "BinaryOperator.hpp"


class LessThanEqualOperator: public BinaryOperator, public RValue
{
public:
    LessThanEqualOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("<=")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~LessThanEqualOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

