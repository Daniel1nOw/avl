#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "kopiec.h"


kopiec::node::node(int x, node* rdz) {
    wart = x;
    rodz = rdz;
    stopien = 0;
}

void kopiec::add(int x) {

    node nowy(x, NULL);
    nowy.wart = x;
    roots.push_back(nowy);
    if (roots.size() == 1)
        najmniej = roots.begin();
    if (x < najmniej->wart) {
        najmniej = roots.end();
        --najmniej;
    }

}

void kopiec::add(kopiec meld) {
    for (list<node>::iterator it = meld.roots.begin(); it != meld.roots.end(); it++) {
        roots.push_back(*it);
        if (it->wart < najmniej->wart) {
            najmniej = roots.end();
            --najmniej;
        }
    }
}

void kopiec::getMin() {
    if (roots.empty() == false)
        cout << najmniej->wart;
}

void kopiec::delMin() { //zwraca najmniejszy element i go usuwa:
    if (roots.empty() == true)
        return;
    int ips;
    for (int i = 0; i < 3; i++) {
        stopnie.push_back(NULL);
    }
    if (najmniej->child.empty() == false) { //dzieci usuwanego dodaj do root listy
        for (list<node>::iterator it = najmniej->child.begin(); it != najmniej->child.end(); ++it) {
            roots.push_back(*it);
            it->stopien = it->child.size(); // stopien korzenia = liczba jego dzieci
        }
    }
    cout << najmniej->wart << " "; // zmienic na return wartosc zamiast drukowac?
    roots.erase(najmniej); //usuwanie najmniejszego klucza
    if (roots.empty() == true) return;
    for (list<node>::iterator it = roots.begin(); it != roots.end(); it++) {
        if (stopnie.size() - 2 < it->stopien) {
            stopnie.push_back(NULL);
            stopnie.push_back(NULL);
        }
        if (stopnie[it->stopien] == NULL) {
            stopnie[it->stopien] = &(*it);
            continue;
        }
        else {
            if (it->wart < stopnie[it->stopien]->wart) {
                it->child.push_back(*stopnie[it->stopien]);
                stopnie[it->stopien]->rodz = &(*it);
                stopnie[it->stopien] = &(*it);
                it->stopien++;
                ips = it->stopien;
            }
            else { // jesli obecny root jest wiekszy to idzie jako childo do tego z listy
                stopnie[it->stopien]->child.push_back(*it);
                it->rodz = stopnie[it->stopien];
                stopnie[it->stopien]->stopien++;
                ips = stopnie[it->stopien]->stopien;
            }
        }
        // pierwsze porownania sprawdzaja root w root liscie vs element w liscie stopnie
        // a w petli nizej porownania tylko miedzy elementami listy stopnie

        int iter = 0;
        // - drugi element
        while (iter == 0) {
            if (stopnie.size() - 2 < ips) {
                stopnie.push_back(NULL);
                stopnie.push_back(NULL);
            }
            if (stopnie[ips] == NULL) {
                stopnie[ips] = stopnie[ips - 1];
                stopnie[ips - 1] = NULL;
                iter = 2;
                if (stopnie.size() - 2 < ips) {
                    stopnie.push_back(NULL);
                    stopnie.push_back(NULL);
                }
            }
            else if (stopnie[ips]->wart < stopnie[ips - 1]->wart) {
                stopnie[ips]->child.push_back(*stopnie[ips - 1]);
                stopnie[ips - 1]->rodz = stopnie[ips];
                stopnie[ips]->stopien++;
                stopnie[ips - 1] = NULL;
                ips++;
            }
            else {
                stopnie[ips - 1]->child.push_back(*stopnie[ips]);
                stopnie[ips]->rodz = stopnie[ips - 1];
                stopnie[ips] = stopnie[ips - 1];
                stopnie[ips - 1] = NULL;
                stopnie[ips]->stopien++;
                ips++;
            }

        }
    }
    //usniecie rootwow starych i dodanie nowych z listy stopnie


    for (int i = 0; i < stopnie.size(); i++) {
        if (stopnie[i] != NULL) {
            newroots.push_back(*stopnie[i]);
        }
    }
    stopnie.clear();
    roots.clear();
    for (list<node>::iterator it = newroots.begin(); it != newroots.end(); ++it) {
        roots.push_back(*it);
    }

    newroots.clear();
    najmniej = roots.begin();
    for (list<node>::iterator it = roots.begin(); it != roots.end(); ++it) {

        if (it->wart < najmniej->wart) {
            najmniej = it;

        }
    }
}

void kopiec::seeroots() {
    for (list<node>::iterator it = roots.begin(); it != roots.end(); ++it) {

        cout << it->wart << ", ";
    }
}
void kopiec::decreaseKey(int x, int y) {
    for (list<node>::iterator it = roots.begin(); it != roots.end(); ++it) {
        if (it->wart == x) {
            it->wart = y;
            if(it->rodz != NULL)
                roots.push_back(*it);
            if (y < najmniej->wart) {
                najmniej = roots.end();
                --najmniej;
            }
        }
        if (it->child.empty() == false) {
            //list<node>* childmierz = &it->child;
            checkch(&it->child, x, y);
        }

    }
}

void kopiec::checkch(list<node>* adr, int x, int y) {
    for (list<node>::iterator it2 = adr->begin(); it2 != adr->end(); ++it2) {
        if (it2->wart == x) {
            it2->wart = y;
            roots.push_back(*it2);
            if (y < najmniej->wart) {
                najmniej = roots.end();
                --najmniej;
            }

            for (list<node>::iterator it = roots.begin(); it != roots.end(); ++it) {
                if (it->child.empty() == false) delch(&it->child, y);
            }

            return;
        }
        if (it2->child.empty() == false) {
            checkch(&it2->child, x, y);
        }
    }
}
void kopiec::delch(list<node>* adr, int y) {
    for (list<node>::iterator it2 = adr->begin(); it2 != adr->end(); ++it2) {
        if (it2->wart == y) {
            adr->erase(it2);
            return;
        }
        if (it2->child.empty() == false) {
            delch(&it2->child, y);
        }
    }
}