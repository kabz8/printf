#include "main.h"

/**
 * my_get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @index: Pointer to the current index in the format string.
 * @arg_list: List of arguments to be printed.
 *
 * Return: Width.
 */
int my_get_width(const char *format, int *index, va_list arg_list)
{
    int curr_index;
    int width = 0;

    for (curr_index = *index + 1; format[curr_index] != '\0'; curr_index++)
    {
        if (my_is_digit(format[curr_index]))
        {
            width *= 10;
            width += format[curr_index] - '0';
        }
        else if (format[curr_index] == '*')
        {
            curr_index++;
            width = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *index = curr_index - 1;

    return width;
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

