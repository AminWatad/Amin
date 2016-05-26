#include "composite.h"
//--------------------------------------------------------------------------
// Op Class
//--------------------------------------------------------------------------
Op::Op() : Base(), value(0){};
Op::Op(double val) : Base(), value(val){};

Base* Op::get_left() { return NULL; }
Base* Op::get_right() { return NULL; }
void Op::accept(Visitor* visit)
{
    visit->opNode(this);
}
void Op::print() {
    cout << this->value; 
}
double Op::evaluate() { 
    return this->value; 
};
Iterator* Op::create_iterator() { 
    return new NullIterator(this);
}

//--------------------------------------------------------------------------
// Operator Base Class
//--------------------------------------------------------------------------
Operator::Operator() : Base(){ };

Operator::Operator(Base* l, Base* r) : left(l), right(r){  };

Base* Operator::get_left() { return left; };

Base* Operator::get_right() { return right; };

Iterator* Operator::create_iterator() { 
    return new OperatorIterator(this);
}

//--------------------------------------------------------------------------
// Unary Base Class
//--------------------------------------------------------------------------
UnaryOperator::UnaryOperator() : Base(){};
UnaryOperator::UnaryOperator(Base* c) : child(c) { };

Base* UnaryOperator::get_left() { return child; }
Base* UnaryOperator::get_right() { return NULL; }
Iterator* UnaryOperator::create_iterator() { return new UnaryIterator(this); }

//--------------------------------------------------------------------------
// Add Class
//--------------------------------------------------------------------------
Add::Add() : Operator() { };
Add::Add(Base* left, Base* right) : Operator(left,right) { };

void Add::print() { cout << "+"; }
void Add::accept(Visitor* visit)
{
    visit->addNode();
}
double Add::evaluate() { return this->left->evaluate() + this->right->evaluate(); };

//--------------------------------------------------------------------------
// Sub Class
//--------------------------------------------------------------------------
Sub::Sub() : Operator() { };
Sub::Sub(Base* left, Base* right) : Operator(left,right) { };

void Sub::print() { cout << "-"; }
void Sub::accept(Visitor* visit)
{
    visit->subNode();
}
double Sub::evaluate() { return this->left->evaluate() - this->right->evaluate(); };

//--------------------------------------------------------------------------
// Mult Class
//--------------------------------------------------------------------------
Mult::Mult() : Operator() { };
Mult::Mult(Base* left, Base* right) : Operator(left,right) { };

void Mult::print() { cout << "*"; }
void Mult::accept(Visitor* visit)
{
    visit->multNode();
}
double Mult::evaluate() { return this->left->evaluate() * this->right->evaluate(); };

//--------------------------------------------------------------------------
// Sqr Class
//--------------------------------------------------------------------------
Sqr::Sqr() : UnaryOperator() { };
Sqr::Sqr(Base* child) : UnaryOperator(child) { };

void Sqr::print() { cout << "^2"; }
void Sqr::accept(Visitor* visit)
{
    visit->sqrNode();
}
double Sqr::evaluate() { return pow(this->child->evaluate(),2); };

//--------------------------------------------------------------------------
// Root Class
//--------------------------------------------------------------------------
Root::Root() : UnaryOperator() { };
Root::Root(Base* child) : UnaryOperator(child) { };

void Root::accept(Visitor* visit)
{
    visit->rootNode();
}
void Root::print() { cout << "ROOT"; }
double Root::evaluate() { return this->child->evaluate(); };