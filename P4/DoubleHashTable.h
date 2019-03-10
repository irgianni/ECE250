#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  igianni
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>
using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete [] array;
    delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
	return (count == 0);
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int val = static_cast<int>(obj) % array_size;
    return (val < 0) ? val+array_size : val;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int val = (static_cast<int>(obj) / array_size) % array_size;
    val = (val < 0) ? val+array_size : val;
    val = (val%2 == 0) ? val+1 : val;
	return val;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	if (empty())
        return false;
    int pos = h1(obj);
    int counter = 0;
    while (counter < array_size && array_state[pos] != EMPTY &&
            (array[pos] != obj || array_state[pos] != OCCUPIED)) {
        pos = (pos+h2(obj)) % array_size;
        counter++;
    }
    if (array[pos] == obj && array_state[pos] == OCCUPIED)
        return true;
    return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    if (count >= array_size)
        throw overflow();
    int pos = h1(obj);
    while (array_state[pos] == OCCUPIED)
        pos = (pos+h2(obj)) % array_size;
    array[pos] = obj;
    array_state[pos] = OCCUPIED;
    count++;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    if (empty())
        return false;
    int pos = h1(obj);
    int counter = 0;
    while (counter < array_size && array_state[pos] != EMPTY &&
           (array[pos] != obj || array_state[pos] != OCCUPIED)) {
        pos = (pos+h2(obj)) % array_size;
        counter++;
    }
    if (array[pos] == obj && array_state[pos] == OCCUPIED) {
        array[pos] = -1;
        array_state[pos] = DELETED;
        --count;
        return true;
    }
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    for (int i = 0; i < array_size; i++) {
        array[i] = 0;
        array_state[i] = EMPTY;
    }
    count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
    cout << "Value : State" << endl;
    for (int i = 0; i < array_size; i++)
        cout << array[i] << " : " << array_state[i] << endl;
	return;
}

#endif
