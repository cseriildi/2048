#include "2048.h"

unsigned int	ascii_fits(t_tile *tile, t_board *board)
{
	if (tile->win.size_y < 4)
		return (0);
	unsigned int	ascii_width = 0;
	int	num = tile->number;
	int digit;
	while (num > 0)
	{
		digit = num % 10;
		num /= 10;
		ascii_width += ft_strlen(board->ascii_numbers[digit][0]);
		// mvwprintw(tile->win.win, 0, 0, "ascii_width: %d\n", ascii_width);
	}
	if (ascii_width > tile->win.size_x)
	{
		// mvwprintw(tile->win.win, 0, 0, "ascii_width: %d\n", ascii_width);
		return (0);
	}
	return (ascii_width);
}

static unsigned int	print_ascii_number(int digit, t_tile *tile, t_board *board, unsigned int x, unsigned int y)
{
	// char ascii[4][3] = board->ascii_numbers[digit];
	x = x - ft_strlen(board->ascii_numbers[digit][0]);
	// mvwprintw(tile->win.win, 0, 0, "number: %d", tile->number);
	// mvwprintw(tile->win.win, 1, 0, "board->ascii_numbers[digit][1]: %s", board->ascii_numbers[digit][1]);
	for (int i = 0; board->ascii_numbers[digit][i]; i++)
	{
		mvwprintw(tile->win.win, y + i, x, "%s", board->ascii_numbers[digit][i]);
		// mvwprintw(tile->win.win, 0,0, "%s", board->ascii_numbers[digit][i]);
	}
	(void)tile;
	(void)board;
	(void)y;
	(void)x;
	return x;
}

void print_ascii_centered(int ascii_width, t_tile *tile, t_board *board)
{
	int num = tile->number;
	// mvwprintw(tile->win.win, 1, 0, "ascii_width: %d\n", ascii_width);
	unsigned int start_x = get_center_pos(&tile->win, ascii_width);
	unsigned int end_x = tile->win.size_x - start_x;
	unsigned int start_y;
	
	start_y = tile->win.size_y / 2 - 2;
	while (num > 0)
	{
		int digit = num % 10;
		num /= 10;
		end_x = print_ascii_number(digit, tile, board, end_x, start_y);
	}
}