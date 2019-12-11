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

class SegmentTree {
public:
    SegmentTree(const vector<long long> &data): 
        tree((1 << (int(log2(data.size() - 1)) + 2)) - 1, 0) {
        int n = (1 << (int(log2(data.size() - 1)) + 1));
        for (int i = 0; i < data.size(); ++i) {
            tree[i + n - 1] = data[i];
        }
        for (int i = n - 2; i >= 0; --i) {
            tree[i] = tree[left(i)] + tree[right(i)];
        }
    }

    long long rsq(int l, int r) const{
        long long ans = 0;
        int n = tree.size() / 2;
        l += n;
        r += n;
        // cout << l << " " << r << endl;
        while (l <= r) {
            
            if (!(l & 1)) {
                ans += tree[l];
            }
            if (r & 1) {
                ans += tree[r];
            }
            l = l / 2;
            if (r - 2 < 0) {
                break;
            }
            r = (r - 2) / 2;
        }
        return ans;       
    }

    void update(int v, long long newValue) {
        int n = tree.size() / 2;
        v += n;
        long long d = newValue - tree[v];
        // cout << l << " " << r << endl;
        tree[v] += d;
        while (v) {
            v = (v - 1) / 2;
            tree[v] += d;
        }
    } 

private:
    vector<long long> tree;
};

int main() {
    int n; 
    cin >> n;
    vector<long long> data(n);

    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    SegmentTree tree(data);

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
