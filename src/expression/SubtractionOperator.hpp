
#ifndef SubtractionOperator_hpp
#define SubtractionOperator_hpp

#include "BinaryOperator.hpp"


class SubtractionOperator: public BinaryOperator, public RValue
{
public:
    SubtractionOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("-")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~SubtractionOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

