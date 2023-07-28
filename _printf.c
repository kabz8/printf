#include "main.h"

void print_output(char output[], int *output_index);

/**
 * _printf - Custom Printf function
 * @format: The format string.
 * Return: The number of printed characters.
 */
 
int _printf(const char *format, ...)
{
	int index, printed = 0, printed_chars = 0;
	int flags, width, precision, size, output_index = 0;
	va_list arg_list;
	char output[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);

	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			output[output_index++] = format[index];
			if (output_index == BUFFER_SIZE)
				print_output(output, &output_index);
			/* write(1, &format[index], 1);*/
			printed_chars++;
		}
		else
		{
			print_output(output, &output_index);
			flags = get_flags(format, &index);
			width = get_width(format, &index, arg_list);
			precision = get_precision(format, &index, arg_list);
			size = get_size(format, &index);
			++index;
			printed = handle_print(format, &index, arg_list, output,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_output(output, &output_index);

	va_end(arg_list);

	return (printed_chars);
}

/**
 * print_output - Prints the contents of the output if it exist
 * @output: Array of chars
 * @output_index: Index at which to add next char, represents the length.
 */
void print_output(char output[], int *output_index)
{
	if (*output_index > 0)
		write(1, &output[0], *output_index);

	*output_index = 0;
}

