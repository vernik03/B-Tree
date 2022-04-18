#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "TreeNode.h"
using namespace std;

class BTree{
public:
    BTree(int temp);
    void TraverseTree();
    TreeNode* Search(double k);
    void Insert(double k);
    void Insert(vector<double> input);
    void Delete(double k);
    vector<string> PaintTree();
    void Find(double k);
private:
    TreeNode* root;
    int t;
};