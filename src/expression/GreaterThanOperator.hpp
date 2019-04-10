
#ifndef GreaterThanOperator_hpp
#define GreaterThanOperator_hpp

#include "BinaryOperator.hpp"


class GreaterThanOperator: public BinaryOperator, public RValue
{
public:
    GreaterThanOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator(">")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~GreaterThanOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

