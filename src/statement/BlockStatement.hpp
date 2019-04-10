
#ifndef BlockStatement_hpp
#define BlockStatement_hpp

#include "Statement.hpp"


class BlockStatement: public Statement
{
public:
    BlockStatement(Statement* p_parentStatement);
    virtual ~BlockStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

    std::vector<Statement*> const& getStatementList() const;
    void appendStatement(Statement* p_statement);

public: // change back to protected
    std::vector<Statement*> m_statements;
    int m_startingStackSize;
};

#endif

