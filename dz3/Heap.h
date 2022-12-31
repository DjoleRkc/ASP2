#ifndef _Heap_h
#define _Heap_h
#include <iostream>
using namespace std;

class Heap
{
private:
	int maxCap = 100, numOfElems=0, m, * values; //m je red hipa
	void copy(const Heap& h);
	void move(Heap& h);
	

public:
	Heap() = default;
	Heap(int m) { this->m = m; values = new int[maxCap]; }
	Heap(int m, int *values,int n);
	Heap(const Heap& h);
	Heap(Heap&& h);
	Heap& operator=(const Heap& h);
	Heap& operator=(Heap&& h);
	friend ostream& operator<<(ostream& os, const Heap& h);
	~Heap();
	int getNumOfElems() const { return numOfElems; }
	int getMinElem() const { return values[0]; }
	int getParent(int i) const { return i / m; }
	int getFirstChild(int i) const { return m * i + 1; }
	int deleteMin(int& steps);
	void add(int elem, int& steps);
	bool deleteKey(int key, int& steps);
	void unionOfTwoHeaps(Heap h, int& steps);
	void convertTo(int newM);
	void destroy();
	
};
int* generisiNiz(int k);
int* unesiNiz(int k);
int* unesiNizDat(int& k);
int* unesiNizDat1(const char* file);
#endif // !_Heap_h