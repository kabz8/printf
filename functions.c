#include "my_print_functions.h"


/**
 * print_char - Prints a character
 * @arg_list: List of arguments
 * @output: Buffer array to handle the print output
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list arg_list, char output[],
                 int flags, int width, int precision, int size)
{
    char c = va_arg(arg_list, int);

    return (handle_write_char(c, output, flags, width, precision, size));
}


/**
 * print_string - Prints a string
 * @arg_list: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list arg_list, char output[],
                   int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(arg_list, char *);

    UNUSED(output);
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

    while (str[length] != '\0')
        length++;

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length)
    {
        if (flags & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else
        {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    return (write(1, str, length));
}


/**
 * print_percent - Prints a percent sign
 * @arg_list: List of arguments
 * @output: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list arg_list, char output[],
                     int flags, int width, int precision, int size)
{
    UNUSED(arg_list);
    UNUSED(output);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return (write(1, "%%", 1));
}


/**
 * print_int - Print integer
 * @arg_list: List of arguments
 * @outpu: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list arg_list, char output[],
                int flags, int width, int precision, int size)
{
    int i = BUFFER_SIZE - 2;
    int is_negative = 0;
    long int n = va_arg(arg_list, long int);
    unsigned long int num;

    n = convert_size_number(n, size);

    if (n == 0)
        output_buffer[i--] = '0';

    output[BUFFER_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        is_negative = 1;
    }

    while (num > 0)
    {
        output[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_number(is_negative, i, output, flags, width, precision, size));
}


/**
 * print_binary - Prints an unsigned number in binary format
 * @arg_list: List of arguments
 * @output: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_binary(va_list arg_list, char output[],
                    int flags, int width, int precision, int size)
{
    unsigned int n, m, i, sum;
    unsigned int a[32];
    int count;

    UNUSED(output);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    n = va_arg(arg_list, unsigned int);
    m = 2147483648; /* (2 ^ 31) */
    a[0] = n / m;
    for (i = 1; i < 32; i++)
    {
        m /= 2;
        a[i] = (n / m) % 2;
    }
    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];

            write(1, &z, 1);
            count++;
        }
    }
    return (count);
}

