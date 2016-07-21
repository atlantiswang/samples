// *******************************************************************
//  see tvector.h for complete documentation of functions
//
//  vector class consistent with a subset of the standard C++ vector class
//  as defined in the draft ANSI standard (part of standard template library)
// *******************************************************************

template <class itemType>
tvector<itemType>::tvector()
//postcondition: vector has a capacity of 0 items
    : mySize(0),
      myCapacity(0),
      myList(0)
{

}

template <class itemType>
tvector<itemType>::tvector(int size)
// precondition: size >= 0
// postcondition: vector has size/capacity of size items
   : mySize(size),
     myCapacity(size),
     myList(new itemType[size])
{

}

template <class itemType>
tvector<itemType>::tvector(int size, const itemType & fillValue)
// precondition: size >= 0
// postcondition: vector has size/capacity of size items, all of which are set
//                by assignment to fillValue after default construction
    : mySize(size),
      myCapacity(size),
      myList(new itemType[size])
{
    int k;
    for(k = 0; k < size; k++)
    {
        myList[k] = fillValue;
    }
}

template <class itemType>
tvector<itemType>::tvector(const tvector<itemType> & vec)
// postcondition: vector is a copy of vec
    : mySize(vec.size()),
      myCapacity(vec.capacity()),
      myList(new itemType[myCapacity])
{
    int k;
        // copy elements
    for(k = 0; k < mySize; k++){
        myList[k] = vec.myList[k];
    }
}

template <class itemType>
tvector<itemType>::~tvector ()
// postcondition: vector is destroyed
{
    delete [] myList;
    myList = 0;       // fail fast
}

template <class itemType>
const tvector<itemType> &
tvector<itemType>::operator = (const tvector<itemType> & rhs)
// postcondition: normal assignment via copying has been performed;
//                if vector and rhs were different sizes, vector
//                has been resized to  match the size of rhs
{
    if (this != &rhs)                           // don't assign to self!
    {
        delete [] myList;                       // get rid of old storage
        myCapacity = rhs.capacity();
        mySize =     rhs.size();
        myList = new itemType [myCapacity];         // allocate new storage

            // copy rhs
        int k;
        for(k=0; k < mySize; k++)
        {
            myList[k] = rhs.myList[k];
        }
    }
    return *this;                               // permit a = b = c = d
}

template <class itemType>
int tvector<itemType>::length() const
// postcondition: returns vector's size (number of memory cells
//                allocated for vector) THIS METHOD IS DEPRECATED
{
    return myCapacity;
}

template <class itemType>
int tvector<itemType>::capacity() const
{
	return myCapacity;
}

template <class itemType>
int tvector<itemType>::size() const
{
    return mySize;
}


template <class itemType>
void tvector<itemType>::push_back(const itemType& t)
{
    if (mySize >= myCapacity)
    {
        reserve(myCapacity == 0 ? 2 : 2*myCapacity);
    }
    myList[mySize] = t;
    mySize++;
}

template <class itemType>
void tvector<itemType>::pop_back()
{
    if (mySize > 0)
    {
        mySize--;
    } 
}


template <class itemType>
itemType & tvector<itemType>::operator [] (int k)
// description: range-checked indexing, returning kth item
// precondition: 0 <= k < length()
// postcondition: returns the kth item
{

    if (k < 0 || myCapacity <= k)
    {
        cerr << "Illegal vector index: " << k << " max index = ";
        cerr << (mySize-1) << endl;
        exit(1);
    }
    return myList[k];
}

template <class itemType>
const itemType & tvector<itemType>::operator [] (int k) const
// safe indexing, returning const reference to avoid modification
// precondition: 0 <= index < length
// postcondition: return index-th item
// exception: aborts if index is out-of-bounds
{
    if (k < 0 || myCapacity <= k)
    {
        cerr << "Illegal vector index: " << k << " max index = ";
        cerr << (mySize-1) << endl;
        exit(1);
    }
    return myList[k];
}

template <class itemType>
void tvector<itemType>::resize(int newSize)
// description:  resizes the vector to newSize elements
// precondition: the current capacity of vector is capacity(); newSize >= 0
//               the current size is size()
// postcondition: size() == newSize.  If newSize > oldsize then
//                the current capacity of vector is newSize; otherwise
//                capacity isn't changed. for each k
//                such that 0 <= k <= min(mySize, newSize), vector[k]
//                is a copy of the original; other elements of vector are
//                initialized using the 0-argument itemType constructor
{    
    if (newSize < mySize)
    {
        mySize = newSize;   // capacity doesn't "shrink"
        return;
    }
         // allocate new storage and copy element into new storage

    int k;
    itemType * newList = new itemType[newSize];
    for(k=0; k < mySize; k++)
    {
        newList[k] = myList[k];
    }
    delete [] myList;                      // de-allocate old storage
    myCapacity = mySize = newSize;         // assign new storage/size
    myList = newList;
}

template <class itemType>
void tvector<itemType>::reserve(int size)
{
    // punt to resize in current implementation
    
    int oldSize = mySize;
    if (size > myCapacity)
    {
        resize(size);
    }
    mySize = oldSize;
}

template <class itemType>
void tvector<itemType>::clear()
{
    mySize = 0;
}
