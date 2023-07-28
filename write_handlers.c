#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @output: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char output[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at output's right */
	int index = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	output[index++] = c;
	output[index] = '\0';

	if (width > 1)
	{
		output[BUFFER_SIZE - 1] = '\0';
		for (index = 0; i < width - 1; index++)
			output[BUFFER_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &output[0], 1) +
					write(1, &output[BUFFER_SIZE - index - 1], width - 1));
		else
			return (write(1, &output[BUFFER_SIZE - index - 1], width - 1) +
					write(1, &output[0], 1));
	}

	return (write(1, &output[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @output: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char output[],
	int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, output, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the output
 * @output: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char output[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int index, padd_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && output[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFFER_SIZE - 2 && output[ind] == '0')
		output[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		output[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (index = 1; index < width - length + 1; index++)
			output[index] = padd;
		output[index] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of output */
		{
			if (extra_c)
				output[--ind] = extra_c;
			return (write(1, &output[ind], length) + write(1, &output[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				output[--ind] = extra_c;
			return (write(1, &output[1], i - 1) + write(1, &output[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				output[--padd_start] = extra_c;
			return (write(1, &output[padd_start], index - padd_start) +
				write(1, &output[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		output[--ind] = extra_c;
	return (write(1, &output[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the output
 * @output: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char output[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFFER_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFFER_SIZE - 2 && output[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		output[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; index < width - length; index++)
			output[index] = padd;

		output[index] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of output [output>padd]*/
		{
			return (write(1, &output[ind], length) + write(1, &output[0], index));
		}
		else /* Asign extra char to left of padding [padd>output]*/
		{
			return (write(1, &output[0], i) + write(1, &output[ind], length));
		}
	}

	return (write(1, &output[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @output: Arrays of chars
 * @ind: Index at which the number starts in the output
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char output[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int index;

	if (width > length)
	{
		for (index = 3; index < width - length + 3; index++)
			output[index] = padd;
		output[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of output */
		{
			output[--ind] = 'x';
			output[--ind] = '0';
			if (extra_c)
				output[--ind] = extra_c;
			return (write(1, &output[ind], length) + write(1, &output[3], index - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of output */
		{
			output[--ind] = 'x';
			output[--ind] = '0';
			if (extra_c)
				output[--ind] = extra_c;
			return (write(1, &output[3], index - 3) + write(1, &output[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				output[--padd_start] = extra_c;
			output[1] = '0';
			output[2] = 'x';
			return (write(1, &output[padd_start], index - padd_start) +
				write(1, &output[ind], length - (1 - padd_start) - 2));
		}
	}
	output[--ind] = 'x';
	output[--ind] = '0';
	if (extra_c)
		output[--ind] = extra_c;
	return (write(1, &output[ind], BUFFER_SIZE - ind - 1));
}

