//
//  main.cpp
//  LearningCPP
//
//  Created by lioneldy on 2016/12/19.
//  Copyright © 2016年 lioneldy. All rights reserved.
//

#include <iostream>
using namespace std;

//6. ZigZag Conversion
string convert(string s, int numRows) {
    if (numRows <= 1) return s;
    string ans = "";
    long lens = s.length();
    int k = 2 * numRows - 2;
    for (int i = 0; i < numRows; i++) {
        for (int j = i; j < lens; j += k) {
            ans = ans + s[j];
            int secondj = j + k - 2*i;
            if (i != 0 && i != numRows - 1 && secondj < lens)
                ans = ans + s[secondj];
        }
    }
    return ans;
}

//7. Reverse Integer
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

//9. Palindrome Number
bool isPalindrome(int x) {
    if(x<0|| (x!=0 &&x%10==0)) return false;
    int sum=0;
    while(x>sum)
    {
        sum = sum*10+x%10;
        x = x/10;
    }
    return (x==sum)||(x==sum/10);
}

//10. Regular Expression Matching
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
