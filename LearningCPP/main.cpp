//
//  main.cpp
//  LearningCPP
//
//  Created by lioneldy on 2016/12/19.
//  Copyright © 2016年 lioneldy. All rights reserved.
//

#include <iostream>
#include <vector>
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
    if (p.empty()) return s.empty();
    if (p[1] == '*') {
        return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
    }else
    return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
}

//11. Container With Most Water
/*int maxArea(vector<int>& height) {
    long size = height.size();
    int maxArea = (height[0] < height[1]) ? height[0]:height[1];
    for (int i = 1; i < size; i ++) {
        for (int j = 0; j < i; j ++) {
            int area;
            if (height[i] < height[j])
                area = height[i] * (i - j);
            else area = height[j] * (i - j);
            if (area > maxArea)
                maxArea = area;
        }
    }
    return maxArea;
}*/
//超时
int maxArea(vector<int>& height) {
    int size = (int)height.size();
    int maxArea = (size - 1) * min(height[0], height[size - 1]);
    for (int i = 0, j = size - 1; j > i; ) {
        int area;
        if (height[i] < height[j])
            i++;
        else j--;
        area = min(height[i], height[j]) * (j - i);
        if (area > maxArea) {
            maxArea = area;
        }
    }
    return maxArea;
}

int main(int argc, const char * argv[]) {
    bool x = isMatch("abbbbbbbbbba", "ab*a");
    printf("%d\n",x);
    return 0;
}
