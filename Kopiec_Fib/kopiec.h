#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class kopiec {
public:
    struct node {
        int wart;
        node* rodz;
        list<node> child;
        int stopien;
        bool dousun;

        node(int x, node* rdz);

    };

    list<node>::iterator najmniej;
    list<node> roots;
    list<node> newroots;

    vector<node*> stopnie;

    void add(int x);
    void add(kopiec meld);
    void getMin();
    void delMin();
    void seeroots();
    void decreaseKey(int x, int y);
    void checkch(list<node>* adr, int x, int y);
    void delch(list<node>* adr, int y);
};