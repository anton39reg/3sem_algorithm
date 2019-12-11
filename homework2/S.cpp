#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int prefixFunc(string input) {
    vector<int> prefix(input.size(), 0);
    int k;
    int max = 0;
    for (int i = 1; i < input.size(); ++i) {
        k = prefix[i - 1];
        while (k > 0 && input[i] != input[k]) {
            k = prefix[k - 1];
        }
        if (input[i] == input[k]) {
            ++k;
        }
        prefix[i] = k;
        if (max < k) {
            max = k;
        }
    }
    return max;
}

long long countDiffSubstr(string input) {
    reverse(input.begin(), input.end());
    long long answer = 0;
    int last = input.size();
    for (int i = last - 1; i >= 0; --i) {
        answer += ((last - i) - prefixFunc(input.substr(i, last)));
    }
    return answer;
}

int main() {
    string input;
    cin >> input;

    cout << countDiffSubstr(input) << endl;
}
