#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class sparseTableMin {
public:
    explicit sparseTableMin(const vector<long long> &data): 
        table(vector<vector<long long>>(int(log2(data.size())) + 1,
        vector<long long>(data.size(), 0))),
        binaryLog(vector<int>(data.size() + 1, 0)) {
        
        table[0] = data;
        fillTable();
        binaryLog[1] = 0;
        for (int i = 2; i < data.size() + 1; ++i) {
            binaryLog[i] = binaryLog[i / 2] + 1;
        }
    }

    long long rmq(int s, int f) {
        int j = binaryLog[f - s + 1];
        return min(table[j][s], table[j][f - (1 << j) + 1]);
    }

private:
    void fillTable() {
        for (int i = 1; i < table.size(); ++i) {
            for (int j = 0; j + (1 << i) - 1 < table[0].size(); ++j) {
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i-1))]);
            }
        }
    }
   
    vector<int> binaryLog;
    vector<vector<long long>> table;
};


int main() {
    int n, m;
    int a;
    cin >> n >> m >> a;;
    vector<long long> data(n);
    int last = a;
    for (int i = 0; i < n; ++i) {
        data[i] = last;
        last = (last * 23 + 21563) % 16714589;
        //cout << data[i] << " ";
    }
    //cout << endl;
    sparseTableMin res(data);
    int s, f;
    cin >> s >> f;
    int ans;
    for (int i = 0; i < m; ++i) {
        if (s <= f) {
            ans = res.rmq(s - 1, f - 1);
        }
        else {
            ans = res.rmq(f - 1, s - 1);
        }
        if (i + 1 == m) {
            break;
        }
        s = (17 * s + 751 + ans + 2 * (i + 1)) % n + 1;
        f = (13 * f + 593 + ans + 5 * (i + 1)) % n + 1;
    }
    cout << s << " " << f << " " << ans << endl;
}
