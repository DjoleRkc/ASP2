#include "Heap.h"
#include <queue>
#include <fstream>
void Heap::copy(const Heap& h)
{
	this->m = h.m;
	this->maxCap = h.maxCap;
	this->numOfElems = h.numOfElems;
	this->values = new int[maxCap];
	for (size_t i = 0; i < numOfElems; i++) values[i] = h.values[i];
}
void Heap::move(Heap& h)
{
	this->m = h.m;
	this->maxCap = h.maxCap;
	this->numOfElems = h.numOfElems;
	this->values = h.values;
	h.values = nullptr;
}
Heap::Heap(int m, int* values, int n)
{
	int tmp=0;
	this->m = m;
	this->numOfElems = 0;
	this->values = new int[maxCap];
	for (size_t i = 0; i < n; i++) add(values[i], tmp);
}
Heap::Heap(const Heap& h)
{
	copy(h);
}

Heap::Heap(Heap&& h)
{
	move(h);
}
Heap& Heap::operator=(const Heap& h)
{
	if (this != &h)
	{
		destroy();
		copy(h);
	}
	return *this;
}
Heap::~Heap()
{
	destroy();
}
Heap& Heap::operator=(Heap&& h)
{
	if (this != &h)
	{
		destroy();
		move(h);
	}
	return *this;
}
int Heap::deleteMin(int& steps)
{
	int tmp = this->values[0], index;
	this->values[0] = this->values[numOfElems - 1];
	this->numOfElems--;
	int curr = 0, firstChild = getFirstChild(curr);
	while (firstChild < numOfElems)
	{
		int min = values[curr];
		for (int i = 0; i < m; i++) {
			if (firstChild + i >= numOfElems) break;
			if (values[firstChild + i] < min)
			{
				min = values[firstChild + i];
				index = firstChild + i;
			}
		}
		if (min < values[curr]) {
			swap(values[curr], values[index]);
			curr = index;
			firstChild = getFirstChild(curr);
			steps++;
		}
		else break;
	}
	return tmp;
}

void Heap::add(int elem, int& steps)
{
	int curr = numOfElems;
	int parent = getParent(curr-1);
	numOfElems++; steps++;
	if (numOfElems > maxCap) {
		maxCap *= 2;
		int *novi = new int[maxCap];
		for (size_t i = 0; i < numOfElems; i++) novi[i] = values[i];
		values = nullptr;
		delete[] values;
		values = novi;
	}
	values[curr] = elem;
	while (curr != 0 && values[parent] > elem) {
		swap(values[curr], values[parent]);
		curr = parent;
		parent = getParent(curr);
		steps++;
	}
}

bool Heap::deleteKey(int key, int& steps)
{
	bool flag = false;
	Heap novi(m);
	for (size_t i = 0; i < numOfElems; i++)
	{
		if (values[i] != key) novi.add(values[i], steps);
		else flag=true;
	}
	this->numOfElems = novi.numOfElems;
	for (size_t i = 0; i < numOfElems; i++) values[i] = novi.values[i];
	return flag;
}

void Heap::unionOfTwoHeaps(Heap h, int& steps)
{
	Heap novi(m);
	for (size_t i = 0; i < this->numOfElems; i++) novi.add(this->values[i], steps);
	for (size_t i = 0; i < h.numOfElems; i++) novi.add(h.values[i], steps);
	this->numOfElems = novi.numOfElems;
	for (size_t i = 0; i < numOfElems; i++) values[i] = novi.values[i];
}

void Heap::convertTo(int newM)
{
	int temp=0;
	Heap novi(newM);
	for (size_t i = 0; i < numOfElems; i++) novi.add(values[i], temp);
	this->m = novi.m;
	this->numOfElems = novi.numOfElems;
	for (size_t i = 0; i < numOfElems; i++) values[i] = novi.values[i];
}

void Heap::destroy()
{
	delete[] values;
	values = nullptr;
	numOfElems = 0;
	
}


ostream& operator<<(ostream& os,  const Heap& h)
{
	queue <int> queueVal;
	queue <int> queueInd;
	int i;
	int lineLength = 62;
	int firstSkip = lineLength;
	int inBetweenSkip;
	queueVal.push(h.values[0]);
	queueInd.push(0);
	for (int j = 0; j < 10; j++) {
		if (queueVal.empty()) break;
		inBetweenSkip = firstSkip;
		firstSkip = (firstSkip - h.m) / h.m;
		for (int l = 0; l < firstSkip; l++)
			os << " ";
		int tmp = pow(h.m, j);
		for (int k = 0; k<tmp; k++)
		{
			if (queueVal.empty()) break;
			int val = queueVal.front();
			int ind = queueInd.front();

			queueVal.pop();
			queueInd.pop();
			for (size_t p = 0; p < h.m; p++)
			{
				int child = h.getFirstChild(ind) + p;
				if (child > h.numOfElems-1) break;
				queueVal.push(h.values[child]);
				queueInd.push(child);
			}
			os << val<< " ";
			for (int f = 0; f < inBetweenSkip; f++)
				os << " ";
		}
		os << endl;
	}
	return os << endl << endl;
}

int* unesiNiz(int k) {
	int* niz = new int[k];
	cout << "Unesi niz:" << endl;
	for (int i = 0; i < k; i++)
	{
		cin >> niz[i];
	}
	return niz;
}


int* unesiNizDat(int &k) {
	int* niz = nullptr;
	string fajl;
	cout << "Unesi naziv fajla: ";
	cin >> fajl;
	ifstream in;
	in.open(fajl);
	if (in.is_open())
	{
		niz = new int[100000];
		while (!in.eof()) {
			in >> niz[k];
			k++;
		}
	}
	k--;
	return niz;
}

int* unesiNizDat1(const char* file) {
	int k = 0;
	int* niz = nullptr;
	ifstream in;
	in.open(file);
	if (in.is_open())
	{
		niz = new int[100000];
		while (!in.eof()) {
			in >> niz[k];
			k++;
		}
	}
	return niz;
}

int* generisiNiz(int k) {
	int* niz = new int[k];
	srand(time(0));
	for (int i = 0; i < k; i++)
	{
		niz[i] = 1 + (rand() % 1000);
	}
	return niz;
}
