
#ifndef AdditionOperator_hpp
#define AdditionOperator_hpp

#include "BinaryOperator.hpp"


class AdditionOperator: public BinaryOperator, public RValue
{
public:
    AdditionOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("+")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~AdditionOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

