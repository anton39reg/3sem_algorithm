#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;


int get(vector<pair<int, int>> &p, int x) {
    if (p[x].first != x) {
        p[x].first = get(p, p[x].first);
    }
    return p[x].first;
}


void unionComp(vector<pair<int, int>> &p,
    vector<int> &r, int x, int y) {
    x = get(p, x);
    y = get(p, y);
    if (x == y) {
        return;   
    }
    if (r[x] == r[y]) {
        ++r[x];
    }
    if (r[x] < r[y]) {
        p[x].first = y;
        p[y].second += p[x].second;
    }
    else {
        p[y].first = x;
        p[x].second += p[y].second;
    }
}



int main() {
    int N, M;
 
    cin >> N >> M;
     
    vector<pair<int, int>> p(N);
    vector<int> r(N);
    for (int i = 0; i < N; ++i) {
        p[i].first = i;
        p[i].second = 1;
        r[i] = 0;
    }
    
    int v, u;
    int res = M;
    for (int i = 0; i < M; ++i) {
        cin >> v >> u;
        v = get(p, v);
        u = get(p, u);
        if (v != u) {
            unionComp(p, r, v, u);
            v = get(p, v);
            if (p[v].second == N) {
                res = i + 1;
                break;
            }
        }
    }
    cout << res << endl;
}
