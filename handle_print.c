#include "main.h"

/**
 * my_handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @arg_list: List of arguments to be printed.
 * @index: Current index in the format string.
 * @output: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: Get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int my_handle_print(const char *format, int *index, va_list arg_list,
                    char output[], int flags, int width, int precision, int size)
{
    int i, unknown_len = 0, printed_chars = -1;
    fmt_t fmt_types[] = {
        {'c', my_print_char}, {'s', my_print_string}, {'%', my_print_percent},
        {'i', my_print_int}, {'d', my_print_int}, {'b', my_print_binary},
        {'u', my_print_unsigned}, {'o', my_print_octal}, {'x', my_print_hexadecimal},
        {'X', my_print_hexa_upper}, {'p', my_print_pointer}, {'S', my_print_non_printable},
        {'r', my_print_reverse}, {'R', my_print_rot13string}, {'\0', NULL}
    };

    for (i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (format[*index] == fmt_types[i].fmt)
            return (fmt_types[i].fn(arg_list, output, flags, width, precision, size));
    }

    if (fmt_types[i].fmt == '\0')
    {
        if (format[*index] == '\0')
            return (-1);
        unknown_len += write(1, "%%", 1);
        if (format[*index - 1] == ' ')
            unknown_len += write(1, " ", 1);
        else if (width)
        {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%')
                --(*index);
            if (format[*index] == ' ')
                --(*index);
            return (1);
        }
        unknown_len += write(1, &format[*index], 1);
        return (unknown_len);
    }

    return (printed_chars);
}

