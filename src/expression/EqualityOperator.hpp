
#ifndef EqualityOperator_hpp
#define EqualityOperator_hpp

#include "BinaryOperator.hpp"


class EqualityOperator: public BinaryOperator, public RValue
{
public:
    EqualityOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("==")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~EqualityOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

