#include <iostream>
#include <vector>
#include <string>
#include "BTree.h"

using namespace std;

int main() {
    BTree t(2);
    //t.Insert({8.5,9.1,10.286,11,21,15.5,10,22});

    for (int i = 1; i < 51; i++)
    {
        t.Insert(i);
    }
    t.PaintTree();
    for (double i = 5; i < 46; i++)
    {
        t.Delete(i);
    }
    t.PaintTree();
    //t.ArrInsert({8.5,9.1,10.286,11.0,15.245,16,17.86,18,20.45,23.0});

    // cout << "The B-tree is: ";
    //t.TraverseTree();
   // t.Delete(11);
   
   //t.Find(10.286);
    //t.Find(3);

    //t.Find(10.286);

    //t.Find(11);
    //t.Insert(2);
    //t.Insert(20);
    //t.Insert(13.1);
    //t.PaintTree();
    //t.Delete(11);
    //t.PaintTree();

    //t.Find(11);


}