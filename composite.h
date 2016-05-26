#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <sstream>
#include <math.h>
#include <string>
#include "iterator.h"
#include "PrintVisitor.h"
using namespace std;

class Iterator;
class NullIterator;
class OperatorIterator;
class UnaryIterator;
class Visitor;

//Abstract Base Class
class Base {
    public:
        Base(){};

        //virtual
        virtual void print() = 0;
        virtual double evaluate() = 0;
        virtual Iterator* create_iterator() = 0;
        virtual Base* get_left() = 0;
        virtual Base* get_right() = 0;
        virtual void accept(Visitor* visit) = 0;
};

//Leaf Class
class Op: public Base {
    private:
        double value;

    public:
        Op();
        Op(double val);

        Base* get_left();
        Base* get_right();
        double evaluate();
        void accept(Visitor* visit);
        void print();
        Iterator* create_iterator();
};

//Composite Base Classes
class Operator: public Base {
    protected:
        Base* left, *right;
    public:
        Operator();
        Operator(Base* l, Base* r);

        Base* get_left();
        Base* get_right();
        virtual void accept(Visitor* visit) = 0;
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
        Iterator* create_iterator();
};

class UnaryOperator: public Base {
    protected:
        Base* child;
    public:
        UnaryOperator();
        UnaryOperator(Base* c);

        Base* get_left();
        Base* get_right();
        virtual void accept(Visitor* visit) = 0;
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
        Iterator* create_iterator();
};

//Composite Classes
class Add: public Operator {
    public:
        Add();
        Add(Base* left, Base* right);
        void accept(Visitor* visit);
        void print();
        double evaluate();
};

class Sub: public Operator {
    public:
        Sub();
        Sub(Base* left, Base* right);
        void accept(Visitor* visit);
        void print();
        double evaluate();
};

class Mult: public Operator {
    public:
        Mult();
        Mult(Base* left, Base* right);
        void accept(Visitor* visit);
        void print();
        double evaluate();
};

class Sqr: public UnaryOperator {
    public:
        Sqr();
        Sqr(Base* child);
        void accept(Visitor* visit);
        void print();
        double evaluate();
};

class Root: public UnaryOperator {
    public:
        Root();
        Root(Base* root);
        void accept(Visitor* visit);
        void print();
        double evaluate();
};

#endif
