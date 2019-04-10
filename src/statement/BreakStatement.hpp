
#ifndef BreakStatement_hpp
#define BreakStatement_hpp

#include "Statement.hpp"

class SourceFile;


class BreakStatement: public Statement
{
public:
    BreakStatement(Statement* parentStatement);
    virtual ~BreakStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

protected:
    SourceFile* m_sourceFile;
};

#endif

