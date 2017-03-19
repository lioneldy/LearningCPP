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

利用动态规划的思路，依次遍历数字字符串，每遍历一个数字，将现有vector中的字符串挨个与之可能的字符结合生成新字符串，并更新vector。比如按第一个键，假设有三种可能"abc"，再按第二个键有"def"，更新vector后从3种增加到3\*3=9种，如果再多一个按键有"wxyz"，依次与vector种已有元素结合后就从9种增加到9\*4=36种。

## 18. 4Sum

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

	A solution set is:
	[
  	[-1,  0, 0, 1],
  	[-2, -1, 1, 2],
  	[-2,  0, 0, 2]
	]
	
#### 思路

基于第15题3sum，我们先确定第一个数，然后把问题降到3sum，再确定第二个数把问题降到2sum，这样总共需要计算n\*(n-1)\*n次，所以这样解法的时间复杂度是O(n^3)。

依次类推，还可以把这个解法推广到Nsum。

## 19. Remove Nth Node From End of List

Given a linked list, remove the nth node from the end of list and return its head.

	For example,

   	Given linked list: 1->2->3->4->5, and n = 2.

   	After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass.

#### 思路

因为题目要求只遍历一次，所以需要两个指针。假设链表长度为m，一个指针先走n步，另外一个指针再跟着一起走直到第一个指针走到尾部，这样第一个指针走了m步，第二个指针走了m-n步，第二个指针所指向的节点即是需删除节点。

需要注意，我们应添加一个头指针来指向链表头部，两个指针从头指针开始出发，而不是传入的链表头，否则会出错。

## 20. Valid Parentheses

Given a string containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

The brackets must close in the correct order, `"()"` and `"()[]{}"` are all valid but `"(]"` and `"([)]"` are not.

#### 思路

利用栈可以很好地解决这个问题，当遇到左括号时入栈，遇到右括号时出栈，如果匹配则继续扫描，否则返回false，需要注意的是只能是对应的左右括号算匹配。

## 21. Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

#### 思路

这题比较简单，新建一个链表，当l1与l2不为空时比较两个指针所指值的大小，较小的加入新链表尾部，然后其指针往后走一步，若其中一个指针走到头了，即为空的时候，把另外一个非空链表加入新链表尾部即可。

## 22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

	[
  	"((()))",
  	"(()())",
  	"(())()",
  	"()(())",
  	"()()()"
	]

#### 思路

n对括号，有n个左括号和n个右括号，我们通过观察可以发现一些规律，首先是任意前m个字符中一定是左括号大于等于右括号的，不然这个字符串就是不合法的，其次就是第一个字符一定是左括号，最后一个字符一定是右括号。我们可以用一个递归来完成输出，如果右括号数等于n则将当前字符串存入vector；如果左括号小于n，字符串加一个"("，然后左括号数加一并递归调用；如果右括号小于左括号数，字符串加一个")"，然后右括号数加一并递归调用。

## 23. Merge K Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

#### 思路

采用类似归并排序的思路，从list中选两个链表，利用21题方法排序，两两排序后直到最后list里面只剩一个链表，假设有N个链表，平均每个链表长度为M，算法复杂度大概是O(M*logN)。

## 24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.For example,Given 1->2->3->4, you should return the list as 2->1->4->3.Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

#### 思路

如果链表长度是偶数，则两两配对翻转，1->2->3->4 => 2->1->4->3。

如果链表长度是奇数，则最后一个不变，1->2->3->4->5 => 2->1->4->3->5。

我用到了3个指针，p、q、r分别指向待交换对的第一个节点、第二个节点以及上一对的后节点，基本交换步骤如下：

	while(p != nullptr) {	//当p不为空时循环
		q = p->next;
		if(q == nullptr) break;		//当链表长度为奇数时最后节点不做交换
		r->next = q;
		r = p;					//上一对节点末尾指向当前对
		p->next = q->next;
		q->next = p;			//交换两个节点
		p->next = q;			
		p = p->next;			//p指向下一对待交换对的第一个节点
	}
	
## 25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,

Given this linked list: `1->2->3->4->5`

For k = 2, you should return: `2->1->4->3->5`

For k = 3, you should return: `3->2->1->4->5`

#### 思路

题目要求对链表进行k元组翻转，24题是k=2的情况，现在把k扩展到任意正整数的情况。从所给的例子中，我们不难发现，当链表剩下的节点数小于k的时候是不进行翻转的。我们以一个长度为5的链表进行3元组翻转作示例，来讲解我的思路：

	-1 -> 1 -> 2 -> 3 -> 4 -> 5
	 |    |    |    
	pre  cur  nex  

	-1 -> 2 -> 1 -> 3 -> 4 -> 5
 	 |         |    |     
	pre       cur  nex  

	-1 -> 3 -> 2 -> 1 -> 4 -> 5
	 |              |    |     
	pre            cur  nex  
	
上图是一次循环所进行的步骤，首先需要给当前需要翻转的k元祖申请一个头指针pre，指向该链表的第一个节点的前序节点，cur指针指向当前k元组的第一个节点，nex指针指向k元祖中需要翻转的下一个节点。

   	while(num>=k) {						//num为链表长度，需提前遍历一遍链表得到，当剩余链表长度不小于k时继续翻转
   		cur = pre->next;				//初始化当前k元组的cur指针
      	nex = cur->next;
      	for(int i = 1; i < k; ++i) {	//每次将k元组的下一个节点放到最前面，k-1次后完成翻转
		cur->next = nex->next;
		nex->next = pre->next;
		pre->next = nex;
		nex = cur->next;
		}
		pre = cur;						//一个k元组完成翻转，更新pre指针指向下一个k元组的第一个节点的前序节点
		num -= k;						//更新剩余未翻转链表长度
	}

## 26. Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

#### 思路

这个题比较简单，首先数组是已经排序的，我们只要遍历一遍就可以将重复的数找出来，得到不重复的数组长度length。但是需要注意的一点是，我们还需要更新vector，将前length个数更新成不重复的数，遍历过程中执行下列操作即可：

	if(nums[i] == temp) continue;
        else {
            temp = nums[i];
            nums[length++] = temp;
        }

## 27. Remove Element

Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.

#### 思路

这个题和上一题很类似，上一题是需要返回不重复数的个数，并将vector前length个数更新成不重复的数。而这一题更简单：

	if(nums[i] == val) continue;
        else nums[length++] = nums[i];
        
## 28. Implement strStr()

Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

#### 思路

题目的意思是，如果needle是haystack的子串，那么返回haystack的子串中等于needle的第一个子串的首字符的下标，如果needle不是haystack的子串那么返回-1.

	if (haystack[i] == needle[0]) {		//遍历haystack
		for (int j = 0; j < len2; j++) {	//如果有字符与needle首字符相同，比较后续字符
		if (haystack[i + j] != needle[j]) break;  //如果有不相同的字符结束比较
		else ans++;
		}
		if (ans == len2 - 1) return i;	//如果相同字符数与needle长度相等则结束
		ans = -1;
	}
	
## 29. Divide Two Integers

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

#### 思路

不使用乘、除以及求余三种运算来实现除法，那么第一时间想到的就是除法的本质，被除数是由商个除数相加，再加上余数得到的，那么只需要取被除数和除数的绝对值，然后循环，当被除数的绝对值大于零就减去除数，减的次数即为商，最后根据除数和被除数是否同号来决定商的符号。

但是这样做的话会超时，这里我想到的是利用位运算来降低复杂度。比如15除以3，先将3(11)左移一位得到6(110)，15>6，继续左移，12(1100)依然比15小，此时再左移24就比15大了，所以不再左移，此时左移了两位，那么商就是1<<2 = 100(4)，剩下15 - 12 = 3继续算，循环条件也是当被除数的绝对值小于除数绝对值时停止循环。

最后，溢出时需要返回MAX_INT，而此题溢出的情况只有两种，一是除数为0的时候，二是被除数为MIN_INT，除数为-1的时候。