#include "Heap.h"
#include "PriorityQueue.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int main() {
	int meni, opcija, n = 0, m = 2, *values, steps = 0, tmp, newM, m2;
	PriorityQueue pq;
	Heap h1;
	bool redPostoji = false, heapPostoji=false;
	Heap h2;
	while (true) {
		cout << "Izaberi Heap meni ili Priority Queue meni:";
		cout << endl << "-1) Prekini Program";
		cout << endl << "0) Heap Meni";
		cout << endl << "1) Priority Queue meni";
		cout << endl;
		cin >> meni;
		switch (meni) {
		case 0:
			while (true) {
				cout << "Izaberi opciju:";
				cout << endl << "0) Povratak na top-level meni";
				cout << endl << "1) Stvori Heap sa konzole";
				cout << endl << "2) Stvori Heap iz datoteke";
				cout << endl << "3) Stvori Heap pomocu nasumicnih brojeva";
				cout << endl << "4) Dodaj element u Heap";
				cout << endl << "5) Dohvati minimalni element";
				cout << endl << "6) Obrisi minimalni element";
				cout << endl << "7) Transformisi Heap u Heap zadatog reda";
				cout << endl << "8) Spoji dva Heapa";
				cout << endl << "9) Ispisi Heap";
				cout << endl << "10) Obrisi Heap";
				cout << endl << "11) Obrisi proizvoljni element";
				cout << endl;
				cin >> opcija;
				switch (opcija) {
				case 0: break;
				case 1:
					cout << "Unesi red Heap-a i broj elemenata: " << endl;
					cin >> m >> tmp;
					values = unesiNiz(tmp);
					h1 = Heap(m, values, tmp);
					heapPostoji = true;
					cout << "Heap je napravljen!" << endl;
					continue;
				case 2:
					cout << "Unesi red Heap-a: " << endl;
					cin >> m;
					tmp = 0;
					values = unesiNizDat(tmp);
					h1 = Heap(m, values, tmp);
					heapPostoji = true;
					cout << "Heap je napravljen!" << endl;
					continue;
				case 3:
					cout << "Unesi red Heap-a i broj elemenata: " << endl;
					cin >> m >> tmp;
					values = generisiNiz(tmp);
					h1 = Heap(m, values, tmp);
					heapPostoji = true;
					cout << "Heap je napravljen!" << endl;
					continue;
				case 4:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						cout << "Unesi element za ubacivanje: ";
						cin >> tmp;
						h1.add(tmp, steps);
					}
					continue;
				case 5:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else cout << "Minimalni element je: " << h1.getMinElem() << endl;
					}
					continue;
				case 6:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else {
							tmp = h1.deleteMin(steps);
							cout << "Minimalni element je obrisan i on je bio: " << tmp << endl;
						}
					}
					continue;
				case 7:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else {
							cout << "Unesi novi red Heap-a: ";
							cin >> newM;
							h1.convertTo(newM);
						}
					}
					continue;
				case 8:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else {
							cout << "Unesi red drugog Heap-a i broj elemenata: ";
							cin >> m2>>tmp;
							values = unesiNiz(tmp);
							Heap h2(m2, values, tmp);
							h1.unionOfTwoHeaps(h2, steps);
						}
					}
					continue;
				case 9:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else cout << h1 << endl;
					}
					continue;
				case 10:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						h1.destroy();
						heapPostoji = false;
						cout << "Heap je obrisan!" << endl;
					}
					continue;
				case 11:
					if (!heapPostoji) cout << "Heap nije napravljen!" << endl;
					else {
						if (!h1.getNumOfElems()) cout << "Heap je prazan!" << endl;
						else {
							cout << "Unesi proizvoljni element za brisanje: ";
							cin >> tmp;
							if (h1.deleteKey(tmp, steps)) cout << "Element obrisan!" << endl;
							else cout << "Element ne postoji." << endl;
							
						}
					}
					continue;
				}
				break;
			}
			break;
		case 1:
			while (true)
			{
				cout << endl;
				cout << "Izaberi opciju:";
				cout << endl << "0) Povratak na top-level meni";
				cout << endl << "1) Stvori Prioritetni red sa konzole";
				cout << endl << "2) Stvori Prioritetni red iz datoteke";
				cout << endl << "3) Stvori Prioritetni red pomocu nasumicnih brojeva";
				cout << endl << "4) Da li je red prazan?";
				cout << endl << "5) Dohvati prvi element prioritetnog reda";
				cout << endl << "6) Obrisi prvi element reda";
				cout << endl << "7) Obrisi prvi element reda sa dohvatanjem";
				cout << endl << "8) Umetni element u prioritetni red";
				cout << endl << "9) Izmeri performanse";
				cout << endl;
				cin >> opcija;
				switch (opcija) {
				case 0: break;
				case 1:
					cout << "Unesi red prioritetnog reda i broj elemenata:"<<endl;
					cin >> m>> tmp;
					values = unesiNiz(tmp);
					pq = PriorityQueue(m, values, tmp);
					redPostoji = true;
					cout << "Red je napravljen!" << endl;
					continue;
				case 2:
					cout << "Unesi red prioritetnog reda" << endl;
					cin >> m;
					tmp = 0;
					values = unesiNizDat(tmp);
					pq = PriorityQueue(m, values, tmp);
					redPostoji = true;
					cout << "Red je napravljen!" << endl;
					continue;
				case 3:
					cout << "Unesi red prioritetnog reda i broj elemenata:" << endl;
					cin >> m >> tmp;
					values = generisiNiz(tmp);
					pq = PriorityQueue(m, values, tmp);
					redPostoji = true;
					cout << "Red je napravljen!" << endl;
					continue;
				case 4:
					if (!redPostoji) cout << "Red nije napravljen." << endl;
					else {
						if (pq.isEmpty()) cout << "Red je prazan" << endl;
						else cout << "Red nije prazan" << endl;
					}
					continue;
				case 5:
					if (!redPostoji) cout << "Red nije napravljen." << endl;
					else {
						if (pq.isEmpty()) cout << "Red je prazan" << endl;
						else cout << "Prvi element reda je: " << pq.front() << endl;
					}
					continue;
				case 6:
					if (!redPostoji) cout << "Red nije napravljen." << endl;
					else {
						if (pq.isEmpty()) cout << "Red je prazan" << endl;
						else {
							pq.deleteFront(steps);
							cout << "Prvi element reda obrisan!" << endl;
						}
					}
					continue;
				case 7:
					if (!redPostoji) cout << "Red nije napravljen." << endl;
					else {
						if (pq.isEmpty()) cout << "Red je prazan" << endl;
						else cout << "Prvi element reda obrisan! Taj element je: " << pq.deleteFrontWithReturn(steps) << endl;
					}
					continue;
				case 8:
					if (!redPostoji) cout << "Red nije napravljen." << endl;
					else {
						cout << "Unesi element za ubacivanje:";
						cin >> tmp;
						pq.insert(tmp, steps);
						cout << "Element ubacen!" << endl;
						}
					continue;
				case 9:
					testPerformance();
					continue;

				}
				break;
			}
			break;
		case -1:
			return 0;
		}
	}
}