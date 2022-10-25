#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;


struct Node {
	Node* levi;
	Node* desni;
	Node* otac;
	int kljuc;
	Node* isti;
};
typedef Node* Nodeptr;

struct element
{
	int low;
	int high;
};

int* unesiNiz(int& k) {
	int* niz = new int[k];
	cout << "Unesi niz:" << endl;
	for (int i = 0; i < k; i++)
	{
		cin >> niz[i];
	}
	sort(niz, niz + k, greater<int>());
	return niz;
}


Nodeptr ubaciKljuc(Nodeptr &koren, int kljuc) {
	Nodeptr novi = new Node;
	novi->desni = nullptr;
	novi->levi = nullptr;
	novi->kljuc = kljuc;
	novi->isti = nullptr;
	Nodeptr prev = koren;
	for (Nodeptr current = koren; current != nullptr;)
	{
		prev = current;
		if (current->kljuc > kljuc) current = current->levi;
		else if (current->kljuc < kljuc) current = current->desni;
		else {
			while (current->isti != nullptr) {
				current = current->isti;
			}
			current->isti = novi;
			novi->otac = nullptr;
			return novi;
		}
	}
	novi->otac = prev;
	if (prev == nullptr) koren = novi;
	else if (novi->kljuc < prev->kljuc) prev->levi = novi;
	else if (novi->kljuc > prev->kljuc) prev->desni = novi;
	return koren;
}

void kreirajStablo(Nodeptr& koren, int* niz, int k)
{
	stack <element> s;

	element prvi = { 0, k - 1 };
	s.push(prvi);

	while (!s.empty())
	{
		element trenutni = s.top();
		s.pop();

		if (trenutni.low > trenutni.high)
			continue;

		int mid = trenutni.low + (trenutni.high - trenutni.low) / 2;
		ubaciKljuc(koren, niz[mid]);

		element levi = { trenutni.low, mid - 1 };
		element desni = { mid + 1, trenutni.high };

		s.push(levi);
		s.push(desni);
	}
}

int pretraziStablo(Nodeptr& koren, int kljuc, int &brojac) {
	for (Nodeptr current = koren; current != nullptr; brojac++)
	{
		if (current->kljuc > kljuc) current = current->levi;
		else if (current->kljuc < kljuc) current = current->desni;
		else return 1;
	}
	return -1;
}

int* generisiNiz(int& k, int& low, int& high) {
	int* niz = new int[k];
	srand(time(0));
	for (int i = 0; i < k; i++)
	{
		niz[i] = low + (rand() % (high - low));
	}
	sort(niz, niz + k, greater<int>());
	return niz;
}

void obrisiStablo(Nodeptr& koren) {
	queue <Nodeptr> queue;
	queue.push(koren);
	while (queue.empty() != true) {
		Nodeptr novi = queue.front();
		queue.pop();

		if (novi->levi != nullptr) queue.push(novi->levi);
		if (novi->desni != nullptr) queue.push(novi->desni);
		delete novi;
	}
}

float evaluacijaBst(int* nizKljuceva, Nodeptr koren, int brojKljuceva) {
	int brojKoraka = 0;
	int brojac;
	for (int i = 0; i < brojKljuceva; i++)
	{
		brojac = 1;
		pretraziStablo(koren, nizKljuceva[i], brojac);
		brojKoraka += brojac;
	}
	return ((float)brojKoraka / brojKljuceva);
}

void ispisi( Nodeptr koren, int visina = 7) {

	queue <Nodeptr> queue;
	int i;
	int lineLength = 62;
	int firstSkip = lineLength;
	int inBetweenSkip;

	queue.push(koren);

	for (int j = 0; j <= visina; j++) {
		inBetweenSkip = firstSkip;
		firstSkip = (firstSkip - 2) / 2;
		for (int m = 0; m < firstSkip; m++)
			cout << " ";
		for (int k = 0; k < 1 << j; k++)
		{
			Nodeptr button = queue.front();

			queue.pop();
			if (button) { queue.push(button->levi); queue.push(button->desni); printf("%2d", button->kljuc); }
			else
			{
				queue.push(nullptr);
				queue.push(nullptr);
				cout << "  ";
			}

			for (int l = 0; l < inBetweenSkip; l++)
				cout << " ";
		}
		cout << endl << endl;
	}
}

int main() {
	Nodeptr koren = nullptr;
	int low, high, k, p, temp=0, *nizKljuceva, kljuc, opcija, *niz, brojac=1, rez;
	while (true) {
		cout << "Izaberi opciju:";
		cout << endl << "0) Prekini Program";
		cout << endl << "1) Formiraj stablo";
		cout << endl << "2) Umetni kljuc";
		cout << endl << "3) Pretrazi stablo";
		cout << endl << "4) Ispisi stablo";
		cout << endl << "5) Evaluacija performansi u BST";
		cout << endl << "6) Obrisi stablo iz memorije";
		cout << endl;
		cin >> opcija;
		switch (opcija) {
		case 0: exit(0);
		case 1: if (koren) {
			obrisiStablo(koren); koren = nullptr;
		}
			cout << "Unesi K: ";
			cin >> k;
			niz = unesiNiz(k);
			for (int i = 0; i < k; i++)
			{
				cout << niz[i] << " ";
			}
			cout << endl;
			kreirajStablo(koren, niz, k);
			break;
		case 2: cout << "Unesi kljuc za ubacivanje: ";
			cin >> kljuc;
			ubaciKljuc(koren, kljuc);
			cout << "Kljuc je unet."<<endl;
			break;
		case 3: if (koren == nullptr) { cout << "Stablo je prazno" << endl; break; } 
			    cout << "Unesi kljuc za pretragu: ";
				cin >> kljuc;
				rez = pretraziStablo(koren, kljuc, brojac);
				if (rez==1) cout << "Kljuc je nadjen u "<< brojac <<" koraka"<<endl;
				else cout << "Kljuc nije nadjen."<<endl;
				break;
		case 4: if (koren == nullptr) cout << "Stablo je prazno." << endl;
				else ispisi(koren);
				break;

		case 5: if (koren == nullptr) { cout << "Stablo je prazno" << endl; break; }
			cout << "Unesi p, low i high: ";
			cin >> p >> low >> high;
			nizKljuceva = generisiNiz(p, low, high);
			cout << "Niz kljuceva je: ";
			for (int i = 0; i < p; i++)
			{
				cout << nizKljuceva[i] << " ";
			}
			cout << endl;
			cout << "Prosecan broj koraka potrebnih za pretrazivanje je: ";
			cout << evaluacijaBst(nizKljuceva, koren, p)<<endl;
			break;
		case 6: if (koren == nullptr) cout << "Stablo ne moze da se obrise jer ne postoji."<<endl;
			  else { obrisiStablo(koren); koren = nullptr; }
		}
	}
	return 0;
}