#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

enum {INF = -(1 << 30), LEFT = 1, RIGHT = 2};


int left(int i) {
    return 2*i + 1;
}

int right(int i) {
    return 2*i + 2;
}


class Node {
public:
    int countLeftBrackets;
    int countRightBrackets;
    int lenMaxSeq;

    Node(int l = 0, int r = 0, int m = 0): countLeftBrackets(l),
        countRightBrackets(r), lenMaxSeq(m){}

    Node(const Node &a, const Node &b) {
        int m = min(a.countLeftBrackets, b.countRightBrackets); 
        countLeftBrackets = a.countLeftBrackets + b.countLeftBrackets - m; 
        countRightBrackets = a.countRightBrackets + b.countRightBrackets - m;
        lenMaxSeq = a.lenMaxSeq + b.lenMaxSeq + 2 * m;
    }
};

class SegmentTree {
public:
    SegmentTree(const string &data): 
        tree((1 << (int(log2(data.size() - 1)) + 2)) - 1) {
        int n = (1 << (int(log2(data.size() - 1)) + 1));
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == '(') {
                tree[i + n - 1] = Node(1, 0, 0);
            }
            else if (data[i] == ')') {
                tree[i + n - 1] = Node(0, 1, 0);
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            tree[i] = Node(tree[left(i)], tree[right(i)]);
        }
    }

    Node get(int l, int r) {
        Node leftAns, rightAns;
        int n = tree.size() / 2;
        l += n;
        r += n;
        // cout << l << " " << r << endl;
        while (l <= r) {
            
            if (!(l & 1)) {
                leftAns = Node(leftAns, tree[l]);
            }
            if (r & 1) {
                rightAns = Node(tree[r], rightAns);
            }
            l = l / 2;
            if (r - 2 < 0) {
                break;
            }
            r = (r - 2) / 2;
        }
        return Node(leftAns, rightAns);       
    }

private:
    vector<Node> tree;
};

int main() {
    string seq;
    cin >> seq;
    
    SegmentTree tree(seq);

    int q, l, r;
    Node ans;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        ans = tree.get(l - 1, r - 1);
        cout << ans.lenMaxSeq << endl;
    }
}
