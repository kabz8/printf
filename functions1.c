#include "main.h"

void print_output(char output[], int *output_index);

/**
 * my_printf - Custom Printf function
 * @format: The format string.
 * Return: The number of printed characters.
 */
int my_printf(const char *format, ...)
{
	int i, printed = 0, total_printed = 0;
	int flags, width, precision, size, output_index = 0;
	va_list args;
	char output[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			output[output_index++] = format[i];
			if (output_index == BUFFER_SIZE)
				print_output(output, &output_index);
			printed++;
		}
		else
		{
			print_output(output, &output_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			i++;
			printed = handle_print(format, &i, args, output,
					       flags, width, precision, size);
			if (printed == -1)
				return (-1);
			total_printed += printed;
		}
	}

	print_output(output, &output_index);

	va_end(args);

	return (total_printed);
}

/**
 * print_output - Prints the contents of the output buffer if it exists
 * @output: Array of characters
 * @output_index: Index at which to add the next character, represents the length.
 */
void print_output(char output[], int *output_index)
{
	if (*output_index > 0)
		write(1, &output[0], *output_index);

	*output_index = 0;
}

