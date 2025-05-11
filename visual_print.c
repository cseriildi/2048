#include "2048.h"

unsigned int get_center_pos(t_win *win, unsigned int size)
{
	return (win->size_x / 2 - size / 2);
}

void print_centered(t_win *win, int row, const char *str)
{
	unsigned int center_x = get_center_pos(win, ft_strlen(str));
	mvwprintw(win->win, row, center_x, "%s", str);
}

static unsigned int numlen(unsigned int number)
{
	if (number == 0)
		return 1;

	unsigned int len;
	for (len = 0; number > 0; len++)
		number /= 10;

	return (len);
}

void print_centered_number(t_win *win, int row, unsigned int number)
{
	unsigned int center_x = get_center_pos(win, numlen(number));
	mvwprintw(win->win, row, center_x, "%d", number);
}

static void print_centered_str_number(t_win *win, int row, char *str, unsigned int number)
{
	unsigned int center_x = get_center_pos(win, ft_strlen(str) + numlen(number) + 1);
	mvwprintw(win->win, row, center_x, "%s %d", str, number);
}

void print_stats(t_board *board, unsigned int row)
{	
	wattron(board->score_win.win, A_BOLD);

	if (board->win || board->game_over)
	{
		/*
		print_centered(&board->score_win, row++, "  _ _     _  _ _  _  _  ");
		print_centered(&board->score_win, row++,"/| )_)|_||_ |_  |(_)(_|/\\");
		print_centered(&board->score_win, row," |/__)  | _)|_) |(_) _|\\/");
		*/
		row++;
		print_centered(&board->score_win, row, (board->win ? "YOU WON!" : "GAME OVER!"));
		row++;
	}
	print_centered(&board->score_win, ++row, STATS1);
	wattroff(board->score_win.win, A_BOLD); 

	print_centered_str_number(&board->score_win, ++row,STATS2, board->score);
	print_centered_str_number(&board->score_win, ++row,STATS3, board->max_tile_value);
	print_centered_str_number(&board->score_win, ++row,STATS4, WIN_VALUE);
}
