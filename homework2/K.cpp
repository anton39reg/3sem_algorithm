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
    int size;
    Node *leftChild;
    Node *rightChild;

    explicit Node(): key(0), size(0), priority(rand()), 
        leftChild(nullptr), rightChild(nullptr) {};
    explicit Node(int mKey): key(mKey), size(1), priority(rand()), 
        leftChild(nullptr), rightChild(nullptr) {};

    void resize();
};

int getSize(Node *a) {
    if (a == nullptr) {
        return 0;
    }
    return a->size;
}

void Node::resize() {
    Node::size = 1 + getSize(Node::leftChild) + getSize(Node::rightChild);
}

class Treap {
public:
    explicit Treap(): parent(nullptr), size(0) {}

    void add(int key) {
        if (find(key)) {
            return;
        }

        Node *newNode = new Node(key);
        pair<Node*, Node*> tmp(nullptr, nullptr);

        tmp = split(parent, key);
        newNode = merge(tmp.first, newNode);
        parent = merge(newNode, tmp.second);

        ++size;
    }

    void remove(int key) {
        if (!find(key)) {
            return;
        }
        pair<Node*, Node*> tmp1(nullptr, nullptr);
        pair<Node*, Node*> tmp2(nullptr, nullptr);
        tmp1 = split(parent, key);
        tmp2 = split(tmp1.second, key+1);
        parent = merge(tmp1.first, tmp2.second);
        delete tmp2.first;
    }

    void next(int key) {
        pair<Node*, Node*> tmp(nullptr, nullptr);
        tmp = split(parent, key + 1);
        Node *cur; 
        if (tmp.second == nullptr) {
            cout << "none" << endl;
            return;
        }
        cur = tmp.second;
        while (cur->leftChild != nullptr) {
            cur = cur->leftChild;
        }
        cout << cur->key << endl;
        parent = merge(tmp.first, tmp.second);
    }
    
    void prev(int key) {
        pair<Node*, Node*> tmp(nullptr, nullptr);
        tmp = split(parent, key);
        Node *cur; 
        if (tmp.first == nullptr) {
            cout << "none" << endl;
            return;
        }
        cur = tmp.first;
        while (cur->rightChild != nullptr) {
            cur = cur->rightChild;
        }
        cout << cur->key << endl;
        parent = merge(tmp.first, tmp.second);
    }

    void exists(int key) {
        if (find(key)) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
    }

    void kth(int numb) {
        Node *tmp = parent;
        while (tmp) {
            if (getSize(tmp->leftChild) == numb - 1) {
                cout << tmp->key << endl;
                return;
            }
            else if (getSize(tmp->leftChild) < numb - 1) {
                numb -= (getSize(tmp->leftChild) + 1);
                tmp = tmp->rightChild;
            }
            else {
                tmp = tmp->leftChild;
            }
        }
        cout << "none" << endl;
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
            //cout << tmp->key << endl;
            delete tmp;
        }
    }

private:
    bool find(int key) {
        Node *tmp = parent;
        while (tmp) {
            if (tmp->key == key) {
                return 1;
            } 
            else if (tmp->key > key) {
                tmp = tmp->leftChild;
            }
            else {
                tmp = tmp->rightChild;
            }
        }
        return 0;
    }

    Node* merge(Node *left, Node *right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr){
            return left;
        }
        else {
            if (left->priority > right->priority) {
                left->rightChild = merge(left->rightChild, right);
                left->resize();
                return left;
            }
            else {
                right->leftChild = merge(left, right->leftChild);
                right->resize();
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
        base->resize();
    }

    Node *parent;
    size_t size;
};

int main() {
    int k;
    Treap treap;
    string command;
    while (cin >> command) {
        cin >> k;
        if (command == "insert") {
            treap.add(k);
        }
        else if (command == "exists") {
            treap.exists(k);
        }
        else if (command == "delete") {
            treap.remove(k);
        }
        else if (command == "next") {
            treap.next(k);
            
        }
        else if (command == "prev") {
            treap.prev(k);
        }
        else if (command == "kth") {
            treap.kth(k);
        }
    }
}
