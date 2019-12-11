#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <memory>

using namespace std;

class Node {
public:
    long long key;
    int priority;
    long long sum;
    Node * leftChild;
    Node * rightChild;

    explicit Node(): key(0), priority(rand()), sum(0), 
        leftChild(nullptr), rightChild(nullptr) {};
    explicit Node(long long mKey): key(mKey), priority(rand()), sum(mKey),
        leftChild(nullptr), rightChild(nullptr) {};

    void resum();
};

long long getSum(Node * a) {
    if (a == nullptr) {
        return 0;
    }
    return a->sum;
}

void Node::resum() {
    Node::sum = Node::key + getSum(Node::leftChild) + getSum(Node::rightChild);
}

class Treap {
public:
    explicit Treap(): parent(nullptr), size(0) {}

    void add(long long key) {
        if (find(key)) {
            return;
        }

        Node * newNode(new Node(key));
        pair<Node *, Node *> tmp(nullptr, nullptr);

        tmp = split(parent, key);
        newNode = merge(tmp.first, newNode);
        parent = merge(newNode, tmp.second);

        ++size;
    }

    long long sum(long long l, long long r) {
        pair<Node *, Node *> tmp1(nullptr, nullptr);
        pair<Node *, Node *> tmp2(nullptr, nullptr);

        tmp1 = split(parent, l);
        tmp2 = split(tmp1.second, r + 1);
        long long res = getSum(tmp2.first);
        parent = merge(tmp1.first, merge(tmp2.first, tmp2.second));
        return res;
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
    bool find(long long key) {
        Node * tmp = parent;
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

    Node * merge(Node * left, Node * right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr){
            return left;
        }
        else {
            if (left->priority > right->priority) {
                left->rightChild = merge(left->rightChild, right);
                left->resum();
                return left;
            }
            else {
                right->leftChild = merge(left, right->leftChild);
                right->resum();
                return right;
            }
        }
    }

    pair<Node *, Node *> split(Node * base, 
        long long val) {
        if (base == nullptr) {
            return pair<Node *, Node *>(nullptr, nullptr);
        }
        else {
            if (val > base->key) {
                pair<Node *, Node *> tmp = 
                    split(base->rightChild, val);
                base->rightChild = tmp.first;
                base->resum();
                return pair<Node *, Node *>(base, tmp.second);
            }
            else {
                pair<Node *, Node *> tmp = 
                    split(base->leftChild, val);
                base->leftChild = tmp.second;
                base->resum();
                return pair<Node *, Node *>(tmp.first, base);
            }
        }
    }

    Node * parent;
    size_t size;
};

int main() {
    long long k, n;
    int l, r;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n;
    Treap treap;
    string command;
    long long lastSum = 0;
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "+") {
            cin >> k;
            if (flag == 2) {
                k = (k + lastSum) % 1000000000; 
            }
            treap.add(k);
            flag = 1;
        }
        else if (command == "?") {
            cin >> l >> r;
            lastSum = treap.sum(l, r);
            cout << lastSum << endl;
            flag = 2;
        }
    }
}
