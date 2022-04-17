#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TreeNode {
public:
    TreeNode() {}
    TreeNode(int t1, bool leaf1); 
    void InsertNonFull(double k);
    void SplitChild(int i, TreeNode* y);
    void Traverse();
    void Fill(int idx);
    void Merge(int idx);
    void Deletion(double k);
    void RemoveFromLeaf(int idx);
    void RemoveFromNonLeaf(int idx);  
    void BorrowFromPrev(int idx);
    void BorrowFromNext(int idx);
    int GetPredecessor(int idx);
    int GetSuccessor(int idx);
    int FindKey(double k);
    friend class BTree;
    TreeNode* Search(double k);
    vector<string> PaintTree(vector<string> strings = {}, int level = 0);
private:
    double* keys;
    TreeNode** C;
    bool leaf;
    int t;
    int n; // t – 1 < n < 2t – 1
};
