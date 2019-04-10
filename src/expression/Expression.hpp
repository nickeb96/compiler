
#ifndef Expression_hpp
#define Expression_hpp

#include <ostream>
#include <boost/logic/tribool.hpp>
#include "RValue.hpp"
#include "LValue.hpp"

using namespace boost::logic;


class Expression
{
protected:
    Expression() = default;

public:
    virtual ~Expression() = default;
    virtual std::string toString(tribool withParentheses = indeterminate) const = 0;
    virtual void assembly(std::ostream& os) const = 0;
};

#endif

