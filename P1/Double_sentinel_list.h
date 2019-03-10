/*****************************************
 * UW User ID:  igianni
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
public:
    class Double_node {
    public:
        Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );
        
        Type value() const;
        Double_node *previous() const;
        Double_node *next() const;
        
        Type         node_value;
        Double_node *previous_node;
        Double_node *next_node;
    };
    
    Double_sentinel_list();
    Double_sentinel_list( Double_sentinel_list const & );
    Double_sentinel_list( Double_sentinel_list && );
    ~Double_sentinel_list();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    Type front() const;
    Type back() const;
    
    Double_node *begin() const;
    Double_node *end() const;
    Double_node *rbegin() const;
    Double_node *rend() const;
    
    Double_node *find( Type const & ) const;
    int count( Type const & ) const;
    
    // Mutators
    
    void swap( Double_sentinel_list & );
    Double_sentinel_list &operator=( Double_sentinel_list );
    Double_sentinel_list &operator=( Double_sentinel_list && );
    
    void push_front( Type const & );
    void push_back( Type const & );
    
    void pop_front();
    void pop_back();
    
    int erase( Type const & );
    
private:
    Double_node *list_head;
    Double_node *list_tail;
    int list_size;
    
    // List any additional private member functions you author here
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *hs = new Double_node;
    Double_node *ts = new Double_node;
    
    list_head = hs;
    hs->next_node = ts;
    hs->previous_node = nullptr;
    
    ts->previous_node = hs;
    ts->next_node = nullptr;
    list_tail = ts;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    if(list.size() == 0) {
        Double_node *hs = new Double_node;
        Double_node *ts = new Double_node;
        
        list_head = hs;
        hs->next_node = ts;
        hs->previous_node = nullptr;
        
        ts->previous_node = hs;
        ts->next_node = nullptr;
        list_tail = ts;
    }
    else {
        list_head = new Double_node(*list.rend());
        list_tail = new Double_node(*list.end());
        Double_node *curr = new Double_node;
        curr = list_head;
        list_head->next_node = curr;
        Double_node *trav =  new Double_node(*list.begin());
        for (int i = 0; i < list.list_size; i++) {
            Double_node *nn = new Double_node(*trav);
            curr->next_node = nn;
            nn->previous_node = curr;
            
            curr = nn;
            trav = trav->next_node;
            
            list_size += 1;
        }
        curr->next_node = list_tail;
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *hs = new Double_node;
    Double_node *ts = new Double_node;
    
    list_head = hs;
    hs->next_node = ts;
    hs->previous_node = nullptr;
    
    ts->previous_node = hs;
    ts->next_node = nullptr;
    list_tail = ts;
    
    swap(list);
    
    hs->next_node = ts;
    ts->previous_node = hs;
    list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    for (int i = 0; i < size(); i++) {
        pop_front();
    }
    delete list_head;
    list_head = nullptr;
    delete list_tail;
    list_tail = nullptr;
    list_size = 0;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    if (list_size == 0) {
        return true;
    }
    return false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    if (list_size == 0) {
        throw std::underflow_error("Underflow");
    }
    return list_head->next_node->value(); // This returns a default value of Type
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if (list_size == 0) {
        throw std::underflow_error("Underflow");
    }
    return list_tail->previous_node->value(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    return list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    return list_tail->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    Double_node *curr = new Double_node(front());
    for (int i = 0; i < list_size; i++) {
        if (curr->value() == obj) {
            std::cout << curr;
            return curr;
        }
        curr = curr->next();
    }
    std::cout << list_tail;
    return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    int node_count = 0;
    for (auto *ptr = begin(); ptr != end(); ptr = ptr->next()) {
        if (ptr->value() == obj) {
            node_count += 1;
        }
    }
    return node_count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    // This is done for you
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    Double_node *n = new Double_node;
    n->node_value = obj;
    n->next_node = begin();
    n->previous_node = list_head;
    begin()->previous_node = n;
    list_head->next_node = n;
    list_size += 1;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node *n = new Double_node;
    n->node_value = obj;
    n->previous_node = rbegin();
    n->next_node = list_tail;
    rbegin()->next_node = n;
    list_tail->previous_node = n;
    list_size += 1;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    if (list_size == 0) {
        throw std::underflow_error("Underflow");
    }
    Double_node *dummy = begin();
    dummy->next()->previous_node = list_head;
    list_head->next_node = dummy->next();
    delete dummy;
    dummy = nullptr;
    list_size -= 1;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    if (list_size == 0) {
        throw std::underflow_error("Underflow");
    }
    Double_node *dummy = rbegin();
    dummy->previous()->next_node = list_tail;
    list_tail->previous_node = dummy->previous();
    delete dummy;
    dummy = nullptr;
    list_size -= 1;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    int node_count = 0;
    Double_node *curr = new Double_node(front());
    for (int i = 0; i < list_size; i++) {
        if (curr->node_value == obj) {
            node_count += 1;
            curr->next()->previous_node = curr->previous();
            curr->previous()->next_node = curr->next();
        }
        curr = curr->next();
        delete curr;
        curr = nullptr;
    }
    return node_count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
                                                     Type const &nv,
                                                     typename Double_sentinel_list<Type>::Double_node *pn,
                                                     typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), // This assigns 'node_value' the default value of Type
previous_node( pn ),
next_node( nn ) {
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
    return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
    return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
    return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";
    
    for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.rend() || ptr == list.end() ) {
            out << "->S";
        } else {
            out << "->" << ptr->value();
        }
    }
    
    out << "->0" << std::endl << "tail";
    
    for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
        if ( ptr == list.rend() || ptr == list.end() ) {
            out << "->S";
        } else {
            out << "->" << ptr->value();
        }
    }
    
    out << "->0";
    
    return out;
}

#endif
