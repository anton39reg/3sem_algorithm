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
    vector<int> &r, int x, int y, int w) {
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
        p[y].second += p[x].second + w;
    }
    else {
        p[y].first = x;
        p[x].second += p[y].second + w;
    }
}



int main() {
    int N, M;
 
    cin >> N >> M;
     
    vector<pair<int, int>> p(N);
    vector<int> r(N);
    for (int i = 0; i < N; ++i) {
        p[i].first = i;
        p[i].second = 0;
        r[i] = 0;
    }
    
    int oper;
    int v, u, w;
    for (int i = 0; i < M; ++i) {
        cin >> oper;
        if (oper == 1) {
            cin >> v >> u >> w;
            v = get(p, v - 1);
            u = get(p, u - 1);
            if (v != u) {
                unionComp(p, r, v, u, w);
            }
            else {
                p[v].second += w;
            }
        }
        else if (oper == 2) {
            cin >> v;
            v = get(p, v - 1);
            cout << p[v].second << endl;
        }
    }
}
