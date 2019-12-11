#include <iostream>
#include <vector> 
#include <string>

using namespace std;


vector<int> zFunc(const string &input) {
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
    string input;
    cin >> input;
    vector<int> answer(zFunc(input));
    
    for (int val: answer) {
        cout << val << " ";
    }
    cout << endl;
}
