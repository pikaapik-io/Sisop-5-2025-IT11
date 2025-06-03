#include "std_lib.h"

int div(int a, int b) {
    int neg = 0;
    if (a < 0) {
        a = -a;
        neg = !neg;
    }
    if (b < 0) {
        b = -b;
        neg = !neg;
    }

    int result = 0;
    while (a >= b) {
        a -= b;
        result++;
    }

    return neg ? -result : result;
}

int mod(int a, int b) {
    int div_result = div(a, b);
    return a - (div_result * b);
}

bool strcmp(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

void strcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    *num = result * sign;
}

void itoa(int num, char *str) {
    int i = 0;
    int is_neg = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_neg = 1;
        num = -num;
    }

    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_neg)
        str[i++] = '-';

    str[i] = '\0';

    // Balik string
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void sleep(unsigned int ticks)
{
  unsigned int start = getBiosTick();
  while (getBiosTick() - start < ticks);
}
