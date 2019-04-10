
#ifndef IdentifierExpression_hpp
#define IdentifierExpression_hpp

#include "LeafExpression.hpp"
#include "../statement/BlockStatement.hpp"
#include "../statement/VariableDefStatement.hpp"
#include "../statement/FunctionDefStatement.hpp"


class IdentifierExpression: public LeafExpression, public LValue
{
public:
    IdentifierExpression(std::string const& name, Statement* parentStatement)
    :m_name(name)
    {
        Statement* statement = parentStatement;
        BlockStatement* blockStatement;
        FunctionDefStatement* functionDef;
        bool found = false;

        while (statement)
        {
            if (blockStatement = dynamic_cast<BlockStatement*>(statement))
            {
                for (auto iter = blockStatement->getStatementList().rbegin(); iter != blockStatement->getStatementList().rend(); ++iter)
                {
                    VariableDefStatement* variableDef = dynamic_cast<VariableDefStatement*>(*iter);
                    if (variableDef && variableDef->m_name == m_name)
                    {
                        m_offset = variableDef->m_stackFrameOffset;
                        found = true;
                        break;
                    }
                }

                if (found)
                    break;
            }
            else if (functionDef = dynamic_cast<FunctionDefStatement*>(statement))
            {
                for (auto iter = functionDef->m_parameters.rbegin(); iter != functionDef->m_parameters.rend(); ++iter)
                {
                    if ((*iter)->m_name == m_name)
                    {
                        m_offset = (*iter)->m_stackFrameOffset;
                        found = true;
                        break;
                    }
                }
            }
            statement = statement->getParentStatement();
        }

        if (!found)
        {
        }
    }

    virtual ~IdentifierExpression() = default;

    virtual std::string toString(tribool withParenthesis = indeterminate) const
    {
        std::string rtn;

        if (indeterminate(withParenthesis))
            withParenthesis = false;

        if (withParenthesis)
            rtn += "(";

        rtn += m_name;

        if (withParenthesis)
            rtn += ")";

        return rtn;
    }

    virtual void assembly(std::ostream& os) const;

public: // change back to protected
    std::string m_name;
    int m_offset;
};

#endif

