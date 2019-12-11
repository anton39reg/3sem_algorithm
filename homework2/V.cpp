#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<int> prefixFunc(string input) {
    vector<int> prefix(input.size(), 0);
    int k;
    for (int i = 1; i < input.size(); ++i) {
        k = prefix[i - 1];
        while (k > 0 && input[i] != input[k]) {
            k = prefix[k - 1];
        }
        if (input[i] == input[k]) {
            ++k;
        }
        prefix[i] = k;
    }
    return prefix;
}

int main() {
    int n;
    cin >> n;
    string input;
    cin >> input;
    
    string tmp = "*" + input;
    reverse(input.begin(), input.end());
    tmp = input + tmp;
    vector<int> prefix(prefixFunc(tmp));
    
    for (int i = n + 1; i < prefix.size(); ++i) {
        cout << prefix[i] << " ";
    }
    cout << endl;
}
