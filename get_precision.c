#include "main.h"

/**
 * my_get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * @arg_list: List of arguments to be printed
 *
 * Return: Precision.
 */
int my_get_precision(const char *format, int *index, va_list arg_list)
{
    int curr_index = *index + 1;
    int precision = -1;

    if (format[curr_index] != '.')
        return (precision);

    precision = 0;

    for (curr_index += 1; format[curr_index] != '\0'; curr_index++)
    {
        if (my_is_digit(format[curr_index]))
        {
            precision *= 10;
            precision += format[curr_index] - '0';
        }
        else if (format[curr_index] == '*')
        {
            curr_index++;
            precision = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *index = curr_index - 1;

    return (precision);
}

/**
 * my_is_digit - Check if a character is a digit (0-9)
 * @c: The character to be checked
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int my_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

