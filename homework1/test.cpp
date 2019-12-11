#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>

using namespace std;

enum {MAX = 1 << 30,
    MAX_COUNT = 1000000};

void relax(vector<int> &minPath,
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &orderOfVisit, 
    int u, int v, int w) {
        if (minPath[v] > minPath[u] + w) {
            minPath[v] = minPath[u] + w;
            orderOfVisit.push({minPath[v], v});
        } 
    }

void dijkstra(vector<list<pair<int, int>>> &graph, int s, int f) {
    vector<int> minPath(graph.size(), MAX);
    vector<int> visited(graph.size(), 0);
    minPath[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> orderOfVisit;
    orderOfVisit.push({minPath[s], s}); 
    pair<int, int> cur;
    while (!orderOfVisit.empty()) {
        cur = orderOfVisit.top();
        orderOfVisit.pop();
        visited[cur.second] = 1;
        for (auto v: graph[cur.second]) {
            if (visited[v.first]) {
                continue;
            }
            relax(minPath, orderOfVisit, cur.second, v.first, v.second);
        }
        while (!orderOfVisit.empty() && visited[orderOfVisit.top().second]) {
            orderOfVisit.pop();
        }
    }
    cout << minPath[f] << endl;
}

int main() {
    int N, U, D, I, J, L;
    cin >> N >> U >> D >> I >> J >> L;
    vector<list<pair<int, int>>> graph(MAX_COUNT + L);
    for (int i = 0; i < MAX_COUNT - 1; ++i) {
        graph[i].push_back({i + 1, U});
        graph[i+1].push_back({i, D});
    }
    int count;
    for (int i = 0; i < L; ++i) {
        cin >> count;
        int floor;
        for (int j = 0; j < count; ++j) {
            cin >> floor;
            --floor;
            graph[floor].push_back({MAX_COUNT + i, I});
            graph[MAX_COUNT + i].push_back({floor, J});
            
        }
    }
    dijkstra(graph, 0, N - 1);
}
