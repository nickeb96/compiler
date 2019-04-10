
#ifndef NopStatement_hpp
#define NopStatement_hpp

#include "Statement.hpp"


class NopStatement: public Statement
{
public:
    NopStatement(Statement* parentStatement);
    virtual ~NopStatement() = default;
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;
};

#endif

