#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include "random_key_gen.cpp"
typedef unsigned long long ul;

ul djb2(char *str){
    ul hash = 5381;
    int c;
    while((c=*str++)) hash = ((hash<<5)+hash) + c; // 33
    return hash;
}


int main() {
    srand(time(0));

    int length = 10;
    char* str = random_string(length);
    std::cout << "Original string: " << str << std::endl;

    shuffle_string(str);
    std::cout << "Shuffled string: " << str << std::endl;

    free(str);
    return 0;
}