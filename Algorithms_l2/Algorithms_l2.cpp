#include <iostream>
#include <vector>
#include <string>
#include "BTree.h"

using namespace std;

int main() {
    BTree t(2);
    t.ArrInsert({ 8.5,9.1,10.286,11,12});

    //t.ArrInsert({8.5,9.1,10.286,11.0,15.245,16,17.86,18,20.45,23.0});

    cout << "The B-tree is: ";
    t.TraverseTree();

    t.PaintTree();
    cout << endl;
    t.Find(10.286);
    t.Delete(10.286);
    t.Find(10.286);
    t.Find(3);
}