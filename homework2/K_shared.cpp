#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <memory>

using namespace std;

class Node {
public:
    int key;
    int priority;
    int size;
    shared_ptr<Node> leftChild;
    shared_ptr<Node> rightChild;

    explicit Node(): key(0), size(0), priority(rand()), 
        leftChild(nullptr), rightChild(nullptr) {};
    explicit Node(int mKey): key(mKey), size(1), priority(rand()), 
        leftChild(nullptr), rightChild(nullptr) {};

    void resize();
};

int getSize(shared_ptr<Node> a) {
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

        shared_ptr<Node> newNode(new Node(key));
        pair<shared_ptr<Node>, shared_ptr<Node>> tmp(nullptr, nullptr);

        tmp = split(parent, key);
        newNode = merge(tmp.first, newNode);
        parent = merge(newNode, tmp.second);

        ++size;
    }

    void remove(int key) {
        if (!find(key)) {
            return;
        }
        pair<shared_ptr<Node>, shared_ptr<Node>> tmp1(nullptr, nullptr);
        pair<shared_ptr<Node>, shared_ptr<Node>> tmp2(nullptr, nullptr);
        tmp1 = split(parent, key);
        tmp2 = split(tmp1.second, key + 1);
        parent = merge(tmp1.first, tmp2.second);
    }

    void next(int key) {
        pair<shared_ptr<Node>, shared_ptr<Node>> tmp(nullptr, nullptr);
        tmp = split(parent, key + 1);
        shared_ptr<Node> cur; 
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
        pair<shared_ptr<Node>, shared_ptr<Node>> tmp(nullptr, nullptr);
        tmp = split(parent, key);
        shared_ptr<Node> cur; 
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
        shared_ptr<Node> tmp = parent;
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
    

private:
    bool find(int key) {
        shared_ptr<Node> tmp = parent;
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

    shared_ptr<Node> merge(shared_ptr<Node> left, shared_ptr<Node> right) {
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

    pair<shared_ptr<Node>, shared_ptr<Node>> split(shared_ptr<Node> base, 
        int val) {
        if (base == nullptr) {
            return pair<shared_ptr<Node>, shared_ptr<Node>>(nullptr, nullptr);
        }
        else {
            if (val > base->key) {
                pair<shared_ptr<Node>, shared_ptr<Node>> tmp = 
                    split(base->rightChild, val);
                base->rightChild = tmp.first;
                return pair<shared_ptr<Node>, shared_ptr<Node>>(base, tmp.second);
            }
            else {
                pair<shared_ptr<Node>, shared_ptr<Node>> tmp = 
                    split(base->leftChild, val);
                base->leftChild = tmp.second;
                return pair<shared_ptr<Node>, shared_ptr<Node>>(tmp.first, base);
            }
        }
        base->resize();
    }

    shared_ptr<Node> parent;
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
