#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Hedder.h"

int StrCmp(char * str1,char * str2) {
    int j = 0;
    while((str1[j] != '\0') || (str2[j] != '\0') || (str1[j] != '\n') || (str2[j] != '\n')) {
        if (str1[j] != str2[j]) {
            if((StrLen(str1)-StrLen(str2)) != 0){
                return (StrLen(str1)-StrLen(str2));
            }
            else{
                return ((int)str1[j] - (int)str2[j]);
            }
        }
        j++;
    }
    if((StrLen(str1)-StrLen(str2)) != 0){
        return (StrLen(str1)-StrLen(str2));
    }
    else{
        return ((int)str1[j-1] - (int)str2[j-1]);
    }
}


int StrLen(const char * str){
    int j = 0;
    while(str[j] != '\0'){
        j++;
    }
    return j;
}

char * StrCpy(char * dst, const char * src){
    int j = 0;
     while(src[j] != '\0'){
        dst[j] = src[j];
        j++;
    }
    return dst;
}

const char * StrChr(const char * str1, int c){
    int j = 0;
    while(str1[j] != '\0'){
        if(str1[j] == c){
            return &str1[j];
        }
        j++;
    }
    return NULL;
}

char * StrCat(char * dst, const char * src){
    int j = 0;
    int n = StrLen(dst);
    do{
        dst[n+j] = src[j];
    } while(src[j++] != '\0');

    return dst;
}

int Atoi(const char * str){
    int sum = 0;
    int n = StrLen(str);
    for(int i = 0;i<n;i++){
        sum += (str[n-i-1]-48)*(int)pow(10, i);
    }
    return sum;
}

char * Itoa(int n, char str[]){
    int a =n;
    int j=0;
    while(a>10){
        a /= 10;
        j++;
    }

    int i=0;
    while(n>0){
        str[j-i] = (char)(n%10 + '0');
        n /= 10;
        i++;
    }
    str[j+1]= '\0';
    return str;
}

char * StrDup(const char * str){
    char * dst  = (char*)calloc((size_t)(StrLen(str) + 1), sizeof(char));
    StrCpy(dst, str);
    return dst;
}

int GetLine(char ** lineptr, FILE * stream){
    size_t n = 10;
    int i = 0;
    char * ptr = (char*)calloc(n, sizeof(char));
    *(ptr + n-1) = '\0';
    char c = (char)getc(stream);
    while(c != '\n' && c != EOF){
        if((size_t)i == n-1){
            n = n * 2;
            ptr = (char*)realloc(ptr,n);              //?????????????// 0 00 000 0000
            *(ptr + n-1) = '\0';
        }
        *(ptr + i) = c;
        c = (char)getc(stream);
        i++;
    }

    *lineptr = (char*)realloc(ptr,n * sizeof(char));
    *(*(lineptr)+i) = '\0';
    if(c == EOF){
        return 1; ///c maybe allways \n
    }
    else{
        return 0;
    }
}

char * StrTok(const char * str, const char tok){
    static const char * pos = NULL;
    if(str == NULL){
        str = pos;
    }
    int i = 0;
    int n = 10;
    int x = 1;
    char * ptr = (char*)calloc((size_t)n, sizeof(char));
    char c =*(str+i);
    while(c != tok){
        if(i == n){
            x++;
            ptr = (char*)realloc(ptr, (size_t)pow(n, x));
            n = (int)pow(n, x);
        }
        *(ptr + i) = c;

        i++;
        c = *(str+i);
    }
    pos = (str + i + 1);

    return ptr;
}

int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
int min(int a, int b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}
