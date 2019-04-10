
#ifndef ContinueStatement_hpp
#define ContinueStatement_hpp

#include "Statement.hpp"

class SourceFile;


class ContinueStatement: public Statement
{
public:
    ContinueStatement(Statement* parentStatement);
    virtual ~ContinueStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

protected:
    SourceFile* m_sourceFile;
};

#endif

