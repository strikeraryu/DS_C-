#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------------------
/**----------------
  Vector
 ---------------**/

template <typename Object>

class Vector
{
private:
    int theSize;
    int theCapacity;
    Object *objects;

public:
    // constructors
    // constructor which works only when explicitly called
    explicit Vector(int theSize_ = 0) : theSize(theSize_), theCapacity(theSize_ + SPARE_CAPACITY) { objects = new Object[theCapacity]; }

    // copy contructor
    Vector(const Vector &rhs) : objects(NULL) { operator=(rhs); }

    // destructor
    ~Vector() { delete[] objects; }

    // operator overloading
    //operator overloading for =
    const Vector &operator=(const Vector &rhs)
    {
        if (this != rhs)
        {
            delete[] objects;
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;

            objects = new Object[theCapacity];
            for (int i = 0; i < theSize; i++)
                objects[i] = rhs.objects[i];
        }
    }

    //operator overloading for []
    Object &operator[](int index) { return objects[index]; }
    const Object &operator[](int index) const { return objects[index]; }

    // main funtions
    void resize(int newsize)
    {
        if (newsize > theCapacity)
            reserve(newsize * 2 + 1);
        theSize = newsize;
    }

    void reserve(int newcapacity)
    {
        if (newcapacity < theSize)
            return;

        Object *oldarray = objects;

        objects = new Object[newcapacity];
        for (int i = 0; i < theSize; i++)
            objects[i] = oldarray[i];

        theCapacity = newcapacity;
        delete[] oldarray;
    }

    bool empty() const { return theSize == 0; }
    int size() const { return theSize; }
    int capacity() const { return theCapacity; }

    void push_back(const Object &x)
    {
        if (theSize == theCapacity)
            reserve(theSize * 2 + 1);
        objects[theSize++] = x;
    }

    void pop_back() { theSize--; }

    const Object &back() const { return objects[theSize - 1]; }

    // iterator for vector
    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() { return &objects[0]; }
    const_iterator begin() const { return &objects[0]; }
    iterator end() { return &objects[0]; }
    const_iterator end() const { return &objects[0]; }

    enum
    {
        SPARE_CAPACITY = 16
    };
};

// ------------------------------------------------------------------------------------------------------
