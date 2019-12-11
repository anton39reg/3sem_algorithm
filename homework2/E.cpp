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
    int maxVal;
    int count;

    Node(): maxVal(INF), count(0) {}

    Node(const Node &a, const Node &b) {
        maxVal = max(a.maxVal, b.maxVal);
        if (a.maxVal > b.maxVal) {
            count = a.count;
        }
        else if (a.maxVal == b.maxVal) {
            count = a.count + b.count;
        }
        else {
            count = b.count;
        }
    }
};

class SegmentTree {
public:
    SegmentTree(const vector<int> &data): 
        tree((1 << (int(log2(data.size() - 1)) + 2)) - 1) {
        int n = (1 << (int(log2(data.size() - 1)) + 1));
        for (int i = 0; i < data.size(); ++i) {
            tree[i + n - 1].maxVal = data[i];
            tree[i + n - 1].count = 1;
        }
        for (int i = n - 2; i >= 0; --i) {
            tree[i] = Node(tree[left(i)], tree[right(i)]);
        }
    }

    Node rmq(int l, int r) {
        Node ans;
        int n = tree.size() / 2;
        l += n;
        r += n;
        // cout << l << " " << r << endl;
        while (l <= r) {
            
            if (!(l & 1)) {
                ans = Node(ans, tree[l]);
            }
            if (r & 1) {
                ans = Node(ans, tree[r]);
            }
            l = l / 2;
            if (r - 2 < 0) {
                break;
            }
            r = (r - 2) / 2;
        }
        return ans;       
    }

private:
    vector<Node> tree;
};

int main() {
    int n; 
    cin >> n;
    vector<int> data(n);

    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    SegmentTree tree(data);

    int q, l, r;
    Node ans;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        ans = tree.rmq(l - 1, r - 1);
        cout << ans.maxVal << " " << ans.count << endl;
    }
}
