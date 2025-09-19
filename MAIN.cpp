#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Hedder.h"
#include "MyAssert.h"


char ** ReadText(FILE * fin);
char ** ReadText2(FILE * fin, char ** a);

void    PrintText(char ** text);

void    TextSort(char *** text);
void    TextISort(char *** text);

void    TextEraseChars(char *** text, const char * chars);
void    SwapStr(char *** text, int n1, int n2);
//int     comp(void ** a, void ** b);

int main(int argc, char * argv[]){
    printf("Meow\n");

    FILE * fin = fopen(argv[1], "r");
    MyAssert(fin == NULL);

    char ** Text = ReadText(fin);
    TextSort(&Text);
    PrintText(Text);

    for(int i = 0; Text[i] != NULL; i++){
        free(Text[i]);
    }
    free(Text);
    fclose(fin);

    return 0;

}

char ** ReadText(FILE * file){
    MyAssert(file == NULL);

    size_t n = 10;
    int    a = 0;
    int    i = 0;
    char ** ptr = (char**)calloc(n, sizeof(char*));
    while(a != 1){
        if((size_t)i == n){
            n  = n * 2;
            ptr = (char**)realloc(ptr,n * sizeof(char*));
        }
        a = GetLine(&ptr[i], file);
        i++;
    }
    ptr[i] = NULL;
    return ptr;
}

void PrintText(char ** text){
    MyAssert(text == NULL);
    int i = 0;
    while(text[i] != NULL){
        printf("%s\n", text[i]);
        i++;
    }
}

void TextSort(char *** text){
    MyAssert(text == NULL);

    int i = 0;
    while((*(text))[i] != NULL){
        i++;
    }
    i-=2;

    for(int k = i; k >= 0; k--){
        for(int j = 0; j < k; j++){
            for(int n = 0; n < min(StrLen((*text)[j]), StrLen((*text)[j + 1])); n++)
            {
                if(*(*(*(text) + j)+n) - *(*(*(text) + j+1)+n) > 0){
                    SwapStr(text, j, j + 1);
                    n = min(StrLen((*text)[j]), StrLen((*text)[j + 1]));
                }
                else{
                    n = min(StrLen((*text)[j]), StrLen((*text)[j + 1]));
                }
            }
        }
    }
}

void TextISort(char *** text){
    MyAssert(text == NULL);

    int i = 0;
    while((*(text))[i] != NULL){
        i++;
    }
    i-=2;
    for(int k = i; k >= 0; k--){
        for(int j = 0; j < k; j++){
            for(int n = 0; n < min(StrLen((*text)[j]), StrLen((*text)[j + 1])); n++){
                //printf("ABC\n");
                if(*(*(*(text) + j) + StrLen((*text)[j]) - n -1) - *(*(*(text) + j + 1) + StrLen((*text)[j + 1]) - n -1) > 0){
                    //printf("ABC\n");
                    SwapStr(text, j, j + 1);
                    n = min(StrLen((*text)[j]), StrLen((*text)[j + 1]));
                }
                else{
                    n = min(StrLen((*text)[j]), StrLen((*text)[j + 1]));
                }
            }
        }
    }
}

///*
void TextEraseChars(char *** text, const char * chars){
    MyAssert(text == NULL);

    int j = 0, i = 0;
    while((*text)[j+1] != NULL){
        for(int k = 0; k < StrLen(chars); k++){
            if((((*text)[j])[i] == chars[k]) && ((*text)[j])[i+1] == '\0'){
                ((*text)[j])[i] = '\0';
            }
        }
        if(((*text)[j])[i] == '\0'){
            i=0;
            j++;
        }
        i++;
    }
    j=0;
    i=0;
    //while((*text)[j+1] != NULL){
    //    while(((*text)[j])[i+1] != '\0' && ((*text)[j])[i+1] != '\n'){
    //        i++;
    //        j++;
    //    }
    //}
}
//*/
void SwapStr(char *** text, int n1, int n2){
    MyAssert(text == NULL);

    char * a = *(*(text) + n2);
    *(*(text) + n2) = *(*(text) + n1);
    *(*(text) + n1) = a;
}

char ** ReadText2(FILE * fin, char ** a){
    MyAssert(fin == NULL);
    MyAssert(a == NULL);

    fseek(fin, 0, SEEK_END);
    size_t n = (long unsigned int)ftell(fin);
    *a = (char*)calloc(n+1, sizeof(char));
    fseek(fin, 0, SEEK_SET);
    fread(*a, sizeof(char), n, fin);
    (*a)[n] = '\0';
    int i = 0;
    int sum = 1;
    while((*a)[i] != '\0'){
        if((*a)[i] == '\n'){
            //printf("%d \\n %d\n", i, sum);
            (*a)[i] = '\0';
            sum++;
        }
        i++;
    }
    char ** ptr = (char**)calloc((size_t)(sum+1), sizeof(char*));
    int len = i;
    i = 0;
    int j = 0;
    ptr[i] = (*a);
    i++;
    for(j = 0; j<len; j++){
        if((*a)[j] == '\0'){
            //printf("%d new_str \n", j);
            ptr[i] = (*a) + j + 1;
            i++;
        }
    }
    ptr[sum] = NULL;
    return ptr;
}
/*
int comp(void **a, void **b) {
    for(int n = 0; n < min(StrLen((char *)a), StrLen((char *)b)); n++){
        if(*((char *)a+n) - *((char *)b+n) > 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}
*/
