//
//  main.cpp
//  LearningCPP
//
//  Created by lioneldy on 2016/12/19.
//  Copyright © 2016年 lioneldy. All rights reserved.
//

#include <iostream>
using namespace std;

string convert(string s, int numRows) {
    string ans = "";
    if (s.length()==0) {
        return ans;
    }
    if (numRows == 1) {
        return s;
    }
    long lens = s.length();
    int k = 2 * numRows - 2;
    for (int i = 0; i < numRows; i++) {
        bool isOdd = true;
        for (int j = i; j < lens; ) {
            ans = ans + s[j];
            if (i == 0 || i == (numRows - 1)) {
                j += k;
                continue;
            }
            if (isOdd) {
                j = j + k - 2i;
            }
            else {
                j = j + 2i;
            }
            isOdd = !isOdd;
        }
    }
    return ans;
}

int reverseInt(int x) {
    long long ans = 0;
    for (; x; x /= 10) {
        ans = ans*10 + x%10;
    }
    if (ans > INT_MAX || ans < INT_MIN) {
        return 0;
    }
    return (int)ans;
}

bool isMatch(string s, string p) {
    long i = s.length();
    long j = p.length();
    for (; i&&j; i--,j--) {
        if (s[i-1] == '.' || p[j-1] == '.')
            continue;
        else if ((s[i-1] == '*'&&i>=j) || (p[j-1] == '*'&&j>=i))
            return true;
        else if (s[i-1] != p[j-1])
            return false;
    }
    if (i == 0 && j == 0) {
        return true;
    }
    else return false;
}

int main(int argc, const char * argv[]) {
    bool x = isMatch("aaa", "ab*a");
    printf("%d\n",x);
    return 0;
}
