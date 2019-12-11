#include <iostream>
#include <vector>

using namespace std;


unsigned int a, b;
unsigned int cur = 0;

unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8; 
}


int main() {
    int m, q;
    cin >> m >> q;
    cin >> a >> b;

    vector<unsigned int> data(1 << 24, 0);
    vector<unsigned int> prefix(1 << 24, 0);

    unsigned int l, r, add;
    for (int i = 0; i < m; ++i) {
        add = nextRand();
        l = nextRand();
        r = nextRand();
       // cout << add << " " << l << " " << r << endl;
        
        if (l > r) {
            swap(l, r);
        }
        data[l] += add;
        data[r + 1] -= add;
    }

    unsigned int value = 0;
    for (int i = 0; i < (1 << 24); ++i) {
        value += data[i];
        if (i > 0) {
            prefix[i] = value + prefix[i - 1];
        }
        else {
            prefix[i] = data[0];
        }
    }

    unsigned int ans = 0;
    for (int i = 0; i < q; ++i) {
        l = nextRand();
        r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        if (l != 0) {
            ans += prefix[r] - prefix[l - 1];
        }
        else {
            ans += prefix[r];
        }
    }
    cout << ans << endl;
}
