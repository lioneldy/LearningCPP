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

//最大公约数
int gcd(int a, int b) {
    return (a % b == 0) ? b : gcd(b, a % b);
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

//17. Letter Combinations of a Phone Number
vector<string> letterCombinations(string digits) {
    string nums[]={"0","1","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
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

//43. Jump Game2
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

//79. Word Search
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

int main(int argc, const char * argv[]) {
    minDistance("a", "b");
    return 0;
}
