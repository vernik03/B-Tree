#pragma once
#include "TreeNode.h"
using namespace std;


TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new double[2 * t - 1];
    C = new TreeNode * [2 * t];
    n = 0;
}

int TreeNode::FindKey(double k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}
void TreeNode::SplitChild(int i, TreeNode* y) {
    TreeNode* z = new TreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}

TreeNode* TreeNode::Search(double k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->Search(k);
}

void TreeNode::Traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->Traverse();
        cout << " " << keys[i];
    }

    if (leaf == false)
        C[i]->Traverse();
}


void TreeNode::InsertNonFull(double k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            SplitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->InsertNonFull(k);
    }
}

void TreeNode::Merge(int idx) {
    TreeNode* child = C[idx];
    TreeNode* sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

void TreeNode::Deletion(double k) {
    int idx = FindKey(k);

    if (idx < n && keys[idx] == k) {
        if (leaf)
            RemoveFromLeaf(idx);
        else
            RemoveFromNonLeaf(idx);
    }
    else {
        if (leaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            Fill(idx);

        if (flag && idx > n)
            C[idx - 1]->Deletion(k);
        else
            C[idx]->Deletion(k);
    }
    return;
}

void TreeNode::RemoveFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    n--;

    return;
}

void TreeNode::RemoveFromNonLeaf(int idx) {
    double k = keys[idx];

    if (C[idx]->n >= t) {
        int pred = GetPredecessor(idx);
        keys[idx] = pred;
        C[idx]->Deletion(pred);
    }

    else if (C[idx + 1]->n >= t) {
        int succ = GetSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->Deletion(succ);
    }

    else {
        Merge(idx);
        C[idx]->Deletion(k);
    }
    return;
}

int TreeNode::GetPredecessor(int idx) {
    TreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys[cur->n - 1];
}

int TreeNode::GetSuccessor(int idx) {
    TreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys[0];
}

void TreeNode::Fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        BorrowFromPrev(idx);

    else if (idx != n && C[idx + 1]->n >= t)
        BorrowFromPrev(idx);

    else {
        if (idx != n)
            Merge(idx);
        else
            Merge(idx - 1);
    }
    return;
}

void TreeNode::BorrowFromPrev(int idx) {
    TreeNode* child = C[idx];
    TreeNode* sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void TreeNode::BorrowFromNext(int idx) {
    TreeNode* child = C[idx];
    TreeNode* sibling = C[idx + 1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

vector<string> TreeNode::PaintTree(vector<string> strings, int level) {
    if (strings.size() == level) {
        strings.push_back("");
    }
    
    for (int i = 0; i < n; i++) {
        if (!this->leaf) {
            strings = this->C[i]->PaintTree(strings, level + 1);
        }

        strings[level] += to_string(this->keys[i]);
        strings[level] += " ";
        string addition = " ";
        for (int j = 0; j < to_string(this->keys[i]).size(); j++) {
            addition += " ";
        }
        for (int j = 0; j < strings.size(); j++) {
            if (j != level) {
                strings[j] += addition;
            }
        }
    }
    if (!this->leaf) {
        strings = this->C[n]->PaintTree(strings, level + 1);
    }
    return strings;
}
