/*Нека је дата табела CUSTOMER_ACCOUNT која представља табелу из једног
стандардног benchmark-a за тестирање перформанси база података. Структура ове табеле
је следећа: (CA_ID, CA_B_ID, CA_C_ID, CA_NAME, CA_TAX_ST, CA_BAL). CA_ID је
примарни кључ табеле (целобројни податак), и индекс се креира над њим. Параметри
CA_B_ID, CA_C_ID, CA_TAX_ST су административни подаци везани за рачун
(целобројног типа), CA_NAME представља име рачуна (стринг), а CA_BAL представља
стање на рачуну (реалан број).
Табела је дата текстуалном датотеком која има следећу структуру (| преставља делимитер
у датотеци):
CA_ID|CA_B_ID|CA_C_ID|CA_NAME|CA_TAX_ST|CA_BAL
Потребно је имплементирати Б+ стабло реда m (где је m минимално 3, а максимално 10)
као индексну структуру (у наставку индекс) над табелом CUSTOMER_ACCOUNT ради
ефикасног претраживања рачуна по примарном кључу. За сваки кључ је везан и
показивач на структуру која чува све податке о рачуну.
Реализовати следеће операције над индексом:
1. [20 поена] Стварање и уништавање индекса над табелом
CUSTOMER_ACCOUNT. Приликом стварања индекса корисник уноси ред Б+
стабла.
2. [5 поена] Испис индекса на стандардни излаз тако да су појединачни чворови
уочљиви (међусобно размакнути). Ова ставка ће бити тестирана за мале величине
табела (репрезентативна величина табеле за ову ставку је дата у датотеци
CustomerAccount20.txt)
3. [15 поена] Додавање новог записа (рекорда) у табелу (уносе се сви подаци о
рачуну)
4. [15 поена] Брисање записа у табели по задатом примарном кључу. Корисник
задаје примарни кључ записа који се брише.
5. [15 поена] Претраживање једног података. Корисник задаје један примарни кључ
по коме се врши претрага. Претрага треба да на стандардни излаз испише
одговарајући запис, као и укупан број корака за које је целокупна претрага
завршена.
6. [15 поена] Претраживање k података. Корисник задаје број примарних кључева
(параметар k) и низ кључева дужине k над којима се врши претрага. Кључеви у
низу су у произвољном редоследу. Претрага треба да на стандардни излаз испише
укупан број корака за које је целокупна претрага завршена, као и да креира
датотеку са пронађеним записима, према горњем формату.
7. [15 поена] Претраживање k сукцесивних података. Корисник задаје број
примарних кључева (параметар k) и примарни кључ почетног записа. Претрага
треба да на стандардни излаз испише укупан број корака за које је целокупна
претрага завршена, као и да креира датотеку са пронађеним записима, према
горњем формату.
Корисник са програмом интерагује путем једноставног менија. Програм треба да испише
садржај менија, а затим да чека да корисник изабере (унесе путем тастатуре) редни број
неке од понуђених ставки, након чега, пре извршења, од корисника очекује да по потреби
унесе додатне параметре. Поступак се понавља све док корисник у менију не изабере
опцију за прекид програма.
*/


#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct Zapis {
    long long int CA_ID, CA_B_ID, CA_C_ID, CA_TAX_ST;
    double CA_BAL;
    string CA_NAME;
};

struct Node {
    bool isLeaf = false;
    int numOfElems = 0;
    int level = 0;
    long long int values[10];
    Node* subTrees[11];
    Zapis* zapisi[10];
    Node* parent = nullptr;
    Node* next = nullptr;
};

typedef Node* Nodeptr;

Nodeptr makeNode() {
    Nodeptr novi = new Node;
    for (size_t i = 0; i < 10; i++) {
        novi->values[i] = 0;
        novi->zapisi[i] = nullptr;
        novi->subTrees[i] = nullptr;
    }
    novi->subTrees[10] = nullptr;
    return novi;
}

Nodeptr findLeaf(Nodeptr root, long long int key, int& brojac) {
    Nodeptr current = root;
    brojac++;
    while (current->isLeaf != true)
    {
        for (int i = 0; i < current->numOfElems; i++)
        {
            if (current->values[i] >= key) {
                current = current->subTrees[i];
                break;
            }
            if (i == current->numOfElems - 1)
            {
                current = current->subTrees[i + 1];
                break;
            }
        }
        brojac++;
    }
    return current;
}

void printZapis(Nodeptr root, long long int key, int& brojac) {
    brojac = 0;
    Nodeptr leaf = findLeaf(root, key, brojac);
    for (size_t j = 0; j < leaf->numOfElems; j++)
    {
        if (leaf->values[j] == key) {
            cout << "Trazeni zapis je: ";
            cout << leaf->zapisi[j]->CA_ID << " " << leaf->zapisi[j]->CA_B_ID << " " << leaf->zapisi[j]->CA_C_ID << " " << leaf->zapisi[j]->CA_NAME << " " << leaf->zapisi[j]->CA_TAX_ST << " " << leaf->zapisi[j]->CA_BAL << endl;
            cout << "Potreban broj koraka je: " << brojac << endl;
            return;
        }
    }
    cout << "Ne postoji trazeni zapis." << endl;
}

void split(Nodeptr current, int m) {
    Nodeptr novi = makeNode();
    int a = ceil((double)m / 2);
    if (current->isLeaf) novi->isLeaf = true;
    novi->parent = current->parent;
    for (size_t i = novi->parent->numOfElems; i >= 0; i--) {
        if (i && novi->parent->values[i - 1] > current->values[a - 1]) {
            novi->parent->values[i] = novi->parent->values[i - 1];
            novi->parent->subTrees[i + 1] = novi->parent->subTrees[i];
        }
        else {
            novi->parent->values[i] = current->values[a - 1];
            novi->parent->subTrees[i + 1] = novi;
            break;
        }
    }

    novi->numOfElems = m - a;
    novi->parent->numOfElems++;
    current->numOfElems = a;
    novi->subTrees[m - a] = current->subTrees[m];
    if (novi->subTrees[m - a]) novi->subTrees[m - a]->parent = novi;
    for (size_t i = 0; i < m - a; i++)
    {
        novi->values[i] = current->values[a + i];
        current->values[a + i] = 0;
        if (novi->isLeaf == true) {
            novi->zapisi[i] = current->zapisi[a + i];
            current->zapisi[a + i] = nullptr;
        }
        else {
            novi->subTrees[i] = current->subTrees[a + i];
            novi->subTrees[i]->parent = novi;
            current->subTrees[a + i] = nullptr;
        }
    }
    if (current->isLeaf) {
        novi->next = current->next;
        current->next = novi;
    }
    else {
        current->values[a] = 0;
        current->subTrees[a + 1] = nullptr;
        current->numOfElems--;
    }
}

Nodeptr insertKey(Nodeptr root, long long int key, int m, Zapis* zapis) {
    int brojac = 0;
    auto leaf = findLeaf(root, key, brojac);
    for (size_t i = leaf->numOfElems; i >= 0; i--) {
        if (i && leaf->values[i - 1] > key) {
            leaf->values[i] = leaf->values[i - 1];
            leaf->zapisi[i] = leaf->zapisi[i - 1];
        }
        else {
            leaf->values[i] = key;
            leaf->zapisi[i] = zapis;
            break;
        }
    }

    leaf->numOfElems++;
    if (leaf->numOfElems == m)
    {
        Nodeptr current = leaf;
        while (current->numOfElems == m && current != root)
        {
            split(current, m);
            current = current->parent;
        }
        if (current == root && current->numOfElems == m) {
            Nodeptr newRoot = makeNode();
            newRoot->subTrees[0] = root;
            root->parent = newRoot;
            split(current, m);
            root = newRoot;
        }
    }
    return root;
}

Nodeptr createTree(string file, int m, Nodeptr root) {
    char c1, c2, c3, c4, c5, c6;
    ifstream in;
    in.open(file);
    if (in.is_open())
    {
        Zapis* novi = new Zapis;
        in >> novi->CA_ID >> c1 >> novi->CA_B_ID >> c2 >> novi->CA_C_ID >> c3;
        getline(in, novi->CA_NAME, '|');
        in >> novi->CA_TAX_ST >> c5 >> novi->CA_BAL;
        while (!in.eof()) {
            root = insertKey(root, novi->CA_ID, m, novi);
            novi = new Zapis;
            in >> novi->CA_ID >> c1 >> novi->CA_B_ID >> c2 >> novi->CA_C_ID >> c3;
            getline(in, novi->CA_NAME, '|');
            in >> novi->CA_TAX_ST >> c5 >> novi->CA_BAL;

        }
    }
    return root;
}

void searchK(int k, long long int* niz, int& brojac, Nodeptr root) {
    ofstream file;
    file.open("izlazK.txt");
    for (size_t i = 0; i < k; i++)
    {
        Nodeptr tmp = findLeaf(root, niz[i], brojac);
        for (size_t j = 0; j < tmp->numOfElems; j++)
        {
            if (niz[i] == tmp->values[j]) {
                file << tmp->zapisi[j]->CA_ID << " " << tmp->zapisi[j]->CA_B_ID << " " << tmp->zapisi[j]->CA_C_ID << " " << tmp->zapisi[j]->CA_NAME << " " << tmp->zapisi[j]->CA_TAX_ST << " " << tmp->zapisi[j]->CA_BAL << endl;
                break;
            }
        }
    }
    cout << "Broj potrebnih koraka je: " << brojac << endl;
}

void searchKSucc(int k, long long int key, int& brojac, Nodeptr root) {
    ofstream file;
    file.open("izlazKSucc.txt");
    Nodeptr tmp = findLeaf(root, key, brojac);
    brojac--;
    for (size_t i = 0; i < k && tmp; brojac++)
    {
        for (size_t j = 0; j < tmp->numOfElems && i < k; j++)
        {
            if (key <= tmp->values[j]) {
                i++;
                file << tmp->zapisi[j]->CA_ID << " " << tmp->zapisi[j]->CA_B_ID << " " << tmp->zapisi[j]->CA_C_ID << " " << tmp->zapisi[j]->CA_NAME << " " << tmp->zapisi[j]->CA_TAX_ST << " " << tmp->zapisi[j]->CA_BAL << endl;
            }
        }
        tmp = tmp->next;
    }
    cout << "Ukupan broj koraka potrebnih za pretragu je : " << brojac << endl;
}

void setLevel(Nodeptr root)
{
    queue <Nodeptr> queue;
    queue.push(root);
    while (queue.empty() != true) {
        Nodeptr novi = queue.front();
        queue.pop();
        for (size_t i = 0; i < novi->numOfElems + 1; i++)
        {
            if (!novi->isLeaf)
            {
                novi->subTrees[i]->level = novi->level + 1;
                queue.push(novi->subTrees[i]);
            }
        }
    }
}

void printTree(Nodeptr root, int m, int h) {
    queue <Nodeptr> queue;
    int i;
    int lineLength = 62;
    int firstSkip = lineLength;
    int inBetweenSkip;

    setLevel(root);
    queue.push(root);
    for (int j = 0; j < h; j++) {
        if (queue.empty()) break;
        inBetweenSkip = firstSkip;
        firstSkip = (firstSkip - m) / m;
        for (int l = 0; l < firstSkip; l++)
            cout << " ";
        int tmp = pow(m, j);
        for (int k = 0; ; k++)
        {
            if (queue.empty()) break;
            Nodeptr button = queue.front();

            queue.pop();
            if (button)
            {
                cout << "(";
                for (size_t p = 0; p < button->numOfElems + 1; p++)
                {
                    if (!button->isLeaf) queue.push(button->subTrees[p]);
                    if (p != button->numOfElems) cout << button->values[p] % 10000;
                    if (p < button->numOfElems - 1) cout << " ";
                }
                cout << ")";
                if (button->isLeaf && button->next != nullptr) cout << "->";
                if (!queue.empty() && button->level != queue.front()->level) {
                    cout << endl << endl;
                    inBetweenSkip = firstSkip;
                    firstSkip = (firstSkip - m) / m;
                    for (int l = 0; l < firstSkip; l++)
                        cout << " ";
                    continue;
                }
            }
            for (int f = 0; f < inBetweenSkip; f++)
                cout << " ";
        }
    }
    cout << endl << endl;
}

void deleteTree(Nodeptr& root) {
    queue <Nodeptr> queue;
    queue.push(root);
    while (queue.empty() != true) {
        Nodeptr novi = queue.front();
        queue.pop();
        for (size_t i = 0; i < novi->numOfElems + 1; i++)
        {
            if (novi->isLeaf && i != novi->numOfElems) delete novi->zapisi[i];
            else if (!novi->isLeaf) queue.push(novi->subTrees[i]);
        }
        delete novi;
    }
}

int findDivider(Nodeptr node) {
    Nodeptr curr = node->parent;
    for (size_t i = 0; i < curr->numOfElems; i++)
    {
        if (curr->subTrees[i] == node) return i;
    }
}

void deleteKey(Nodeptr node, long long int key, char side) {
    bool flag = false;
    for (size_t i = 0; i < node->numOfElems; i++)
    {

        if (node->values[i] == key) flag = true;
        if (flag) {
            node->values[i] = node->values[i + 1];
            if (node->isLeaf) node->zapisi[i] = node->zapisi[i + 1];
            else {
                if (side == 'l') node->subTrees[i] = node->subTrees[i + 1];
                else node->subTrees[i + 1] = node->subTrees[i + 2];
            }
        }
    }
    if (flag) {
        node->subTrees[node->numOfElems] = nullptr;
        node->numOfElems--;
    }
}

void borrowRight(Nodeptr node, Nodeptr rightBro) {
    int divider = findDivider(node);
    if (node->isLeaf) {
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > rightBro->values[0]) {
                node->values[i] = node->values[i - 1];
                node->zapisi[i] = node->zapisi[i - 1];
            }
            else {
                node->values[i] = rightBro->values[0];
                node->zapisi[i] = rightBro->zapisi[0];
                break;
            }
        }
        node->numOfElems++;
    }
    else {
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > node->parent->values[divider]) {
                node->values[i] = node->values[i - 1];
                node->subTrees[i + 1] = node->subTrees[i];
            }
            else {
                node->values[i] = node->parent->values[divider];
                node->subTrees[i + 1] = rightBro->subTrees[0];
                break;
            }
        }
        node->numOfElems++;
        rightBro->subTrees[0]->parent = node;
    }
    node->parent->values[divider] = rightBro->values[0];
    deleteKey(rightBro, rightBro->values[0], 'l');
}

void borrowLeft(Nodeptr node, Nodeptr leftBro) {
    int divider = findDivider(leftBro);
    int last = leftBro->numOfElems - 1;
    if (node->isLeaf) {
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > leftBro->values[last]) {
                node->values[i] = node->values[i - 1];
                node->zapisi[i] = node->zapisi[i - 1];
            }
            else {
                node->values[i] = leftBro->values[last];
                node->zapisi[i] = leftBro->zapisi[last];
                break;
            }
        }
        node->numOfElems++;
    }
    else {
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > node->parent->values[divider]) {
                node->values[i] = node->values[i - 1];
                node->subTrees[i + 1] = node->subTrees[i];
            }
            else {
                node->values[i] = node->parent->values[divider];
                node->subTrees[i + 1] = leftBro->subTrees[last + 1];
                break;
            }
        }
        node->numOfElems++;
        leftBro->subTrees[last + 1]->parent = node;
    }
    node->parent->values[divider] = leftBro->values[last];
    deleteKey(leftBro, leftBro->values[last], 'r');
}

void mergeWithRight(Nodeptr node, Nodeptr rightBro) {
    int divider = findDivider(node);
    if (!node->isLeaf) {
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > node->parent->values[divider]) {
                node->values[i] = node->values[i - 1];
                node->subTrees[i + 1] = node->subTrees[i];
            }
            else {
                node->values[i] = node->parent->values[divider];
                node->subTrees[i + 1] = rightBro->subTrees[0];
                break;
            }
        }
        node->numOfElems++;
        rightBro->subTrees[0]->parent = node;
    }

    for (size_t j = 0; j < rightBro->numOfElems; j++)
    {
        if (rightBro->isLeaf) {
            for (size_t i = node->numOfElems; i >= 0; i--) {
                if (i && node->values[i - 1] > rightBro->values[j]) {
                    node->values[i] = node->values[i - 1];
                    node->zapisi[i] = node->zapisi[i - 1];
                }
                else {
                    node->values[i] = rightBro->values[j];
                    node->zapisi[i] = rightBro->zapisi[j];
                    break;
                }
            }
            node->numOfElems++;
        }
        else {
            for (size_t i = node->numOfElems; i >= 0; i--) {
                if (i && node->values[i - 1] > rightBro->values[j]) {
                    node->values[i] = node->values[i - 1];
                    node->subTrees[i + 1] = node->subTrees[i];
                }
                else {
                    node->values[i] = rightBro->values[j];
                    node->subTrees[i + 1] = rightBro->subTrees[j + 1];
                    break;
                }
            }
            node->numOfElems++;
            rightBro->subTrees[j + 1]->parent = node;
        }
    }
    deleteKey(node->parent, node->parent->values[divider], 'r');
}

void mergeWithLeft(Nodeptr node, Nodeptr leftBro) {
    int last = leftBro->numOfElems - 1;
    int divider = findDivider(leftBro);
    if (!node->isLeaf) {
        node->subTrees[node->numOfElems + 1] = node->subTrees[node->numOfElems];
        for (size_t i = node->numOfElems; i >= 0; i--) {
            if (i && node->values[i - 1] > node->parent->values[divider]) {
                node->values[i] = node->values[i - 1];
                node->subTrees[i] = node->subTrees[i - 1];
            }
            else {
                node->values[i] = node->parent->values[divider];
                node->subTrees[i] = leftBro->subTrees[last + 1];
                break;
            }
        }
        node->numOfElems++;
        leftBro->subTrees[last + 1]->parent = node;
    }

    for (size_t j = 0; j < leftBro->numOfElems; j++)
    {
        if (leftBro->isLeaf) {
            for (size_t i = node->numOfElems; i >= 0; i--) {
                if (i && node->values[i - 1] > leftBro->values[j]) {
                    node->values[i] = node->values[i - 1];
                    node->zapisi[i] = node->zapisi[i - 1];
                }
                else {
                    node->values[i] = leftBro->values[j];
                    node->zapisi[i] = leftBro->zapisi[j];
                    break;
                }
            }
            node->numOfElems++;
        }
        else {
            node->subTrees[node->numOfElems + 1] = node->subTrees[node->numOfElems];
            for (size_t i = node->numOfElems; i >= 0; i--) {
                if (i && node->values[i - 1] > leftBro->values[j]) {
                    node->values[i] = node->values[i - 1];
                    node->subTrees[i] = node->subTrees[i - 1];
                }
                else {
                    node->values[i] = leftBro->values[j];
                    node->subTrees[i] = leftBro->subTrees[j];
                    break;
                }
            }
            node->numOfElems++;
            leftBro->subTrees[j]->parent = node;
        }
    }
    deleteKey(node->parent, node->parent->values[divider], 'l');
}

void setSuccessor(Nodeptr root) {
    int brojac = 0;
    Nodeptr current, leaf = findLeaf(root, 1, brojac);
    while (leaf) {
        current = leaf;
        while (current->parent && current->parent->subTrees[current->parent->numOfElems] == current) {
            current = current->parent;
        }
        if (current->parent) current->parent->values[findDivider(current)] = leaf->values[leaf->numOfElems - 1];
        leaf = leaf->next;
    }
}

Nodeptr deleteAndRearrange(Nodeptr root, long long int key, int m) {
    int brojac = 0, min;
    Nodeptr  node = findLeaf(root, key, brojac);
    int divider = findDivider(node);
    Nodeptr rightBro = nullptr, leftBro = nullptr;
    deleteKey(node, key, 'r');
    int minInternal = ceil((double)m / 2) - 1;
    int minLeaf = floor((double)m / 2);
    min = minLeaf;
    while (node->numOfElems < min && node != root) {
        int divider = findDivider(node);
        if (divider != 0) {
            leftBro = node->parent->subTrees[divider - 1];
        }
        else leftBro = nullptr;

        if (divider != node->parent->numOfElems) {
            rightBro = node->parent->subTrees[divider + 1];
        }
        else rightBro = nullptr;
        if (rightBro != nullptr && rightBro->numOfElems >= min + 1) borrowRight(node, rightBro);
        else if (leftBro != nullptr && leftBro->numOfElems >= min + 1) borrowLeft(node, leftBro);
        else if (rightBro != nullptr) mergeWithRight(node, rightBro);
        else mergeWithLeft(node, leftBro);
        if (node->parent == root && root->numOfElems == 0) {
            delete root;
            root = node;
            root->parent = nullptr;
            node->next = root;
        }
        node = node->parent;
        min = minInternal;
    }
    setSuccessor(root);
    return root;
}

long long int* unesiNiz(int k) {
    long long int* niz = new long long int[k];
    cout << "Unesi niz:" << endl;
    for (int i = 0; i < k; i++)
    {
        cin >> niz[i];
    }
    return niz;
}

int main()
{
    string file = "CustomerAccount20.txt";
    int m, k, brojac = 0, opcija;
    char c1, c2, c3, c4, c5, c6;
    Zapis* novi = new Zapis;
    long long int key, * niz;
    Nodeptr root = makeNode();
    root->isLeaf = true;
    root->level = 1;
    while (true) {
        cout << "Izaberi opciju:";
        cout << endl << "0) Prekini Program";
        cout << endl << "1) Generisi Indeks";
        cout << endl << "2) Unisti Indeks";
        cout << endl << "3) Ispisi Indeks";
        cout << endl << "4) Dodaj Zapis";
        cout << endl << "5) Obrisi Zapis";
        cout << endl << "6) Pretrazi Zapis";
        cout << endl << "7) Pretrazi K Zapisa";
        cout << endl << "8) Pretrazi K  Sukcesivnih Zapisa";
        cout << endl;
        cin >> opcija;
        switch (opcija) {
        case 0: exit(0);
        case 1: if (root->numOfElems != 0) cout << "Indeks vec postoji." << endl;
              else
        {
            cout << "Unesi M: ";
            cin >> m;
            root = createTree(file, m, root);
            cout << "Stablo kreirano!" << endl;
        }
              break;
        case 2:
            if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
            else {
                deleteTree(root);
                root = makeNode();
                root->isLeaf = true;
            }
            cout << "Stablo obrisano!" << endl;
            break;
        case 3:
            if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
            else {
                setLevel(root);
                brojac = 0;
                Nodeptr tmp = findLeaf(root, 1, brojac);
                printTree(root, m, brojac);
            }
            break;
        case 4:
            cout << "Unesi Zapis: ";
            cin >> novi->CA_ID >> c1 >> novi->CA_B_ID >> c2 >> novi->CA_C_ID >> c3;
            getline(cin, novi->CA_NAME, '|');
            cin >> novi->CA_TAX_ST >> c4 >> novi->CA_BAL;
            insertKey(root, novi->CA_ID, m, novi);
            cout << "Zapis dodat!" << endl;
            break;

        case 5:
            if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
            else {
                cout << "Unesi primarni kljuc: ";
                cin >> key;
                deleteAndRearrange(root, key, m);
                cout << "Zapis obrisan!" << endl;
            }
            break;
        case 6: if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
              else {
            cout << "Unesi primarni kljuc: ";
            cin >> key;
            printZapis(root, key, brojac);
        }
              break;
        case 7: if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
              else {
            cout << "Unesi k: ";
            cin >> k;
            niz = unesiNiz(k);
            brojac = 0;
            searchK(k, niz, brojac, root);
            cout << "Datoteka kreirana!" << endl;
        }
              break;

        case 8: cout << "don't say this number :D" << endl;
            if (root->numOfElems == 0) cout << "Indeks ne postoji." << endl;
            else {
                cout << "Unesi k: ";
                cin >> k;
                cout << "Unesi pocetni primarni kljuc: ";
                cin >> key;
                brojac = 0;
                searchKSucc(k, key, brojac, root);
                cout << "Datoteka kreirana!" << endl;
            }
            break;
        default: cout << "Opcija ne postoji!" << endl;
        }
    }
}
