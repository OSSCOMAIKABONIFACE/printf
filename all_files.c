#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * output_char - Prints a char
 * @args: List a of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int output_char(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (output_string(c, cache, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * str_output - Prints a string
 * @args: List a of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int str_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(cache);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * cent_output - Prints a percent sign
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int cent_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(cache);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * int_output - Print int
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int int_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	int i = CACHE_SIZE - 2;
	int is_negative = 0;
	long int i = va_arg(args, long int);
	unsigned long int rom;

	n = size_upgrade(n, size);

	if (n == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		cache[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (output_num(is_negative, i, cache, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * bin_output - Prints an unsigned number
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int bin_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, add;
	unsigned int a[32];
	int read;

	UNUSED(cache);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, add = 0, read = 0; i < 32; i++)
	{
		add += a[i];
		if (add || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			read++;
		}
	}
	return (read);
}



#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * unsigned_output - Prints an unsigned number
 * @args: List a of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int unsigned_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * octal_output - Prints an unsigned number in octal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int octal_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{

	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		cache[i--] = '0';

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * hex_output - Prints an unsigned number in hexadecimal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	return (hex_output(args, "0123456789abcdef", cache,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * upper_hex_output - Prints an unsigned number in upper hexadecimal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int upper_hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	return (hex_output(args, "0123456789ABCDEF", cache,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * hex_output - Prints a hexadecimal number in lower or upper
 * @args: Lista of arguments
 * @pend: Array of values to map the number to
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int hex_output(va_list args, char pend[], char cache[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = pend[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		cache[i--] = flag_ch;
		cache[i--] = '0';
	}

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}



#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * unsigned_output - Prints an unsigned number
 * @args: List a of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int unsigned_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * octal_output - Prints an unsigned number in octal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int octal_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{

	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		cache[i--] = '0';

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * hex_output - Prints an unsigned number in hexadecimal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	return (hex_output(args, "0123456789abcdef", cache,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * upper_hex_output - Prints an unsigned number in upper hexadecimal notation
 * @args: Lista of arguments
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int upper_hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size)
{
	return (hex_output(args, "0123456789ABCDEF", cache,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * hex_output - Prints a hexadecimal number in lower or upper
 * @args: Lista of arguments
 * @pend: Array of values to map the number to
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int hex_output(va_list args, char pend[], char cache[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = CACHE_SIZE - 2;
	unsigned long int rom = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = size_reload(num, size);

	if (num == 0)
		cache[i--] = '0';

	cache[CACHE_SIZE - 1] = '\0';

	while (num > 0)
	{
		cache[i--] = pend[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		cache[i--] = flag_ch;
		cache[i--] = '0';
	}

	i++;

	return (print_unsigned int (0, i, cache, flags, width, precision, size));
}



#include "main.h"

/**
 * get_args - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_args(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, rec_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (rec_i = *i + 1; format[rec_i] != '\0'; rec_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[rec_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = rec_i - 1;

	return (flags);
}



#include "main.h"

/**
 * prec_update - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int prec_update(const char *format, int *i, va_list list)
{
	int rec_i = *i + 1;
	int precision = -1;

	if (format[rec_i] != '.')
		return (precision);

	precision = 0;

	for (rec_i += 1; format[rec_i] != '\0'; rec_i++)
	{
		if (is_char(format[rec_i]))
		{
			precision *= 10;
			precision += format[rec_i] - '0';
		}
		else if (format[rec_i] == '*')
		{
			rec_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = rec_i - 1;

	return (precision);
}



#include "main.h"

/**
 * size_input - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int size_input(const char *format, int *i)
{
	int rec_i = *i + 1;
	int size = 0;

	if (format[rec_i] == 'l')
		size = LONG_S;
	else if (format[rec_i] == 'h')
		size = SHORT_S;

	if (size == 0)
		*i = rec_i - 1;
	else
		*i = rec_i;

	return (size);
}



#include "main.h"

/**
 * width_input - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int width_input(const char *format, int *i, va_list list)
{
	int rec_i;
	int width = 0;

	for (rec_i = *i + 1; format[rec_i] != '\0'; rec_i++)
	{
		if (is_char(format[rec_i]))
		{
			width *= 10;
			width += format[rec_i] - '0';
		}
		else if (format[rec_i] == '*')
		{
			rec_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = rec_i - 1;

	return (width);
}


#include "main.h"
/**
 * print_output - Prints an argument based on its type
 * @syn: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @cache: Cache array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int print_output(const char *syn, int *ind, va_list list, char cache[],
	int flags, int width, int precision, int size)
{
	int i, x_len = 0, printed_chars = -1;
	syn_t syn_args[] = {
		{'c', output_char}, {'s', str_output}, {'%', cent_output},
		{'i', int_output}, {'d', int_output}, {'b', bin_output},
		{'u', unsigned_output}, {'o', octal_output}, {'x', hex_output},
		{'X', upper_hex_output}, {'p', output_pointer}, {'S', print_non_printable},
		{'r', reverse_output}, {'R', rot13_output}, {'\0', NULL}
	};
	for (i = 0; syn_args[i].syn != '\0'; i++)
		if (syn[*ind] == syn_args[i].syn)
			return (syn_args[i].fn(list, cache, flags, width, precision, size));

	if (syn_args[i].syn == '\0')
	{
		if (syn[*ind] == '\0')
			return (-1);
		x_len += write(1, "%%", 1);
		if (syn[*ind - 1] == ' ')
			x_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (syn[*ind] != ' ' && syn[*ind] != '%')
				--(*ind);
			if (syn[*ind] == ' ')
				--(*ind);
			return (1);
		}
		x_len += write(1, &syn[*ind], 1);
		return (x_len);
	}
	return (printed_chars);
}




#include "main.h"

/**
 * can_output - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int can_output(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * replace_code - Append ascci in hexadecimal code to cache
 * @cache: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int replace_code(char ascii_code, char cache[], int i)
{
	char pend[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	cache[i++] = '\\';
	cache[i++] = 'x';

	cache[i++] = pend[ascii_code / 16];
	cache[i] = pend[ascii_code % 16];

	return (3);
}

/**
 * is_char - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_char(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * size_upgrade - Casts a number to the specified size
 * @rom: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int size_upgrade(long int rom, int size)
{
	if (size == LONG_S)
		return (num);
	else if (size == SHORT_S)
		return ((short)num);

	return ((int)num);
}

/**
 * size_reload - Casts a number to the specified size
 * @rom: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int size_reload(unsigned long int rom, int size)
{
	if (size == LONG_S)
		return (num);
	else if (size == SHORT_S)
		return ((unsigned short)num);

	return ((unsigned int)num);
}




#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * output_string - Prints a string
 * @c: char args.
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int output_string(char c, char cache[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and subind at cache's right */
	int i = 0;
	char sub = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		sub = '0';

	cache[i++] = c;
	cache[i] = '\0';

	if (width > 1)
	{
		cache[CACHE_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			cache[CACHE_SIZE - i - 2] = sub;

		if (flags & F_MINUS)
			return (write(1, &cache[0], 1) +
					write(1, &cache[CACHE_SIZE - i - 1], width - 1));
		else
			return (write(1, &cache[CACHE_SIZE - i - 1], width - 1) +
					write(1, &cache[0], 1));
	}

	return (write(1, &cache[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * output_num - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char args.
 * @cache: Cache array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int output_num(int is_negative, int ind, char cache[],
	int flags, int width, int precision, int size)
{
	int len = CACHE_SIZE - ind - 1;
	char sub = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		sub = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (print_num(ind, cache, flags, width, precision,
		len, sub, extra_ch));
}

/**
 * print_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the cache
 * @cache: Cache
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @len: Number len
 * @sub: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int print_num(int ind, char cache[],
	int flags, int width, int prec,
	int len, char sub, char extra_c)
{
	int i, sub_start = 1;

	if (prec == 0 && ind == CACHE_SIZE - 2 && cache[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == CACHE_SIZE - 2 && cache[ind] == '0')
		cache[ind] = sub = ' '; /* width is displayed with subing ' ' */
	if (prec > 0 && prec < len)
		sub = ' ';
	while (prec > len)
		cache[--ind] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			cache[i] = sub;
		cache[i] = '\0';
		if (flags & F_MINUS && sub == ' ')/* Asign extra char to left of cache */
		{
			if (extra_c)
				cache[--ind] = extra_c;
			return (write(1, &cache[ind], len) + write(1, &cache[1], i - 1));
		}
		else if (!(flags & F_MINUS) && sub == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				cache[--ind] = extra_c;
			return (write(1, &cache[1], i - 1) + write(1, &cache[ind], len));
		}
		else if (!(flags & F_MINUS) && sub == '0')/* extra char to left of sub */
		{
			if (extra_c)
				cache[--sub_start] = extra_c;
			return (write(1, &cache[sub_start], i - sub_start) +
				write(1, &cache[ind], len - (1 - sub_start)));
		}
	}
	if (extra_c)
		cache[--ind] = extra_c;
	return (write(1, &cache[ind], len));
}

/**
 * print_unsigned - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the cache
 * @cache: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int print_unsigned(int is_negative, int ind,
	char cache[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = CACHE_SIZE - ind - 1, i = 0;
	char sub = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == CACHE_SIZE - 2 && cache[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		sub = ' ';

	while (precision > len)
	{
		cache[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		sub = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			cache[i] = sub;

		cache[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of cache [cache>sub]*/
		{
			return (write(1, &cache[ind], len) + write(1, &cache[0], i));
		}
		else /* Asign extra char to left of subing [sub>cache]*/
		{
			return (write(1, &cache[0], i) + write(1, &cache[ind], len));
		}
	}

	return (write(1, &cache[ind], len));
}

/**
 * pointer_output - Write a memory address
 * @cache: Arrays of chars
 * @ind: Index at which the number starts in the cache
 * @len: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @sub: Char representing the subing
 * @extra_c: Char representing extra char
 * @sub_start: Index at which subing should start
 *
 * Return: Number of written chars.
 */
int pointer_output(char cache[], int ind, int len,
	int width, int flags, char sub, char extra_c, int sub_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			cache[i] = sub;
		cache[i] = '\0';
		if (flags & F_MINUS && sub == ' ')/* Asign extra char to left of cache */
		{
			cache[--ind] = 'x';
			cache[--ind] = '0';
			if (extra_c)
				cache[--ind] = extra_c;
			return (write(1, &cache[ind], len) + write(1, &cache[3], i - 3));
		}
		else if (!(flags & F_MINUS) && sub == ' ')/* extra char to left of cache */
		{
			cache[--ind] = 'x';
			cache[--ind] = '0';
			if (extra_c)
				cache[--ind] = extra_c;
			return (write(1, &cache[3], i - 3) + write(1, &cache[ind], len));
		}
		else if (!(flags & F_MINUS) && sub == '0')/* extra char to left of sub */
		{
			if (extra_c)
				cache[--sub_start] = extra_c;
			cache[1] = '0';
			cache[2] = 'x';
			return (write(1, &cache[sub_start], i - sub_start) +
				write(1, &cache[ind], len - (1 - sub_start) - 2));
		}
	}
	cache[--ind] = 'x';
	cache[--ind] = '0';
	if (extra_c)
		cache[--ind] = extra_c;
	return (write(1, &cache[ind], CACHE_SIZE - ind - 1));
}



#include "main.h"

void print_cache(char cache[], int *index_cache);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, index_cache = 0;
	va_list list;
	char cache[CACHE_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			cache[index_cache++] = format[i];
			if (index_cache == CACHE_SIZE)
				print_cache(cache, &index_cachecache_index);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_cache(cache, &index_cachecache_index);
			flags = get_args(format, &i);
			width = width_input(format, &i, list);
			precision = prec_update(format, &i, list);
			size = size_input(format, &i);
			++i;
			printed = print_output(format, &i, list, cache,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_cache(cache, &index_cachecache_index);

	va_end(list);

	return (printed_chars);
}

/**
 * print_cache - Prints the contents of the cache if it exist
 * @cache: Array of chars
 * @index_cache: Index at which to add next char, represents the len.
 */
void print_cache(char cache[], int *index_cache)
{
	if (*index_cache > 0)
		write(1, &cache[0], *index_cache);

	*index_cache = 0;
}




#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define CACHE_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define LONG_S 2
#define SHORT_S 1

/**
 * struct syn - Struct op
 *
 * @syn: The format.
 * @fn: The function associated.
 */
struct syn
{
	char syn;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct syn syn_t - Struct op
 *
 * @syn: The format.
 * @fm_t: The function associated.
 */
typedef struct syn syn_t;

int _printf(const char *format, ...);
int print_output(const char *syn, int *i,
va_list list, char cache[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int output_char(va_list args, char cache[],
	int flags, int width, int precision, int size);
int str_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int cent_output(va_list args, char cache[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int int_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int bin_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int unsigned_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int octal_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size);
int upper_hex_output(va_list args, char cache[],
	int flags, int width, int precision, int size);

int hex_output(va_list args, char pend[],
char cache[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list args, char cache[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int output_pointer(va_list args, char cache[],
	int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_args(const char *format, int *i);
int width_input(const char *format, int *i, va_list list);
int prec_update(const char *format, int *i, va_list list);
int size_input(const char *format, int *i);

/*Function to print string in reverse*/
int reverse_output(va_list args, char cache[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int rot13_output(va_list args, char cache[],
	int flags, int width, int precision, int size);

/* width handler */
int output_string(char c, char cache[],
	int flags, int width, int precision, int size);
int output_num(int is_positive, int ind, char cache[],
	int flags, int width, int precision, int size);
int print_num(int ind, char bff[], int flags, int width, int precision,
	int len, char sub, char extra_c);
int pointer_output(char cache[], int ind, int len,
	int width, int flags, char sub, char extra_c, int sub_start);

int print_unsigned(int is_negative, int ind,
char cache[],
	int flags, int width, int precision, int size);

/****************** UTILS ******************/
int can_output(char);
int replace_code(char, char[], int);
int is_char(char);

long int size_upgrade(long int rom, int size);
long int size_reload(unsigned long int rom, int size);

#endif /* MAIN_H */


