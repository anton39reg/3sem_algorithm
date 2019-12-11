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

Node * merge(Node *leftPart, Node *rightPart) {
    if (leftPart == nullptr) {
        return rightPart;
    }
    if (rightPart == nullptr) {
        return leftPart;
    }
    if (leftPart->priority < rightPart->priority) {
        leftPart->rightChild = merge(leftPart->rightChild, rightPart);
        return leftPart;
    }
    else {
        rightPart->leftChild = merge(leftPart, rightPart->leftChild);
        return rightPart;
    }

}

Node * buildTreap(const vector<tuple<int, int, int>> &data, int left, int right) {
    if (left == right) {
        return new Node(get<0>(data[left]), get<1>(data[left]), 
            get<2>(data[left]));
    }
    int mid = (left + right) / 2;
    Node * leftPart = buildTreap(data, left, mid);
    Node * rightPart = buildTreap(data, mid + 1, right);
    return merge(leftPart, rightPart);
}

void print(Node *parent, int size) {
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

    Node *parent = buildTreap(data, 0, n - 1);
    print(parent, n);
}

