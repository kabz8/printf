#include "main.h"

/**
 * my_get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 *
 * Return: Size.
 */
int my_get_size(const char *format, int *index)
{
    int curr_index = *index + 1;
    int size = 0;

    if (format[curr_index] == 'l')
        size = S_LONG;
    else if (format[curr_index] == 'h')
        size = S_SHORT;

    if (size == 0)
        *index = curr_index - 1;
    else
        *index = curr_index;

    return (size);
}

