
#ifndef MultiplicationOperator_hpp
#define MultiplicationOperator_hpp

#include "BinaryOperator.hpp"


class MultiplicationOperator: public BinaryOperator, public RValue
{
public:
    MultiplicationOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("*")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~MultiplicationOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

