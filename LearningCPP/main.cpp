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

//12. Integer to Roman
string intToRoman(int num) {
    string geweiArray[10] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    string shiweiArray[10] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    string baiweiArray[10] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    string qianweiArray[4] = {"","M","MM","MMM"};
    string roman = "";
    roman = qianweiArray[num / 1000] + baiweiArray[(num / 100) % 10] + shiweiArray[(num / 10) % 10] + geweiArray[num % 10];
    return roman;
}

//13. Roman to Integer
int romanToInt(string s) {
    int ans = 0;
    int size = (int)s.length();
    for (int i = size - 1; i >= 0; i--) {
        switch (s[i]) {
            case 'I':
                ans += ans >= 5 ? -1 : 1;
                break;
            case 'V':
                ans += 5;
                break;
            case 'X':
                ans += ans >= 50 ? -10 : 10;
                break;
            case 'L':
                ans += 50;
                break;
            case 'C':
                ans += ans >= 500 ? -100 : 100;
                break;
            case 'D':
                ans += 500;
                break;
            case 'M':
                ans += 1000;
                break;
            default:
                break;
        }
    }
    return ans;
}

//14. Longest Common Prefix
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    int maxPrefix = (int)strs[0].length();
    int size = (int)strs.size();
    for (int i = 1; i < size; i++) {
        int j = 0;
        int length = (int)strs[i].length();
        for (; j < maxPrefix && j < length; j++) {
            if (strs[0][j] != strs[i][j]) break;
        }
        if (j < maxPrefix) maxPrefix = j;
    }
    return strs[0].substr(0,maxPrefix);
}

//15. 3Sum
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    int size = (int)nums.size();
    for (int i = 0; i < size; i ++) {
        int begin = i + 1;
        int end = size - 1;
        while (begin < end){
            int sum = nums[i] + nums[begin] +nums[end];
            if (sum > 0) end--;
            else if (sum < 0) begin++;
            else {
                vector<int> tri(3,0);
                tri[0] = nums[i];
                tri[1] = nums[begin];
                tri[2] = nums[end];
                ans.push_back(tri);
                while (begin < end && nums[begin] == tri[1]) begin++;
                while (begin < end && nums[end] == tri[2]) end--;
            }
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

//16. 3Sum Closest
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int size = (int)nums.size();
    int closest = INT_MAX;
    int ans = closest;
    for (int i = 0; i < size; i ++) {
        int begin = i + 1;
        int end = size - 1;
        while (begin < end){
            int sum = nums[i] + nums[begin] +nums[end];
            if (sum > target) {
                if (sum - target < closest) {
                    closest = sum - target;
                    ans = sum;
                }
                end--;
            }
            else if (sum < target) {
                if (target - sum < closest) {
                    closest = target - sum;
                    ans = sum;
                }
                begin++;
            }
            else {
                return target;
            }
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    vector<int> nums(4,0);
    nums[0] = 1;
    nums[1] = 1;
    nums[2] = 1;
    int closest = threeSumClosest(nums, 100);
    printf("%d\n",closest);
    return 0;
}
