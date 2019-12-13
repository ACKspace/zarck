#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "vanalles.h"

char wordspace[128];

// strings to uppercase
void ucase(char *s)
{
  int i = 0;
  char c;

  while(1)
  {
    c = s[i];
    if (c==0)
      break;
    c = toupper(c);
    s[i] = c;
    i++;
  }
}

int removetrailingcrlf(char *s)
{
  int len, found = 0;
  len = strlen(s);
  if (len > 0)
  {
    if ((s[len-1]==13) || (s[len-1]==10))
    {
      s[len-1] = 0;
      found = 1;
    }
  }
  if (len > 1)
  {
    if ((s[len-2]==13) || (s[len-2]==10))
    {
      s[len-2] = 0;
      found = 1;
    }
  }
  return found;
}

// kinda destructive version of trim
char *trim(char *s)
{
  int triml=0, trimr=0;
  int len, i;

  len = strlen(s);
  if (len==0)
    return NULL;

  // trim left
  for (i=0; i<len; i++)
  {
    if (s[i]==' ')
      triml++;
    else
      break;
  }
  if (triml==len)
    return NULL; //all spaces

  // trim right
  for (i=len-1; i>=0; i--)
  {
    if (s[i]==' ')
      trimr++;
    else
      break;
  }
  s[len-trimr] = 0;

  return (s+triml);
}

void spaceditemcpy(char *dest, char *src, char c)
{
  int i=0;
  while ((src[i] != c) && (src[i] != 0))
    i++;
  memcpy(dest, src, i);
  dest[i] = 0;
}

char* xthword(char *src, int n)
{
  int i=0, wordn=0, found=false, maxn;
  maxn = strlen(src);
  while (src[i]!=0)
  {
    if (wordn==n)
    {
      found = true;
      break;
    }
    if (src[i]==' ')
    {
      wordn++;
      while ((src[i]==' ')&&(i<maxn))
        i++;
    }
    else
    {
      i++;
    }
    if (i>=maxn)
      break;
  }
  if (found)
    spaceditemcpy(wordspace, src+i, ' ');
  else
    wordspace[0] = 0;
  return wordspace;
}

int emptystring(char *src)
{
  int i, n;
  if (src==NULL)
    return true;
  if (src[0]==0)
    return true;
  n = strlen(src);
  for (i=0; i<n; i++)
  {
    if (src[i]!=' ')
      return false;
  }
  return true;
}

int initwordrec(int words, WORDREC *wr)
{
  int i;
  for (i=0; i<words; i++)
    wr[i].pos = 0;
  return 0;
}

int wordrecognize(char c, int words, WORDREC *wr)
{
  int i;
  int match = 0;
  for (i=0; i<words; i++)
  {
    if (wr[i].data[wr[i].pos]==c)
    {
      wr[i].pos++;
      if (wr[i].pos == wr[i].len)
      {
        wr[i].pos = 0;  // match!
        match = i+1;
      } 
    }
    else
    {
      wr[i].pos = 0;
    }
  }
  return match;
}
