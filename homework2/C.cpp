#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

class sparseTableSum {
public:
    explicit sparseTableSum(const vector<size_t> &data): 
        table(vector<vector<size_t>>(int(log2(data.size())) + 1,
        vector<size_t>(data.size(), 0))),
        binaryLog(vector<int>(data.size() + 1, 0)) {
        
        table[0] = data;
        fillTable();
        binaryLog[1] = 0;
        for (int i = 2; i < data.size() + 1; ++i) {
            binaryLog[i] = binaryLog[i / 2] + 1;
        }
    }

    long long rmq(int l, int r) {
        int k = binaryLog[r - l + 1];
        long long res = 0;
        for (int i = k; i >= 0; --i) {
            if ((1 << i) <= r - l + 1) {
                res = gcd(res, table[i][l]);
                l += (1 << i);
            }
        }
        return res;
    }

private:
    void fillTable() {
        for (int i = 1; i < table.size(); ++i) {
            for (int j = 0; j + (1 << i) - 1 < table[0].size(); ++j) {
                table[i][j] = gcd(table[i - 1][j], table[i - 1][j + (1 << (i-1))]);
            }
        }
    }
   
    vector<int> binaryLog;
    vector<vector<size_t>> table;
};

int main() {
    int n, q;
    cin >> n;
    vector<size_t> data(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    sparseTableSum res(data);

    int l, r;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        cout << res.rmq(l - 1, r - 1) << endl;
    }
    cout << endl;
}
