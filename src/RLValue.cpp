
#include "expression/RValue.hpp"
#include "expression/LValue.hpp"

#include "expression/Expression.hpp"



RValue::~RValue()
{
}

void RValue::rValueGenCode(std::ostream& os) const
{
    dynamic_cast<const Expression*>(this)->assembly(os);
}

std::ostream& operator <<(std::ostream& os, RValue const& rvalue)
{
    rvalue.rValueGenCode(os);
    return os;
}


LValue::~LValue()
{
}

void LValue::rValueGenCode(std::ostream& os) const
{
    dynamic_cast<const Expression*>(this)->assembly(os);
    os << "movq (%rax), %rax" << std::endl;
}

std::ostream& operator <<(std::ostream& os, LValue const& lvalue)
{
    dynamic_cast<Expression const&>(lvalue).assembly(os);
    return os;
}

