/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * Name: Irene Gianni
 * uWaterloo User ID:  igianni@uwaterloo.ca
 * Submitted for ECE 250 (Project 2)
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {
    
private:
    int *array;
    int count;
    int array_size;
    int initial_size;
    
public:
    Dynamic_stack(int = 10);
    ~Dynamic_stack();
    
    int top() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    
    void push( int const & );
    int pop();
    void clear();
};

Dynamic_stack::Dynamic_stack( int n ): // Constructor
// Initializing the member variables. If no argument is included, array_size & initial_size will take 10 as the default.
count( 0 ),
array_size( n ),
initial_size(n)
{
    if (n < 1) { // If n<1, then n=1.
        array_size = 1;
        initial_size = 1;
    }
    array = new int[array_size];
}


Dynamic_stack::~Dynamic_stack() { // Destructor
    // Delete the array and free up the memory allocated.
    delete [] array;
    array = nullptr;
}


int Dynamic_stack::top() const { // Accessor for the last item added (the top of the stack).
    if (empty()) {
        throw underflow(); // Throw underflow if empty.
        return 0;
    }
    return array[count-1];
}


int Dynamic_stack::size() const { // Accessor for the number of items currently in the list.
    return count;
}


bool Dynamic_stack::empty() const { // To check whether the stack is empty or not.
    if (count == 0) {
        return true;
    }
    return false;
}


int Dynamic_stack::capacity() const { // Check the current size of the array.
    return array_size;
}


void Dynamic_stack::push( int const &obj ) { // Mutator to add and object &obj to the stack.
    if (count == array_size) { // This check whether the array is full or not, if it is, a new array twice the size will be generated.
        int *newarray = new int[array_size*2];
        array_size = 2*array_size;
        for (int i = 0; i < count; i++) { // This loop will copy the values in the old array to the new array. O(n)
            newarray[i] = array[i];
        }
        delete [] array;
        array = nullptr;
        array = newarray;
    }
    array[count] = obj; // Whether or not a new array is generated, or the current array is sufficient, add the object to the stack.
    count++; // Increment the size count.
}

int Dynamic_stack::pop() { // Delete the topmost object of the stack (the last item in the array).
    if (empty()) {
        throw underflow(); // Throw underflow if empty.
        return 0;
    }
    int x = top();
    count--; // Decrement the size count.
    return x; // Return the object 'popped' from the stack.
}

void Dynamic_stack::clear() { // Remove all elements in the stack.
    delete [] array; // Deleting the array.
    array = nullptr;
    if (array_size != initial_size) { // If the array size is changed, return it to the original size.
        array_size = initial_size;
    }
    count = 0; // Change back the count.
    array = new int[array_size]; // Create the new array.
}
#endif
