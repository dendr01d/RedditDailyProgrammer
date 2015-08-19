/*
My submission for challenge #228 (easy)
https://www.reddit.com/r/dailyprogrammer/comments/3h9pde/20150817_challenge_228_easy_letters_in/?ref=share&ref_source=link
*/

#include <string>
#include <iostream>

using namespace std;

bool leq(char a, char b) {
    return a <= b;
}

bool geq(char a, char b) {
    return a >= b;
}

bool ordered (string str, bool(*func)(char, char)) {
    for (unsigned int i = 0; i < str.size() - 1; ++i) {
        if (!func(str[i], str[i+1])) {
            return false;
        }
    }
    return true;
}

int main() {
    string str;
    
    while(cin >> str) {
        
        if (ordered(str, leq)) {
            cout << str << " IN ORDER\n";
        }
        else if (ordered(str, geq)) {
            cout << str << " REVERSE ORDER\n";
        }
        else {
            cout << str << " NOT IN ORDER\n";
        }
    }
    return 0;
}
