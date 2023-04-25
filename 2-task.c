#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * _printcheck - checks and matches format with function
 * @format: format from argument to check
 * @list: the list argument to print
 * Return: function type to be passed on to the print string function
 */
int _printcheck(const char format, va_list list)
{
        unsigned int i;
        char c1;
        int ret = -1;

        /**
         * functionStruct - collection of func and specifiers
         * @specifier: format specifier
         * @printFunction: function pointer to print function
         */
        functionStruct functions[] = {
                {'c', _printchar}, {'s', _printstring},
                {'i', _printint}, {'d', _printint},
                {'\0', NULL}
        };

        for (i = 0; functions[i].specifier != '\0'; i++)
        {
                if (format == functions[i].specifier)
                {
                        ret = functions[i].printFunctions(list);
                        break;
                }
        }

        if (ret == -1)
        {
                c1 = '%';
                write(STDOUT_FILENO, &c1, 1);
                write(STDOUT_FILENO, &format, 1);
        }

        return (ret);
}

