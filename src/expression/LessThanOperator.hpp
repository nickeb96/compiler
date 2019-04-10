
#ifndef LessThanOperator_hpp
#define LessThanOperator_hpp

#include "BinaryOperator.hpp"


class LessThanOperator: public BinaryOperator, public RValue
{
public:
    LessThanOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("<")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~LessThanOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

