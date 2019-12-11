#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <set>

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
    
    Graph(vector<list<int>> mGraph): colorVertex(mGraph.size(), WHITE),
        countVertex(mGraph.size()), graph(mGraph) {}

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

    vector<list<int>> getReverseGraph() {
        vector<list<int>> result(countVertex);
        for (int u = 0; u < countVertex; ++u) {
            for (auto v: graph[u]) {
                result[v].push_back(u);
            }
        }
        return result;
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

void visitSort(Graph &g, int v, int &time, map<int, int> &timeVertex) {
    g.setColorVertex(v, GRAY);
    ++time;
    for (auto u: g.getNeighbourhood(v)) {
        if (g.getColorVertex(u) == WHITE) {
            visitSort(g, u, time, timeVertex);
        }
    }
    ++time;
    timeVertex[time] = v;
    g.setColorVertex(v, BLACK);
}

map<int, int> topSort(Graph &g) {
    int time = 0;
    map<int, int> timeVertex;
    for (int v = 0; v < g.getCountVertex(); ++v) {
        if (g.getColorVertex(v) == WHITE) {
            visitSort(g, v, time, timeVertex);
        }
    }
    return timeVertex;
}

void visitStrongComponents(Graph &g, int v, vector<list<int>> &strongComponents) {
    g.setColorVertex(v, GRAY);
    int lastComponent = strongComponents.size() - 1;
    strongComponents[lastComponent].push_back(v);
    for (auto neighbor: g.getNeighbourhood(v)) {
        if (g.getColorVertex(neighbor) == WHITE) {
            visitStrongComponents(g, neighbor, strongComponents);
        }
    }
    g.setColorVertex(v, BLACK);
}

vector<list<int>> dfsStrongComponents(Graph rG,map<int, int> orderOfVisit) {
    vector<list<int>> strongComponents;
    for (auto elem = orderOfVisit.rbegin(); elem != orderOfVisit.rend(); ++elem) {
        if (rG.getColorVertex(elem->second) == WHITE) {
            strongComponents.push_back(list<int>());
            visitStrongComponents(rG, elem->second, strongComponents);
        }
    }
    return strongComponents;
}


int main() {
    int N, M;
    cin >> N >> M;
    Graph g(N);
    g.readData(M);
    
    map<int, int> orderOfVisit = topSort(g);

    Graph reverseG(g.getReverseGraph());
    vector<list<int>> strongComponents(dfsStrongComponents(reverseG,
        orderOfVisit));

    map<int, int> vertexComp;
    for (int i = 0; i < strongComponents.size(); ++i) {
        for (auto v: strongComponents[i]) {
            vertexComp[v] = i;
        }
    }

    cout << strongComponents.size() << endl;
    for (auto v: vertexComp) {
        cout << v.second + 1 << " ";
    }
    cout << endl;
}
