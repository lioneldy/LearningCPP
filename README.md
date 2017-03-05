# LeetcodePractice

用C++刷Leetcode题

## 2. Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Input:** (2 -> 4 -> 3) + (5 -> 6 -> 4)

**Output:** 7 -> 0 -> 8

#### 思路：

题目中明确了一点，存储在链表中的数是倒序的，比如例子中的2 -> 4 -> 3表示的数就应该是342，这无疑是降低了难度的，我们只需要从头到尾遍历一遍链表即可，算法就是小学时候的笔算加法，从低位往高位依次加，然后注意一下进位即可。

## 3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given `"abcabcbb"`, the answer is `"abc"`, which the length is 3.

Given `"bbbbb"`, the answer is `"b"`, with the length of 1.

Given `"pwwkew"`, the answer is `"wke"`, with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

#### 思路：

用`m`表示当前子串第一个字符的前一个位置，`i`为当前扫描位置，关键的问题是如何判断`s[i]`是否在当前子串重复过，这里我利用的是数组来存储<字符ASCII码，下标（最近出现位置）>，这里只需要一个256大小的数组即可，初始化为`vector<int> dictMap(256,-1)`。

我们从开始向后扫描，如果字符`s[i]`在当前字符串没有出现过，那么此时最大不重复字符串长度`maxLength = max(maxLength, i - m)`（`m`的初始值为`-1`），并令`dictMap[s[i]] = i`。

因为每一个字符只能出现一次，如果出现重复，即`s[i]`处出现重复的话，意味着`dictMap[s[i]] > m`，此时我们需要指定新的不重复字符串的起点，因为`dictMap[s[i]]`表示`s[i]`上一次出现的下标，所以新的子串的第一个字符的前一个位置即`m = dictMap[s[i]]`，最后再令`dictMap[s[i]] = i`。

这样我们就只需要遍历一遍字符串即可得到最长不重复字符串的长度。

## 6. ZigZag Conversion

The string **`"PAYPALISHIRING"`** is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

	P   A   H   N
	A P L S I I G
	Y   I   R

And then read line by line: **`"PAHNAPLSIIGYIR"`**
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
**`convert("PAYPALISHIRING", 3)`** should return **`"PAHNAPLSIIGYIR"`**.

#### 思路1：

整体思路是从第一排一直扫描到第nRows排，直接拼接出新的字符串并返回。首先我们可以看到P到A为一个循环，其中`cycle = 4`，此时`nRows = 3`,我们在来看看`nRows = 4`的情况：

	P     I    N
	A   L S  I G
	Y A   H R  
	P     I
	
此时P到I为一个循环，其中`cycle = 6`，我们可以看得出来，nRows每增加一行，循环距离增加2。我们再来看看除了第一行和最后一行（这两排均相差`cycle = 2 * nRows - 2`，可以直接扫描出来）以外的中间行，可以知道在中间会额外插入一个字符，易证这个字符距离上一个循环点`cycle - 2 * i`，具体实现见代码。

#### 思路2：

建立一个大小为nRows的字符串数组，依次扫描原字符串，类似于电梯算法，设置一个flag，`flag = true`时从上往下存入字符，即`strArray[j++] += s[i++]`，当`flag = false`时从下往上存入字符，即`strArray[j--] += s[i++]`，当`j = 0`时flag置为true，当`j = nRows`时flag置为false，扫描完整个原字符串s后，将字符串数组strArray依次拼接起来即得到结果。

## 7. Reverse Integer

Reverse digits of an integer.

**Example1**: x = 123, return 321

**Example2**: x = -123, return -321

#### 思路：

直接翻转，用一个循环即可得到翻转后的数字，需要注意的是传入值和返回值都是int型，但是int型翻转后可能会越界，如果越界即大于INT_MAX或小于INT_MIN时返回0即可。

## 9. Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.

#### 思路：

可以直接利用第7题结果，如果翻转数和它本身相等即为回文数。

**优化：**其实只用翻转一半，如1221，翻转一半后12和12两个相等即可返回true，如果是奇数位的话，如12321，只需要12和123/10相等即可返回true，具体实现见代码。

注意：负数没有回文数。

## 10. Regular Expression Matching

Implement regular expression matching with support for '.' and '*'.
	
	'.' Matches any single character.
	'*' Matches zero or more of the preceding element.

	The matching should cover the entire input string (not partial).

	The function prototype should be:
	bool isMatch(const char *s, const char *p)

	Some examples:
	isMatch("aa","a") → false
	isMatch("aa","aa") → true
	isMatch("aaa","aa") → false
	isMatch("aa", "a*") → true
	isMatch("aa", ".*") → true
	isMatch("ab", ".*") → true
	isMatch("aab", "c*a*b") → true

#### 思路：

	这个题首先得明白题目的意思，','是可以匹配任意的一个字符，而'*'可以匹配0个或者多个它前面的元素。
	我们来看看几个比较难以理解的例子：
	isMatch("aaabc",".*") → true
	这里匹配，因为右边的字符串可以看做是"....."(".*"此时表示匹配5个'.'，而每个'.'可以匹配任意字符)。
	isMatch("aab", "c*a*b") → true
	这里"c*"表示匹配0个'c'，"*a"表示匹配2个'a'，因此也是匹配的。

明白这几个例子的例子后我们再来看，这个题其实只要把'*'出现作为一种特殊情况就可以了，大体思路是利用递归，只要第一个字符匹配，并且截去第一个字符后剩下的字符串也匹配，那么整个字符串就是匹配的。

1. 当字符串p为空时，如果字符串s也为空，则匹配，否则不匹配；
2. 当字符串p非空时，考虑字符串p的第二个字符是否为'*'
	- 如果是，那么此时整个字符串匹配的条件就是
		- s与截去前两个字符的p匹配（此时匹配0个'*'前面的元素），即`isMatch(s,p.substr(2))`
		- s不为空且当前字符匹配且s截去第一个字符与p匹配（此时递归，即匹配1个或多个'*'前面的元素），即`s.empty()&&(s[0]==p[0]||p[0]=='.')&&isMatch(s.substr(1),p)`
	- 如果不是，那么此时整个字符串匹配的条件就是
		- s不为空且当前字符匹配且s、p分别截去第一个字符也匹配，即`s.empty()&&(s[0]==p[0]||p[0]=='.')&&isMatch(s.substr(1),p.substr(1))`

## 11. Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

#### 思路：

这个题的意思是，给你一个数组，height[i]表示x轴上x=i点处的竖线的高度，任意两根竖线与x轴构成这个装水的容器，由木桶原理我们可以知道，一个木桶装水量的多少取决于最短的那根木板，所以height[i]与height[j]构成的容器的容量就等于小的那个高度*(j-i)。

最开始我的想法是，依次遍历数组，每遍历一个，就让它与前面的几个数依次构成容器计算容积，然后设一个变量maxArea来储存最大容积，最后返回这个最大容积。然而这个方法的时间复杂度我们可以算出来是n(n-1)/2即O(n^2)，最后超时了。

改进后的算法是先计算最左和最右两根线所构成的容器的容积(height[i]与height[j]，其中i=0，j=height.size()-1)，即底边最大的情况，然后如果height[i]较小，则i++，反之j--，直到i==j，这样扫过只需计算n次，时间复杂度降到了O(n)，同样通过一个变量maxArea来保存最大容积。

## 12. Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

#### 思路：

罗马数字采用七个罗马字母作数字、即Ⅰ（1）、X（10）、C（100）、M（1000）、V（5）、L（50）、D（500）。记数的方法：

1. 相同的数字连写，所表示的数等于这些数字相加得到的数，如 Ⅲ=3；
2. 小的数字在大的数字的右边，所表示的数等于这些数字相加得到的数，如 Ⅷ=8、Ⅻ=12；
3. 小的数字（限于 Ⅰ、X 和 C）在大的数字的左边，所表示的数等于大数减小数得到的数，如 Ⅳ=4、Ⅸ=9。

我的思路就是把罗马数字的个十百千位分别用一个字符串数组罗列出来，然后转换后拼接即可。

## 13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

#### 思路：

从上面一题我们可以发现，比如13（XIII）、16（XVI）、14（XIV）、7（VII）、9（IX），我们从右向左扫描整个罗马数字字符串，如果出现I的时候，这个数已经大于5了，比如IV先扫描到V就是5，IX先扫描到X就是10，那么I就应该取-1，其他时候I都取1，同理可以得到X、C的取值规则，而V、L、D是没有相减规则的，取正值即可。这样从右向左扫描完整个字符串，用一个变量来存储每个字符转成数之后的和即可。

## 14. Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

#### 思路：

因为最长共同前缀字符串一定也是第一个字符串的前缀，所以我们只需要找到最长共同前缀的长度即可，如果只有一个字符串，那它的最长共同前缀就是它本身。如果字符串数组大小大于1，那么从第二个开始往后扫描，依次比较它们与当前最长共同前缀字符串，获得二者的最长前缀，这一定也是整个字符串数组的最长前缀。

## 15. 3Sum

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

	For example, given array S = [-1, 0, 1, 2, -1, -4],

	A solution set is:
	[
  	  [-1, 0, 1],
  	  [-1, -1, 2]
	]
	
#### 思路：

如果把所有的可能都遍历一遍的话，时间复杂度是O(n^3)，必定超时，所以此方案并不可行。要想把时间复杂度降到O(n^2)，我的想法是第一个数确定，剩下的数只扫描一遍，那么时间复杂度就满足要求了。

首先把传入的数组排序，然后从第一个数开始，第一个数确定后，其下标为i，那么我们设两个指针，一个指向第i+1个数，即`begin = i + 1`，第二个指向最后一个数，即`end = size - 1`，因为数组排序过，所以`S[begin]`是剩下数组中最小的数，`S[end]`是最大的数，如果这三个数之和大于0，那么我们只需让最大的数小一些，即`end--`；反之如果三个数之和小于0，则让最小的数大一些，即`begin++`；如果三个数之和为0，那么满足条件，将三个数存入解容器tri中，同时`begin++`和`end--`，直到`begin = end`，一遍循环结束。

这样扫描的好处是第i个数只需要计算n-i次，时间复杂度降到了O(n^2)，还需要注意的一点是题目要求不能有重复的，所以当取到满足条件的数组时，要加一个判断：` 
while (begin < end && nums[begin] == tri[1]) begin++;
while (begin < end && nums[end] == tri[2]) end--;`

同时，每次i++的时候加一个
`while (i + 1 < size && nums[i] == nums [i+1]) i++;`以保证不重复。

## 16. 3Sum Closest

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

#### 思路：

遍历方式同上一题，此时我们只需要把0换成target比较就可以了，同时用一个closest变量存放最小差值，ans变量存放最小差值时候的sum值，最后返回ans即可，如果遍历过程中出现`sum = target`这种情况直接返回target即可。

注：closest默认值需要取一个比较大的值，否则会出错。

## 17. Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.

	Input:Digit string "23"
	Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.

#### 思路

利用动态规划的思路，依次遍历数字字符串，每遍历一个数字，将现有vector中的字符串挨个与之可能的字符结合生成新字符串，并更新vector。