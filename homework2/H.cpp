#include <iostream>
#include <vector>

using namespace std;

class BinIndexedTree {
public:
    BinIndexedTree(int n, int m): tree(n, vector<long long>(m, 0)),
        sizeX(n), sizeY(m) {}

    long long rsq(int x1, int y1, int x2, int y2) const {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + 
            sum(x1 - 1, y1 - 1);
    }

    void add(int x, int y, long long d) {
        for (int i = x; i < sizeX; i = (i | (i + 1))) {
            for (int j = y; j < sizeY; j = (j | (j + 1))) {
                tree[i][j] += d;
            }
        }
    }
private:
    long long sum(int x, int y) const {
        long long res = 0;
        for (int i = x; i >= 0; i = ((i & (i + 1)) - 1)) {
            for (int j = y; j >= 0; j = ((j & (j + 1)) - 1)) {
                res += tree[i][j];
            }
        }
        return res;
    }
    
    vector<vector<long long>> tree;
    long long sizeX;
    long long sizeY;
};

int main() {
    int n, m; 
    cin >> n >> m;

    BinIndexedTree tree(n, m);

    long long q, x1, y1, x2, y2, add;
    int command;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> command;
        if (command == 1) {
            cin >> x1 >> y1 >> add;
            tree.add(x1 - 1, y1 - 1, add);
        }
        else if (command == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << tree.rsq(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << endl;
        }
    }
}
