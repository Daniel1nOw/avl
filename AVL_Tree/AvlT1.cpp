#include <iostream>
#include <vector>
#include "AvlT.h"

using namespace std;


Avl::node::node() {
	l = NULL;
	r = NULL;
	h = -1;
}

Avl::Avl() {
	root.par = NULL;
	emroot = true;
}

void Avl::insert(int x) {
    if (emroot == true) {
        root.wart = x;
        emroot = false;
        return;
    }
    now = &root;
    node* p = new node;
    p->wart = x;

    while (true) {
        if (x < now->wart) {
            if (now->l == NULL) {
                now->l = p;
                p->par = now;
                hdo(&root);
                rotacje(now);
                return;
            }
            now = now->l;
            continue;
        }
        else if (x > now->wart) {
            if (now->r == NULL) {
                now->r = p;
                p->par = now;
                hdo(&root);
                rotacje(now);
                return;
            }
            now = now->r;
            continue;
        }
        else return;
    }
}

void Avl::rotacje(node* teraz) {
    while (now != NULL) {
        if (bdo(now) < -1) {
            if (now->r->b == 1) { // podwójna rotacja
                node* tempr = now->r;
                now->r = now->r->l;
                now->r->par = now;
                node* temprr = now->r->r;
                now->r->r = tempr;
                now->r->r->par = now->r;
                now->r->r->l = temprr;
                if (now->r->r->l != NULL)
                    now->r->r->l->par = now->r->r;
                hdo(&root);
                bdo(now);
                bdo(now->r);
                bdo(now->r->r);
            } // rotacja rr
            if (now->par != NULL)
                now->par->r = now->r;
            now->r->par = now->par;
            now->par = now->r;
            now->r = now->r->l;
            if (now->par->l != NULL)
                now->par->l->par = now;
            now->par->l = now;

            if (now == &root) {     //zmiana korzenia na inny wêze³
                node* pc = new node;
                *pc = *now;
                root = *now->par;
                now->l = pc;
                now->l->par = now;
                now->r->par = now;
                if (now->l->l != NULL)
                    now->l->l->par = now->l;
                if (now->l->r != NULL)
                    now->l->r->par = now->l;
                now = now->l;
            }

            hdo(&root);
            bdo(now);
            bdo(now->par);
            bdo(now->par->r);
            if (now->par != NULL)
                now = now->par->par;
        }
        else if (bdo(now) > 1) {
            if (bdo(now->l) == -1) {    // podwójna rotacja
                node* tempr = now->l;
                now->l = now->l->r;
                now->l->par = now;
                node* temprr = now->l->l;
                now->l->l = tempr;
                now->l->l->par = now->l;
                now->l->l->r = temprr;
                if (now->l->l->r != NULL)
                    now->l->l->r->par = now->l->l;
                hdo(&root); // aktualizacja wysokosci i balansu wezlow
                bdo(now);
                bdo(now->l);
                bdo(now->l->l);
            } // rotacja ll
            if (now->par != NULL)
                now->par->l = now->l;
            now->l->par = now->par;
            now->par = now->l;
            now->l = now->l->r;
            if (now->par->r != NULL)
                now->par->r->par = now;
            now->par->r = now;

            if (now == &root) {     //zmiana korzenia na inny wêze³
                node* pc = new node;
                *pc = *now;
                root = *now->par;
                now->r = pc;
                now->r->par = now;
                now->l->par = now;
                if (now->r->l != NULL)
                    now->r->l->par = now->r;
                if (now->r->r != NULL)
                    now->r->r->par = now->r;
                now = now->r;
            }

            hdo(&root); // aktualizacja wysokosci i balansu wezlow
            bdo(now);
            bdo(now->par);
            bdo(now->par->l);
            if (now->par != NULL)
                now = now->par->par;
        }
        else now = now->par;
    }
}

int Avl::hdo(node* hnow1) {
    node* hnow = hnow1;

    if (hnow->l == NULL && hnow->r == NULL) {
        hnow->h = 0;
        return 0;
    }
    else if (hnow->l == NULL && hnow->r != NULL) {
        hnow->h = hdo(hnow->r) + 1;
        return hdo(hnow->r) + 1;
    }
    else if (hnow->l != NULL && hnow->r == NULL) {
        hnow->h = hdo(hnow->l) + 1; 
        return hdo(hnow->l) + 1;
    }
    else if (hnow->l != NULL && hnow->r != NULL) {
        if (hdo(hnow->l) > hdo(hnow->r)) {
            hnow->h = hdo(hnow->l) + 1;
            return hdo(hnow->l) + 1;
        }
        else {
            hnow->h = hdo(hnow->r) + 1;
            return hdo(hnow->r) + 1;
        }
    }
}

int Avl::bdo(node* hnow1) {
    node* hnow = hnow1;

    if (hnow->l == NULL && hnow->r == NULL) {
        hnow->b = 0;
        return 0;
    }
    else if (hnow->l == NULL && hnow->r != NULL) {
        hnow->b = 0 - hnow->r->h - 1;
        return 0 - hnow->r->h - 1;
    }
    else if (hnow->l != NULL && hnow->r == NULL) {
        hnow->b = hnow->l->h + 1;
        return hnow->l->h + 1;
    }
    else if (hnow->l != NULL && hnow->r != NULL) {
        hnow->b = hnow->l->h - hnow->r->h;
        return hnow->l->h - hnow->r->h;
    }
}

void Avl::del(int x) {
    if (emroot == true) {
        cout << "brak elementow do usuniecia " << endl;
        return;
    }
    else if (root.l == NULL && root.r == NULL) { // istnieje tylko korzen
        emroot = true;
        return;
    }
    now = &root;
    while (true) {

        if (now->wart == x)
        {
            if (now->l == NULL && now->r == NULL) //usuwany wezel jest lisciem
            {
                node* usun = now;
                if (now->par->wart < now->wart) {
                    now = now->par;
                    delete usun;
                    now->r = NULL;
                }
                else {
                    now = now->par;
                    delete usun;
                    now->l = NULL;
                }
                hdo(&root);
                rotacje(now);
                return;
            }
            else if (now->l == NULL && now->r != NULL) //wezel ma tylko prawego potomka
            {
                node* usun = now;
                node* nprawy = now->r;
                node* rodz = now->par;

                if (now->wart == root.wart) { // jesli usuwany wezel jest korzeniem
                    root = *root.r;
                    root.par = NULL;
                }
                else {

                    if (now->wart > now->par->wart) {
                        now = now->par;
                        now->r = nprawy;
                        now->r->par = rodz;
                        delete usun;
                    }
                    else {
                        now = now->par;
                        now->l = nprawy;
                        now->l->par = rodz;
                        delete usun;
                    }
                }
                hdo(&root);
                rotacje(now);
                return;
            }
            else if (now->l != NULL && now->r == NULL) //wezel ma tylko lewego potomka
            {
                node* usun = now;
                node* nlewy = now->l;
                node* rodz = now->par;

                if (now->wart == root.wart) { // jesli usuwany wezel jest korzeniem
                    root = *root.l;
                    root.par = NULL;
                }
                else {

                    if (now->wart > now->par->wart) {
                        now = now->par;
                        now->r = nlewy;
                        now->r->par = rodz;
                        delete usun;
                    }
                    else {
                        now = now->par;
                        now->l = nlewy;
                        now->l->par = rodz;
                        delete usun;
                    }
                }
                hdo(&root);
                rotacje(now);
                return;
            }

            else if (now->l != NULL && now->r != NULL)  // wezel ma obu potomkow
            {
                node* usun = now;
                node* rodz = now->par;
                node* temp;

                now = now->l;
                while (now->r != NULL) {
                    now = now->r;
                }
                temp = now;
                temp->wart = now->wart;
                now = usun;
                now->wart = temp->wart;
                now = temp;
                x = temp->wart;
            }
        } // chodzenie prawo/lewo:
        else if ((x < now->wart && now->l == NULL) || (x > now->wart && now->r == NULL)) {
            cout << "element nie istnieje" << endl;
            return;
        }
        else if (x < now->wart) {
            now = now->l;
        }
        else if (x > now->wart) {
            now = now->r;
        }
    }
}

void Avl::search() {
    now = &root;
    vector<int> odwiedzone;
    //odwiedzone.clear();
    bool nieodw = false;
    int opcja = 1;

    if (emroot == true) return;

    while (now->l != NULL) { // do ostatniego elementu po lewej
        now = now->l;
    }
    cout << now->wart << " ";
    odwiedzone.push_back(now->wart);

    while (true) {
        nieodw = false;
        switch (opcja) {
        case 1:
        {
            if (now->r == NULL) {
                if (now->par == NULL) return;
                now = now->par;
                while (nieodw == false) {
                    nieodw = true;
                    for (vector<int>::iterator it = odwiedzone.begin(); it != odwiedzone.end(); ++it) {
                        if (now->wart == *it) {
                            nieodw = false;
                            it = odwiedzone.end() - 1;
                        }
                    }
                    if (nieodw == true) {
                        cout << now->wart << " ";
                        odwiedzone.push_back(now->wart);
                        if (now->par == NULL && now->r != NULL) {
                            opcja = 2;
                            continue;
                        }
                        opcja = 1;
                    }
                    else {
                        if (now->par == NULL) return;
                        now = now->par;
                    }
                }
            }
            else opcja = 2;
        }
        break;
        case 2:
        {
            now = now->r;
            if (now->l == NULL) {
                cout << now->wart << " ";
                odwiedzone.push_back(now->wart);
                opcja = 1;
            }
            else opcja = 3;
        }
        break;
        case 3:
        {
            now = now->l;
            if (now->l == NULL) {
                cout << now->wart << " ";
                odwiedzone.push_back(now->wart);
                opcja = 1;
            }
            else opcja = 3;
        }
        }
    }
}