#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "BasicFuncs.cpp"


char ** ReadText(FILE * fin);
void    PrintText(char ** text);
void    TextSort(char *** text);
void    TextEraseChars(char *** text, const char * chars);
void    SwapStr(char *** text, int n1, int n2);

int main(int argc, char * argv[]){
    FILE * fin = fopen(argv[1], "r");
    char ** Text = ReadText(fin);
    TextSort(&Text);
    //TextEraseChars(&Text," ?!':;’,.");
    PrintText(Text);
    for (int i = 0; Text[i] != NULL; i++){
        free(Text[i]);
    }
    free(Text);
    fclose(fin);
    return 0;

}

char ** ReadText(FILE * file){
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
    int i = 0;
    while(text[i+1] != NULL){
        printf("%s\n", text[i]);
        i++;
    }
}

void TextSort(char *** text){
    int i = 0;
    while((*(text))[i] != NULL){
        i++;
    }
    i-=2;
    for(int k = i; k >= 0; k--){
        for(int j = 0; j < k; j++){
            for(int n = 0; n < min(StrLen((*text)[j]), StrLen((*text)[j+1])); n++){
                if(*(*(*(text) + j)+n) - *(*(*(text) + j+1)+n) > 0){
                    SwapStr(text, j, j+1);
                    n = min(StrLen((*text)[j]),StrLen((*text)[j+1]));
                }
                else{
                    n = min(StrLen((*text)[j]),StrLen((*text)[j+1]));
                }
            }
        }
    }
}
/*
void TextEraseChars(char *** text, const char * chars){
    int j = 0, i = 0;
    while((*text)[j+1] != NULL){
        for(int k = 0; k < StrLen(chars); k++){
            if(((*text)[j])[i] == chars[k]){
                ((*text)[j])[i] = '*';
            }
        }
        if(((*text)[j])[i+1] == '\0'){
            i=0;
            j++;
        }
        i++;
    }
    j=0;
    i=0;
    while((*text)[j+1] != NULL){
        while(((*text)[j])[i+1] != '\0' && ((*text)[j])[i+1] != '\n'){
            i++;
            j++;
        }
    }
}
*/
void SwapStr(char *** text, int n1, int n2){
    char * a = *(*(text) + n2);
    *(*(text) + n2) = *(*(text) + n1);
    *(*(text) + n1) = a;
}
