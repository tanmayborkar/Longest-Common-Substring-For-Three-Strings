/*
Name:- Tanmay Borkar

The following code is used to find the longest common substring using Suffix Arrays and LCP.

Input:
Three Strings

Output:
Longest Common Substring



Reference:-
1. http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR18/SAcommonSubStr2.c
2. https://www.youtube.com/watch?v=Ic80xQFWevc
3. M.A. Babenko and T.A. Starikovskaya, “Computing Longest Common Substrings Via Suffix Arrays” Proc. 3rd Int’l Computer Science Symp. in Russia, CSR 2008, LNCS5010, Springer, 64-75.
*/
// Use suffix array and LCP to compute

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char s[1000000], s1[500000], s2[500000], s3[500000];
int n,           // length of s[] including \0
sa[1000000],   // suffix array for s[]
rank[1000000], // rank[i] gives the rank (subscript) of s[i] in sa[]
lcp[1000000];  // lcp[i] indicates the number of identical prefix symbols
			   // for s[sa[i-1]] and s[sa[i]]

int suffixCompare(const void *xVoidPt, const void *yVoidPt)
{
	// Used in qsort call to generate suffix array.
	int *xPt = (int*)xVoidPt, *yPt = (int*)yVoidPt;

	return strcmp(&s[*xPt], &s[*yPt]);
}

void computeRank()
{
	// Computes rank as the inverse permutation of the suffix array
	int i;

	for (i = 0; i<n; i++)
		rank[sa[i]] = i;
}

void computeLCP()
{
	//Kasai et al linear-time construction
	int h, i, j, k;

	h = 0;  // Index to support result that lcp[rank[i]]>=lcp[rank[i-1]]-1
	for (i = 0; i<n; i++)
	{
		k = rank[i];
		if (k == 0)
			lcp[k] = (-1);
		else
		{
			j = sa[k - 1];
			// Attempt to extend lcp
			while (i + h<n && j + h<n && s[i + h] == s[j + h])
				h++;
			lcp[k] = h;
		}
		if (h>0)
			h--;  // Decrease according to result
	}
}

int main()
{
	int i, j, k, p, m, dollarPos, hashpos, LCSpos = 0, LCSlength = 0;


	scanf("%s", s1);
	scanf("%s", s2);
	scanf("%s", s3);

	//Concatinate Strings
	for (i = 0; s1[i] != '\0'; i++)
		s[i] = s1[i];

	dollarPos = i;
	s[i++] = '$';
	for (j = 0; s2[j] != '\0'; j++)
		s[i + j] = s2[j];

	n = i + j;
	hashpos = n;
	s[n++] = '#';
	for (m = 0; s3[m] != '\0'; m++)
		s[n + m] = s3[m];

	printf(" \n", s);
	s[n + m] = '\0';
	n = n + m + 1;


	printf("n is %d\n", n);

	// Quick-and-dirty suffix array construction
	for (i = 0; i<n; i++)
		sa[i] = i;
	qsort(sa, n, sizeof(int), suffixCompare);
	//Find LCP for the strings
	computeRank();
	computeLCP();
	if (n<20000)
	{
		printf("i   sa  suffix                              lcp s rank lcp[rank]\n");
		for (i = 0; i<n; i++)
			printf("%-3d %-3d %-35.35s %-3d %c  %-3d  %-3d\n",
				i, sa[i], &s[sa[i]], lcp[i], s[i], rank[i], lcp[rank[i]]);
	}
	
	//Find the Longest Common Substring
	int c = 0;
	int sc1 = 0,sc2 = 0, sc3 = 0;
	int x, y, z, fx, fy, fz;
	int minLCP = 0, max;
	for (j = 1; j < n; j++) {
		for (i = j; i < n; i++) {
			if (!(sc1 == 1 && sc2 == 1 && sc3 == 1)) {
				if (sa[i] < dollarPos) {
					if(sc1==0)
						c++;
					sc1 = 1;
					x = i;
				}
				if (sa[i] > dollarPos && sa[i] < hashpos) {
					if (sc2 == 0)
						c++;
					sc2 = 1;
					y = i;
				}
				if (sa[i] > hashpos) {
					if (sc3 == 0)
						c++;
					sc3 = 1;
					z = i;
				}
			}

			

			if (c==3) {
				int min, mid;
				
				if (x<y && x<z) {
					j = x;
					sc1 = 0;
					min = x;
				}
				else if (y<x && y<z) {
					j = y;
					sc2 = 0;
					min = y;
				}
				else {
					j = z;
					sc3 = 0;
					min = z;
				}


				if (x>y && x>z) {
					max = x;
				}
				else if (y>x && y>z) {
					max = y;
				}
				else {
					max = z;
				}
				
				if (x != max && x != min) {
					mid = x;
				}
				if (y != max && y != min) {
					mid = y;
				}
				if (z != max && z != min) {
					mid = z;
				}
				
				minLCP = lcp[max - 1] < lcp[max] ? lcp[max - 1] : lcp[max];

				if (minLCP > LCSlength) {
					LCSpos = max;
					LCSlength = minLCP;
					
					fx = min;
					fy = mid;
					fz = max;
					
					c = c-1;
					j = j + 1;
					break;
				}
				
				c = c - 1;
				j = j + 1;
				break;
			}
		}
	}
	
	//Display the Longest Common Substring
	printf("Length of longest common substring is %d\n", LCSlength);
	printf("x at %d, y ends at %d, z at %d\n", fx,fy,fz);
	for (i = 0; i<LCSlength; i++)
		printf("%c", s[sa[LCSpos] + i]);
	printf("\n");
	
	return 0;
}