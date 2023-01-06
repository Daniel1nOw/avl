#include <iostream>
#include <vector>

using namespace std;


class Avl {
public:
	struct node {
		int wart; // wartoœæ wêz³a 
		node* l;  // wskaŸnik na lewe dziecko
		node* r;  // wskaŸnik na prawe dziecko
		node* par;// wskaŸnik na rodzica
		int h;	  // wysokosc
		int b;    // balans

		node();
	};
	node* now;  // wskaŸnik na bie¿¹cy wêze³
	node root;
	bool emroot;

	Avl();

	void insert(int x);			// dodawanie wez³ów
	void rotacje(node* teraz);
	int hdo(node* hnow1);		// okreœlanie wysokoœci wszystkich wêz³ow
	int bdo(node* hnow1);		// okreœlanie balansu konkretnego wêz³a
	void del(int x);			// usuwanie wêz³ów
	void search();				// przeszukiwanie wêz³a w kolejnoœci rosn¹cej
};