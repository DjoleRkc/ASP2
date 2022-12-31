
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int* unesiNiz(int &k) {
	int* niz = new int[k];
	cout << "Unesi niz:"<<endl;
	for (int i = 0; i < k; i++)
	{
		cin >> niz[i];
	}
	sort(niz, niz + k, greater<int>());
	return niz;
}


int* unesiNizDat(int &k) {
	int* niz = nullptr;
	string fajl;
	cin >>fajl;
	ifstream in;
	in.open(fajl);
	if(in.is_open() )
	{
		niz = new int[1000];
		while (!in.eof() ) {
			in >> niz[k];
			k++;
		}
		sort(niz, niz + k, greater<int>());
	}
	return niz;
}

int* generisiNiz(int& k, int& low, int& high) {
	int* niz = new int[k];
	srand(time(0));
	for (int i = 0; i < k; i++)
	{
		niz[i] = low + (rand()%(high-low));
	}
	sort(niz, niz + k, greater<int>());
	return niz;
}

int pretraziNiz(int &brojac, int* niz, int kljuc, int m, int k, int donjaGranica=0) {
	int low = donjaGranica;
	int high = k-1;
	int* mids = new int[m - 1];
	while (high >= low) {
		if (kljuc == niz[high]) return high;
		if (kljuc == niz[low]) return low;
		for (int i = 0; i < m - 1; i++)
		{
			brojac++;
			mids[i] = low + ((high - low) * (i + 1) / m);
			if (niz[mids[i]] == kljuc) return mids[i];
			brojac++;
			if (i == 0) {
				if (niz[low] < kljuc) return -1;
				if(kljuc<niz[mids[i]]) low = mids[i] + 1;
				if (niz[low] > kljuc and kljuc > niz[mids[i]])
				{
					high = mids[i]-1;
					break;
				}
			}
			else {
				if (niz[mids[i - 1]] < kljuc) return -1;
				if (kljuc < niz[mids[i]]) low = mids[i] + 1;
				if (niz[mids[i - 1]] > kljuc and kljuc > niz[mids[i]])
				{
					low = mids[i - 1] + 1;
					high = mids[i] - 1;
					break;
				}
			}
		}
	}
	return -1;
}

void pretraziNizOptimizovano(int* niz, int* nizKljuceva, int m, int k, int p) {
	int donjaGranica, temp;
	int* indeksi = new int[k];
	int brojacIndeksa = 0;
	int brojac = 0;
	for (int j = 0; j < p; j++)
	{
		if (brojacIndeksa == 0) donjaGranica = 0;
		else donjaGranica = indeksi[brojacIndeksa - 1];
		temp = pretraziNiz(brojac, niz, nizKljuceva[j], m, k, donjaGranica);
		if (temp != -1) {
			indeksi[brojacIndeksa] = temp;
			brojacIndeksa++;
		}
		cout << temp<< " ";
	}
	cout << endl;
	delete[] indeksi;
}

int main() {
	int k, low, high, kljuc, m, p, *niz=nullptr, opcija, *nizKljuceva, index, brojac=0, zbir;
	while (true) {
		cout << "Izaberi opciju:";
		cout << endl << "0) Prekini Program";
		cout << endl << "1) Unesi niz sa tastature";
		cout << endl << "2) Unesi niz iz datoteke";
		cout << endl << "3) Generisi niz";
		cout << endl << "4) Pretrazi niz";
		cout << endl << "5) Pretrazi niz (optimizovano)";
		cout << endl << "6) Evaluacija pretrage";
		cout << endl << "7) Evaluacija pretrage (optimizovano)";
		cout << endl;
		cin >> opcija;
		switch (opcija) {
		case 0: exit(0);
		case 1: cout << "Unesi K: ";
				cin >> k;
				niz = unesiNiz(k);
				for (int i = 0; i < k; i++)
				{
					cout << niz[i] << " ";
				}
				cout << endl;
				break;
		case 2: k = 0;
                cout << "Ucitaj naziv datoteke: ";
				niz = unesiNizDat(k);
                if (niz == nullptr) cout << "Datoteka ne postoji." << endl;
                else {
                    for (int i = 0; i < k; i++) {
                        cout << niz[i] << " ";
                    }
                    cout << endl;
                }
				break;
		case 3: cout << "Unesi K, low i high: ";
				cin >> k >> low >> high;
				niz = generisiNiz(k, low, high);
				for (int i = 0; i < k; i++)
				{
					cout << niz[i] << " ";
				}
				cout << endl;
				break;
		case 4: if (niz == nullptr) cout << "Niz je prazan, ucitaj niz." << endl;
			  else {
				cout << "Unesi m i kljuc: ";
				cin >> m >> kljuc;
				index = pretraziNiz(brojac, niz, kljuc, m, k);
				if (index == -1) cout << "Kljuc nije nadjen." << endl;
				else cout << "Kljuc je nadjen na indeksu: " << index << endl;
				}
			  break;
				
		case 5: if (niz == nullptr) cout << "Niz je prazan, ucitaj niz." << endl; 
			  else {
			cout << "Unesi p i m: ";
			cin >> p >> m;
			nizKljuceva = unesiNiz(p);
			cout << "Niz kljuceva je: ";
			for (int i = 0; i < p; i++)
			{
				cout << nizKljuceva[i] << " ";
			}
			cout << endl;
			pretraziNizOptimizovano(niz, nizKljuceva, m, k, p);
		}
			  break;
		case 6: if (niz == nullptr) cout << "Niz je prazan, ucitaj niz." << endl;
                else {
                cout << "Unesi p: ";
                cin >> p;
                nizKljuceva = unesiNiz(p);
				//nizKljuceva = generisiNiz(p, niz[k-1], niz[0]);
				cout << "Niz kljuceva je: ";
				for (int i = 0; i < p; i++)
				{
					cout << nizKljuceva[i] << " ";
				}
				cout << endl;
                for(int i = 2; i < 7;i++) {
                    zbir = 0;
                    cout << "Prosecan broj koraka za m=" << i << ": ";
                    for(int j = 0; j < p; j++ )
                    {
                        brojac = 0;
                        pretraziNiz(brojac, niz, nizKljuceva[j], i, k);
                        zbir +=brojac;
                    }
                    cout << (float)zbir / p << endl;
                }
            }
            break;
		case 7: if (niz == nullptr) cout << "Niz je prazan, ucitaj niz." << endl;
            else {
                cout << "Unesi p: ";
                cin >> p;
                nizKljuceva = unesiNiz(p);
                for(int i = 2; i < 7;i++) {
                    zbir = 0;
                    low = -1;
                    cout << "Prosecan broj koraka za m=" << i << ": ";
                    for(int j = 0; j < p; j++ )
                    {
                        brojac = 0;
                        if(low != -1)
                            index = pretraziNiz(brojac, niz, nizKljuceva[j], i, k, low);
                        else
                            index = pretraziNiz(brojac, niz, nizKljuceva[j], i, k, 0);

                        if(index!= -1)
                            low = index;

                        zbir +=brojac;
                    }
                    cout << (float)zbir / p << endl;
                }
            }
			break;
		default: cout<<"Opcija ne postoji!"<<endl;
		}
	}
}
