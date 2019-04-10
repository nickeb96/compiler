
#ifndef NotOperator_hpp
#define NotOperator_hpp

#include "UnaryOperator.hpp"


class NotOperator: public UnaryOperator, public RValue
{
public:
    NotOperator(Expression* p_right = nullptr):
    UnaryOperator("-")
    {
        m_right = p_right;
    }

    virtual ~NotOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

