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
        case '\r': // Carriage return: reset column to 0
        {
            term_col = 0;
            break;
        }
        case '\b': // Backspace: move back one character
        {
            if (term_col > 0)
            {
                term_col--;
            }
            else if (term_row > 0) // Move up to the previous line if we're at the start of the current line
            {
                term_row--;
                term_col = VGA_COLS - 1;
            }

            // Clear the character at the new position
            const size_t index = (VGA_COLS * term_row) + term_col;
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
            break;
        }
        case '\t': // Tab: insert spaces until we reach the next multiple of 4
        {
            const int tab_size = 4;
            int spaces_to_next_tab_stop = tab_size - (term_col % tab_size);
            while (spaces_to_next_tab_stop > 0)
            {
                printc(' '); // Insert space characters
                spaces_to_next_tab_stop--;
            }
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

    // Handle the end of the line (move to the next row if the column exceeds the width)
    if (term_col >= VGA_COLS)
    {
        term_col = 0;
        term_row++;
    }

    // Handle scrolling if we exceed the screen height
    if (term_row >= VGA_ROWS)
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