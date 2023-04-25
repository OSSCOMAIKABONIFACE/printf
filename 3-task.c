#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * _printint - prints an integer
 * @list: argument to print
 * Return: numier of digits printed
 */
int _printint(va_list list)
{
    int num = va_arg(list, int);
    int digit_count = 0;
    int is_negative = 0;
    char *num_str;
    int temp;
    int printed_chars = 0;
    int i;

    if (num < 0) {
        is_negative = 1;
        num *= -1;
        digit_count++;
    }

    temp = num;
    while (temp > 0) {
        temp /= 10;
        digit_count++;
    }

    num_str = malloc((digit_count + 1) * sizeof(char));
    if (num_str == NULL) {
        return (-1);
    }

    num_str[digit_count] = '\0';

    for (i = digit_count - 1; i >= 0; i--) {
        num_str[i] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        printed_chars += write(STDOUT_FILENO, "-", 1);
    }

    printed_chars += write(STDOUT_FILENO, num_str, digit_count);

    free(num_str);

    return printed_chars;
}

