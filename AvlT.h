#include <iostream>
#include <vector>

using namespace std;


class Avl {
public:
	struct node {
		int wart; // warto�� w�z�a 
		node* l;  // wska�nik na lewe dziecko
		node* r;  // wska�nik na prawe dziecko
		node* par;// wska�nik na rodzica
		int h;	  // wysokosc
		int b;    // balans

		node();
	};
	node* now;  // wska�nik na bie��cy w�ze�
	node root;
	bool emroot;

	Avl();

	void insert(int x);			// dodawanie wez��w
	void rotacje(node* teraz);
	int hdo(node* hnow1);		// okre�lanie wysoko�ci wszystkich w�z�ow
	int bdo(node* hnow1);		// okre�lanie balansu konkretnego w�z�a
	void del(int x);			// usuwanie w�z��w
	void search();				// przeszukiwanie w�z�a w kolejno�ci rosn�cej
};