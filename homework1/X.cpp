#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long one = 1;
long long MAX = one << 50;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<long long>> w(n, vector<long long>(N, MAX));
    for (int i = 0; i < N; ++i) {
        w[i][i] = 0;
    }
    long long q;
    int u, v;
    for (long long i = 0; i < M; ++i) {
        cin >> u >> v >> q;
        --u;
        --v;
        w[u][v] = q;
    } 
    vector<int> order(K);
    for (int i = 0; i < K; ++i) {
        cin >> u;
        --u;
        order[i] = u; 
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (w[i][j] > w[i][k] + w[k][j]) {
                    w[i][j] = w[i][k] + w[k][j];
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < K - 1; ++i) {
        
    }
}
