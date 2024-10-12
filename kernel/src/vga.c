#include <stddef.h>
#include <stdint.h>
#include "vga.h"

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;
// By default, the VGA textmode buffer has a size of 80x25 characters
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// We start displaying text in the top-left of the screen (column = 0, row = 0)
int term_col = 0;
int term_row = 0;
uint8_t term_color = VGA_COLOR_WHITE; // Black background, White foreground

void clear_screen()
{
	for (int col = 0; col < VGA_COLS; col++)
	{
		for (int row = 0; row < VGA_ROWS; row++)
		{
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' '; // Set the character to blank (a space character)
		}
	}
}

void set_term_color(uint8_t color)
{
	term_color = color;
}

void prints_color(const char *string,uint8_t temp_color)
{
	uint8_t colour_before=term_color;
	set_term_color(temp_color);
	prints(string);
	set_term_color(colour_before);
}

void scroll()
{
	// Move each row of the buffer up by one line
	for (int row = 1; row < VGA_ROWS; row++)
	{
		for (int col = 0; col < VGA_COLS; col++)
		{
			vga_buffer[(row - 1) * VGA_COLS + col] = vga_buffer[row * VGA_COLS + col];
		}
	}

	// Clear the last row
	int last_row_index = (VGA_ROWS - 1) * VGA_COLS;
	for (int col = 0; col < VGA_COLS; col++)
	{
		vga_buffer[last_row_index + col] = (term_color << 8) | ' ';
	}

	// Update terminal row
	term_row--;

	// Ensure terminal row is within bounds
	if (term_row < 0)
	{
		term_row = 0;
	}
}

void printc(char c)
{
	switch (c)
	{
	case '\n': // Newline characters should return the column to 0, and increment the row
	{
		term_col = 0;
		term_row++;
		break;
	}
	default: // Normal characters just get displayed and then increment the column
	{
		const size_t index = (VGA_COLS * term_row) + term_col; // Like before, calculate the buffer index
		vga_buffer[index] = ((uint16_t)term_color << 8) | c;
		term_col++;
		break;
	}
	}
	// What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
	if (term_col >= VGA_COLS) // width
	{
		term_col = 0;
		term_row++;
	}
	// If we get past the last row
	if (term_row >= VGA_ROWS) // height
	{
		scroll();
	}
}

void prints(const char *string)
{
	for (size_t i = 0; string[i] != '\0'; i++)
	{
		printc(string[i]);
	}
}