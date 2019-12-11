#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

class Node {
public:
    int key;
    int priority;
    int number;
    Node *leftChild;
    Node *rightChild;

    explicit Node(int mKey = 0, int mPriority = 0, int mNumber = 0): key(mKey), 
        priority(mPriority), number(mNumber), leftChild(nullptr), 
        rightChild(nullptr) {};
};


class Treap {
public:
    explicit Treap(): parent(nullptr), size(0) {}

    void add(int key, int priority, int number) {
        Node *newNode = new Node(key, priority, number);
        pair<Node*, Node*> tmp(nullptr, nullptr);

        tmp = split(parent, key);
        newNode = merge(tmp.first, newNode);
        parent = merge(newNode, tmp.second);

        ++size;
    }
    
    void print() {
        if (size == 0) {
            return;
        }
        vector<int> par(size, 0);
        vector<int> left(size, 0);
        vector<int> right(size, 0);
        queue<Node*> q;
        q.push(parent);
        Node *tmp;
        while (!q.empty()) {
            tmp = q.front();
            int curNumber = tmp->number;
            q.pop();
            if (tmp->leftChild != nullptr) {
                q.push(tmp->leftChild);
                left[curNumber] = tmp->leftChild->number + 1;
                par[tmp->leftChild->number] = curNumber + 1;
            }
            if (tmp->rightChild != nullptr) {
                q.push(tmp->rightChild);
                right[curNumber] = tmp->rightChild->number + 1;
                par[tmp->rightChild->number] = curNumber + 1;
            }
        }
        cout << "YES" << endl;
        for (int i = 0; i < size; ++i) {
            cout << par[i] << " " << left[i] << " " << right[i] << endl;
        }
    }
    ~Treap() {
        if (parent == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(parent);
        Node *tmp;
        while (!q.empty()) {
            tmp = q.front();
            q.pop();
            if (tmp->leftChild != nullptr) {
                q.push(tmp->leftChild);
            }
            if (tmp->rightChild != nullptr) {
                q.push(tmp->rightChild);
            }
            delete tmp;
        }
    }

private:
    Node* merge(Node *left, Node *right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr){
            return left;
        }
        else {
            if (left->priority < right->priority) {
                left->rightChild = merge(left->rightChild, right);
                return left;
            }
            else {
                right->leftChild = merge(left, right->leftChild);
                return right;
            }
        }
    }

    pair<Node*, Node*> split(Node *base, int val) {
        if (base == nullptr) {
            return pair<Node*, Node*>(nullptr, nullptr);
        }
        else {
            if (val > base->key) {
                pair<Node*, Node*> tmp = split(base->rightChild, val);
                base->rightChild = tmp.first;
                return pair<Node*, Node*>(base, tmp.second);
            }
            else {
                pair<Node*, Node*> tmp = split(base->leftChild, val);
                base->leftChild = tmp.second;
                return pair<Node*, Node*>(tmp.first, base);
            }
        }
    }

    Node *parent;
    size_t size;
};

int main() {
    int n;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n;
    vector<tuple<int, int, int>> data(n);

    int k, p;
    for (int i = 0; i < n; ++i) {
        cin >> k >> p;
        data[i] = make_tuple(k, p, i);
    }
    sort(data.begin(), data.end());
    Treap treap;
    for (int i = 0; i < n; ++i) {
        treap.add(get<0>(data[i]), get<1>(data[i]), get<2>(data[i]));
    }
    treap.print();
}
