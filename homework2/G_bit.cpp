#include <iostream>
#include <vector>

using namespace std;

class BinIndexedTree {
public:
    BinIndexedTree(const vector<long long> &m_data): tree(m_data.size(), 0),
        data(m_data), size(m_data.size()) {
        for (int i = 0; i < size; ++i) {
            add(i, data[i]);
        }    
    }

    void update(int i, int val) {
        int d = val - data[i];
        data[i] = val;
        add(i, d);
    }

    long long rsq(int l, int r) const {
        return sum(r) - sum(l - 1);
    }

    void add(int i, int d) {
        while (i < size) {
            tree[i] += d;
            i = i | (i + 1);
        }
    }
private:
    long long sum(int i) const {
        long long res = 0;
        while (i >= 0) {
            res += tree[i];
            i = (i & (i + 1)) - 1;
        }
        return res;
    }
    
    vector<long long> data;
    vector<long long> tree;
    long long size;
};

int main() {
    int n; 
    cin >> n;
    vector<long long> data(n);

    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    BinIndexedTree tree(data);

    long long q, l, r, newValue;
    string command;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> command;
        if (command == "s") {
            cin >> l >> r;
            cout << tree.rsq(l - 1, r - 1) << " ";
        }
        else if (command == "u") {
            cin >> l >> newValue;
            tree.update(l - 1, newValue);
        }
    }
    cout << endl;
}
