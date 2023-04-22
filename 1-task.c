#include "main.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _printf - prints output according to a format
 * @format: character string containing zero or more directives
 *
 * Return: number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
        const char *f;
        va_list args;
        int len = 0;

        va_start(args, format);
        for (f = format; f && *f; f++)
        {
                if (*f != '%')
                {
                        write(1, f, 1);
                        len++;
                        continue;
                }
                switch (*++f)
                {
                        case 'c':
                                write(1, &va_arg(args, int), 1);
                                len++;
                                break;
                        case 's':
                                len += write(1, va_arg(args, char *), 1);
                                break;
                        case '%':
                                write(1, "%", 1);
                                len++;
                                break;
                        default:
                                write(1, "%", 1);
                                write(1, &*f, 1);
                                len += 2;
                                break;
                }
        }
        va_end(args);

        return (len);
}

