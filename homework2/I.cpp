#include <iostream>
#include <vector>

using namespace std;

class BinIndexedTree {
public:
    explicit BinIndexedTree(int mN): 
        tree(mN, vector<vector<long long>>(mN, vector<long long>(mN, 0))), n(mN) {}

    long long rsq(int x1, int y1, int z1, int x2, int y2, int z2) const {
        return sum(x2, y2, z2) - sum(x2, y2, z1 - 1) - sum(x2, y1 - 1, z2) - 
            sum(x1 - 1, y2, z2) + sum(x1 - 1, y1 - 1, z2) +
            sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y2, z1 - 1) - 
            sum(x1 - 1, y1 - 1, z1 - 1);
    }

    void add(int x, int y, int z, long long d) {
        for (int i = x; i < n; i = (i | (i + 1))) {
            for (int j = y; j < n; j = (j | (j + 1))) {
                for (int k = z; k < n; k = (k | (k + 1))) {
                    tree[i][j][k] += d;
                }
            }
        }
    }
private:
    long long sum(int x, int y, int z) const {
        long long res = 0;
        for (int i = x; i >= 0; i = ((i & (i + 1)) - 1)) {
            for (int j = y; j >= 0; j = ((j & (j + 1)) - 1)) {
                for (int k = z; k >= 0; k = ((k & (k + 1)) - 1)) {
                    res += tree[i][j][k];
                }
            }
        }
        return res;
    }
    
    vector<vector<vector<long long>>> tree;
    long long n;
};

int main() {
    int n; 
    cin >> n;

    BinIndexedTree tree(n);

    long long q, x1, y1, z1, x2, y2, z2, add;
    int command;
    do {
        cin >> command;
        if (command == 1) {
            cin >> x1 >> y1 >> z1 >> add;
            tree.add(x1, y1, z1, add);
        }
        else if (command == 2) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << tree.rsq(x1, y1, z1, x2, y2, z2) << endl;
        }
    } while (command != 3);
}
