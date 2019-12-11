#include <iostream>
#include <vector>
#include <queue>

const long long INF = 20090009990;
const int MAX_COUNT = 1000000;

struct Edge{
    int start;
    int finish;
    long long weight;
    Edge(int a = 0, int b = 0, long long c = 0){
        start = a;
        finish = b;
        weight = c;
    }
};

typedef std::vector<std::vector<Edge> > G_List;

void Dijkstra(const G_List &g, std::vector<long long> &d, int StartVertex){
    std::vector<bool> used(g.size(), false);
    d[StartVertex] = 0;
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int> >, std::greater<std::pair<long long, int> > > queue; // dist, vertex
    int current;
    queue.push(std::make_pair(d[StartVertex], StartVertex));
    while (!queue.empty()) {
        current = queue.top().second;
        queue.pop();
        used[current] = true;
        for (int i = 0; i < g[current].size(); ++i) {
            if(!used[g[current][i].finish] && d[g[current][i].finish] > d[current] + g[current][i].weight){
                d[g[current][i].finish] = d[current] + g[current][i].weight;
                queue.push(std::make_pair(d[g[current][i].finish], g[current][i].finish));
            }
        }
        while (!queue.empty() && used[queue.top().second]) {
            queue.pop();
        }
    }
}

int main(){
    int N, U, D, I, J, L; //N - кол-во этажей
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> N >> U >> D >> I >> J >> L; // U - подъём, D - спуск, внос - I, вынос - J; L - кол-во лифтов
    G_List g(MAX_COUNT + L);
    for (int k = 0; k < MAX_COUNT - 1; ++k) {
        g[k].push_back(Edge(k, k + 1, U));
        g[k + 1].push_back(Edge(k + 1, k, D));
    }

    for (int Count, j = 0; j < L; ++j) {
        std::cin >> Count;
        for (int K, i = 0; i < Count; ++i) {
            std::cin >> K;
            g[K - 1].push_back(Edge(K - 1, MAX_COUNT + j, I));
            g[MAX_COUNT + j].push_back(Edge(MAX_COUNT + j, K - 1, J));
        }
    }
    std::vector<long long> d (MAX_COUNT + L, INF);
    Dijkstra(g, d,  0);

    std::cout << d[N - 1];
}

