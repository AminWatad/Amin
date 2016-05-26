#include "PrintVisitor.h"

Visitor::Visitor()
{
}

PrintVisitor::PrintVisitor()
{
}

void PrintVisitor::rootNode()
{
}

void PrintVisitor::sqrNode()
{
    output += "^2 ";
}
void PrintVisitor::multNode()
{
    output += "* ";
}
void PrintVisitor::subNode()
{
    output += "- ";
}
void PrintVisitor::addNode()
{
    output += "+ ";
}
void PrintVisitor::opNode(Op* op)
{
    ostringstream s;
    s << op->evaluate();
    output += s.str();
    output += " ";
}
void PrintVisitor::execute()
{
    cout << output << endl;
}