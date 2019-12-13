/*
* No Copyright
*
* The person who associated a work with this deed has dedicated the work to the public domain by waiving all of his or her rights to the work worldwide under copyright law, including all related and neighboring rights, to the extent allowed by law.
*
* You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission.
*
* See https://creativecommons.org/share-your-work/public-domain/cc0/ for more information on the license.
*/

#define false 0
#define true !0

// word recognize

typedef struct WORDREC
{
  int pos;
  int len;
  char data[50];
} WORDREC;

int initwordrec(int words, WORDREC* wr);
int wordrecognize(char c, int words, WORDREC* wr);

// other stuff

void ucase(char *s);
int removetrailingcrlf(char* s);
char* trim(char* s);
char* xthword(char* src, int n);
int emptystring(char* src);
