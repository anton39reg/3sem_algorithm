#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

enum {INF = -(1 << 30)};


int left(int i) {
    return 2*i + 1;
}

int right(int i) {
    return 2*i + 2;
}


class Node {
public:
    uint64_t value;

    Node(): value(0){}
};

class SegmentTree {
public:
    explicit SegmentTree(const vector<uint64_t> &data): 
        tree((1 << (int(log2(data.size() - 1)) + 2)) - 1) {
        int n = (1 << (int(log2(data.size() - 1)) + 1));
        for (int i = 0; i < data.size(); ++i) {
            tree[i + n - 1].value = data[i];
        }
    }

    uint64_t get(int v) const {
        uint64_t ans;
        int n = tree.size() / 2;
        v += n;
        ans = tree[v].value;
        // cout << l << " " << r << endl;
        while (v) {
            v = (v - 1) / 2;
            ans += tree[v].value;
        }
        return ans;       
    }

    void update(uint64_t add, int l, int r) {
        int n = tree.size() / 2;
        l += n;
        r += n;
        while (l <= r) {
            if (!(l & 1)) {
                tree[l].value += add;
            }
            if (r & 1) {
                tree[r].value += add;
            }
            l = l / 2;
            if (r - 2 < 0) {
                break;
            }
            r = (r - 2) / 2;
        }
    }

private:
    vector<Node> tree;
};

int main() {
    int n; 
    cin >> n;
    vector<uint64_t> data(n);

    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    SegmentTree tree(data);

    int q, l, r;
    uint64_t add;
    string command;
    Node ans;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> command;
        if (command == "g") {
            cin >> l;
            cout << tree.get(l - 1) << endl;
        }
        else if (command == "a") {
            cin >> l >> r >> add;
            tree.update(add, l - 1, r - 1);
        }
    }
}
