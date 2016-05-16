class  Iterator  {  
    protected :
        Base*self_ptr; 
        Base*current_ptr;

    public :
        Iterator  ( Base * ptr )  {  this ­> self_ptr  = ptr ; }
       
        /*Setsuptheiteratortostartatthebeginningoftraversal*/  
        virtual  void first ()  =  0;
            
        /*Moveontothenextelement*/  
        virtual  void  next ()  =  0;
       
        /*Returnsifyouhavefinishediteratingthroughallelements*/  
        virtual  bool is_done () =0;
             
        /*Returntheelementtheiteratoriscurrentlyat*/  
        virtual  Base * current()=0;
};

class NullIterator : public Iterator {
    public:
        NullIterator(Base* ptr);

        void first();
        void next();
        bool is_done() return true;
        Base* current() return NULL;
};

class PreOrderIterator : public Iterator {
    protected:
        stack<Iterator*> iterators;

    public:
        PreOrderIterator(Base* ptr);

        void first() {
            while (!iterators.empty()) iterators.pop();

            iterator* it = new iterator(Base* ptr);
            iterators.push(it);
        }
        void next() {
            Iterator* it = this->iterators.top();
            this->iterators.push(it);

            while (it.top()->is_done()) {
                it->pop();
            }
        }
            
        bool is_done() {
            if(iterators.empty()) return true;
            else return false;
        }
        Base* current() {
            return iterators.top();
        }

};
