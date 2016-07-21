#ifndef _AVECTOR_H
#define _AVECTOR_H

template <class itemType>
class tvector
{
  public:

  // constructors/destructor
    tvector( );                        // default constructor (size==0)
    explicit tvector( int size );      // initial size of vector is size
    tvector( int size, const itemType & fillValue ); // all entries == fillValue
    tvector( const tvector & vec );   // copy constructor
    ~tvector( );                       // destructor

  // assignment
    const tvector & operator = ( const tvector & vec );

  // accessors
    int  length( )   const;        // support for old programs, deprecated
    int  capacity( ) const;        // use in place of length()
    int  size( )     const;        // # elements constructed/stored

  // indexing
    itemType &       operator [ ] ( int index );       // indexing with range checking
    const itemType & operator [ ] ( int index ) const; // indexing with range checking

  // modifiers
    void resize( int newSize );             // change size dynamically;
                                            // can result in losing values
    void reserve(int size);                 // reserve size capacity
    void push_back(const itemType& t);
    void pop_back();
    void clear();                           // size == 0, capacity unchanged
                                                
  private:

    int  mySize;                            // # elements in array
    int  myCapacity;                        // capacity of array
    itemType * myList;                      // array used for storage
};

// *******************************************************************
//  Specifications for vector functions
//
//  The template parameter itemType must satisfy the following two conditions:
//   (1) itemType has a 0-argument constructor
//   (2) operator = is defined for itemType
//  Any violation of these conditions may result in compilation failure.
//
//  Any violation of a function's precondition will result in an error message
//  followed by a call to abort.
//
//  constructors/destructor
//
//   tvector( )
//     postcondition: vector has a capacity of 0 items, and therefore it will
//                    need to be resized
//
//   tvector( int size )
//     precondition: size >= 0
//     postcondition: vector has a capacity of size items
//
//   tvector( int size, const itemType & fillValue )
//     precondition: size >= 0
//     postcondition: vector has a capacity of size items, all of which are set
//                    by assignment to fillValue after default construction
//
//   tvector( const tvector & vec )
//     postcondition: vector is a copy of vec
//
//   ~tvector( )
//     postcondition: vector is destroyed
//
//  assignment
//
//   const tvector & operator = ( const tvector & rhs )
//     postcondition: normal assignment via copying has been performed;
//                    if vector and rhs were different sizes, vector
//                    has been resized to  match the size of rhs
//
//  accessor
//
//   int  length( ) const
//     postcondition: returns vector's size (number of memory cells
//                    allocated for vector)
//
//  indexing
//
//   itemType &       operator [ ] ( int k )       -- index into nonconst vector
//   const itemType & operator [ ] ( int k ) const -- index into const vector
//     description: range-checked indexing, returning kth item
//     precondition: 0 <= k < length()
//     postcondition: returns the kth item
//
//  modifier
//
//   void resize( int newSize )
//     description:  resizes the vector to newSize elements
//     precondition: the current capacity of vector is length; newSize >= 0
//
//     postcondition: the current capacity of vector is newSize; for each k
//                    such that 0 <= k <= min(length, newSize), vector[k]
//                    is a copy of the original; other elements of vector are
//                    initialized using the 0-argument itemType constructor
//                    Note: if newSize < length, elements may be lost
//
//  examples of use
//      tvector<int> v1;         // 0-element vector
//      tvector<int> v2(4);      // 4-element vector
//      tvector<int> v3(4, 22);  // 4-element vector, all elements == 22.

#include "tvector.cpp"
#endif


