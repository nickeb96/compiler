
#include "SourceFile.hpp"

#include <list>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <deque>

#include "statement/all.hpp"
#include "expression/all.hpp"
#include "expression/RawToken.hpp"



// forward decl
Expression* tokenListToTree(std::list<Expression*> tokens, Statement* parentStatement);



SourceFile::SourceFile()
{
    m_labelCount = 0;
}

SourceFile::~SourceFile()
{
}

std::string SourceFile::getNewLabel() const
{
    ++m_labelCount;
    return "L" + std::to_string(m_labelCount);
}

void parseLeaves(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->isIdentifier())
            {
                delete *iter;
                *iter = new IdentifierExpression(token->toString(), parentStatement);
            }
            else if (token->isIntegerLiteral())
            {
                delete *iter;
                *iter = new IntegerLiteral(token->toString());
            }
        }
    }
}

// All of the parsing functions discriminate between unary and binary operators
// of the same character (i.e. * for deref and * for multiplication) by checking
// the elements next to the operator to see if they are raw tokens or already
// parsed expressions.

void parsePostfixOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "(")
            {
                auto before = iter;
                --before;
                if (dynamic_cast<Expression*>(*before))
                {
                    Expression* left = dynamic_cast<Expression*>(*before);
                    tokens.erase(before);
                    FunctionCallOperator* func = new FunctionCallOperator(left);
                    delete *iter;
                    *iter = func;

                    ++iter;

                    std::list<Expression*> argument;
                    while (true)
                    {
                        if ((*iter)->toString() == ")")
                        {
                            if (!argument.empty())
                                func->appendArgument(tokenListToTree(std::move(argument), parentStatement));
                            delete *iter;
                            break;
                        }
                        else if ((*iter)->toString() == ",")
                        {
                            func->appendArgument(tokenListToTree(std::move(argument), parentStatement));
                            delete *iter;
                            ++iter;
                        }
                        else
                        {
                            argument.push_back(*iter);
                            iter = tokens.erase(iter);
                        }
                    }
                    tokens.erase(iter--);
                }
            }
            else if (token->toString() == "[")
            {
                std::cerr << "I have no idea how to parse subscript operators yet" << std::endl;
            }
        }
    }
}

void parseUnaryOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = --tokens.end(); iter != --tokens.begin(); --iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "-" || token->toString() == "&" || token->toString() == "*" || token->toString() == "!")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if ((iter == tokens.begin() || dynamic_cast<RawToken*>(*before)) && dynamic_cast<Expression*>(*after))
                {
                    Expression* right = dynamic_cast<Expression*>(*after);
                    tokens.erase(after);
                    delete *iter;
                    if (token->toString() == "-")
                    {
                        *iter = new NegationOperator(right);
                    }
                    else if (token->toString() == "&")
                    {
                        *iter = new AddressOfOperator(right);
                    }
                    else if (token->toString() == "*")
                    {
                        *iter = new DereferenceOperator(right);
                    }
                    else if (token->toString() == "!")
                    {
                        *iter = new NotOperator(right);
                    }
                }
            }
        }
    }
}

void parseMultiplicativeOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "*" || token->toString() == "/" || token->toString() == "%")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    if (token->toString() == "*")
                    {
                        delete *iter;
                        *iter = new MultiplicationOperator(left, right);
                    }
                    else if (token->toString() == "/")
                    {
                        delete *iter;
                        *iter = new DivisionOperator(left, right);
                    }
                    else if (token->toString() == "%")
                    {
                        delete *iter;
                        *iter = new ModuloOperator(left, right);
                    }
                }
            }
        }
    }
}

void parseAdditiveOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "+" || token->toString() == "-")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    if (token->toString() == "+")
                    {
                        delete *iter;
                        *iter = new AdditionOperator(left, right);
                    }
                    else if (token->toString() == "-")
                    {
                        delete *iter;
                        *iter = new SubtractionOperator(left, right);
                    }
                }
            }
        }
    }
}

void parseComparisonOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "<" || token->toString() == ">" || token->toString() == "<=" || token->toString() == ">=")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    delete *iter;
                    if (token->toString() == "<")
                    {
                        *iter = new LessThanOperator(left, right);
                    }
                    else if (token->toString() == ">")
                    {
                        *iter = new GreaterThanOperator(left, right);
                    }
                    else if (token->toString() == "<=")
                    {
                        *iter = new LessThanEqualOperator(left, right);
                    }
                    else if (token->toString() == ">=")
                    {
                        *iter = new GreaterThanEqualOperator(left, right);
                    }
                }
            }
        }
    }
}

void parseEqualityOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "==" || token->toString() == "!=")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    delete *iter;
                    if (token->toString() == "==")
                    {
                        *iter = new EqualityOperator(left, right);
                    }
                    else if (token->toString() == "!=")
                    {
                        *iter = new InequalityOperator(left, right);
                    }
                }
            }
        }
    }
}


void parseLogicalOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "&&")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    delete *iter;
                    auto temp = new AndOperator(left, right);
                    temp->setParentStatement(parentStatement);
                    *iter = temp;
                }
            }
        }
    }
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "||")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    delete *iter;
                    auto temp = new OrOperator(left, right);
                    temp->setParentStatement(parentStatement);
                    *iter = temp;
                }
            }
        }
    }
}

void parseAssignmentOperators(std::list<Expression*>& tokens, Statement* parentStatement)
{
    for (auto iter = --tokens.end(); iter != --tokens.begin(); --iter)
    {
        RawToken* token = dynamic_cast<RawToken*>(*iter);
        if (token)
        {
            if (token->toString() == "=")
            {
                auto before = iter;
                auto after = iter;
                --before;
                ++after;
                if (dynamic_cast<Expression*>(*before) && dynamic_cast<Expression*>(*after))
                {
                    Expression* left(dynamic_cast<Expression*>(*before));
                    Expression* right(dynamic_cast<Expression*>(*after));
                    tokens.erase(before);
                    tokens.erase(after);
                    delete *iter;
                    *iter = new AssignmentOperator(left, right);
                }
            }
        }
    }
}

Expression* tokenListToTree(std::list<Expression*> tokens, Statement* parentStatement)
{
    // go through and look for parenthesies here, recursively call this function to handle parenthesis,
    // replace first opening parenthesis to last closing parenthesis with return, create new RawToken list to pass

    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        auto before = iter;
        --before;
        if ((*iter)->toString() == "(" && (iter == tokens.begin() || (dynamic_cast<RawToken*>(*before) && !dynamic_cast<RawToken*>(*before)->isIdentifier())))
        {
            std::list<Expression*> parenthesizedExpression;
            auto start = iter;
            auto finish = iter;
            --iter;
            int parenthesesDepth = 1;
            while (parenthesesDepth > 0)
            {
                ++finish;
                if ((*finish)->toString() == ")")
                {
                    --parenthesesDepth;
                }
                else if ((*finish)->toString() == "(")
                {
                    ++parenthesesDepth;
                }
            }
            start = tokens.erase(start);
            finish = tokens.erase(finish);
            parenthesizedExpression.splice(parenthesizedExpression.begin(), tokens, start, finish);
            ++iter;
            tokens.insert(iter, tokenListToTree(std::move(parenthesizedExpression), parentStatement));
            --iter;
        }
    }

    std::cerr << "tokenListToTree's tokens:" << std::endl;
    for (auto const& each : tokens)
    {
        std::cerr << each->toString() << std::endl;
    }

    parseLeaves(tokens, parentStatement);
    parsePostfixOperators(tokens, parentStatement);
    parseUnaryOperators(tokens, parentStatement);
    parseMultiplicativeOperators(tokens, parentStatement);
    parseAdditiveOperators(tokens, parentStatement);
    parseComparisonOperators(tokens, parentStatement);
    parseEqualityOperators(tokens, parentStatement);
    parseLogicalOperators(tokens, parentStatement);
    parseAssignmentOperators(tokens, parentStatement);

    if (tokens.size() != 1)
    {
        std::cerr << "***Something bad happened in tokenListToTree" << std::endl;
        std::cerr << "***the number of expressions after tokenization was not 1" << std::endl;
        std::cerr << "***it was " << tokens.size() << std::endl;
        std::cerr << "***here they are" << std::endl;
        for (auto const& each : tokens)
        {
            std::cerr << each->toString() << " | " << typeid(*each).name() << std::endl;
        }
    }

    return dynamic_cast<Expression*>(tokens.front());
}


Statement* parseStatement(std::deque<std::string>& tokens, Statement* parentStatement);


SingleStatement* parseSingleStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    SingleStatement* singleStatement = new SingleStatement(parentStatement);
    std::list<Expression*> tokenList;

    while (!tokens.empty())
    {
        if (tokens.front() == ";")
        {
            tokens.pop_front();
            break;
        }
        else
        {
            tokenList.push_back(new RawToken(tokens.front()));
            tokens.pop_front();
        }
    }

    singleStatement->setExpression(tokenListToTree(tokenList, singleStatement));

    return singleStatement;
}

BlockStatement* parseBlockStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    BlockStatement* blockStatement = new BlockStatement(parentStatement);

    tokens.pop_front(); // pop "{"

    while (true)
    {
        if (tokens.front() == "}")
            break;

        blockStatement->appendStatement(parseStatement(tokens, blockStatement));
    }

    tokens.pop_front(); // pop "}"

    return blockStatement;
}

IfElseStatement* parseIfElseStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    IfElseStatement* ifElseStatement = new IfElseStatement(parentStatement);
    std::list<Expression*> tokenList;

    tokens.pop_front(); // pop "if" token

    //new stuff

    int depth = 0;

    do
    {
        if (tokens.front() == "(")
            depth += 1;
        else if (tokens.front() == ")")
            depth -= 1;
        tokenList.push_back(new RawToken(tokens.front()));
        tokens.pop_front();
    } while (depth > 0);

    //end of new stuff

/* vv what i had before vv

    tokens.pop_front(); // (
    while (tokens.front() != ")")
    {
        tokenList.push_back(new RawToken(tokens.front()));
        tokens.pop_front();
    }
    tokens.pop_front(); // )
    */


    ifElseStatement->setCondition(tokenListToTree(std::move(tokenList), ifElseStatement));
    ifElseStatement->setIfBody(parseStatement(tokens, ifElseStatement));

    if (tokens.front() == "else")
    {
        tokens.pop_front(); // pop "else" token
        ifElseStatement->setElseBody(parseStatement(tokens, ifElseStatement));
    }
    else
    {
        ifElseStatement->setElseBody(new NopStatement(ifElseStatement));
    }

    return ifElseStatement;
}

WhileStatement* parseWhileStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    WhileStatement* whileStatement = new WhileStatement(parentStatement);
    std::list<Expression*> tokenList;

    tokens.pop_front(); // pop "while" token

    int depth = 0;
    do
    {
        if (tokens.front() == "(")
            depth += 1;
        else if (tokens.front() == ")")
            depth -= 1;
        tokenList.push_back(new RawToken(tokens.front()));
        tokens.pop_front();
    } while (depth > 0);

    whileStatement->setCondition(tokenListToTree(std::move(tokenList), whileStatement));
    whileStatement->setLoopBody(parseStatement(tokens, whileStatement));

    return whileStatement;
}

BreakStatement* parseBreakStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    BreakStatement* breakStatement = new BreakStatement(parentStatement);

    tokens.pop_front(); // pop "break" token
    tokens.pop_front(); // pop ;

    return breakStatement;
}

ContinueStatement* parseContinueStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    ContinueStatement* continueStatement = new ContinueStatement(parentStatement);

    tokens.pop_front(); // pop continue
    tokens.pop_front(); // pop ;

    return continueStatement;
}

VariableDefStatement* parseVariableDefStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    VariableDefStatement* variableDef = new VariableDefStatement(parentStatement);

    tokens.pop_front(); // pop primitive
    variableDef->m_name = tokens.front();
    tokens.pop_front(); // pop name
    std::cerr << "THIS SHOULD BE A SEMICOLON -> " << tokens.front() << std::endl;
    tokens.pop_front(); // ;
    std::cerr << "THIS SHOULD BE THE START OF THE NEXT STATEMENT -> " << tokens.front() << std::endl;

    return variableDef;
}

Statement* parseStatement(std::deque<std::string>& tokens, Statement* parentStatement)
{
    Statement* rtn = nullptr;

    std::cerr << "parsing statement with tokens: ";
    for (std::string token : tokens)
    {
        std::cerr << token << " | ";
    }
    std::cerr << std::endl;

    if (tokens.front() == "quad") // variable declaration
    {
        std::cerr << "calling parseVariableDefStatement" << std::endl;
        rtn = parseVariableDefStatement(tokens, parentStatement);
    }
    else if (tokens.front() == "{") // block statement
    {
        std::cerr << "calling parseBlockStatement" << std::endl;
        rtn = parseBlockStatement(tokens, parentStatement);
    }
    else if (tokens.front() == "if") // if else statement
    {
        std::cerr << "calling parseVariableDefStatement" << std::endl;
        rtn = parseIfElseStatement(tokens, parentStatement);
    }
    else if (tokens.front() == "while")
    {
        rtn = parseWhileStatement(tokens, parentStatement);
    }
    else if (tokens.front() == "break")
    {
        rtn = parseBreakStatement(tokens, parentStatement);
    }
    else if (tokens.front() == "continue")
    {
        rtn = parseContinueStatement(tokens, parentStatement);
    }
    else // single statement
    {
        std::cerr << "calling parseSingleStatement" << std::endl;
        rtn = parseSingleStatement(tokens, parentStatement);
    }

    return rtn;
}


void SourceFile::makeAbstractSyntaxTree(std::istream& input)
{
    std::deque<std::string> tokens;

    while (true)
    {
        std::string temp;
        input >> temp;
        if (!input)
            break;
        tokens.push_back(temp);
    }

    std::cerr << "done tokenizing" << std::endl;

    while (!tokens.empty())
    {
        if (tokens.front() == "void")
        {
            FunctionDefStatement* functionDef = new FunctionDefStatement();
            functionDef->m_sourceFile = this;

            tokens.pop_front(); // void
            functionDef->m_name = tokens.front();

            std::cerr << "working on function \"" << functionDef->m_name << "\"" << std::endl;

            tokens.pop_front(); // fname
            tokens.pop_front(); // (

            while (tokens.front() != ")") // func ( quad a , quad b ) { ...
            {
                std::deque<std::string> tokenList;
                while (tokens.front() != "," && tokens.front() != ")")
                {
                    tokenList.push_back(tokens.front());
                    tokens.pop_front();
                }
                tokenList.push_back(";");
                functionDef->m_parameters.push_back(parseVariableDefStatement(tokenList, functionDef));
                if (tokens.front() == ",")
                {
                    tokens.pop_front();
                }
            }

            tokens.pop_front(); // )

            functionDef->m_body = dynamic_cast<BlockStatement*>(parseStatement(tokens, functionDef));
            std::cerr << "Turning AST back into C source code:" << std::endl;
            std::cerr << functionDef->toString() << std::endl;
            for (auto in : functionDef->m_parameters)
            {
                std::cerr << in->m_stackFrameOffset << std::endl;
            }
            m_functions.push_back(functionDef);
        }
    }
}

void SourceFile::genAssembly(std::ostream& output)
{
    this->assembly(output);
}

