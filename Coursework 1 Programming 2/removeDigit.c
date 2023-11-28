#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

bool digitInNumber(int digit, int number) {
    char str[10];
    sprintf(str, "%d", number);
    char strDigit[2];
    sprintf(strDigit, "%d", digit);
    char* ptr = strstr(str, strDigit);
    
    if ((ptr) != NULL) {
        return true;
    }
    return false;
}

void removeDigit (int x, int n, int* a, int* b) {
    for (int i = 0; i < n; i++) {
        if (digitInNumber(x, i)) {
            continue;
        }
        int c = n - i;
        if (digitInNumber(x, c) || c <= 0) {
            continue;
        }
        (*a) = i;
        (*b) = c;
    }
}

int main() {
    int a;
    int b;
    removeDigit(1, 10, &a, &b);
    printf("a: %d , b: %d", a, b);
    return 0;
}