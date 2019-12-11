#include <iostream>
#include <vector> 
#include <string>
#include <set>

using namespace std;


vector<int> zFunc(const vector<int> &input) {
    vector<int> answer(input.size(), 0);
    answer[0] = input.size();
    int left = 0;
    int right = 0;
    for (int i = 1; i < input.size(); ++i) {
        answer[i] = max(0, min(right - i, answer[i - left]));
        while (i + answer[i] < input.size() && 
            input[answer[i]] == input[i + answer[i]]) {
            ++answer[i];
        }
        if (i + answer[i] > right) {
            left = i;
            right = i + answer[i];
        }
    }
    return answer;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> input(2*N + 1);
    int tmp;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        input[i] = tmp;
        input[2*N - i] = tmp;
    }
    input[N] = -1; 

    vector<int> valueZFunc(zFunc(input));
    size_t sizeInput = input.size(); 
    
    set<int, greater<int>> answer = {0};
    for (int i = N; i < sizeInput; ++i) {
        if ((valueZFunc[i] % 2 == 0) && ((valueZFunc[i] + i) == sizeInput)) {
            answer.insert(valueZFunc[i] / 2);
        }
    }
    for (auto elem: answer) {
        cout << N - elem << " ";
    }
    cout << endl;
}
