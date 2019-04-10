
#ifndef DivisionOperator_hpp
#define DivisionOperator_hpp

#include "BinaryOperator.hpp"


class DivisionOperator: public BinaryOperator, public RValue
{
public:
    DivisionOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("/")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~DivisionOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

