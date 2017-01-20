# LeetcodePractice

用C++刷Leetcode题

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