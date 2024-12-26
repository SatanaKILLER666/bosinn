#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* strtolower(char *str) {
    char* result = calloc(strlen(str), sizeof(char));

    for(int i = 0; i < strlen(str); i++) {
        if(str[i] >= 65 & str[i] <= 90) {
            result[i] = str[i] + 32;
        }
        else {
            result[i] = str[i];
        }
    }
    return result;
}

char* strtoupper(char *str) {
    char* result = calloc(strlen(str), sizeof(char));

    for(int i = 0; i < strlen(str); i++) {
        if(str[i] >= 97 & str[i] <= 122) {
            result[i] = str[i] - 32;
        }
        else {
            result[i] = str[i];
        }
    }

    return result;
}

int strcmp_insensitive(const char *str1, const char *str2) {
    char tempstr1[strlen(str1)];
    char tempstr2[strlen(str2)];
    strcpy(tempstr1, str1);
    strcpy(tempstr2, str2);
    strcpy(tempstr1, strtolower(tempstr1));
    strcpy(tempstr2, strtolower(tempstr2));
    if(strcmp(tempstr1, tempstr2) > 0) {
        return strcmp(tempstr1, tempstr2);
    }
    return strcmp(tempstr2, tempstr1);
}

char* strreverse(char *str) {
    for(int i = 0; i < strlen(str)/2; i++) {
        char temp = str[i];
        str[i] = str[strlen(str)-1-i];
        str[strlen(str)-1-i] = temp;
    }
    return str;
}

char* strtrim(char *str) {
    char* start = str;
    char* end = str + strlen(str) - 1;
    int i = 0;
    while(*start <= 32) {
        start++;
    }
    while(*end <= 32) {
        *end = '\0';
        end--;
    }
    return memmove(str, start, end - start+2);
}

char* strrmchar(char *str, char symbol) {
    char* pos = strrchr(str, symbol);
    while(pos != NULL) {
        memmove(pos, pos+1, str + strlen(str) - pos);
        pos = strrchr(str, symbol);
    }
    return str;
}
size_t strcountchar(const char *str, char symbol) {
    int res = 0;
    char* start = strchr(str, symbol);
    while (start != NULL) {
        res++;
        start = strchr(start+1, symbol);
    }
    return res;
}
char* substr(const char* str, size_t pos, size_t count) {
    if(pos + count > strlen(str)) {
        count = strlen(str)-pos;
    }
    char* result = (char*)calloc(count, sizeof(*str));
    for(int i = pos; i < pos+count; i++) {
        result[i-pos] = str[i];
    }
    return result;
}
int strfindlastof(const char *str, const char *symbols) { 
    char* start = strpbrk(str, symbols);
    char* temp;
    while(start != NULL) {
        temp = start;
        start = strpbrk(start+1, symbols);
    }
    return temp-str;
}
int strispalindrome(const char *str) {
    int result = 1;

    char tempstr[strlen(str)];
    strcpy(tempstr, str);
    strcpy(tempstr, strtolower(tempstr));

    int nLetters = 0;
    for(int i = 0; i < strlen(str); i++) {
        if((str[i] >= 97 & str[i] <= 122) || (str[i] >= 65 & str[i] <= 90)) {
            nLetters++;
        }
    }

    char* onlyLetters = (char*)calloc(nLetters, sizeof(*str));
    int j = 0;
    for(int i = 0; i < strlen(tempstr); i++) {
        if((tempstr[i] >= 97 & tempstr[i] <= 122)) {
            onlyLetters[j] = tempstr[i];
            j++;
        }
    }
    for(int i = 0; i < strlen(onlyLetters); i++) {
        if(onlyLetters[i] != onlyLetters[strlen(onlyLetters) - 1 - i]) {
            result = result&0;
        }
    }
    return result;
}
size_t strcountwords(const char *str) {
    unsigned result = 0;
    char tempstr[strlen(str)];
    strcpy(tempstr, str);
    char* tok = strtok(tempstr, " "); 
    while(tok != NULL) {
        result += 1;
        tok = strtok(NULL, " ");
    }
    return result;
}

int cmp(const void* str1, const void* str2 )
{
    char* const *word1 = str1;
    char* const *word2 = str2;

    return strcmp(strtolower(*word1), strtolower(*word2));
}


char** strtowords(const char *str, size_t *count) {

    int maxWord = 0;
    char tempstr[strlen(str)];
    strcpy(tempstr, str);

    //Finding n of words
    int nWords = 0;
    char* tok = strtok(tempstr, " "); 
    while(tok != NULL) {
        nWords++;
        if(maxWord < strlen(tok)) {
            maxWord = strlen(tok);
        }
        tok = strtok(NULL, " ");
    }
    *count = nWords;

    //Init of the array
    char** result = NULL;
    result = (char**)malloc(nWords * sizeof(char*));
    for(int i = 0; i < nWords; i++) {
        result[i] = (char*)malloc((maxWord+1) * sizeof(char));
    }

    //Remove punctuation
    strcpy(tempstr, str);
    strrmchar(tempstr, '.');
    strrmchar(tempstr, '?');
    strrmchar(tempstr, '"');
    strrmchar(tempstr, '!');
    strrmchar(tempstr, ',');
    strrmchar(tempstr, '-');
    strrmchar(tempstr, '\'');
    strrmchar(tempstr, ':');
    strrmchar(tempstr, ')');
    strrmchar(tempstr, '(');
    strrmchar(tempstr, ';');


    //Filling the array
    int i = 0;
    tok = strtok(tempstr, " "); 
    while(tok != NULL) {
        strcpy(result[i], tok);
        tok = strtok(NULL, " ");
        i++;
    }

    qsort(result, nWords, sizeof(char*), cmp);
    return result;
}

int strisipv4(const char *str) {
    char* end;
    char tempstr[strlen(str)];
    strcpy(tempstr, str);
    int i = 0, check = 0;
    char* tokIp = strtok(tempstr, "/");
    char* tokAfter = strtok(NULL, "/");
    char* tok = strtok(tokIp, "."); 
    while(tok != NULL) {
            int temp = strtol(tok, &end, 10);
            if(end == tok || *end != '\0') {
                return 0;
            }
            if((strlen(tok) > 1) & tok[0] == '0') {
                return 0;
            }
            if(temp < 0 || temp > 255) {
                return 0;
            }
        tok = strtok(NULL, ".");
        i++;

    }
    if(tokAfter != NULL){
    int temp = strtol(tokAfter, &end, 10);
        if(end == tok || *end != '\0') {
            return 0;
        }
        if(temp < 0 || temp > 32) {
            return 0;
        }  
        if((strlen(tokAfter) > 1) & tokAfter[0] == '0') {
            return 0;
        }
    }
    return 1;
}
size_t* strcountchars(const char *str) {
    unsigned* array = (unsigned*)calloc(256, sizeof(unsigned));
    for(int i = 0; i < strlen(str); i++) {
        array[str[i]]+=1;
    }
    return array;
}