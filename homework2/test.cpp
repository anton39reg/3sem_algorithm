#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <string>

using namespace std;

vector<int> BuildPrefixFunction(const string &input) {
    size_t  input_size = input.size();
    vector<int> prefix(input_size, 0);
    for (int i = 1; i < input_size; ++i) {
        int k = prefix[i - 1];
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


string MakeSipher(const vector<string> &words) {
    const size_t count_words = words.size();
    string sipher = words[0];
    for (int i = 1; i < count_words; ++i) {
        string max_suffix_to_process = sipher.substr(max(0, static_cast<int> (sipher.size() - words[i].size())));
        string merged = words[i] + "#" + max_suffix_to_process;
        vector<int> prefix_func = BuildPrefixFunction(merged);
        sipher += words[i].substr(prefix_func.back());
    }
    return sipher;
}

int main(){
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }
    cout << MakeSipher(words);
    return 0;
}
