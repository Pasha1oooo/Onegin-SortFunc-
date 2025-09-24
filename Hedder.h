#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int          StrLen(const char * str1);
int          StrCmp(char * str1, char * str2);
int          StrCmp2(char * str1, char * str2);
char *       StrCpy(char * str1, const char * str2);
char *       StrCat(char * str1, const char * str2);
const char * StrChr(const char * str1, int c);
int          Atoi(const char * str);
char *       Itoa(int n, char str[]);
char *       StrDup(const char * str);
char *       StrTok(const char * str, const char tok);
int          max(int a, int b);
int          min(int a, int b);
int          GetLine(char ** lineptr, FILE * stream);
bool         ComparisonStr(const char * str1, const char * str2);

