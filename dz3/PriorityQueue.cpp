#include "PriorityQueue.h"
#include <chrono>
using namespace std;

bool PriorityQueue::isEmpty() const
{
    if (h.getNumOfElems()) return false;
    return true;
}

void testPerformance()
{
    PriorityQueue pq;
    const char* files[4]={ "test_100.txt", "test_1000.txt", "test_10000.txt", "test_100000.txt" };
	int sizes[3] = { 2, 4, 8 }, *niz;
	int fileSizes[4] = { 100, 1000, 10000, 100000 };
	int steps = 0;
	printf("%30s%30s\t%30s%30s\t%30s\n", "Velicina skupa i red Heap-a", "Vreme umetanja", "Broj koraka prilikom umetanja", "Vreme brisanja", "Broj koraka prilikom brisanja");
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
				steps = 0;
				pq = PriorityQueue(sizes[j]);
				niz=unesiNizDat1(files[i]);
				auto pocetak = chrono::high_resolution_clock::now();
				for (size_t l = 0; l < fileSizes[i]; l++)
				{
					pq.insert(niz[l], steps);
				}
				auto kraj = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> protekloVreme = kraj - pocetak;
				printf("%20d,%d\t%30lf ms%30d", fileSizes[i], sizes[j], protekloVreme.count(), steps);
				steps = 0;
				pocetak = chrono::high_resolution_clock::now();
				for (size_t k = 0; k < fileSizes[i]; k++)
				{
					pq.deleteFront(steps);
				}
				kraj = chrono::high_resolution_clock::now();
				protekloVreme = kraj - pocetak;
				printf("%30lf ms%30d\n", protekloVreme.count(), steps);
				
		}
	}
}
