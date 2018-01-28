//
//  main.cpp
//  LearningCPP
//
//  Created by lioneldy on 2016/12/19.
//  Copyright © 2016年 lioneldy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <list>
#include <sstream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

//2. Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *sumList = new ListNode(0);
    ListNode *ans = sumList;
    int c = 0;
    while (l1 || l2 || c) {
        int sum = (l1 ? l1 -> val : 0) + (l2 ? l2 -> val : 0) + c;
        c = sum/10;
        sumList->next = new ListNode(sum % 10);
        sumList = sumList->next;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
    }
    return ans -> next;
}

//3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s) {
    int maxLenth = 0;
    vector<int> dictMap(256,-1);
    int m = -1;
    for (int i = 0; i < s.length(); i++) {
        m = max(dictMap[s[i]],m);
        dictMap[s[i]] = i;
        maxLenth = max(i - m, maxLenth);
    }
    return maxLenth;
}

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
    if(x < 0 || (x != 0 && x % 10 == 0)) return false;
    int sum = 0;
    while(x > sum) {
        sum = sum * 10 + x % 10;
        x = x / 10;
    }
    return (x == sum) || (x == sum / 10);
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

//最大公约数
int getGcd(int a, int b) {
    return (a % b == 0) ? b : getGcd(b, a % b);
}

//全排列算法
void Swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}
//在pszStr数组中，[nBegin,nEnd)中是否有数字与下标为nEnd的数字相等
bool IsSwap(char *pszStr, int nBegin, int nEnd) {
    for (int i = nBegin; i < nEnd; i++)
        if (pszStr[i] == pszStr[nEnd])
            return false;
    return true;
}
bool isSwap(string& str, int start, int end) {
    for (int i = start; i < end; i++)
        if (str[i] == str[end])
            return true;
    return false;
}
//k表示当前选取到第几个数,m表示共有多少数.
void AllRange(char *pszStr, int k, int m) {
    if (k == m) {
        static int s_i = 1;
        printf("  第%3d个排列\t%s\n", s_i++, pszStr);
    }
    else {
        for (int i = k; i <= m; i++) {//第i个数分别与它后面的数字交换就能得到新的排列
            if (IsSwap(pszStr, k, i)) {
                Swap(pszStr + k, pszStr + i);
                AllRange(pszStr, k + 1, m);
                Swap(pszStr + k, pszStr + i);
            }
        }
    }
}
//全排列算法之字符串
void permutations(vector<string> &res, string &str, int k, int m) {
    if (k == m) {
        res.push_back(str);
    } else {
        for (int i = k; i <= m; i++) {
            if (!isSwap(str, k, i)) {
                swap(str[k], str[i]);
                permutations(res, str, k + 1, m);
                swap(str[k], str[i]);
            }
        }
    }
}


//17. Letter Combinations of a Phone Number
vector<string> letterCombinations(string digits) {
    string nums[] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    long length = digits.length();
    for (int i = 0; i < length; i++) {
        if (!ans.size()) {
            ans.push_back("");
        }
        vector<string> temp;
        for (int j = 0; j < ans.size(); j++) {
            string str = nums[digits[i] - '0'];
            for (int k = 0; k < str.length(); k++) {
                temp.push_back(ans[j] + str[k]);
            }
        }
        ans = temp;
    }
    return ans;
}

//18. 4Sum
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ans;
    int size = (int)nums.size();
    if (size < 3) {
        return ans;
    }
    sort(nums.begin(), nums.end());
    for (int i = 0; i < size; i++) {
        int target_3 = target - nums[i];
        for (int j = i + 1; j < size; j++) {
            int target_2 = target_3 - nums[j];
            int begin = j + 1;
            int end = size - 1;
            while (begin < end) {
                int twosum = nums[begin] + nums[end];
                if (twosum > target_2) {
                    end--;
                }
                else if (twosum < target_2) {
                    begin++;
                }else {
                    vector<int> temp(4,0);
                    temp[0] = nums[i];
                    temp[1] = nums[j];
                    temp[2] = nums[begin];
                    temp[3] = nums[end];
                    ans.push_back(temp);
                    while (begin < end && nums[begin] == temp[2]) {
                        begin++;
                    }
                    while (begin < end && nums[end] == temp[3] ) {
                        end--;
                    }
                }
            }
            while (j + 1 < size && nums[j] == nums [j+1]) j++;
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

//19. Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode realHead(0);
    realHead.next = head;
    head = &realHead;
    ListNode *p = &realHead;
    while (n-- > 0) {
        p = p->next;
    }
    while (p->next != nullptr) {
        p = p->next;
        head = head->next;
    }
    head->next = head->next->next;
    return realHead.next;
}

//20. Valid Parentheses
bool isValid(string s) {
    string stack = "";
    int size = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack += s[i];
            size++;
        }
        if (s[i] == ')') {
            if (stack[size - 1] != '(') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
        if (s[i] == ']') {
            if (stack[size - 1] != '[') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
        if (s[i] == '}') {
            if (stack[size - 1] != '{') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
    }
    
    if (size > 0) {
        return false;
    }
    return true;
}

//21. Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode head(0);
    ListNode *p = &head;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            p->next = l1;
            l1 = l1->next;
        }else {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }
    if (l1 != nullptr) {
        p->next = l1;
    }
    if (l2 != nullptr) {
        p->next = l2;
    }
    return head.next;
}

//22. Generate Parentheses
void generateParenthesisPart(vector<string> &ans, int rn, int ln, int n, string s) {
    if (rn == n) {
        ans.push_back(s);
        return;
    }
    if (ln < n) {
        generateParenthesisPart(ans, rn, ln + 1, n, s + "(");
    }
    if (rn < ln) {
        generateParenthesisPart(ans, rn + 1, ln, n, s + ")");
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> ans;
    generateParenthesisPart(ans, 0, 0, n, "");
    return ans;
}

//23. Merge k Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists) {
    int k = (int)lists.size();
    if (k == 0) {
        return nullptr;
    }
    while (k > 1) {
        for (int i = 0; i < k/2; i++) {
            lists[i] = mergeTwoLists(lists[i], lists[k - 1 - i]);
        }
        k = (k+1)/2;
    }
    return lists.front();
}

//24. Swap Nodes in Pairs
ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *p = head;
    ListNode *q = head->next;
    head = q;
    ListNode *r = p;
    p->next = q->next;
    q->next = p;
    p = p->next;
    while (p != nullptr) {
        q = p->next;
        if (q == nullptr) {
            break;
        }
        r->next = q;
        r = p;
        p->next = q->next;
        q->next = p;
        p = p->next;
    }
    return head;
}

//25. Reverse Nodes in k-Group 
ListNode* reverseKGroup(ListNode* head, int k) {
    if(k == 1) return head;
    ListNode preHead(-1);
    preHead.next = head;
    ListNode *p, *q, *pre;
    pre = &preHead;
    int n = 0;
    while (head != nullptr) {
        n++;
        head = head->next;
    }
    while (n >= k) {
        p = pre->next;
        q = p->next;
        for (int i = 1; i < k; i++) {
            p->next = q->next;
            q->next = pre->next;
            pre->next = q;
            q = p->next;
        }
        pre = p;
        n -= k;
    }
    return preHead.next;
}

//26. Remove Duplicates from Sorted Array
int removeDuplicates(vector<int>& nums) {
    if(nums.empty()) return 0;
    int temp = nums[0];
    int length = 1;
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] == temp) continue;
        else {
            temp = nums[i];
            nums[length++] = temp;
        }
    }
    return length;
}

//27. Remove Element
int removeElement(vector<int>& nums, int val) {
    int length = 0;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] == val) continue;
        else nums[length++] = nums[i];
    }
    return length;
}

//28. Implement strStr()
int strStr(string haystack, string needle) {
    int len1 = (int)haystack.length(), len2 = (int)needle.length();
    if(len2 == 0) return 0;
    int ans = -1;
    for (int i = 0; i <= len1 - len2; i++) {
        if (haystack[i] == needle[0]) {
            for (int j = 0; j < len2; j++) {
                if (haystack[i + j] != needle[j]) {
                    break;
                } else ans++;
            }
            if (ans == len2 - 1) {
                return i;
            }
            ans = -1;
        }
    }
    return -1;
}

//29. Divide Two Integers
int divide(int dividend, int divisor) {
    if(divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
    long divid = labs(dividend);
    long divis = labs(divisor);
    int ans = 0;
    while (divid >= divis) {
        long temp = divis, times = 1;
        while (divid >= (temp << 1)) {
            temp <<= 1;
            times <<= 1;
        }
        divid -= temp;
        ans += times;
    }
    if ((divisor > 0) ^ (dividend > 0)) return -ans;
    else return ans;
}

//30. Substring with Concatenation of All Words
vector<int> Substring(string s, vector<string>& words) {
    vector<int> ans;
    if (words.size() == 0 || s.size() == 0) return ans;
    unordered_map<string, int> dict;
    for (int i = 0; i < words.size(); i++) dict[words[i]]++;
    int len = (int)words[0].length(), nums = (int)words.size(), n = (int)s.length();
    for (int i = 0; i <= n - nums * len; i++) {
        unordered_map<string, int> seen;
        int j = 0;
        for (; j < nums; j++) {
            string temp = s.substr(i + j * len, len);
            if (dict.find(temp) != dict.end()) {
                seen[temp]++;
                if (seen[temp] > dict[temp]) break;
            } else break;
        }
        if (j == nums) ans.push_back(i);
    }
    return ans;
}

//31. Next Permutation
void nextPermutation(vector<int>& nums) {
    int size = (int)nums.size();
    if (size < 2) return;
    int i = size - 2, j;
    while (i >= 0) {
        if (nums[i] < nums[i + 1]) break;
        i--;
    }
    if (i != -1) {
        j = size - 1;
        while (j > i) {
            if (nums[j] > nums[i]) {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                break;
            }
            j--;
        }
    }
    for (j = size - 1, i++; i < j; i++,j--) {
        int temp;
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

//32. Longest Valid Parentheses (stack solution)
int longestValidParentheses(string s) {
    stack<int> stack;
    int n = (int)s.length();
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') stack.push(i);
        else {
            if (!stack.empty()) {
                if (s[stack.top()] == '(') stack.pop();
                else stack.push(i);
            } else stack.push(i);
        }
    }
    int maxLen = 0, i = n;
    if (stack.empty()) return n;
    while (!stack.empty()) {
        int j = stack.top();
        stack.pop();
        maxLen = max(i - j - 1, maxLen);
        i = j;
    }
    maxLen = max(maxLen, i);
    return maxLen;
}
//DP solution
int longestValidParenthesesByDp(string s) {
    int len = (int)s.length();
    if (len < 2) return 0;
    vector<int> longest(len, 0);
    int maxLen = 0;
    for (int i = 1; i < len; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                longest[i] = (i - 2) >= 0 ? longest[i - 2] + 2 : 2;
            } else {
                if (i - longest[i - 1] >= 0 && s[i - longest[i - 1] - 1] == '(') {
                    longest[i] = longest[i - 1] + ((i - longest[i - 1] - 2 >= 0) ? longest[i - longest[i - 1] - 2] : 0) + 2;
                }
            }
            maxLen = longest[i] > maxLen ? longest[i] : maxLen;
        }
    }
    return maxLen;
}

//61. Rotate List
ListNode* rotateRight(ListNode* head, int k) {
    ListNode *p = head, *q = head;
    int n = 0;
    while (p != nullptr) {
        p = p->next;
        n++;
    }
    p = head;
    k %= n;
    while (k--) {
        p = p->next;
    }
    while (p->next != nullptr) {
        p = p->next;
        q = q->next;
    }
    p->next = head;
    head = q->next;
    q->next = nullptr;
    return head;
}

//83. Remove Duplicates from Sorted List
ListNode* deleteDuplicates(ListNode* head) {
    ListNode *q = head;
    if (head == nullptr) return head;
    ListNode *p = head->next;
    while (p != nullptr) {
        if (p != nullptr && p->val == q->val) q->next = p->next;
        else q = q->next;
        p = p->next;
    }
    return head;
}

//82. Remove Duplicates from Sorted List II
ListNode* deleteDuplicatesII(ListNode* head) {
    if (head == nullptr) return head;
    ListNode *q, *p = head->next;
    ListNode preHead = ListNode(0);
    preHead.next = head;
    q = &preHead;
    while (p != nullptr) {
        if (p->val != q->next->val) {
            q = q->next;
        } else {
            while (p->val == q->next->val && p->next != nullptr) {
                p = p->next;
            }
            if (p->val == q->next->val && p->next == nullptr) q->next = p->next;
            else q->next = p;
        }
        p = p->next;
    }
    return preHead.next;
}

//86. Partition List 
ListNode* partition(ListNode* head, int x) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode preHead(0);
    preHead.next = head;
    ListNode *p = &preHead, *q = head, *r = &preHead;
    while (q != nullptr) {
        if (q->val >= x) {
            q = q->next;
            r = p->next;
            break;
        }
        q = q->next;
        p = p->next;
    }
    while (q != nullptr) {
        if (q->val < x) {
            r->next = q->next;
            q->next = p->next;
            p->next = q;
            q = r->next;
            p = p->next;
        } else {
            q = q->next;
            r = r->next;
        }
    }
    return preHead.next;
}

//92. Reverse Linked List II 
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (head == nullptr || head->next == nullptr || m == n) {
        return head;
    }
    ListNode preHead(0);
    preHead.next = head;
    ListNode *pre = &preHead, *p, *q;
    n -= m;
    while (m-- > 1) {
        pre = pre->next;
    }
    p = pre->next;
    q = p->next;
    while (n--) {
        p->next = q->next;
        q->next = pre->next;
        pre->next = q;
        q = p->next;
    }
    return preHead.next;
}

//34. Search for a Range 
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> ans(2, -1);
    int first = 0, end = (int)nums.size() - 1, mid = 0;
    if (nums.empty()) return ans;
    while (first <= end) {
        mid = (first + end) / 2;
        if (nums[mid] > target) {
            end = mid - 1;
        } else if (nums[mid] < target) {
            first = mid + 1;
        } else break;
    }
    if (nums[mid] == target) {
        first = mid;
        end = mid;
        while (nums[first] == target && first >= 0) first--;
        while (nums[end] == target && end < nums.size()) end++;
        ans[0] = first + 1;
        ans[1] = end - 1;
    }
    return ans;
}

//35. Search Insert Position 
int searchInsert(vector<int>& nums, int target) {
    int i = 0;
    for(; i < nums.size(); i++){
        if(nums[i] >= target) break;
    }
    return i;
}

//36. Valid Sudoku 
bool isValidSudoku(vector<vector<char>>& board) {
    int a[10][10] = {0}, b[10][10] = {0}, c[10][10] = {0};
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            if(board[i][j] == '.') continue;
            else {
                int k = board[i][j] - '0';
                a[i][k]++;
                b[k][j]++;
                int tmp = i/3 + (j/3) * 3;
                c[tmp][k]++;
                if(a[i][k] > 1 || b[k][j] > 1 || c[tmp][k] > 1) return false;
            }
        }
    }
    return true;
}

//38. Count and Say
string countAndSay(int n) {
    if(n == 0) return "";
    string ans = "1";
    if (n == 1) {
        return ans;
    }
    for(int i = 1; i < n; i++) {
        string res = "";
        int count = 1;
        char tmp = ans[0];
        for(int j = 1; j < ans.length(); j++) {
            if(ans[j] == tmp) count++;
            else {
                res = res + to_string(count) + tmp;
                count = 1;
                tmp = ans[j];
            }
        }
        res = res + to_string(count) + tmp;
        ans = res;
    }
    return ans;
}

//39. Combination Sum
void combinationSumMethod(vector<vector<int>>& ans, vector<int>& res, vector<int>& candidates, int target, int begin, int n) {
    if (!target) {
        ans.push_back(res);
        return;
    }
    for (int i = begin; i < n && target >= candidates[i]; i++) {
        res.push_back(candidates[i]);
        combinationSumMethod(ans, res, candidates, target - candidates[i], i, n);
        res.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    int n = (int)candidates.size();
    vector<int> res;
    sort(candidates.begin(), candidates.end());
    combinationSumMethod(ans, res, candidates, target, 0, n);
    return ans;
}

//40. Combination Sum2
void combinationSum2Method(set<vector<int>>& ans, vector<int>& res, vector<int>& candidates, int target, int begin, int n) {
    if (!target) {
        ans.insert(res);
        return;
    }
    for (int i = begin; i < n && target >= candidates[i]; i++) {
        res.push_back(candidates[i]);
        combinationSum2Method(ans, res, candidates, target - candidates[i], i + 1, n);
        res.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    set<vector<int>> tmp;
    int n = (int)candidates.size();
    vector<int> res;
    sort(candidates.begin(), candidates.end());
    combinationSum2Method(tmp, res, candidates, target, 0, n);
    vector<vector<int>> ans;
    set<vector<int>>::iterator it = tmp.begin();
    for (; it!=tmp.end(); it++) {
        ans.push_back(*it);
    }
    return ans;
}

//41. First Missing Positive
int firstMissingPositive(vector<int>& nums) {
    int n = (int)nums.size();
    for (int i = 0; i < n; i++) {
        while(nums[i] > 0 && nums[i] < n && nums[nums[i] - 1] != nums[i])
            swap(nums[i], nums[nums[i] - 1]);
    }
    for (int i = 0; i < n; i++) {
        if(nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

//42. Trapping Rain Water
int trap(vector<int>& height) {
    int ans = 0, left = 0, right = (int)height.size() - 1;
    int lower = 0, level = 0;
    while (left < right) {
        lower = height[height[left] < height[right] ? left++ : right--];
        level = max(lower, level);
        ans += level - lower;
    }
    return ans;
}

//45. Jump Game2
int jump(vector<int>& nums) {
    int n = (int)nums.size();
    if(n <= 1) return 0;
    int reach = 0, tmp = 0, cnt = 0, i = 0;
    while (reach - i + 1 > 0) {
        cnt++;
        for(; i <= reach; i++){
            tmp = max(tmp, nums[i] + i);
            if(tmp >= n - 1) return cnt;
        }
        reach = tmp;
    }
    return cnt;
}

//48. Rotate Image
void rotate(vector<vector<int>>& matrix) {
    int n = (int)matrix.size();
    for(int i = 0; i < n / 2; i ++) {
        for(int j = 0; j < n; j ++) {
            swap(matrix[i][j], matrix[n - i - 1][j]);
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = i; j < n; j ++) {
            swap(matrix[j][i], matrix[i][j]);
        }
    }
}

//53. Maximum Subarray

int maxSubArray(vector<int>& nums) {
    int maxSum = 0;
    int tmp = 0;
    for (int i = 0; i < nums.size(); i++) {
        tmp += nums[i];
        if (tmp > maxSum) {
            maxSum = tmp;
        }
        if (tmp < 0) {
            tmp = 0;
        }
    }
    return maxSum;
}

//55. Jump Game
bool canJump(vector<int>& nums) {
    int n = (int)nums.size();
    int i = 0, reach = 0;
    for(; i < n && i <= reach; i++)
        reach = max(i + nums[i], reach);
    return i == n;
}

//54. Spiral Matrix
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;
    if (matrix.empty()) return ans;
    int left = 0, top = 0;
    int right = (int)matrix[0].size();
    int bottom = (int)matrix.size();
    while (left < right || top < bottom) {
        if (top < bottom) {
            for (int i = left; i < right; i++) {
                ans.push_back(matrix[top][i]);
            }
            top++;
        }
        if (left < right) {
            for (int j = top; j < bottom; j++) {
                ans.push_back(matrix[j][right - 1]);
            }
            right--;
        }
        if (top < bottom) {
            for (int i = right - 1; i >= left; i--) {
                ans.push_back(matrix[bottom - 1][i]);
            }
            bottom--;
        }
        if (left < right) {
            for (int j = bottom - 1; j >= top; j--) {
                ans.push_back(matrix[j][left]);
            }
            left++;
        }
    }
    return ans;
}

//56. Merge Intervals
bool cmp(Interval a, Interval b) {
    return a.start < b.start;
}
vector<Interval> merge(vector<Interval>& intervals) {
    vector<Interval> ans;
    sort(intervals.begin(), intervals.end(), cmp);
    for (int i = 0; i < intervals.size(); i++) {
        int s = intervals[i].start;
        int e = intervals[i].end;
        for (int j = i + 1; j < intervals.size(); j++) {
            int tmp = intervals[j].start;
            if (tmp > e) {
                break;
            } else {
                if(e < intervals[j].end) e = intervals[j].end;
                i++;
            }
        }
        Interval a =  Interval(s, e);
        ans.push_back(a);
    }
    return ans;
}

//59. Spiral Matrix II
vector<vector<int>> generateMatrix(int n) {
    int num = 1;
    vector<vector<int>> ans(n, vector<int>(n));
    int l = 0, u = 0, r = n - 1, d = n - 1;
    while ((l <= r || u <= d) && num <= n * n) {
        if (l <= r && num <= n * n) {
            for (int i = l; i <= r; i++)
                ans[u][i] = num++;
            u++;
        }
        if (u <= d && num <= n * n) {
            for (int i = u; i <= d; i++)
                ans[i][r] = num++;
            r--;
        }
        if (l <= r && num <= n * n) {
            for (int i = r; i >= l; i--)
                ans[d][i] = num++;
            d--;
        }
        if (u <= d && num <= n * n) {
            for (int i = d; i >= u; i--)
                ans[i][l] = num++;
            l++;
        }
    }
    return ans;
}

//62. Unique Paths
int uniquePaths(int m, int n) {
    vector<vector<int>> nums(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            nums[i][j] = nums[i - 1][j] + nums[i][j - 1];
    return nums[m - 1][n - 1];
}

//63. Unique Paths II
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = (int)obstacleGrid.size();
    int n = (int)obstacleGrid[0].size();
    vector<vector<int>> nums(m, vector<int>(n, 1));
    for (int i = 0; i < m; i++)
        if(obstacleGrid[i][0] == 1) {
            while(i < m) {
                nums[i][0] = 0;
                i++;
            }
        }
    for (int j = 0; j < n; j++)
        if(obstacleGrid[0][j] == 1) {
            while (j < n) {
                nums[0][j] = 0;
                j++;
            }
        }
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++) {
            if(obstacleGrid[i][j] == 1) {
                nums[i][j] = 0;
                continue;
            } else nums[i][j] = nums[i - 1][j] + nums[i][j - 1];
        }
    return nums[m - 1][n - 1];
}

//64. Minimum Path Sum
int minPathSum(vector<vector<int>>& grid) {
    int m = (int)grid.size();
    int n = (int)grid[0].size();
    for (int i = 1; i < m; i++)
        grid[i][0] += grid[i - 1][0];
    for (int j = 1; j < n; j++)
        grid[0][j] += grid[0][j - 1];
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
    return grid[m - 1][n - 1];
}

//73. Set Matrix Zeroes
void setZeroes(vector<vector<int>>& matrix) {
    int m = (int)matrix.size();
    int n = (int)matrix[0].size();
    vector<bool> row(m, false);
    vector<bool> col(n, false);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == 0) {
                row[i] = true;
                col[j] = true;
            }
    for (int i = 0; i < m; i++)
        if (row[i]) {
            for (int j = 0; j < n; j++)
                matrix[i][j] = 0;
        }
    for (int j = 0; j < n; j++)
        if (col[j]) {
            for (int i = 0; i < m; i++)
                matrix[i][j] = 0;
        }
}

//74. Search a 2D Matrix
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int m = (int)matrix.size();
    int n = (int)matrix[0].size();
    int start = 0, end = m * n - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        int i = mid / n, j = mid % n;
        if (matrix[i][j] < target) start = mid + 1;
        else if (matrix[i][j] > target) end = mid - 1;
        else return true;
    }
    return false;
}

//75. Sort Colors
void sortColors(vector<int>& nums) {
    int n = (int)nums.size();
    int i = 0, j = n - 1;
    while (i < j) {
        while (nums[i] == 2 && i < j) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            j--;
        }
        i++;
    }
    i = 0;
    while (i < j) {
        while (nums[j] == 0 && i < j) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++;
        }
        j--;
    }
}

//78. Subsets
void getSubsets(vector<int>& sub, vector<vector<int>>& subs, vector<int>& nums, int n) {
    subs.push_back(sub);
    for (int i = n; i < nums.size(); i++) {
        sub.push_back(nums[i]);
        getSubsets(sub, subs, nums, i + 1);
        sub.pop_back();
    }
    return;
}
vector<vector<int>> subsets(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    vector<int> sub;
    getSubsets(sub, ans, nums, 0);
    return ans;
}

//79. Word Search (回溯)
bool isFound(vector<vector<char>>& board, const char* w, int i, int j) {
    int m = (int)board.size();
    int n = (int)board[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] == '\0' || board[i][j] != *w) {
        return false;
    }
    if (*(w + 1) == '\0') return true;
    char t = board[i][j];
    board[i][j] = '\0';
    if (isFound(board, w + 1, i + 1, j) || isFound(board, w + 1, i - 1, j) || isFound(board, w + 1, i, j + 1) || isFound(board, w + 1, i, j - 1)) {
        return true;
    }
    board[i][j] = t;
    return false;
}
bool exist(vector<vector<char>>& board, string word) {
    if (board.empty()) {
        return false;
    }
    int m = (int)board.size();
    int n = (int)board[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (isFound(board, word.c_str(), i, j)) {
                return true;
            }
        }
    }
    return false;
}

//80. Remove Duplicates from Sorted Array II
int removeDuplicates2(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])
            nums[i++] = n;
    return i;
}

//44. Wildcard Matching
bool isMatch2(string s, string p) {
    int m = (int)s.length(), n = (int)p.length();
    int i = 0, j = 0, star = -1, match = 0;
    while (i < m) {
        if (j < n && (s[i] == p[j] || p[j] == '?')) {
            i++;
            j++;
        } else if (j < n && p[j] == '*') {
            star = j++;
            match = i;
        } else if (star >= 0) {
            i = ++match;
            j = star + 1;
        } else return false;
    }
    while (j < n && p[j] == '*') j++;
    return j == n;
}

//70. Climbing Stairs
int climbStairs(int n) {
    vector<int> ans(n + 1, 0);
    ans[0] = 1;
    ans[1] = 1;
    for (int i = 2; i <= n; i++) {
        ans[i] = ans[i - 1] + ans[i - 2];
    }
    return ans[n];
}

//72. Edit Distance
int minDistance(string word1, string word2) {
    int m = (int)word1.length();
    int n = (int)word2.length();
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
    for (int i = 1; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
            }
        }
    }
    return dp[m][n];
}

//43. Multiply Strings
string multiply(string num1, string num2) {
    string sum(num1.length() + num2.length(), '0');
    for (int i = (int)num2.length() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = (int)num1.length() - 1; j >= 0; j--) {
            int tmp = (num2[i] - '0') * (num1[j] - '0') + carry + (sum[i + j + 1] - '0');
            sum[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        sum[i] += carry;
    }
    size_t startp = sum.find_first_not_of('0');
    if (string::npos != startp) {
        return sum.substr(startp);
    }
    return "0";
}

//46. Permutations
void permutations(vector<vector<int>> &res, vector<int> &nums, int k, int m) {
    if (k == m) {
        res.push_back(nums);
    } else {
        for (int i = k; i < m; i++) {
            swap(nums[k], nums[i]);
            permutations(res, nums, k + 1, m);
            swap(nums[k], nums[i]);
        }
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    int m = (int)nums.size();
    permutations(res, nums, 0, m - 1);
    return res;
}

//49. Group Anagrams
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    vector<vector<string>> res;
    for (string s : strs) {
        string t = s;
        sort(t.begin(), t.end());
        mp[t].push_back(s);
    }
    for (auto m : mp) {
        vector<string> ans = m.second;
        sort(ans.begin(), ans.end());
        res.push_back(ans);
    }
    return res;
}

//50. Pow(x, n)
double myPow(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) {
        x = 1 / x;
        n = -n;
    }
    if (n % 2 == 0) return myPow(x * x, n / 2);
    else return x * myPow(x * x, (n - 1) / 2);
}

//51. N-Queens
bool isNQueensValid(vector<string> res, int row, int col, int n) {
    for (int i = row; i >= 0; i--) {
        if (res[i][col] == 'Q') {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (res[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (res[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

void solveNQueens(vector<vector<string>> &ans, vector<string> &res, int row, int n) {
    if (row == n) {
        ans.push_back(res);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (isNQueensValid(res, row, i, n)) {
            res[row][i] = 'Q';
            solveNQueens(ans, res, row + 1, n);
            res[row][i] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> res(n, string(n, '.'));
    solveNQueens(ans, res, 0, n);
    return ans;
}

//58. Length of Last Word
int lengthOfLastWord(string s) {
    int len = 0, i = (int)s.size() - 1;
    while (s[i] == ' ') {
        i--;
    }
    for (; i >= 0; i--) {
        if (s[i] == ' ') {
            break;
        } else len++;
    }
    return len;
}

//60. Permutation Sequence
string getPermutation(int n, int k) {
    vector<string> nums = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string res = "";
    vector<int> pNums(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        pNums[i] = pNums[i - 1] * i;
    }
    k--;
    while (n--) {
        int index = k / pNums[n];
        res = res + nums[index];
        nums.erase(nums.begin() + index);
        k -= index * pNums[n];
    }
    return res;
}

//67. Add Binary
string addBinary(string a, string b) {
    string res = "";
    int c = 0;
    int i = (int)a.size(), j = (int)b.size();
    while (i || j || c) {
        int x = i > 0 ? (a[--i] - '0') : 0;
        int y = j > 0 ? (b[--j] - '0') : 0;
        int tmp = x + y + c;
        if (tmp > 1) {
            tmp -= 2;
            c = 1;
        } else c = 0;
        res = to_string(tmp) + res;
    }
    return res;
}

//69. Sqrt(x)
int mySqrt(int x) {
    long long r = x;
    while (r * r > x)
        r = (r + x / r) / 2;
    return (int)r;
}

//76. Minimum Window Substring
string minWindow(string s, string t) {
    vector<int> map(128, 0);
    for (auto c : t) map[c]++;
    int counter = (int)t.length(), begin = 0, end = 0, d = INT_MAX, head = 0;
    while (end < s.length()) {
        if (map[s[end++]]-- > 0) {
            counter--;
        }
        while (counter == 0) {
            if (end - begin < d) {
                d = end - begin;
                head = begin;
            }
            if (map[s[begin++]]++ == 0) {
                counter++;
            }
        }
    }
    return d == INT_MAX ? "" : s.substr(head, d);
}

//77. Combinations
void combinations(vector<vector<int>> &res, vector<int> &ans, int k, int n, int begin, int count) {
    if (count == k) {
        res.push_back(ans);
        return;
    }
    for (int i = begin; i <= n; i++) {
        ans.push_back(i);
        combinations(res, ans, k, n, i + 1, count + 1);
        ans.pop_back();
    }
}
vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> ans;
    combinations(res, ans, k, n, 1, 0);
    return res;
}
vector<vector<int>> combine2(int n, int k) {
    vector<vector<int>> res;
    vector<int> temp(k, 0);
    int i = 0;
    while (i >= 0) {
        temp[i]++;
        if (temp[i] > n) i--;
        else if (i == k - 1) res.push_back(temp);
        else {
            i++;
            temp[i] = temp[i - 1];
        }
    }
    return res;
}

//84. Largest Rectangle in Histogram
int largestRectangleArea(vector<int> &heights) {
    int ret = 0;
    heights.push_back(0);
    vector<int> index;
    for(int i = 0; i < heights.size(); i++) {
        while(index.size() > 0 && heights[index.back()] >= heights[i]) {
            int h = heights[index.back()];
            index.pop_back();
            int sidx = index.size() > 0 ? index.back() : -1;
            if(h * (i-sidx-1) > ret)
                ret = h * (i-sidx-1);
        }
        index.push_back(i);
    }
    return ret;
}

//85. Maximal Rectangle
int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.empty()) return 0;
    const int m = (int)matrix.size();
    const int n = (int)matrix[0].size();
    vector<int> left(n, 0);
    vector<int> right(n, n);
    vector<int> height(n, 0);
    int maxA = 0;
    for(int i = 0; i < m; i++) {
        int cur_left = 0, cur_right = n;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == '1') height[j]++;
            else height[j] = 0;
        }
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == '1') left[j] = max(left[j], cur_left);
            else {
                left[j] = 0;
                cur_left = j + 1;
            }
        }
        for(int j = n - 1; j >= 0; j--) {
            if(matrix[i][j] == '1') right[j] = min(right[j], cur_right);
            else {
                right[j] = n;
                cur_right = j;
            }
        }
        for(int j = 0; j < n; j++)
            maxA = max(maxA, (right[j] - left[j]) * height[j]);
    }
    return maxA;
}

//88. Merge Sorted Array
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int k = m + n - 1;
    int i = m - 1;
    int j = n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

//100. Same Tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) {
        return true;
    }
    if (p && q) {
        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    } else return false;
}

//101. Symmetric Tree
bool isSymmetric(TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    queue<TreeNode*> q1, q2;
    q1.push(root->left);
    q2.push(root->right);
    while (!q1.empty() && !q2.empty()) {
        TreeNode* left = q1.front();
        q1.pop();
        TreeNode* right = q2.front();
        q2.pop();
        if (left == NULL && right == NULL) {
            continue;
        }
        if (left == NULL || right == NULL) {
            return false;
        }
        if (left->val != right->val) {
            return false;
        }
        q1.push(left->left);
        q1.push(left->right);
        q2.push(right->right);
        q2.push(right->left);
    }
    return true;
}
bool isSymmetricHelp(TreeNode* left, TreeNode* right) {
    if (left == NULL && right == NULL) {
        return true;
    } else return left->val == right->val && isSymmetricHelp(left->left, right->right) && isSymmetricHelp(left->right, right->left);
}
bool isSymmetric2(TreeNode* root) {
    if (root == NULL) return true;
    return isSymmetricHelp(root->left, root->right);
}

//104. Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if (root == NULL) return 0;
    else return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
}

//107. Binary Tree Level Order Traversal II
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> ans;
    vector<TreeNode*> q;
    if (root == NULL) {
        return ans;
    }
    q.push_back(root);
    while (!q.empty()) {
        vector<TreeNode*> qtmp;
        vector<int> tmp;
        for (int i = 0; i < q.size(); i++) {
            if (q[i] != NULL) {
                tmp.push_back(q[i]->val);
                qtmp.push_back(q[i]->left);
                qtmp.push_back(q[i]->right);
            }
        }
        q = qtmp;
        ans.push_back(tmp);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

//108. Convert Sorted Array to Binary Search Tree
TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.size() == 0) return NULL;
    int mid = (int)nums.size() / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    vector<int> leftNums(nums.begin(), nums.begin() + mid);
    vector<int> rightNums(nums.begin() + mid + 1, nums.end());
    root->left = sortedArrayToBST(leftNums);
    root->right = sortedArrayToBST(rightNums);
    return root;
}

//110. Balanced Binary Tree
bool isBalanced(TreeNode* root) {
    if (root == NULL) return true;
    else return abs(maxDepth(root->right) - maxDepth(root->left)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

//111. Minimum Depth of Binary Tree
int minDepth(TreeNode* root) {
//  非递归法
    if (root == NULL) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 1;
    while (!q.empty()) {
        int n = (int)q.size();
        while (n--) {
            TreeNode* tmp = q.front();
            q.pop();
            if (tmp == NULL) {
                continue;
            } else {
                if (tmp->left == NULL && tmp->right == NULL) return depth;
                q.push(tmp->left);
                q.push(tmp->right);
            }
        }
        depth++;
    }
    return depth;
//    递归法
//    if(root==NULL) return 0;
//    if(root->left==NULL) return minDepth(root->right)+1;
//    if(root->right==NULL) return minDepth(root->left)+1;
//    return min(minDepth(root->left),minDepth(root->right))+1;
}

//112. Path Sum
bool hasPathSum(TreeNode* root, int sum) {
    if (root == NULL) {
        return false;
    }
    if (root->val == sum && root->left == NULL && root->right == NULL) {
        return true;
    } else return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

//118. Pascal's Triangle
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    if (numRows == 0) {
        return ans;
    }
    vector<int> one;
    one.push_back(1);
    ans.push_back(one);
    for (int i = 1; i < numRows; i++) {
        vector<int> tmp;
        tmp.push_back(1);
        for (int j = 1; j < i; j++) {
            tmp.push_back(ans[i - 1][j - 1] + ans[i - 1][j]);
        }
        tmp.push_back(1);
        ans.push_back(tmp);
    }
    return ans;
}

//119. Pascal's Triangle II
vector<int> getRow(int rowIndex) {
    vector<int> res(rowIndex + 1, 0);
    res[0] = 1;
    for (int i = 1; i <= rowIndex; i++) {
        for (int j = 1; j <= i; j++) {
            res[j] += res[j - 1];
        }
    }
    return res;
}

//94. Binary Tree Inorder Traversal
vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    vector<int> ans;
    TreeNode* p = root;
    while (!s.empty() || p != NULL) {
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            s.pop();
            ans.push_back(p->val);
            p = p->right;
        }
    }
    return ans;
}

//93. Restore IP Addresses
vector<string> restoreIpAddresses(string s) {
    vector<string> ans;
    string tmp;
    for (int a = 1; a <= 3; a++) {
        for (int b = 1; b <= 3; b++) {
            for (int c = 1; c <= 3; c++) {
                for (int d = 1; d <= 3; d++) {
                    if (a + b + c + d == s.length()) {
                        int A = stoi(s.substr(0, a));
                        int B = stoi(s.substr(a, b));
                        int C = stoi(s.substr(a+b, c));
                        int D = stoi(s.substr(a+b+c, d));
                        if (A<=255 && B<=255 && C<=255 && D<=255)
                            if ( (tmp=to_string(A)+"."+to_string(B)+"."+to_string(C)+"."+to_string(D)).length() == s.length()+3)
                                ans.push_back(tmp);
                    }
                }
            }
        }
    }
    return ans;
}

//96. Unique Binary Search Trees
int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    return dp[n];
}

//125. Valid Palindrome
bool isPalindrome(string s) {
    int i = 0, j = (int)s.length() - 1;
    while (i < j) {
        while (isalnum(s[i]) == 0 && i < j) i++;
        while (isalnum(s[j]) == 0 && i < j) j--;
        if (toupper(s[i]) != toupper(s[j])) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

//141. Linked List Cycle
bool hasCycle(ListNode *head) {
    ListNode *p = head, *q = head;
    while (p != NULL) {
        if (p->next == NULL) return false;
        p = p->next->next;
        q = q->next;
        if (p == q) return true;
    }
    return false;
}

//160. Intersection of Two Linked Lists
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *p = headA, *q = headB;
    while (p != q) {
        p = p->next == NULL ? headB : p->next;
        q = q->next == NULL ? headA : q->next;
    }
    return p;
}

//90. Subsets II
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> ans = {{}};
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ) {
        int count = 0;
        while (count + i < nums.size() && nums[count + i] == nums[i]) count++;
        int preN = (int)ans.size();
        for (int k = 0; k < preN; k++) {
            vector<int> tmp = ans[k];
            for (int j = 0; j < count; j++) {
                tmp.push_back(nums[i]);
                ans.push_back(tmp);
            }
        }
        i += count;
    }
    return ans;
}

//95. Unique Binary Search Trees II
TreeNode* clone(TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode *newRoot = new TreeNode(root->val);
    newRoot->left = clone(root->left);
    newRoot->right = clone(root->right);
    return newRoot;
}
vector<TreeNode*> generateTrees(int n) {
    vector<TreeNode*> ans;
    if (n > 0) {
        TreeNode *root = new TreeNode(1);
        ans.push_back(root);
    }
    for (int i = 2; i <= n; i++) {
        vector<TreeNode*> tmp;
        for (int j = 0; j < ans.size(); j++) {
            TreeNode *oldRoot = ans[j];
            TreeNode *target = clone(oldRoot);
            TreeNode *newRoot = new TreeNode(i);
            newRoot->left = target;
            tmp.push_back(newRoot);
            if (oldRoot != NULL) {
                TreeNode *tmpOld = clone(oldRoot);
                TreeNode *p = tmpOld;
                while (p != NULL) {
                    TreeNode *pr = p->right;
                    TreeNode *newNode = new TreeNode(i);
                    p->right = newNode;
                    newNode->left = pr;
                    TreeNode *q = clone(tmpOld);
                    tmp.push_back(q);
                    p->right = pr;
                    p = p->right;
                }
            }
        }
        ans = tmp;
    }
    return ans;
}

//169. Majority Element
int majorityElement(vector<int>& nums) {
    int ans = nums[0], count = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == ans) count++;
        else count--;
        if (count < 0) {
            ans = nums[i];
            count = 1;
        }
    }
    return ans;
}

//167. Two Sum II - Input array is sorted
vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> ans;
    for (int i = 0, j = (int) numbers.size() - 1; i < j; ) {
        int tmp = numbers[i] + numbers[j];
        if (tmp == target) {
            ans.push_back(i + 1);
            ans.push_back(j + 1);
            return ans;
        } else if (tmp > target) j--;
        else i++;
    }
    return ans;
}

//98. Validate Binary Search Tree
bool isValidBSTHelp(TreeNode* root, TreeNode *minNode, TreeNode *maxNode) {
    if (root == NULL) return true;
    if ((minNode != NULL && minNode->val >= root->val) || (maxNode != NULL && maxNode->val <= root->val)) return false;
    else return isValidBSTHelp(root->left, minNode, root) && isValidBSTHelp(root->right, root, maxNode);
}
bool isValidBST(TreeNode* root) {
    if (root == NULL) return true;
    else return isValidBSTHelp(root, NULL, NULL);
}

//97. Interleaving String
bool isInterleave(string s1, string s2, string s3) {
    if (s1.length() + s2.length() != s3.length()) {
        return false;
    }
    bool dp[s1.length() + 1][s2.length() + 1];
    for (int i = 0; i < s1.length(); i++) {
        for (int j = 0; j < s2.length(); j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
            } else {
                dp[i][j] = (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]) || (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
            }
        }
    }
    return dp[s1.length()][s2.length()];
}

//99. Recover Binary Search Tree
void recoverTree(TreeNode* root) {
    TreeNode *firstNode = NULL;
    TreeNode *secondNode = NULL;
    TreeNode *preNode = NULL;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (!s.empty() || p != NULL) {
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (preNode == NULL) {
            preNode = s.top();
        }
        TreeNode *tmp = s.top();
        if (tmp->val < preNode->val) {
            if (firstNode == NULL) {
                firstNode = preNode;
                secondNode = tmp;
            } else secondNode = tmp;
        }
        p = tmp->right;
        preNode = tmp;
        s.pop();
    }
    int tmp = firstNode->val;
    firstNode->val = secondNode->val;
    secondNode->val = tmp;
}

//102. Binary Tree Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = (int)q.size();
        vector<int> res;
        while (n--) {
            TreeNode* tmp = q.front();
            if (tmp != NULL) {
                res.push_back(tmp->val);
                q.push(tmp->left);
                q.push(tmp->right);
            }
            q.pop();
        }
        if (!res.empty()) ans.push_back(res);
    }
    return ans;
}

//103. Binary Tree Zigzag Level Order Traversal
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    stack<TreeNode*> s;
    s.push(root);
    bool rightToLeft = false;
    while (!s.empty()) {
        int n = (int)s.size();
        vector<int> res;
        stack<TreeNode*> tmpS;
        while (n--) {
            TreeNode* tmp = s.top();
            s.pop();
            if (tmp != NULL) {
                res.push_back(tmp->val);
                if (rightToLeft) {
                    tmpS.push(tmp->right);
                    tmpS.push(tmp->left);
                } else {
                    tmpS.push(tmp->left);
                    tmpS.push(tmp->right);
                }
            }
        }
        s = tmpS;
        rightToLeft = !rightToLeft;
        if (!res.empty()) ans.push_back(res);
    }
    return ans;
}

//109. Convert Sorted List to Binary Search Tree
ListNode* list109;
int count(ListNode* head) {
    int ans = 0;
    while (head != NULL) {
        ans++;
        head = head->next;
    }
    return ans;
}
TreeNode* generateBST(int n) {
    if (n == 0) return NULL;
    int mid = n / 2;
    TreeNode* node = new TreeNode(0);
    node->left = generateBST(mid);
    node->val = list109->val;
    list109 = list109->next;
    node->right = generateBST(n - mid - 1);
    return node;
}
TreeNode* sortedListToBST(ListNode* head) {
    list109 = head;
    return generateBST(count(head));
}

//113. Path Sum II
void pathSumHelp(TreeNode* root, int sum, vector<vector<int>> &ans, vector<int> &res) {
    if (root == NULL) return;
    res.push_back(root->val);
    if (root->val == sum && root->left == NULL && root->right == NULL) ans.push_back(res);
    pathSumHelp(root->left, sum - root->val, ans, res);
    pathSumHelp(root->right, sum - root->val, ans, res);
    res.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> ans;
    vector<int> res;
    pathSumHelp(root, sum, ans, res);
    return ans;
}

//114. Flatten Binary Tree to Linked List
void flatten(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* now = root;
    while (now != NULL) {
        if (now->left != NULL) {
            TreeNode* pre = now->left;
            while (pre->right != NULL) {
                pre = pre->right;
            }
            pre->right = now->right;
            now->right = now->left;
            now->left = NULL;
        }
        now = now->right;
    }
}

//747. Largest Number Greater Than Twice of Others
int dominantIndex(vector<int>& nums) {
    if (nums.empty()) {
        return -1;
    }
    int index = 0;
    int maxNum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
            index = i;
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (i == index) {
            continue;
        }
        if (nums[i] * 2 > maxNum) {
            return -1;
        }
    }
    return index;
}

//106. Construct Binary Tree from Postorder and Inorder Traversal
TreeNode* buildTreeHelp(vector<int> postorder, vector<int> inorder, int pStart, int pEnd, int inStart, int inEnd) {
    if (inStart > inEnd) {
        return NULL;
    }
    TreeNode* p = new TreeNode(postorder[pEnd]);
    int pos = 0;
    for (int i = inStart; i <= inEnd; i++) {
        if (postorder[pEnd] == inorder[i]) {
            pos = i;
            break;
        }
    }
    p->left = buildTreeHelp(postorder, inorder, pStart, pStart + pos - inStart - 1, inStart, pos - 1);
    p->right = buildTreeHelp(postorder, inorder, pEnd - (inEnd - pos), pEnd - 1, pos + 1, inEnd);
    return p;
}
//105. Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* buildTreeHelp2(vector<int> preorder, vector<int> inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd) {
        return NULL;
    }
    TreeNode* p = new TreeNode(preorder[preStart]);
    int pos = 0;
    for (int i = inStart; i <= inEnd; i++) {
        if (preorder[preStart] == inorder[i]) {
            pos = i;
            break;
        }
    }
    p->left = buildTreeHelp(preorder, inorder, preStart + 1, pos - inStart + preStart, inStart, pos - 1);
    p->right = buildTreeHelp(preorder, inorder, preEnd - inEnd + pos + 1, preEnd, pos + 1, inEnd);
    return p;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = (int)postorder.size();
    TreeNode* root = buildTreeHelp(postorder, inorder, 0, n - 1, 0, n - 1);
    return root;
}

//115. Distinct Subsequences
int numDistinct(string s, string t) {
    int n = (int)s.length(), m = (int)t.length();
    vector<vector<int>> ans(m + 1, vector<int> (n + 1));
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                ans[i][j] = 1;
            } else if (j == 0) {
                ans[i][j] = 0;
            } else {
                ans[i][j] = s[j - 1] == t[i - 1] ? (ans[i - 1][j - 1] + ans[i][j - 1]) : ans[i][j - 1];
            }
        }
    }
    return ans[m][n];
}

//116. Populating Next Right Pointers in Each Node
void connect(TreeLinkNode *root) {
    TreeLinkNode *pre = root;
    TreeLinkNode *cur = NULL;
    if (pre == NULL) return;
    while (pre->left != NULL) {
        cur = pre;
        while (cur != NULL) {
            cur->left->next = cur->right;
            if (cur->next != NULL) cur->right->next = cur->next->left;
            cur = cur->next;
        }
        pre = pre->left;
    }
}

//116. Populating Next Right Pointers in Each Node II
void connect2(TreeLinkNode *root) {
    TreeLinkNode *pre = NULL, *head = NULL;
    TreeLinkNode *cur = root;
    if (cur == NULL) return;
    while (cur != NULL) {
        while (cur != NULL) {
            if (cur->left != NULL) {
                if (pre != NULL) {
                    pre->next = cur->left;
                } else {
                    head = cur->left;
                }
                pre = cur->left;
            }
            if (cur->right != NULL) {
                if (pre != NULL) {
                    pre->next = cur->right;
                } else {
                    head = cur->right;
                }
                pre = cur->right;
            }
            cur = cur->next;
        }
        cur = head;
        head = NULL;
        pre = NULL;
    }
}

//120. Triangle
int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty()) return 0;
    int minNum = INT_MAX;
    for (int i = 0; i < triangle.size(); i++) {
        for (int j = 0; j < triangle[i].size(); j++) {
            if (i > 0) {
                if (j == 0) {
                    triangle[i][j] += triangle[i - 1][j];
                } else if (j == triangle[i].size() - 1) {
                    triangle[i][j] += triangle[i - 1][j - 1];
                } else {
                    triangle[i][j] += min(triangle[i - 1][j], triangle[i - 1][j - 1]);
                }
            }
            if (i == triangle.size() - 1) {
                minNum = min(minNum, triangle[i][j]);
            }
        }
    }
    return minNum;
}

//123. Best Time to Buy and Sell Stock III
int maxProfit(vector<int>& prices) {
    int hold1 = INT_MIN, hold2 = INT_MIN;
    int release1 = 0, release2 = 0;
    for (int price : prices) {
        release2 = max(release2, hold2 + price);
        hold2 = max(hold2, release1 - price);
        release1 = max(release1, hold1 + price);
        hold1 = max(hold1, -price);
    }
    return release2;
}

//124. Binary Tree Maximum Path Sum
int maxPathSumHelp(TreeNode* root, int &maxSum) {
    if (root == NULL) return 0;
    int l = max(0, maxPathSumHelp(root->left, maxSum));
    int r = max(0, maxPathSumHelp(root->right, maxSum));
    maxSum = max(maxSum, l + r + root->val);
    return root->val + max(l, r);
}
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelp(root, maxSum);
    return maxSum;
}

//128. Longest Consecutive Sequence
int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> m;
    int maxLen = 0;
    for (int num : nums) {
        if (m[num]) continue;
        m[num] = m[num + 1] + m[num - 1] + 1;
        m[num + m[num + 1]] = m[num];
        m[num - m[num - 1]] = m[num];
        maxLen = max(maxLen, m[num]);
    }
    return maxLen;
}

//129. Sum Root to Leaf Numbers
void sumNumbersHelp(TreeNode* root, int &sum, int num, int c) {
    if (root == NULL) return;
    num = root->val + num * c;
    if (root->left == NULL && root->right == NULL) sum += num;
    sumNumbersHelp(root->left, sum, num, 10);
    sumNumbersHelp(root->right, sum, num, 10);
}
int sumNumbers(TreeNode* root) {
    int sum = 0;
    sumNumbersHelp(root, sum, 0, 1);
    return sum;
}

//130. Surrounded Regions
bool isCoordinateValid(Point a, int m, int n) {
    if (a.x < 0 || a.x >= m || a.y < 0 || a.y >= n) {
        return false;
    } else return true;
}
void solveBFS(vector<vector<bool>> &visited, vector<vector<bool>> &surrounded, vector<vector<char>> board, int i, int j, int m, int n) {
    vector<vector<bool>> tmp = surrounded;
    bool flag = false;
    visited[i][j] = true;
    tmp[i][j] = false;
    queue<Point> q;
    q.push(Point(i, j));
    while (!q.empty()) {
        Point dot = q.front();
        if (dot.x == 0 || dot.x == m - 1 || dot.y == 0 || dot.y == n - 1) {
            flag = true;
        }
        if (isCoordinateValid(Point(dot.x + 1, dot.y), m, n) && !visited[dot.x + 1][dot.y] && board[dot.x + 1][dot.y] == 'O') {
            tmp[dot.x + 1][dot.y] = false;
            q.push(Point(dot.x + 1, dot.y));
            visited[dot.x + 1][dot.y] = true;
        }
        if (isCoordinateValid(Point(dot.x, dot.y + 1), m, n) && !visited[dot.x][dot.y + 1] && board[dot.x][dot.y + 1] == 'O') {
            tmp[dot.x][dot.y + 1] = false;
            q.push(Point(dot.x, dot.y + 1));
            visited[dot.x][dot.y + 1] = true;
        }
        if (isCoordinateValid(Point(dot.x - 1, dot.y), m, n) && !visited[dot.x - 1][dot.y] && board[dot.x - 1][dot.y] == 'O') {
            tmp[dot.x - 1][dot.y] = false;
            q.push(Point(dot.x - 1, dot.y));
            visited[dot.x - 1][dot.y] = true;
        }
        if (isCoordinateValid(Point(dot.x, dot.y - 1), m, n) && !visited[dot.x][dot.y - 1] && board[dot.x][dot.y - 1] == 'O') {
            tmp[dot.x][dot.y - 1] = false;
            q.push(Point(dot.x, dot.y - 1));
            visited[dot.x][dot.y - 1] = true;
        }
        q.pop();
    }
    if (flag) {
        surrounded = tmp;
    }
}
void solve(vector<vector<char>>& board) {
    if (board.empty()) return;
    int m = (int)board.size();
    int n = (int)board[0].size();
    vector<vector<bool>> surrounded(m, vector<bool> (n, true));
    vector<vector<bool>> visited(m, vector<bool> (n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') {
                if (!visited[i][j]) {
                    solveBFS(visited, surrounded, board, i, j, m, n);
                }
                if (surrounded[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
}

//131. Palindrome Partitioning
bool isPalindrome(string s, int begin, int end) {
    while (begin < end) {
        if (s[begin] != s[end]) {
            return false;
        }
        begin++;
        end--;
    }
    return true;
}
void partitionHelp(vector<vector<string>> &ans, vector<string> &res, int index, string s) {
    if (index == s.length()) {
        ans.push_back(res);
    }
    for (int i = 0; i < s.length() - index; i++) {
        if (isPalindrome(s, index, index + i)) {
            res.push_back(s.substr(index, i + 1));
            partitionHelp(ans, res, index + i + 1, s);
            res.pop_back();
        }
    }
}
vector<vector<string>> partition(string s) {
    vector<vector<string>> ans;
    vector<string> res;
    if (s.empty()) return ans;
    partitionHelp(ans, res, 0, s);
    return ans;
}

//132. Palindrome Partitioning II
int minCut(string s) {
    int n = (int)s.length();
    vector<int> cuts(n + 1);
    for (int i = 0; i <= n; i++) cuts[i] = i - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; j++) {
            if (cuts[i - j] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j] + 1;
            }
        }
        for (int j = 1; i - j + 1 >= 0 && i + j < n && s[i - j + 1] == s[i + j]; j++){
            if (cuts[i - j + 1] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j + 1] + 1;
            }
        }
    }
    return cuts[n];
}

//133. Clone Graph
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == NULL) return NULL;
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> dict;
    UndirectedGraphNode* copyNode = new UndirectedGraphNode(node->label);
    dict[node] = copyNode;
    queue<UndirectedGraphNode*> q;
    q.push(node);
    while (!q.empty()) {
        UndirectedGraphNode* cur = q.front();
        for (UndirectedGraphNode* neighbor : cur->neighbors) {
            if (dict.find(neighbor) == dict.end()) {
                UndirectedGraphNode* tmp = new UndirectedGraphNode(neighbor->label);
                dict[neighbor] = tmp;
                q.push(neighbor);
            }
            dict[cur]->neighbors.push_back(dict[neighbor]);
        }
        q.pop();
    }
    return copyNode;
}

//134. Gas Station
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, restGas = 0, start = 0;
    for (int i = 0; i < gas.size(); i++) {
        restGas += gas[i] - cost[i];
        total += gas[i] - cost[i];
        if (restGas < 0) {
            restGas = 0;
            start = i + 1;
        }
    }
    return total < 0 ? -1 : start;
}

//135. Candy
int candy(vector<int>& ratings) {
    int len = (int)ratings.size();
    if (len <= 1) return len;
    vector<int> nums(len, 1);
    for (int i = 1; i < len; i++) {
        if (ratings[i] > ratings[i - 1]) {
            nums[i] = nums[i - 1] + 1;
        }
    }
    int ans = nums[len - 1];
    for (int i = len - 1; i > 0; i--) {
        if (ratings[i - 1] > ratings[i]) {
            nums[i - 1] = max(nums[i] + 1, nums[i - 1]);
        }
        ans += nums[i - 1];
    }
    return ans;
}

//138. Copy List with Random Pointer
RandomListNode *copyRandomList(RandomListNode *head) {
    if (head == NULL) return NULL;
    RandomListNode* copyHead = new RandomListNode(head->label);
    unordered_map<RandomListNode*, RandomListNode*> dict;
    dict[head] = copyHead;
    RandomListNode *p = head, *q = copyHead;
    while (p->next != NULL) {
        if (dict.find(p->next) == dict.end()) {
            q->next = new RandomListNode(p->next->label);
            dict[p->next] = q->next;
        } else {
            q->next = dict[p->next];
        }
        if (p->random != NULL) {
            if (dict.find(p->random) == dict.end()) {
                q->random = new RandomListNode(p->random->label);
                dict[p->random] = q->random;
            } else {
                q->random = dict[p->random];
            }
        }
        p = p->next;
        q = q->next;
    }
    if (p->random != NULL) {
        q->random = dict[p->random];
    }
    return copyHead;
}

//139. Word Break
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet;
    int n = (int)s.size();
    for (int i = 0; i < wordDict.size(); i++) {
        wordSet.insert(wordDict[i]);
    }
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 0; j--) {
            if (dp[j]) {
                string word = s.substr(j, i - j);
                if (wordSet.find(word) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    return dp[n];
}

//140. Word Break II
vector<string> combineWord(string word, vector<string> ans) {
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = ans[i] + " " + word;
    }
    return ans;
}
vector<string> wordBreakHelp(string s, unordered_set<string> wordDict, unordered_map<string, vector<string>> &mp) {
    if (mp.find(s) != mp.end()) {
        return mp[s];
    }
    vector<string> ans;
    if (wordDict.find(s) != wordDict.end()) {
        ans.push_back(s);
    }
    for (int i = 1; i < s.size(); i++) {
        string word = s.substr(i);
        if (wordDict.find(word) != wordDict.end()) {
            string rem = s.substr(0, i);
            vector<string> tmp = combineWord(word, wordBreakHelp(rem, wordDict, mp));
            ans.insert(ans.end(), tmp.begin(), tmp.end());
        }
    }
    mp[s] = ans;
    return ans;
}
vector<string> wordBreakII(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet;
    unordered_map<string, vector<string>> mp;
    vector<string> ans;
    for (int i = 0; i < wordDict.size(); i++) {
        wordSet.insert(wordDict[i]);
    }
    ans = wordBreakHelp(s, wordSet, mp);
    return ans;
}

//142. Linked List Cycle II
ListNode *detectCycle(ListNode *head) {
    ListNode *fast = head, *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            ListNode *node = head;
            while (node != slow) {
                slow = slow->next;
                node = node->next;
            }
            return node;
        }
    }
    return NULL;
}

//143. Reorder List
void reorderList(ListNode* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) return;
    ListNode *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode *cur = slow->next;
    slow->next = NULL;
    ListNode *pre = NULL;
    ListNode *tmp = NULL;
    while (cur != NULL) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    cur = head;
    tmp = cur->next;
    while (pre != NULL) {
        cur->next = pre;
        cur = pre->next;
        pre->next = tmp;
        pre = cur;
        cur = tmp;
        tmp = tmp->next;
    }
}

//144. Binary Tree Preorder Traversal
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (!s.empty() || p != NULL) {
        while (p != NULL) {
            ans.push_back(p->val);
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
    return ans;
}

//145. Binary Tree Postorder Traversal
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> s;
    TreeNode *p = root;
    TreeNode *lastVisit = NULL;
    while (p != NULL) {
        s.push(p);
        p = p->left;
    }
    while (!s.empty()) {
        p = s.top();
        s.pop();
        if (p->right == NULL || p->right == lastVisit) {
            ans.push_back(p->val);
            lastVisit = p;
        } else {
            s.push(p);
            p = p->right;
            while (p != NULL) {
                s.push(p);
                p = p->left;
            }
        }
    }
    return ans;
}

//146. LRU Cache
class LRUCache {
public:
    LRUCache(int capacity) : size(capacity) {}
    
    int get(int key) {
        auto ite = cache.find(key);
        if (ite == cache.end()) return -1;
        lastUsed.splice(lastUsed.begin(), lastUsed, ite->second);
        return ite->second->second;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            auto ite = cache.find(key);
            ite->second->second = value;
            lastUsed.splice(lastUsed.begin(), lastUsed, ite->second);
            return;
        }
        if (cache.size() == size) {
            cache.erase(lastUsed.back().first);
            lastUsed.pop_back();
        }
        lastUsed.emplace_front(key, value);
        cache[key] = lastUsed.begin();
    }
private:
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    list<pair<int, int>> lastUsed;
    size_t size;
};

//147. Insertion Sort List
ListNode* insertionSortList(ListNode* head) {
    ListNode *preHead = new ListNode(0);
    preHead->next = head;
    ListNode *cur = head;
    if (cur == NULL) return NULL;
    ListNode *p = cur->next;
    while (p != NULL) {
        ListNode *pre = preHead;
        while (pre->next != p && pre->next->val <= p->val) {
            pre = pre->next;
        }
        if (pre->next != p) {
            cur->next = p->next;
            p->next = pre->next;
            pre->next = p;
        } else cur = p;
        p = cur->next;
    }
    return preHead->next;
}

//148. Sort List
ListNode* split(ListNode* head, int n) {
    for (int i = 1; head != NULL && i < n; i++) head = head->next;
    if (head == NULL) return NULL;
    ListNode *nextHead = head->next;
    head->next = NULL;
    return nextHead;
}
ListNode* merge(ListNode* l1, ListNode* l2, ListNode* head) {
    ListNode *cur = head;
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 == NULL ? l2 : l1;
    while (cur->next != NULL) cur = cur->next;
    return cur;
}
ListNode* sortList(ListNode* head) {
    int length = 0;
    ListNode* preHead = new ListNode(0);
    preHead->next = head;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    ListNode *left = NULL, *right = NULL, *cur = NULL, *tail = NULL;
    for (int step = 1; step < length; step <<= 1) {
        tail = preHead;
        cur = preHead->next;
        while (cur != NULL) {
            left = cur;
            right = split(left, step);
            cur = split(right, step);
            tail = merge(left, right, tail);
        }
    }
    return preHead->next;
}

//149. Max Points on a Line
struct hashfunc {
    size_t operator() (const pair<int,int>& l) const {
        return l.first ^ l.second;
    }
};
int maxPoints(vector<Point>& points) {
    int maxNum = 0;
    for (int i = 0; i < points.size(); i++) {
        int samePoint = 1;
        unordered_map<pair<int, int>, int, hashfunc> mp;
        for (int j = i + 1; j < points.size(); j++) {
            if (points[i].x == points[j].x && points[i].y == points[j].y) {
                samePoint++;
            } else if (points[i].x == points[j].x) {
                mp[make_pair(1, 0)]++;
            } else {
                int a = points[j].y - points[i].y;
                int b = points[j].x - points[i].x;
                int gcd = getGcd(a, b);
                a /= gcd;
                b /= gcd;
                mp[make_pair(a, b)]++;
            }
        }
        maxNum = max(maxNum, samePoint);
        for (auto it = mp.begin(); it != mp.end(); it++) {
            maxNum = max(maxNum, it->second + samePoint);
        }
    }
    return maxNum;
}

//150. Evaluate Reverse Polish Notation
int evalRPN(vector<string>& tokens) {
    stack<int> s;
    for (auto tmp : tokens) {
        int curNum = 0;
        if (isdigit(tmp.back())) {
            curNum = stoi(tmp);
        } else {
            int num1 = s.top();
            s.pop();
            int num2 = s.top();
            s.pop();
            if (tmp == "+") {
                curNum = num2 + num1;
            } else if (tmp == "-") {
                curNum = num2 - num1;
            } else if (tmp == "*") {
                curNum = num2 * num1;
            } else {
                curNum = num2 / num1;
            }
        }
        s.push(curNum);
    }
    return s.top();
}

//151. Reverse Words in a String
void reverseWords(string &s) {
    string ans = "";
    for (int i = (int)s.length(); i > 0; i--) {
        for (int j = i - 1; j < s.length(); j++) {
            if (s[j] == ' ') {
                if (i == s.length()) {
                    ans = ans + s.substr(j + 1, i - j - 1);
                } else {
                    ans = ans + " " + s.substr(j + 1, i - j - 1);
                }
            }
        }
    }
    s = ans;
}

//152. Maximum Product Subarray
int maxProduct(vector<int>& nums) {
    int maxP = INT_MIN;
    vector<int> dp(nums.size(), INT_MIN);
    vector<int> negativeDp(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++) {
        if (i == 0) {
            dp[i] = nums[i];
            negativeDp[i] = min(nums[i], 0);
            maxP = dp[i];
            continue;
        }
        if (nums[i] == 0) {
            dp[i] = negativeDp[i];
        } else if (nums[i] > 0) {
            dp[i] = max(nums[i], nums[i] * dp[i - 1]);
            negativeDp[i] = min(nums[i] * negativeDp[i - 1], 0);
        } else {
            dp[i] = max(nums[i], nums[i] * negativeDp[i - 1]);
            negativeDp[i] = min(nums[i], nums[i] * dp[i - 1]);
        }
        if (dp[i] > maxP) maxP = dp[i];
    }
    return maxP;
}

//153. Find Minimum in Rotated Sorted Array
int findMin(vector<int> &num) {
    int start = 0, end = (int)num.size() - 1;
    while (start < end) {
        if (num[start] < num[end]) return num[start];
        int mid = (start + end) / 2;
        if (num[start] < num[mid]) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return num[start];
}

//154. Find Minimum in Rotated Sorted Array II
int findMinII(vector<int> &num) {
    int start = 0, end = (int)num.size() - 1;
    while (start < end) {
        if (num[start] == num[end]) {
            end--;
            continue;
        }
        if (num[start] <= num[end]) return num[start];
        int mid = (start + end) / 2;
        if (num[start] <= num[mid]) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return num[start];
}

//162. Find Peak Element
int findPeakElement(vector<int>& nums) {
    if (nums.size() < 2) return 0;
    for (int i = 0; i < nums.size() - 1; i++)
        if (nums[i] > nums[i + 1]) return i;
    return (int)nums.size() - 1;
}

//164. Maximum Gap
int maximumGap(vector<int>& nums) {
    if (nums.size() < 2) return 0;
    sort(nums.begin(), nums.end());
    int maxNum = 0;
    for (int i = 1; i < nums.size(); i++)
        maxNum = max(maxNum, nums[i] - nums[i - 1]);
    return maxNum;
}

//165. Compare Version Numbers
int compareVersion(string version1, string version2) {
    int i = 0, j = 0;
    int m = (int)version1.length(), n = (int)version2.length();
    while (i < m && j < n) {
        int num1 = 1, num2 = 1;
        while (i + num1 < m && version1[i + num1] != '.') num1++;
        while (j + num2 < n && version2[j + num2] != '.') num2++;
        if (stoi(version1.substr(i, num1)) < stoi(version2.substr(j, num2))) return -1;
        if (stoi(version1.substr(i, num1)) > stoi(version2.substr(j, num2))) return 1;
        i += num1 + 1;
        j += num2 + 1;
    }
    while (i < m && (version1[i] == '0' || version1[i] == '.')) i++;
    while (j < n && (version2[j] == '0' || version2[j] == '.')) j++;
    if (i < m) return 1;
    if (j < n) return -1;
    return 0;
}

//166. Fraction to Recurring Decimal
string fractionToDecimal(long long numerator, long long denominator) {
    if (numerator == 0) return "0";
    string ans = "";
    if ((numerator ^ denominator) < 0) ans += "-";
    numerator = abs(numerator);
    denominator = abs(denominator);
    ans += to_string(numerator / denominator);
    long long res = numerator % denominator;
    if (res == 0) return ans;
    ans += ".";
    unordered_map<long long, int> mp;
    while (res) {
        if (mp[res] > 0) {
            ans.insert(mp[res], "(");
            ans += ")";
            return ans;
        }
        mp[res] = (int)ans.size();
        res *= 10;
        ans += to_string(res / denominator);
        res %= denominator;
    }
    return ans;
}

//173. Binary Search Tree Iterator
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        stack<TreeNode*> s;
        TreeNode *p = root;
        while (!s.empty() || p != NULL) {
            while (p != NULL) {
                s.push(p);
                p = p->left;
            }
            if (!s.empty()) {
                p = s.top();
                s.pop();
                q.push(p->val);
                p = p->right;
            }
        }
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !q.empty();
    }
    
    /** @return the next smallest number */
    int next() {
        int ans = q.front();
        q.pop();
        return ans;
    }
private:
    queue<int> q;
};

//174. Dungeon Game
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = (int)dungeon.size();
    int n = (int)dungeon[0].size();
    vector<int> dp(n + 1, INT_MAX);
    dp[n - 1] = 1;
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            dp[j] = min(dp[j], dp[j + 1]) - dungeon[i][j];
            dp[j] = max(1, dp[j]);
        }
    }
    return dp[0];
}

//179. Largest Number
bool largestNumberHelp (int a, int b) {
    string aStr = to_string(a);
    string bStr = to_string(b);
    return aStr + bStr > bStr + aStr;
}
string largestNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end(), largestNumberHelp);
    string ans = "";
    for (int i = 0; i < nums.size(); i++) {
        ans += to_string(nums[i]);
    }
    int j = 0;
    while (j < ans.size() - 1 && ans[j] == '0') j++;
    return ans.substr(j);
}

//187. Repeated DNA Sequences
vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ans;
    unordered_map<string, int> mp;
    for (int i = 0; i + 10 <= s.length(); i++) {
        string tmp = s.substr(i, 10);
        mp[tmp]++;
        if (mp[tmp] == 2) ans.push_back(tmp);
    }
    return ans;
}

//188. Best Time to Buy and Sell Stock IV
int quickSolve(vector<int> prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        profit += prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0;
    }
    return profit;
}
int maxProfit(int k, vector<int>& prices) {
    if (k == 0) return 0;
    if (k > prices.size() / 2) {
        return quickSolve(prices);
    }
    vector<int> release(k, 0);
    vector<int> hold(k, INT_MIN);
    for (auto price : prices) {
        for (int i = k - 1; i > 0; i--) {
            release[i] = max(release[i], hold[i] + price);
            hold[i] = max(hold[i], release[i - 1] - price);
        }
        release[0] = max(release[0], hold[0] + price);
        hold[0] = max(hold[0], -price);
    }
    return release[k - 1];
}

//189. Rotate Array
void rotate(vector<int>& nums, int k) {
    int n = (int)nums.size();
    k %= n;
    reverse(nums.begin(), nums.begin() + n - k) ;
    reverse(nums.begin() + n - k, nums.end());
    reverse(nums.begin(), nums.end());
}

//190. Reverse Bits
uint32_t reverseBits(uint32_t n) {
    uint32_t m = 0;
    for (int i = 0; i++ < 32; n >>= 1) {
        m <<= 1;
        m |= n & 1;
    }
    return m;
}

//191. Number of 1 Bits
int hammingWeight(uint32_t n) {
    int cnt = 0;
    while (n) {
        if (n & 1) cnt++;
        n >>= 1;
    }
    return cnt;
}

//198. House Robber
int rob(vector<int>& nums) {
    int maxMoney1 = 0, maxMoney2 = 0;
    for (int i = 0; i < nums.size(); i++) {
        int tmp = maxMoney1;
        maxMoney1 = max(maxMoney1, maxMoney2 + nums[i]);
        maxMoney2 = tmp;
    }
    return maxMoney1;
}

//199. Binary Tree Right Side View
vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    queue<TreeNode*> q;
    if (root != NULL) q.push(root);
    while (!q.empty()) {
        int n = (int)q.size();
        while (n) {
            n--;
            TreeNode *tmp = q.front();
            if (tmp->left != NULL) q.push(tmp->left);
            if (tmp->right != NULL) q.push(tmp->right);
            if (n == 0) {
                ans.push_back(tmp->val);
            }
            q.pop();
        }
    }
    return ans;
}

//200. Number of Islands
void numIsLandsHelp(vector<vector<bool>>& visited, vector<vector<char>>& grid, int i, int j, int m, int n) {
    if (i < 0 || j < 0 || i >= m || j >= n) return;
    if (grid[i][j] == '0') return;
    if (visited[i][j]) return;
    visited[i][j] = true;
    numIsLandsHelp(visited, grid, i + 1, j, m, n);
    numIsLandsHelp(visited, grid, i - 1, j, m, n);
    numIsLandsHelp(visited, grid, i, j + 1, m, n);
    numIsLandsHelp(visited, grid, i, j - 1, m, n);
}
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;
    int m = (int)grid.size();
    int n = (int)grid[0].size();
    int num = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j] && grid[i][j] == '1') {
                numIsLandsHelp(visited, grid, i, j, m, n);
                num++;
            }
        }
    }
    return num;
}

//201. Bitwise AND of Numbers Range
int rangeBitwiseAnd(int m, int n) {
    int pos = 0;
    while (m != n) {
        pos++;
        m >>= 1;
        n >>= 1;
    }
    return m << pos;
}

//202. Happy Number
bool isHappy(int n) {
    vector<int> squares = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
    unordered_map<int, int> mp;
    while (mp.find(n) == mp.end()) {
        if (n == 1) {
            return true;
        }
        mp[n]++;
        int sum = 0;
        while (n) {
            int tmp = n % 10;
            sum += squares[tmp];
            n /= 10;
        }
        n = sum;
    }
    return false;
}

//203. Remove Linked List Elements
ListNode* removeElements(ListNode* head, int val) {
    ListNode *preHead = new ListNode(0);
    preHead->next = head;
    ListNode *pre = preHead, *p = head;
    while (p != NULL) {
        while (p->val == val) {
            pre->next = p->next;
            p = p->next;
            if (p == NULL) break;
        }
        if (p == NULL) break;
        pre = p;
        p = p->next;
    }
    return preHead->next;
}

//204. Count Primes
int countPrimes(int n) {
    if (n < 2) return 0;
    vector<bool> isPrime(n + 1, true);
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i] == true) {
            count++;
            int p = i + i;
            while (p <= n) {
                isPrime[p] = false;
                p += i;
            }
        }
    }
    return count;
}

//205. Isomorphic Strings
bool isIsomorphic(string s, string t) {
    int n = (int)s.length();
    vector<int> m1(256, 0), m2(256, 0);
    for (int i = 0; i < n; ++i) {
        if (m1[s[i]] != m2[t[i]]) return false;
        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}

//206. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    ListNode *pre = NULL, *p = head;
    while (p != NULL) {
        ListNode *q = p->next;
        p->next = pre;
        pre = p;
        p = q;
    }
    return pre;
}

//207. Course Schedule
/* BFS Solution
vector<int> computeIndegree(vector<unordered_set<int>> graph, int num) {
    vector<int> indegree(num, 0);
    for (int i = 0; i < graph.size(); i++)
        for (int node : graph[i])
            indegree[node]++;
    return indegree;
}
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);
    for (int i = 0; i < prerequisites.size(); i++) {
        graph[prerequisites[i].second].insert(prerequisites[i].first);
    }
    vector<int> indegree = computeIndegree(graph, numCourses);
    for (int i = 0; i < numCourses; i++) {
        int j = 0;
        for (; j < numCourses; j++) {
            if (indegree[j] == 0) {
                break;
            }
        }
        if (j == numCourses) return false;
        indegree[j] = -1;
        for (int neighboor : graph[j])
            indegree[neighboor]--;
    }
    return true;
}
*/
//DFS Solution
bool canFinishHelp(vector<bool> &visited, vector<bool> &onpath, vector<unordered_set<int>> &graph, int course) {
    if (visited[course]) return false;
    onpath[course] = visited[course] = true;
    for (int neigh : graph[course])
        if (onpath[neigh] || canFinishHelp(visited, onpath, graph, neigh))
            return true;
    return onpath[course] = false;
}
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);
    for (auto pre : prerequisites)
        graph[pre.second].insert(pre.first);
    vector<bool> visited(numCourses, false), onpath(numCourses, false);
    for (int i = 0; i < numCourses; i++)
        if (!visited[i] && canFinishHelp(visited, onpath, graph, i))
            return false;
    return true;
}

//208. Implement Trie (Prefix Tree)
class TrieNode {
public:
    vector<TrieNode*> next;
    bool isWord;
    TrieNode () {
        next = vector<TrieNode*>(26);
        isWord = false;
    }
};
class Trie {
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                return false;
            }
            p = p->next[word[i] - 'a'];
        }
        return p->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (p->next[prefix[i] - 'a'] == NULL) {
                return false;
            }
            p = p->next[prefix[i] - 'a'];
        }
        return true;
    }
};

//209. Minimum Size Subarray Sum
int minSubArrayLen(int s, vector<int>& nums) {
    int i = 0, j = 0, minSub = INT_MAX;
    int sum = 0;
    for (; i < nums.size(); i++) {
        sum += nums[i];
        if (sum >= s) minSub = min(minSub, i - j + 1);
        while (sum >= s) {
            sum -= nums[j];
            j++;
            if (sum >= s) minSub = min(minSub, i - j + 1);
        }
    }
    return minSub == INT_MAX ? 0 : minSub;
}

//210. Course Schedule II
vector<int> countIndegree(vector<unordered_set<int>>& graph, int numCourses) {
    vector<int> indegree(numCourses, 0);
    for (int i = 0; i < graph.size(); i++)
        for (int neigh : graph[i])
            indegree[neigh]++;
    return indegree;
}
vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);
    for (auto pre : prerequisites)
        graph[pre.second].insert(pre.first);
    vector<int> indegree = countIndegree(graph, numCourses);
    vector<int> order;
    for (int i = 0; i < numCourses; i++) {
        vector<int> tmp;
        int j = 0;
        for (; j < numCourses; j++)
            if (indegree[j] == 0) break;
        if (j == numCourses) return tmp;
        order.push_back(j);
        indegree[j] = -1;
        for (auto neigh : graph[j])
            indegree[neigh]--;
    }
    return order;
}

//211. Add and Search Word - Data structure design
class WordDictionary {
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isWord = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return isMatch(root, word);
    }
    //212. Word Search II
    void checkWord(vector<vector<char>>& board, vector<string>& res, string curStr, TrieNode *root, int m, int n, int i, int j) {
        if (board[i][j] == '.') return;
        if (root->next[board[i][j] - 'a'] == NULL) return;
        char tmp = board[i][j];
        curStr += tmp;
        board[i][j] = '.';
        if (root->next[tmp - 'a']->isWord) {
            res.push_back(curStr);
            root->next[tmp - 'a']->isWord = false;
        }
        if (i + 1 < m) checkWord(board, res, curStr, root->next[tmp - 'a'], m, n, i + 1, j);
        if (i > 0) checkWord(board, res, curStr, root->next[tmp - 'a'], m, n, i - 1, j);
        if (j + 1 < n) checkWord(board, res, curStr, root->next[tmp - 'a'], m, n, i, j + 1);
        if (j > 0) checkWord(board, res, curStr, root->next[tmp - 'a'], m, n, i, j - 1);
        board[i][j] = tmp;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        if (words.empty() || board.empty()) return ans;
        for (auto word : words) {
            addWord(word);
        }
        int m = (int)board.size();
        int n = (int)board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                checkWord(board, ans, "", root, m, n, i, j);
            }
        }
        return ans;
    }
private:
    bool isMatch(TrieNode* root, string word) {
        if (word.empty()) return root->isWord;
        TrieNode *p = root;
        if (word[0] == '.') {
            for (int i = 0; i < 26; i++)
                if (p->next[i] != NULL && isMatch(p->next[i], word.substr(1)))
                    return true;
        } else {
            if (p->next[word[0] - 'a'] == NULL) {
                return false;
            } else return isMatch(p->next[word[0] - 'a'], word.substr(1));
        }
        return false;
    }
};

//213. House Robber II
int robHelp(vector<int>& nums, int l, int r) {
    int maxMoney1 = 0, maxMoney2 = 0;
    for (int i = l; i < r; i++) {
        int tmp = maxMoney1;
        maxMoney1 = max(maxMoney1, maxMoney2 + nums[i]);
        maxMoney2 = tmp;
    }
    return maxMoney1;
}
int robII(vector<int>& nums) {
    int n = (int)nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return max(robHelp(nums, 0, n - 1), robHelp(nums, 1, n));
}

//214. Shortest Palindrome (KMP)
string shortestPalindrome(string s) {
    string rs = s;
    reverse(rs.begin(), rs.end());
    string tmp = s + "#" + rs;
    vector<int> next(tmp.size(), 0);
    for (int i = 1; i < tmp.size(); i++) {
        int j = next[i - 1];
        while (j > 0 && tmp[i] != tmp[j]) {
            j = next[j - 1];
        }
        if (tmp[i] == tmp[j]) j++;
        next[i] = j;
    }
    return rs.substr(0, s.size() - next[tmp.size() - 1]) + s;
}

//216. Combination Sum III
void combinationSum3Help(vector<vector<int>>& ans, vector<int>& res, int k, int target, int num) {
    if (k < 0) return;
    if (k == 0 && target == 0) {
        ans.push_back(res);
    }
    for (int i = num; i < 10; i++) {
        res.push_back(i);
        combinationSum3Help(ans, res, k - 1, target - i, i + 1);
        res.pop_back();
    }
}
vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> ans;
    vector<int> res;
    combinationSum3Help(ans, res, k, n, 1);
    return ans;
}

//220. Contains Duplicate III
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long long> dict;
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) dict.erase(nums[i - k - 1]);
        auto pos = dict.lower_bound((long long)nums[i] - t);
        if (pos != dict.end() && *pos - nums[i] <= t) return true;
        dict.insert(nums[i]);
    }
    return false;
}

//221. Maximal Square
int maximalSquare(vector<vector<char>>& matrix) {
    int maxSquare = 0;
    if (matrix.empty()) return 0;
    int m = (int)matrix.size();
    int n = (int)matrix[0].size();
    vector<int> left(n, 0), right(n, n), height(n, 0);
    for (int i = 0; i < m; i++) {
        int cur_left = 0, cur_right = n;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1') {
                height[j]++;
                left[j] = max(left[j], cur_left);
            }
            else {
                height[j] = 0;
                cur_left = j + 1;
                left[j] = 0;
            }
        }
        for (int j = n - 1; j >= 0; j--) {
            if (matrix[i][j] == '1') right[j] = min(right[j], cur_right);
            else {
                right[j] = n;
                cur_right = j;
            }
        }
        for (int j = 0; j < n; j++) {
            int len = min(right[j] - left[j], height[j]);
            maxSquare = max(maxSquare, len * len);
        }
    }
    return maxSquare;
}

//222. Count Complete Tree Nodes 递归
int countNodes(TreeNode* root) {
    int ld = 0, rd = 0;
    TreeNode *p = root, *q = root;
    while (p != NULL) {
        p = p->left;
        ld++;
    }
    while (q != NULL) {
        q = q->right;
        rd++;
    }
    if (ld == rd) return pow(2, ld) - 1;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

//223. Rectangle Area
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int left = max(A, E), right = max(min(C, G), left), bottom = max(B, F), top = max(min(D, H), bottom);
    return (D - B)*(C - A) + (G - E)*(H - F) - (right - left)*(top - bottom);
}

//224. Basic Calculator
int calculate(string s) {
    stack<int> nums, opt;
    int num = 0, ans = 0, sign = 1;
    for (auto c : s) {
        if (isdigit(c)) num = num * 10 + c - '0';
        else {
            ans += num * sign;
            num = 0;
            if (c == '+') sign = 1;
            if (c == '-') sign = -1;
            if (c == '(') {
                nums.push(ans);
                opt.push(sign);
                ans = 0;
                sign = 1;
            }
            if (c == ')') {
                ans = nums.top() + opt.top() * ans;
                nums.pop();
                opt.pop();
            }
        }
        ans += num * sign;
    }
    return ans;
}

//226. Invert Binary Tree
void invertTreeHelp(TreeNode* root) {
    if (root == NULL) return;
    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    invertTreeHelp(root->left);
    invertTreeHelp(root->right);
}
TreeNode* invertTree(TreeNode* root) {
    invertTreeHelp(root);
    return root;
}

//227. Basic Calculator II
int calculateII(string s) {
    stack<int> nums, opt;
    int ans = 0, num = 0, cal = 0, sign = 1;
    for (auto c : s) {
        if (isdigit(c)) {
            num = num * 10 + c - '0';
        } else {
            if (c == ' ') continue;
            if (cal == 0) {
                nums.push(num);
                num = 0;
            } else {
                if (cal == 1) {
                    num = nums.top() * num;
                    nums.pop();
                    nums.push(num);
                } else {
                    num = nums.top() / num;
                    nums.pop();
                    nums.push(num);
                }
                num = 0;
            }
            if (c == '+') {
                sign = 1;
                cal = 0;
                opt.push(sign);
            }
            if (c == '-') {
                sign = -1;
                cal = 0;
                opt.push(sign);
            }
            if (c == '*') cal = 1;
            if (c == '/') cal = 2;
        }
    }
    if (cal == 1) {
        num = nums.top() * num;
        nums.pop();
    }
    if (cal == 2) {
        num = nums.top() / num;
        nums.pop();
    }
    while (!opt.empty()) {
        ans += num * opt.top();
        num = nums.top();
        nums.pop();
        opt.pop();
    }
    ans += num;
    return ans;
}

//228. Summary Ranges
vector<string> summaryRanges(vector<int>& nums) {
    vector<string> ans;
    if (nums.empty()) return ans;
    int start = 0, end = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[end] + 1) {
            end++;
        } else {
            if (start == end) {
                ans.push_back(to_string(nums[start]));
            } else {
                ans.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
            }
            start = end = i;
        }
    }
    if (start == end) {
        ans.push_back(to_string(nums[start]));
    } else {
        ans.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
    }
    return ans;
}

//229. Majority Element II
vector<int> majorityElementII(vector<int>& nums) {
    if (nums.empty()) return nums;
    vector<int> ans;
    int cnt1 = 0, cnt2 = 0, candidate1 = 0, candidate2 = 0;
    for (int n : nums) {
        if (n == candidate1) cnt1++;
        else if (n == candidate2) cnt2++;
        else if (cnt1 == 0) {
            candidate1 = n;
            cnt1 = 1;
        } else if (cnt2 == 0) {
            candidate2 = n;
            cnt2 = 1;
        }
        else {
            cnt1--;
            cnt2--;
        }
    }
    cnt1 = 0;
    cnt2 = 0;
    for (int n : nums) {
        if (n == candidate1) cnt1++;
        if (n == candidate2) cnt2++;
    }
    if (cnt1 > nums.size() / 3) {
        ans.push_back(candidate1);
    }
    if (candidate2 != candidate1 && cnt2 > nums.size() / 3) {
        ans.push_back(candidate2);
    }
    return ans;
}

//230. Kth Smallest Element in a BST
int kthSmallest(TreeNode* root, int k) {
    TreeNode *p = root;
    stack<TreeNode*> s;
    while (!s.empty() || p != NULL) {
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            s.pop();
            k--;
            if (k == 0) return p->val;
            p = p->right;
        }
    }
    return 0;
}

//233. Number of Digit One
int countDigitOne(int n) {
    int ones = 0;
    for (long long m = 1; m <= n; m *= 10)
        ones += (n / m + 8) / 10 * m + (n / m % 10 == 1) * (n % m + 1);
    return ones;
}

//234. Palindrome Linked List
bool isPalindrome(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *p = NULL;
    if (fast == NULL) {
        p = reverseList(slow);
    } else p = reverseList(slow->next);
    while (head != slow) {
        if (head->val != p->val) return false;
        head = head->next;
        p = p->next;
    }
    return true;
}

//235. Lowest Common Ancestor of a Binary Search Tree 最小公共祖先
TreeNode* lowestCommonAncestorOfBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) return NULL;
    if (p->val > q->val) {
        TreeNode *tmp = q;
        q = p;
        p = tmp;
    }
    if (root->val >= p->val && root->val <= q->val) return root;
    if (root->val < p->val) return lowestCommonAncestorOfBST(root->right, p, q);
    else return lowestCommonAncestorOfBST(root->left, p, q);
}

//236. Lowest Common Ancestor of a Binary Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL || root == p || root == q) return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left != NULL && right != NULL) return root;
    else return left == NULL ? right : left;
}

//238. Product of Array Except Self
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> ans(nums.size(), 1);
    for (int i = 1; i < nums.size(); i++) {
        ans[i] = ans[i - 1] * nums[i - 1];
    }
    int tmp = 1;
    for (int i = (int)nums.size() - 1; i > 0; i--) {
        tmp *= nums[i];
        ans[i - 1] *= tmp;
    }
    return ans;
}

//239. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    if (nums.empty()) return ans;
    int maxPos = 0;
    for (int i = 0; i < k; i++) if (nums[i] >= nums[maxPos]) maxPos = i;
    ans.push_back(nums[maxPos]);
    for (int i = k; i < nums.size(); i++) {
        if (nums[i] >= nums[maxPos]) maxPos = i;
        if (i - k == maxPos) {
            maxPos++;
            for (int j = maxPos; j <= i; j++)
                if (nums[j] >= nums[maxPos]) maxPos = j;
        }
        ans.push_back(nums[maxPos]);
    }
    return ans;
}

//240. Search a 2D Matrix II
bool searchMatrixII(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int m = (int)matrix.size();
    int n = (int)matrix[0].size();
    int i = 0, j = n - 1;
    while (i < m && j >= 0) {
        if (matrix[i][j] == target) return true;
        else if (matrix[i][j] > target) j--;
        else i++;
    }
    return false;
}

//241. Different Ways to Add Parentheses
vector<int> diffWaysToCompute(string input) {
    vector<int> ans;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
            vector<int> res1 = diffWaysToCompute(input.substr(0, i));
            vector<int> res2 = diffWaysToCompute(input.substr(i + 1));
            for (int n1 : res1) {
                for (int n2 : res2) {
                    if (input[i] == '+') {
                        ans.push_back(n1 + n2);
                    } else if (input[i] == '-') {
                        ans.push_back(n1 - n2);
                    } else {
                        ans.push_back(n1 * n2);
                    }
                }
            }
        }
    }
    if (ans.empty()) {
        ans.push_back(atoi(input.c_str()));
    }
    return ans;
}

//242. Valid Anagram
bool isAnagram(string s, string t) {
    vector<int> dict(256, 0);
    if (s.size() != t.size()) return false;
    for (auto c : s) dict[c]++;
    for (auto c : t) {
        dict[c]--;
        if (dict[c] < 0) return false;
    }
    return true;
}

//257. Binary Tree Paths
void binaryTreePathsHelp(vector<string>& ans, string str, TreeNode* root) {
    if (root == NULL) return;
    str += "->" + to_string(root->val);
    if (root->left == NULL && root->right == NULL) ans.push_back(str);
    if (root->left != NULL) binaryTreePathsHelp(ans, str, root->left);
    if (root->right != NULL) binaryTreePathsHelp(ans, str, root->right);
}
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    if (root == NULL) return ans;
    string str = to_string(root->val);
    if (root->left == NULL && root->right == NULL) ans.push_back(str);
    if (root->left != NULL) binaryTreePathsHelp(ans, str, root->left);
    if (root->right != NULL) binaryTreePathsHelp(ans, str, root->right);
    return ans;
}

//258. Add Digits
int addDigits(int num) {
    while (num / 10 != 0) {
        int tmp = 0;
        while (num) {
            tmp += num % 10;
            num /= 10;
        }
        num = tmp;
    }
    return num;
}

//260. Single Number III
vector<int> singleNumber(vector<int>& nums) {
    if (nums.size() < 2) return nums;
    vector<int> ans;
    int x = 0;
    for (int n : nums) x ^= n;
    int n1 = 0, n2 = 0;
    x &= -x;
    for (int n : nums) {
        if (x ^ n) {
            n1 ^= n;
        } else n2 ^= n;
    }
    if (n1 != n2) {
        ans.push_back(n1);
        ans.push_back(n2);
    }
    return ans;
}

//263. Ugly Number
bool isUgly(int num) {
    if (num == 0) return false;
    while (num % 2 == 0) num /= 2;
    while (num % 3 == 0) num /= 3;
    while (num % 5 == 0) num /= 5;
    if (num < 7) return true;
    else return false;
}

//264. Ugly Number II
int nthUglyNumber(int n) {
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    vector<int> ans(n, 0);
    ans[0] = 1;
    for (int i = 1; i < n; i++) {
        ans[i] = min(ans[cnt1] * 2, min(ans[cnt2] * 3, ans[cnt3] * 5));
        if (ans[i] == ans[cnt1] * 2) cnt1++;
        if (ans[i] == ans[cnt2] * 3) cnt2++;
        if (ans[i] == ans[cnt3] * 5) cnt3++;
    }
    return ans[n - 1];
}

//268. Missing Number
int missingNumber(vector<int>& nums) {
    int n = (int)nums.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        while (nums[i] != i && nums[i] < n) {
            swap(nums[i], nums[nums[i]]);
        }
        if (nums[i] == n) ans = i;
    }
    return ans;
}

//274. H-Index
int hIndex(vector<int>& citations) {
    sort(citations.begin(), citations.end());
    int h = 0;
    for (int i = (int)citations.size() - 1; i >= 0; i--) {
        h++;
        if (h > citations[i]) return h - 1;
    }
    return h;
}

//279. Perfect Squares
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i == j * j) dp[i] = 1;
            else dp[i] = min(dp[i], dp[j * j] + dp[i - j * j]);
        }
    }
    return dp[n];
}

//283. Move Zeroes
void moveZeroes(vector<int>& nums) {
    int pos = 0;
    while (pos < nums.size() && nums[pos] != 0) pos++;
    for (int i = pos + 1; i < nums.size(); i++)
        if (nums[i] != 0)
            nums[pos++] = nums[i];
    while (pos < nums.size()) nums[pos++] = 0;
}

//287. Find the Duplicate Number
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[nums[0]];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    fast = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return fast;
}

//289. Game of Life
void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;
    int m = (int)board.size();
    int n = (int)board[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int k = max(i - 1, 0); k < min(i + 2, m); k++) {
                for (int l = max(j - 1, 0); l < min(j + 2, n); l++) {
                    if (board[k][l] & 1) {
                        cnt++;
                    }
                }
            }
            cnt -= board[i][j];
            if (board[i][j] == 1 && (cnt == 3 || cnt == 2)) board[i][j] = 3;
            if (board[i][j] == 0 && cnt == 3) board[i][j] = 2;
        }
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            board[i][j] >>= 1;
}

//290. Word Pattern
bool wordPattern(string pattern, string str) {
    unordered_map<char, string> dict;
    
    return true;
}

//kmp算法
vector<int> computerPrefix(string str) {
    vector<int> next(str.size(), 0);
    for (int i = 1; i < str.size(); i++) {
        int j = next[i - 1];
        while (j > 0 && str[j] != str[i]) j = next[j - 1];
        if (str[j] == str[i]) j++;
        next[i] = j;
    }
    return next;
}

int kmp(string str, string p, vector<int>& next) {
    int j = 0;
    for (int i = 0; i < str.size(); i++) {
        while (j > 0 && str[i] != p[j]) j = next[j - 1];
        if (str[i] == p[j]) j++;
        if (j == p.size()) return i + 1;
    }
    return -1;
}

//295. Find Median from Data Stream 中位数
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int> small, large;
    
    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (large.size() > small.size()) {
            small.push(-large.top());
            large.pop();
        }
    }
        
    double findMedian() {
        if (small.size() > large.size()) {
            return small.top();
        }
        double ans = (double)(small.top() - large.top()) / 2.0;
        return ans;
    }
};

int main(int argc, const char * argv[]) {
    return 0;
}
