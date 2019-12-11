#include <iostream>
#include <vector>
#include <list>


using namespace std;

struct edge {
    long long u;
    long long v;
    long long tIn; 
    long long tOut;
};

void relax(vector<long long> &lenPath, long long u, long long v, long long tIn, 
    long long tOut) {
        if (lenPath[u] <= tIn && tOut < lenPath[v]) {
            lenPath[v] = tOut;
        } 
    }

int main() {
    long long  N, s, f, M;

    long long INF = 1 << 30;
    
    cin >> N; 
    vector<long long> lenPath(N, INF);
    
    cin >> s >> f >> M;
    
    lenPath[s - 1] = 0;

    list<edge> edges;
    edge tmp;
    for (int i = 0; i < M; ++i) {
        cin >> tmp.u >> tmp.tIn >> tmp.v >> tmp.tOut;
        tmp.u -= 1;
        tmp.v -= 1;
        edges.push_back(tmp);
    }

    for (int i = 0; i < N + M; ++i) {
        for (auto e: edges) {
            relax(lenPath, e.u, e.v, e.tIn, e.tOut);
        }
    }

    cout << lenPath[f - 1] << endl;
}
