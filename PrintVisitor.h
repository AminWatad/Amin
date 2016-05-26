#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include <stack>
#include <string>
#include <sstream>
#include "iterator.h"
#include "composite.h"
using namespace std;

class Op;

class Visitor {
    public:
        Visitor();
        virtual void rootNode() = 0; //For visiting a root node (donothing)
        virtual void sqrNode() = 0; //For visiting a square node
        virtual void multNode() = 0; //For visiting a multiple node
        virtual void subNode() = 0; //For visiting a subtraction node
        virtual void addNode() = 0; //For visiting an add node
        virtual void opNode(Op* op) = 0; //For visiting a leaf node
        virtual void execute() = 0; //Prints all visited nodes
};

class PrintVisitor : public Visitor{
    private:
        string output;
    public:
        PrintVisitor();
        void rootNode();
        void sqrNode();
        void multNode();
        void subNode();
        void addNode();
        void opNode(Op* op);
        void execute();
};

#endif