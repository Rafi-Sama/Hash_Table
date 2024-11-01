#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

char random_char() {
    return 'A' + (rand() % 26);
}

char* random_string(int length) {
    char* str = (char*)malloc(sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++) {
        str[i] = random_char();
    }
    str[length] = '\0';
    return str;
}

void shuffle_string(char* str) {
    int length = strlen(str);
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
