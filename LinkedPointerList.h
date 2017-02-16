/*
 * Light-weight implementation of LinkedList, appropriate for use in Arduino and other memory-critical environments.
 *
 * - Handling pointers, rather than copies of actual contained objects.
 * - Up to 255 entries
 * - No last element pointer
 * - No sequential get-cache
 * - No support for sorting
 *
 * This object consumes just 5 bytes per instance + 4 per node, making itself more appropriate for use in memory-critical
 * environments. Since the class is targeted for use with small lists with up to a few dozens of entries, the optimization
 * cuts are not significantly affecting the performance.
 *
 * Based on LinkedList library by ivanseidel (https://github.com/ivanseidel/LinkedList).
 *
 *  Created on: 31. sij 2017.
 *      Author: JonnieZG
 */

#ifndef LINKEDPOINTERLIST_H_
#define LINKEDPOINTERLIST_H_

#include <stddef.h>

template<class T>
struct PointerListNode {
	T *data;
	PointerListNode<T> *next;
};

template<typename T>
class LinkedPointerList {

protected:
	unsigned char _size;
	PointerListNode<T> *root;

	PointerListNode<T>* getNode(unsigned char index);

public:
	LinkedPointerList();
	virtual ~LinkedPointerList();

	/*
	 * Returns current size of LinkedPointerList
	 */
	virtual int size();
	/*
	 *  Adds a T pointer at the specified index;
	 */
	virtual bool add(int index, T*);
	/*
	 *  Adds a T pointer at the end of the LinkedPointerList;
	 */
	virtual bool add(T*);
	/*
	 * Adds a T pointer to the start of the LinkedPointerList;
	 */
	virtual bool unshift(T*);
	/*
	 *  Sets a T pointer at the specified index;
	 */
	virtual bool set(int index, T*);
	/*
	 * Removes pointer at specified index;
	 * If index is not reachable, returns NULL;
	 */
	virtual T* remove(int index);
	/*
	 * Removes last pointer;
	 */
	virtual T* pop();
	/*
	 * Removes first object;
	 */
	virtual T* shift();
	/*
	 * Gets a pointer at specified index.
	 * Returns the pointer, or NULL if not existing.
	 */
	virtual T* get(int index);

	/*
	 * Clears the entire list.
	 */
	virtual void clear();

};

// ------------ Template Implementation ------------

#include "LinkedPointerList.h"

template<typename T>
LinkedPointerList<T>::LinkedPointerList() {
	root = NULL;
	_size = 0;
}

template<typename T>
LinkedPointerList<T>::~LinkedPointerList() {
	clear();
}

template<typename T>
PointerListNode<T>* LinkedPointerList<T>::getNode(unsigned char index) {

	int _pos = 0;
	PointerListNode<T>* current = root;

	while (_pos < index && current) {
		current = current->next;

		_pos++;
	}

	// Check if the object is the one we require
	if (_pos == index) {
		return current;
	}

	return NULL;
}

template<typename T>
int LinkedPointerList<T>::size() {
	return _size;
}

template<typename T>
bool LinkedPointerList<T>::add(int index, T* _t) {

	if (index >= _size)
		return add(_t);

	if (index == 0)
		return unshift(_t);

	PointerListNode<T> *tmp = new PointerListNode<T>(), *_prev = getNode(index - 1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;

	return true;
}

template<typename T>
bool LinkedPointerList<T>::add(T* _t) {

	PointerListNode<T> *tmp = new PointerListNode<T>();
	tmp->data = _t;
	tmp->next = NULL;

	if (root) {
		// Already have elements inserted
		PointerListNode<T> *last = getNode(size() - 1);
		last->next = tmp;
		last = tmp;
	} else {
		// First element being inserted
		root = tmp;
	}

	_size++;

	return true;
}

template<typename T>
bool LinkedPointerList<T>::unshift(T* _t) {

	if (_size == 0)
		return add(_t);

	PointerListNode<T> *tmp = new PointerListNode<T>();
	tmp->next = root;
	tmp->data = _t;
	root = tmp;

	_size++;

	return true;
}

template<typename T>
bool LinkedPointerList<T>::set(int index, T* _t) {
	// Check if index position is in bounds
	if (index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template<typename T>
T* LinkedPointerList<T>::pop() {
	if (_size <= 0)
		return NULL;

	if (_size >= 2) {
		PointerListNode<T> *tmp = getNode(_size - 2);
		T* ret = tmp->next->data;
		delete (tmp->next);
		tmp->next = NULL;
		_size--;
		return ret;
	} else {
		// Only one element left on the list
		T* ret = root->data;
		delete (root);
		root = NULL;
		_size = 0;
		return ret;
	}
}

template<typename T>
T* LinkedPointerList<T>::shift() {
	if (_size <= 0)
		return NULL;

	if (_size > 1) {
		PointerListNode<T> *_next = root->next;
		T* ret = root->data;
		delete (root);
		root = _next;
		_size--;

		return ret;
	} else {
		// Only one left, then pop()
		return pop();
	}

}

template<typename T>
T* LinkedPointerList<T>::remove(int index) {
	if (index < 0 || index >= _size) {
		return NULL;
	}

	if (index == 0)
		return shift();

	if (index == _size - 1) {
		return pop();
	}

	PointerListNode<T> *tmp = getNode(index - 1);
	PointerListNode<T> *toDelete = tmp->next;
	T* ret = toDelete->data;
	tmp->next = tmp->next->next;
	delete (toDelete);
	_size--;
	return ret;
}

template<typename T>
T* LinkedPointerList<T>::get(int index) {
	PointerListNode<T> *tmp = getNode(index);

	return (tmp ? tmp->data : NULL);
}

template<typename T>
void LinkedPointerList<T>::clear() {
	PointerListNode<T>* tmp;
	while (root != NULL) {
		tmp = root;
		root = root->next;
		delete tmp;
	}
	_size = 0;
}

#endif /* LINKEDPOINTERLIST_H_ */
