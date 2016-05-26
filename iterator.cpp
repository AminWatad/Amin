#include "iterator.h"

Iterator::Iterator(Base* ptr)
{
    this->self_ptr = ptr;
}

OperatorIterator::OperatorIterator(Base * ptr) : Iterator(ptr) { };

void OperatorIterator::first()
{
    current_ptr = self_ptr->get_left();
}


void OperatorIterator::next()
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
bool OperatorIterator::is_done() {
    if(current_ptr == NULL)
    {
        return true;
    }
    return false;
}
Base* OperatorIterator::current()
{
    return current_ptr;
}

void UnaryIterator::first()
{
    current_ptr = self_ptr->get_left();
}

UnaryIterator::UnaryIterator(Base * ptr) : Iterator(ptr) { };

void UnaryIterator::next()
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
bool UnaryIterator::is_done() {
    if(current_ptr == NULL)
    {
        return true;
    }
    return false;
}

Base* UnaryIterator::current()
{
    return current_ptr;
}

NullIterator::NullIterator(Base * ptr) : Iterator(ptr) { };

void NullIterator::first()
{
}

void NullIterator::next()
{
}

bool NullIterator::is_done()
{
    return true;
}
Base* NullIterator::current() {
    return NULL;
}

PreOrderIterator::PreOrderIterator(Base * ptr) : Iterator(ptr) { };

void PreOrderIterator::first() {
    while (!iterators.empty()) iterators.pop();
    Iterator* it = self_ptr->create_iterator();
    it->first();
    iterators.push(it);
}

void PreOrderIterator::next() {
    Iterator* it = this->iterators.top()->current()->create_iterator();
    it->first();
    this->iterators.push(it);
    while (this->iterators.size() > 0 && this->iterators.top()->is_done()) {
        iterators.pop();
        if(!iterators.empty())
        {
            this->iterators.top()->next();
        }
    }
}
    
bool PreOrderIterator::is_done() {
    if(iterators.empty()) return true;
    else return false;
}
Base* PreOrderIterator::current() {
    return iterators.top()->current();
}