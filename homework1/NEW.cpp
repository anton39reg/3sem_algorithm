#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <list>

using namespace std;

uint64_t one = 1;
uint64_t MAX = one << 60;

void readGraph(vector<list<pair<uint64_t, uint64_t>>> &g, uint64_t M) {
    uint64_t u, v, w;
    for (uint64_t i = 0; i < M; ++i) {
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
}

void relaxForFires(vector<uint64_t> &minPath, set<pair<uint64_t, uint64_t>> &orderOfVisit, 
    uint64_t u, uint64_t v, uint64_t w) {
    if (minPath[v] > minPath[u] + w) {
        orderOfVisit.erase({minPath[v], v});
        minPath[v] = minPath[u] + w;
        orderOfVisit.insert({minPath[v], v});
    } 
}


vector<uint64_t> findMinPathForFires(vector<list<pair<uint64_t, uint64_t>>> &graph,
    vector<uint64_t> &fires) {

    vector<uint64_t> minPath(graph.size(), MAX);
    for (auto f: fires) {
        minPath[f] = 0;
    }
    set<pair<uint64_t, uint64_t>> orderOfVisit;
    for (uint64_t i = 0; i < graph.size(); ++i) {
        orderOfVisit.insert({minPath[i], i});
    }
    
    uint64_t cur;
    while (!orderOfVisit.empty()) {
        cur = (*orderOfVisit.begin()).second;
        orderOfVisit.erase(orderOfVisit.begin());
        for (auto v: graph[cur]) {
            relaxForFires(minPath, orderOfVisit, cur, v.first, v.second);
        }
    }
    return minPath;
}


void relaxForPeople(vector<uint64_t> &minPath, set<pair<uint64_t, uint64_t>> &orderOfVisit, 
    const vector<uint64_t> &pathFires, uint64_t u, uint64_t v, uint64_t w) {
    if (minPath[v] > minPath[u] + w && pathFires[v] > minPath[u] + w ) {
        orderOfVisit.erase({minPath[v], v});
        minPath[v] = minPath[u] + w;
        orderOfVisit.insert({minPath[v], v});
    } 
}

vector<uint64_t> findMinPathForPeople(vector<list<pair<uint64_t, uint64_t>>> &graph,
    const vector<uint64_t> &pathFires, uint64_t s) {

    vector<uint64_t> minPath(graph.size(), MAX);
    minPath[s] = 0;
    set<pair<uint64_t, uint64_t>> orderOfVisit;
    for (uint64_t i = 0; i < graph.size(); ++i) {
        orderOfVisit.insert({minPath[i], i});
    }
    
    uint64_t cur;
    while (!orderOfVisit.empty()) {
        cur = (*orderOfVisit.begin()).second;
        orderOfVisit.erase(orderOfVisit.begin());
        for (auto v: graph[cur]) {
            relaxForPeople(minPath, orderOfVisit, pathFires, 
                cur, v.first, v.second);
        }
    }
    return minPath;
}

int main() {
    uint64_t N, M, K, u, v, w;

    cin >> N >> M >> K;

    vector<uint64_t> fires(K);
    for (uint64_t i = 0; i < K; ++i) {
        cin >> u;
        --u;
        fires[i] = u;
    }
    
    vector<list<pair<uint64_t, uint64_t>>> graph(N);
    readGraph(graph, M);
    
    vector<uint64_t> pathFires = findMinPathForFires(graph, fires);

    uint64_t s, f;
    cin >> s >> f;
    --s;
    --f;
    vector<uint64_t> pathPeople = findMinPathForPeople(graph, pathFires, s);

    if (pathPeople[f] != MAX) {
        cout << pathPeople[f] << endl;
    }
    else {
        cout << -1 << endl;
    }
}
