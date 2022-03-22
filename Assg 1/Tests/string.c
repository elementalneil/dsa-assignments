#include <stdio.h>
#include <string.h>
#include <math.h>

void stringOps(char *str){
    strcat(str, "abc");
}

int main(){
    // char str[2];
    // scanf("%s", str);

    // printf("%d", strcmp(str, "a"));

    int x;
    scanf("%d", &x);
    int digits = (floor(log2(x))) + 1;
    printf("%d", digits);
}