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