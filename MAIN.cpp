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
void    TextSortNReg(char *** text);

void    TextEraseChars(char *** text, const char * chars);
void    SwapStr(char *** text, int n1, int n2);
//int   comp(void ** a, void ** b);
bool    ComparisonStr(const char * str1, const char * str2);
FLAGS   FindInFlagBase(int argc, const char * argv[],FILE ** file);
void    PrintHelp(void);
void    DefaultSort(FILE * fin);
void    SortByEnd(FILE * fin);
void    SortNoReg(FILE * fin);


int main(int argc, const char * argv[]){
    printf("Meow\n");

    FILE * fin2 = fopen("POLTORASHKA.txt", "r");
    FILE *  file = NULL;

    switch(FindInFlagBase(argc, argv, &file)){
    case MODE_kit:
    {
        fseek(fin2, 0, SEEK_END);
        size_t n = (long unsigned int)ftell(fin2);
        fseek(fin2, 0, SEEK_SET);
        for (int i=0; i<(int)n; i++){ // no magic numbers
            putchar(getc(fin2)); // sendfile maybe
        }
        return 0;
    }
    case MODE_ByEnd:
        MyAssert(file == NULL);
        SortByEnd(file);
        return 0;
    case MODE_NoReg:
        MyAssert(file == NULL);
        SortNoReg(file);
        return 0;
    case MODE_Help:
        PrintHelp();
        return 0;
    case MODE_Default:
    default :
        MyAssert(file == NULL);
        DefaultSort(file);
        return 0;
    }
    fclose(file);
    fclose(fin2);

    return 0;

}

void DefaultSort(FILE * fin){
    char ** Text = ReadText(fin);
    TextSort(&Text);
    PrintText(Text);

    for(int i = 0; Text[i] != NULL; i++){
        free(Text[i]);
    }
    free(Text);
}

void SortByEnd(FILE * fin){
    char ** Text = ReadText(fin);
    TextISort(&Text);
    PrintText(Text);

    for(int i = 0; Text[i] != NULL; i++){
        free(Text[i]);
    }
    free(Text);
}

void SortNoReg(FILE * fin){
    char ** Text = ReadText(fin);
    TextSortNReg(&Text);
    PrintText(Text);

    for(int i = 0; Text[i] != NULL; i++){
        free(Text[i]);
    }
    free(Text);
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

void TextSortNReg(char *** text){
     MyAssert(text == NULL);

    int i = 0;
    while((*(text))[i] != NULL){
        i++;
    }
    i-=2;
    int a = ' ', b = ' ';
    for(int k = i; k >= 0; k--){
        for(int j = 0; j < k; j++){
            for(int n = 0; n < min(StrLen((*text)[j]), StrLen((*text)[j + 1])); n++)
            {
                a = *(*(*(text) + j)+n);
                b = *(*(*(text) + j+1)+n);
                if(a >= 'a'){
                    printf("Meow\n");
                    a = a + 'A' - 'a';
                }
                if(b >= 'a'){
                    printf("Meow\n");
                    b = b + 'A' - 'a';
                }
                if(a - b > 0){
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

FLAGS FindInFlagBase(int argc, const char * argv[], FILE ** file) {
    for(int i = 0; i < argc; i++) {
        if(ComparisonStr(argv[i],"-D")) {
            *file = fopen(argv[i + 1], "r");
            return MODE_Default;
        }
        if(ComparisonStr(argv[i],"-BE")) {
            *file = fopen(argv[i + 1], "r");
            return MODE_ByEnd;
        }
        if(ComparisonStr(argv[i],"-NR")) {
            *file = fopen(argv[i + 1], "r");
            return MODE_NoReg;
        }
        if(ComparisonStr(argv[i],"--help")) {
            return MODE_Help;
        }
        if(ComparisonStr(argv[i],"--kitten")) {
            return MODE_kit;
        }
    }
    return MODE_Default;
}

bool ComparisonStr(const char * str1, const char * str2) {
    MyAssert(str1 == NULL);
    MyAssert(str2 == NULL);

    int j = 0;
    while((str1[j] != '\0') || (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return false;
        }
        j++;
    }

    return true;
}

void PrintHelp(void) {
    printf("flags :\n");
    printf("-t                  : starts unit tests\n");
    printf("-f <name of file>   : solve tests from file\n");
    printf("--help              : print information about flags\n");
    printf("--kitten              : printit koshku poltorashku\n");
}
