#include <iostream>
#include <vector>
#include "AvlT.h"

using namespace std;

// insert(int x) dodawanie wezła
// del(int x) usuwanie węzła
//search() przeszukiwanie węzła w kolejności rosnącej


int main()
{
    Avl drzewo;

    drzewo.insert(5);
    drzewo.insert(6);
    drzewo.insert(7);
    drzewo.insert(8);
    drzewo.insert(9);
    drzewo.insert(4);
    drzewo.insert(3);
    drzewo.insert(2);
    drzewo.insert(1);

    drzewo.search();
    cout << endl << "wysokosc korzenia: " << drzewo.root.h << endl;

    drzewo.del(3);
    drzewo.del(1);

    drzewo.search();
    cout << endl << "wysokosc korzenia: " << drzewo.root.h << endl;
}


