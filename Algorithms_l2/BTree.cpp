#pragma once
#include "BTree.h"

BTree::BTree(int temp) {
    root = NULL;
    t = temp;
}


void BTree::Insert(double k) {
    if (root == NULL) {
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            TreeNode* s = new TreeNode(t, false);

            s->C[0] = root;

            s->SplitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->InsertNonFull(k);

            root = s;
        }
        else
            root->InsertNonFull(k);
    }
}

void BTree::TraverseTree() {
    if (root != NULL)
    {
        root->Traverse();
    }
}

TreeNode* BTree::Search(double k) {
    if (root == NULL)
    {
        return root;
    }
    else
    {
        return root->Search(k);
    }
}
vector<string> BTree::PaintTree() {
    cout << endl;
    vector<string> res = this->root->PaintTree();
    for (string elem : res) {
        cout << elem << endl;
    }
    return res;
}

void BTree::Find(double k) {
    if (Search(k))
    {
        cout << k << " is found" << endl;
    }
    else
    {
        cout << k << " is not Found" << endl;
    }
}

void BTree::ArrInsert(vector<double> input) {
    for (double in_elem : input)
    {
        Insert(in_elem);
    }
}
void BTree::Delete(double k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->Deletion(k);

    if (root->n == 0) {
        TreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}