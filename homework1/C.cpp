#include <iostream>
#include <vector>
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

int visit(Graph &g, int v) {
    int flag = 0;
    g.setColorVertex(v, GRAY);
    for (auto u: g.getNeighbourhood(v)) {
        if (g.getColorVertex(u) == WHITE) {
            flag = visit(g, u);
            if (flag == 1) {
                return 1;
            }
        }
        else if (g.getColorVertex(u) == GRAY) {
            cout << "YES" << endl;
            printCycle(g, u);
            cout << endl;
            return 1;
        }
    }
    g.setColorVertex(v, BLACK);
    return flag;
}

void dfs(Graph &g) {
    int cicle = 0;
    for (int v = 0; v < g.getCountVertex(); ++v) {
        if (g.getColorVertex(v) == WHITE) {
            cicle = visit(g, v);
            if (cicle == 1) {
                break;
            }
        }
    }
    if (cicle == 0) {
        cout << "No" << endl;
    }
}


int main() {
    int N, M;
    cin >> N >> M;
    Graph g(N);
    g.readData(M);
    dfs(g);
}
