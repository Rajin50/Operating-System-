#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isPalindrome(char *str) {
    char *front = str;
    char *end = str + strlen(str) - 1;

    while (front < end) {
        char frontChar = tolower(*front);
        char endChar = tolower(*end);

        if (frontChar != endChar)
            return false;

        front++;
        end--;
    }
    return true;
}

int main() {
    char input[100];
    printf("Enter a string: ");
    scanf("%s", input);

    if (isPalindrome(input)) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }
    return 0;
}

