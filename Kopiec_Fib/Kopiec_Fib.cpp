#include <iostream>
#include "kopiec.h"


int main()
{
    kopiec nr1;
    nr1.add(7);
    nr1.add(19);
    nr1.add(8);
    nr1.add(2);
    nr1.add(17);

    kopiec nr2;
    nr2.add(13);
    nr2.add(5);
    nr2.add(30);
    nr2.add(10);
    nr2.add(15);
    nr2.add(21);

    nr1.add(nr2);

    // kopiec: 2 5 7 8 10 13 15 17 19 21 30

    nr1.decreaseKey(7, 4);

    // kopiec: 2 4 5 8 10 13 15 17 19 21 30

    nr1.delMin(); // 2
    nr1.delMin(); // 4
    nr1.decreaseKey(19, 9);

    // kopiec: 5 8 9 10 13 15 17 21 30

    nr1.delMin(); // 5
    nr1.delMin(); // 8
    nr1.delMin(); // 9
    nr1.delMin(); // 10

}


