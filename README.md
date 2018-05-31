# Longest-Common-Substring-For-Three-Strings
The program is used to find the Longest Common Substring for three strings using suffix array and Longest Common Prefix. Code clean up required to make code execute in linear time.

Input:
Three Strings

Output:
Longest Common Substring

Explanation:-
The three strings are first combined and add a symbol to indicate the end of a string. The code uses a '$' and a '#'. Then a suffix array and LCP is contructed.
We then create a window such that it includes all the three string. As the execution continues the window reduced from the top and increased from the bottom of the array until it encompasses the three string. The longest common substring is found by identifying the string with the maximum LCP in the window. This LCP indicates the size of the longest common substring.The position from where the LCS is taken in the combined string found from the suffix array.
