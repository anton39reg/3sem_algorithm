#include <iostream>
#include <vector> 
#include <string>
#include <list>

using namespace std;


vector<int> zFunc(const string &input) {
    vector<int> answer(input.length(), 0);
    answer[0] = input.length();
    int left = 0;
    int right = 0;
    for (int i = 1; i < input.length(); ++i) {
        answer[i] = max(0, min(right - i, answer[i - left]));
        while (i + answer[i] < input.length() && 
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
    string wordOnFence, jackWord;
    cin >> wordOnFence >> jackWord;

    string forFindSubstr = wordOnFence + "#" + jackWord;
    vector<int> resZFunc(zFunc(forFindSubstr)); 
    
    int curPos = forFindSubstr.length();
    int resLen = 0;
    list<string> answer;

    for (int i = resZFunc.size(); i > wordOnFence.length(); --i) {
        if (resZFunc[i] + i >= curPos) {
            int delta = resZFunc[i] + i - curPos;
            string word;
            for (int j = i; j < curPos; ++j) {
                word += forFindSubstr[j];
                ++resLen;
            }
            answer.push_front(word);
            curPos -= (resZFunc[i] - delta);
        }
    }
    if (resLen == jackWord.length()) {
        cout << "No" << endl;
        for (auto str: answer) {
            cout << str << " ";
        }
    }
    else {
        cout << "Yes";
    }
}
