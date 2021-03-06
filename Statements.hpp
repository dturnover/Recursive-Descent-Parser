#ifndef EXPRINTER_STATEMENTS_HPP
#define EXPRINTER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "Expr.hpp"
#include "SymTab.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement
{
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements
{
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement
{
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
};

class PrintStatement : public Statement
{
public:
  PrintStatement(std::vector <ExprNode *> testList);
  
  virtual void evaluate(SymTab &symTab);
  virtual void print();
private:
  std::vector <ExprNode *> _testList;
  std::vector <TypeDescriptor *> v; 
};

class ForStatement : public Statement
{
public:
  ForStatement();
  ForStatement(std::vector <ExprNode *> testList, Statements *block, std::string varName);
  
  virtual void evaluate(SymTab &symTab);
  virtual void print();
private:
  std::string _varName;
  std::string _rString;
  std::vector <ExprNode *> _testList;
  Statements *_block;
};

class IfStatement : public Statement
{
public:
  IfStatement(std::vector <ExprNode *> testList, std::vector <Statements *> blocks);

  virtual void evaluate(SymTab &symTab);
  virtual void print();
private:
  std::vector <ExprNode *> _testList;
  std::vector <Statements *> _blocks;
};

class Range {
public:
  Range(int rangeValue);
  Range(int initValue, int rangeValue);
  Range(int initValue, int rangeValue, int stepValue);

  bool condition();
  int stepValue();
  int next();

private:
  int _initValue, _stepValue, _rangeValue;
};

#endif //EXPRINTER_STATEMENTS_HPP

