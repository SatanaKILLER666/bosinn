#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isPalindrome(const char *str1) {
    int left = 0;
    int right = strlen(str1) - 1;

    while (left < right) {
        while (left < right && !isalnum(str1[left])) {
            left++;
        }
        while (left < right && !isalnum(str1[right])) {
            right--;
        }

        if (tolower(str1[left]) != tolower(str1[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    if (isPalindrome(argv[1])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}