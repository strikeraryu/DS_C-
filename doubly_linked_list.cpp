#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------------------------
/**------------------
 Doubly Linked list
 -----------------**/

template <typename Object>

class List
{
    private: 

        /**----------------------------
          
         Data- holds the value of current node
         prev- is a pointer which points to prev node 
         next- is a pointer which points to next node 

        ------------------------------**/
        struct Node
        {
            Object data;
            Node *prev;
            Node *next;
            Node(const Object &d = Object(), Node *p = NULL,Node *n = NULL): data( d ), prev( p ), next( n ) { };
        };

    public:

        // constant itrerator of LIST
        class const_iterator
        {
            public:
                const_iterator() : current( NULL ) {}

                const Object & operator* () const
                {   return retrieve();   }

                const_iterator & operator++ ()
                { 
                    current = current->next; 
                    return *this;
                }

                const_iterator operator++ ( int )
                {
                    const_iterator old = *this;
                    ++( *this );
                    return old;
                }

                bool operator== ( const const_iterator & rhs ) const
                {   return current==rhs.current;    }
                bool operator!= ( const const_iterator & rhs ) const
                {   return !( *this==rhs );    }


            protected:
                Node *current;    

                Object & retrieve() const
                {   return current->data;    }

                const_iterator( Node *p ) : current( p ){}

                friend class List<Object>;
        };

        // iterator of LIST
        class iterator
        {
            public:
                iterator( ) { }

                Object & operator* ( )
                {   return retrieve( );   }
                const Object & operator* ( ) const
                {   return const_iterator::operator* ( );   }

                iterator & operator++ ()
                { 
                    current = current->next; 
                    return *this;
                }

                iterator operator++ ( int )
                {
                    iterator old = *this;
                    ++( *this );
                    return old;
                }

                bool operator== ( const iterator & rhs ) const
                {   return current==rhs.current;    }
                bool operator!= ( const iterator & rhs ) const
                {   return !( *this==rhs );    }

                protected:
                    Node *current;    

                    Object & retrieve() const
                    {   return current->data;    }

                    iterator( Node *p ) : current( p ){ }

                    friend class List<Object>;

        };

    public: 

        // constructor to create a new empty LIST
        List()
        {   init(); }

        // contructor to create a new LIST a copy of passed list
        List(const List &rhs)
        {
            init();
            *this = rhs;
        }

        ~List()
        {
            clear();
            delete head;
        }

        // '=' operator overloading for LIST
        const List & operator= ( const List & rhs )
        {
            if( &rhs == this)
            return *this;
            clear();
            for(const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back( *itr );
            return *this;
        }

        // return a pointer of first node
        iterator begin( ){   return iterator( head->next );  }
        const_iterator begin( ) const{   return const_iterator( head->next );  }

        // return a pointer of tail node 
        iterator end( ){   return iterator( tail );  }
        const_iterator end( ) const{   return const_iterator( tail );  }

        // retrun the size of the list
        int size( ){ return theSize;    }
        // return if list is empty (i.e. size==0)
        bool empty( ){  return size( ) == 0;    }

        // removes every node holding a value
        void clear( )
        {
            while(!empty())
            pop_front();
        }

        // return a pointer of first node
        Object & front( ){  return *begin( );    }
        const Object & front( ) const{  return *begin( );    }

        // return a pointer of last node holding a value
        Object & back( ){  return *--end( );    }
        const Object & back( ) const{  return *--end( );    }

        // add a new node 
        void push_front( const Object & x ){    insert(begin( ), x ); }
        void push_back( const Object & x ){  insert( end( ), x );    }

        // remove a node
        void pop_front(){ erase( begin( ) ); }
        void pop_back(){ erase( end( ) ); }

        // to add a node at speicific location
        iterator insert( iterator itr, const Object & x ) 
        {
            Node *p = itr.current;
            theSize++;
            return  iterator( p->prev = p->prev->next = new Node( x, p->prev, p ));
        }

        // to remove a node at specific location 
        iterator erase( iterator itr )
        {
            Node *p = itr.current;
            iterator ret( p->next );
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            theSize--;

            return ret;
        }

        // to remove all node b/w two location
        iterator erase( iterator start_node, iterator end_node )
        {
            for( iterator itr = start_node; itr!=end_node; )
            itr = erase( itr );

            return end_node;

        }

    private:
        int theSize;
        Node *head;
        Node *tail;

        void init()
        {
            theSize = 0;
            head = new Node();
            tail = new Node();
            head->next = tail;
            tail->prev = head;
        }
};

//--------------------------------------------------------------------------------------------------------------