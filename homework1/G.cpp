#include <iostream>
#include <vector>
#include <queue>
#include <list>


using namespace std;


typedef enum {
    WHITE = 1,
    GRAY = 2,
    BLACK = 3
} colors;

class Graph {
public:
    Graph(int mCountVertex): colorVertex(mCountVertex, WHITE),
        countVertex(mCountVertex),
        graph(mCountVertex, list<int>()) {}

    void readData(int M) {
        int tmpFirst, tmpSecond;
        for (int i = 0; i < M; ++i) {
            cin >> tmpFirst >> tmpSecond;
            graph[tmpFirst - 1].push_back(tmpSecond - 1);
            graph[tmpSecond - 1].push_back(tmpFirst - 1);
        }
    }

    colors getColorVertex(int v) const {
        return colorVertex[v];
    }

    void setColorVertex(int v, colors c) {
        colorVertex[v] =  c;
    }

    list<int> getNeighbourhood(int v) const {
        return graph[v];
    }

    int getCountVertex() {
        return countVertex;
    }

    void clear() {
        for (int i = 0; i < countVertex; ++i) {
            colorVertex[i] = WHITE;
        }
    }


private:
    vector<colors> colorVertex;
    int countVertex;
    vector<list<int>> graph;
};

void printCycle(Graph &g, int v) {
    cout << v + 1 << " ";
    for (auto u: g.getNeighbourhood(v)) {
        if (g.getColorVertex(u) == GRAY) {
            g.setColorVertex(v, BLACK);
            printCycle(g, u);
            break;
        }
    }
}


void bfs(Graph &g, int s, int f) {
    queue<int> visit;
    vector<int> lenPath(g.getCountVertex(), ~0);
    vector<int> prev(g.getCountVertex());
    lenPath[s] = 0;
    prev[s] = s;
    visit.push(s);
    int now;
    while (!visit.empty()) {
        now = visit.front();
        visit.pop();
        g.setColorVertex(now, BLACK);
        for (auto v: g.getNeighbourhood(now)) {
            if (g.getColorVertex(v) == WHITE) {
                visit.push(v);
                g.setColorVertex(v, BLACK);
                lenPath[v] = lenPath[now] + 1;
                prev[v] = now;
            }
        }
    }
    if (lenPath[f] != ~0) {
        cout << lenPath[f] << endl;
        list<int> res;
        int v = f;
        while (v != prev[v]) {
            res.push_front(v);
            v = prev[v];
        }
        res.push_front(v);
        for (auto tmp: res) {
            cout << tmp + 1 << " ";
        }
        cout << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    int N, M, s, f;
    cin >> N >> M >> s >> f;
    Graph g(N);
    g.readData(M);
    bfs(g, s - 1, f - 1);
}
