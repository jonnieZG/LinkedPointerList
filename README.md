# LinkedPointerList

Light-weight implementation of [LinkedList](https://github.com/ivanseidel/LinkedList) class developed by 
[Ivan Seidel](https://github.com/ivanseidel), that is now stripped down to bare minimum, making it appropriate for use
in memory-critical environments like **`Arduino`**. Instead of dealing with actual objects, it deals with pointers to them,
making itself very lightweight, and you responsible for preventing memory leaks.

This object consumes just 5 bytes per instance + 4 per contained node, at the cost of cutting down caching, removing direct
reference to the last and a few other features regarded as optional instead of mandatory. Since the class is **targeted for use
with small lists with up to a few dozens of entries**, the optimization cuts are not significantly affecting the performance.

## Installation

1. [Download](https://github.com/jonnieZG/LinkedPointerList/archive/master.zip) the Latest release from gitHub.
2. Unzip and modify the Folder name to "LinkedPointerList" (Remove the '-version')
3. Paste the modified folder into your Library folder (`Libraries` folder inside  user home directory).
4. Reopen your Arduino IDE.

## NOTE

This README is a modified version of the original LinkedList's README.md by Ivan Seidel.

-------------------------

## Getting started

### The `LinkedPointerList` class

The `LinkedPointerList` is a good choice when you to handle lists of objects of the same type. Unlike the original `LinkedList`,
which was targeted for features, this one is targeted for a very small RAM consumption. Therefore, it is stripped of all
non-vital features, and limited to 255 entries - but in real life you should use it for up to few dozens (since in Arduino
there is not much RAM to begin with).

Since it handles pointers, instead of actual objects, you should take care to prevent memory-leaks.

#### Declaring a LinkedPointerList Object
```c++
// Instantiate a LinkedPointerList holding pointers to your custom objects of type 'MyObject'
LinkedPointerList<MyObject> myList;

// ...which is the same as
LinkedPointerList<MyObject> myList = LinkedPointerList<MyObject>();

// If instantiating a pointer to LinkedPointerList, that you will delete later manually
LinkedPointerList<MyObject> *pMyList = new LinkedPointerList<MyObject>();
```

#### Getting the Size of the List
```c++
// To get the size of a linked list
int listSize = myList.size();

// If using a pointer, you should use -> instead
int pListSize = pMyList->size();
```

#### Adding Entries (Pointers to Elements)

```c++
// Inserting at the END of the list - you must pass POINTERS instead of actual objects
myList.add(&myObject);

// Inserting a pointer at the specified index
myList.add(0, &myObject); // Add at the beginning
myList.add(3, &myObject); // Add at index 3

// Inserting a pointer to the beginning
myList.unshift(&myObject);
```

#### Getting Entries

```c++
// Get a pointer to the FIRST element
MyObject *pMyObject = myList.get(0);

// Get the third element
MyObject *pMyObject = myList.get(2);

// Get the LAST element
MyObject *pMyObject = myList.get(myList.size() - 1);
```

#### Changing Entries
```c++
// Change the first element to point to myObject
myList.set(0, &myObject);

// Change the third element to point to myObject
myList.set(2, &myObject);

// Change the LAST element of the list
myList.set(myList.size() - 1, &myObject);
```

#### Removing Entries
```c++
// Remove the first object
myList.remove(0);

// Get and Delete the third element
MyObject *pMyDeletedObject = myList.remove(2);

// pop() will remove and return the LAST element
MyObject *pMyDeletedObject = myList.pop();

// shift() will remove and return the FIRST element
MyObject *pMyDeletedObject = myList.shift();

// clear() will erase the entire list, leaving it with 0 elements
// NOTE: Clear won't free memory from objects the pointers were
// actually pointing to, so you might consider deleting them manually.
myList.clear();
```
------------------------

## Library Reference

### `PointerListNode` struct

- `T*` `ListNode::data` - Pointer to a contained object

- `PointerListNode<T>` `*next` - Pointer to the next Node

### `LinkedPointerList` class

- `LinkedPointerList<T>::LinkedPointerList()` - Constructor.

- `LinkedPointerList<T>::~LinkedPointerList()` - Destructor. Clears Nodes, without destructing the referenced objects.

- `int` `LinkedPointerList<T>::size()` - Returns the current size of the list.

- `bool` `LinkedPointerList<T>::add(T*)` - Add pointer to element T at the END of the list.

- `bool` `LinkedPointerList<T>::add(int index, T*)` - Add pointer to element T at `index` of the list.

- `bool` `LinkedPointerList<T>::unshift(T*)` - Add pointer to element T at the BEGINNING of the list.

- `bool` `LinkedPointerList<T>::set(int index, T*)` - Set the pointer to element at `index` to T.

- `T*` `LinkedPointerList<T>::remove(int index)` - Remove pointer to element at `index`. Return a pointer to removed element.
   Does not free referenced objects

- `T*` `LinkedPointerList<T>::pop()` - Remove the LAST element. Return a pointer to the removed element.

- `T*` `LinkedPointerList<T>::shift()` - Remove the FIRST element. Return a pointer to the removed element.

- `T*` `LinkedPointerList<T>::get(int index)` - Return a pointer to the element at `index`.

- `void` `LinkedPointerList<T>::clear()` - Removes all elements. Does not free pointer memory.

### Version History

* `1.0 (2017-02-16)`: Original release
