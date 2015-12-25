#ifndef MINHEAP_H
#define MINHEAP_H
#include <vector>
#include <string>
#include "hashtable.h"

class MinHeap {
public:
    MinHeap (int d);
    /* Constructor that builds a d-ary Min Heap
      This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/

    ~MinHeap ();

    void add (std::string item, int priority);
     /* adds the item to the heap, with the given priority. */

    const std::string & peek () const;
     /* returns the element with smallest priority.  If
        multiple items have the smallest priority, it returns
        the string which comes first alphabetically.
        Throws an exception if the heap is empty. */

    void remove ();
     /* removes the element with smallest priority.  If
        multiple items have the smallest priority, it removes
        the string which comes first alphabetically.
        Throws an exception if the heap is empty. */

    void update (std::string item, int priority);
     /* updates the priority for the specified element. 
        Throws an exception if the item is not in the heap. */  

    bool isEmpty ();
     /* returns true iff there are no elements on the heap. */

private:
    int ary;
	  std::vector<std::pair<std::string,int> > heap;
    HashTable table;
    void makeValidUp(int currPos);
    void makeValidDown(int currPos);
};

#endif
