#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precision = -1;

    if (format[curr_i] != '.')
        return (precision);

    precision = 0;

    for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            precision *= 10;
            precision += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            curr_i++;
            precision = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *i = curr_i - 1;

    return (precision);
}

/**
 * _printf - prints output according to a given format
 * @format: string containing zero or more directives
 *
 * Return: the number of characters printed
 */
int _printf(const char *format, ...)
{
    int i, j, len = 0, precision;
    va_list arg_list;

    va_start(arg_list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            precision = get_precision(format, &i, arg_list);

            switch (format[++i])
            {
                case 's':
                {
                    char *str = va_arg(arg_list, char *);
                    int str_len = 0;

                    if (str == NULL)
                        str = "(null)";

                    while (str[str_len] != '\0')
                        str_len++;

                    if (precision < 0)
                        precision = str_len;

                    for (j = 0; j < precision && str[j] != '\0'; j++)
                        len += _putchar(str[j]);

                    break;
                }
                // Handle other format specifiers here
            }
        }
        else
        {
            len += _putchar(format[i]);
        }
    }

    va_end(arg_list);

    return (len);
}
