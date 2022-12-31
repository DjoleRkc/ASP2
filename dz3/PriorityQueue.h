#ifndef _PriorityQueue_h
#define _PriorityQueue_h
#include "Heap.h"
#include <iostream>
using namespace std;


class PriorityQueue
{
private:
	Heap h;
public:
	PriorityQueue() = default;
	PriorityQueue(int m) : h(m) {};
	PriorityQueue(int m, int* values, int n) : h(m, values, n) {};
	bool isEmpty() const;
	int front() const { return h.getMinElem(); }
	void deleteFront(int &steps) { h.deleteMin(steps); }
	int deleteFrontWithReturn(int& steps) { return h.deleteMin(steps); }
	void insert(int elem, int& steps) { h.add(elem, steps); }
};

void testPerformance();
#endif // !_PriorityQueue_h
