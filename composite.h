#ifndef __COMPOSITE_CLASS__
#define __COMPOSITE_CLASS__

#include <iostream>
#include <sstream>
#include <math.h>
#include <string>
#include <stack>
using namespace std;

//Abstract Base Class
class Iterator;
class Base {
    public:
        Base(){};

        //virtual
        virtual void print() = 0;
        virtual double evaluate() = 0;
        virtual Iterator* create_iterator() = 0;
        virtual Base* get_left() = 0;
        virtual Base* get_right() = 0;
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
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
        Iterator* create_iterator();
};

//Composite Classes
class Add: public Operator {
    public:
        Add();
        Add(Base* left, Base* right);

        void print();
        double evaluate();
};

class Sub: public Operator {
    public:
        Sub();
        Sub(Base* left, Base* right);

        void print();
        double evaluate();
};

class Mult: public Operator {
    public:
        Mult();
        Mult(Base* left, Base* right);

        void print();
        double evaluate();
};

class Sqr: public UnaryOperator {
    public:
        Sqr();
        Sqr(Base* child);

        void print();
        double evaluate();
};

class Root: public UnaryOperator {
    public:
        Root();
        Root(Base* root);

        void print();
        double evaluate();
};

class Iterator {
    protected:
        Base* self_ptr;
        Base* current_ptr;
    public:
    Iterator(Base* ptr)
    {
        this->self_ptr = ptr;
    }
    /*Sets up the iterator to start at the beginning of traversal*/
    virtual void first() = 0;
    /*Move on to the next element*/
    virtual void next() = 0;
    /*Returns if you have finished iterating through all elements*/
    virtual bool is_done() = 0;
    /*Return the element the iterator is currently at*/
    virtual Base* current() = 0;
};

class OperatorIterator: public Iterator{
    public:
        OperatorIterator(Base* ptr);
        void first()
        {
            current_ptr = self_ptr->get_left();
        }
        void next()
        {
            if(current_ptr == self_ptr->get_left())
            {
                current_ptr = self_ptr->get_right();
            }
            else
            {
                current_ptr = NULL;
            }
        }
        bool is_done() {
            if(current_ptr == NULL)
            {
                return true;
            }
            return false;
        }
        Base* current()
        {
            return current_ptr;
        }
};

class UnaryIterator : public Iterator {
    public:
        UnaryIterator(Base* ptr);
        void first()
        {
            current_ptr = self_ptr->get_left();
        }
        void next()
        {
            current_ptr = NULL;
        }
        bool is_done()
        {
            if(this->current() == NULL)
            {
                return true;
            }
            return false;
        }
        Base* current()
        {
            return current_ptr;
        }
};

class NullIterator : public Iterator {
    public:
        NullIterator(Base* ptr);
        void first();
        void next();
        bool is_done()
        {
            return true;
        }
        Base* current() {
            return NULL;
        }
};

class PreOrderIterator : public Iterator {
    protected:
        stack<Iterator*> iterators;

    public:
        PreOrderIterator(Base* ptr);

        void first() {
            while (!iterators.empty()) iterators.pop();
            Iterator* it = new PreOrderIterator(this->current());
            iterators.push(it);
        }
        void next() {
            Iterator* it = this->iterators.top();
            this->iterators.push(it);

            while (iterators.top()->is_done()) {
                iterators.pop();
            }
        }
            
        bool is_done() {
            if(iterators.empty()) return true;
            else return false;
        }
        Base* current() {
            return iterators.top()->current();
        }

};

#endif //__COMPOSITE_CLASS__
