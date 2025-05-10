#include "2048.h"
unsigned int ft_sqrt(unsigned int n)
{
	unsigned int i = 0;
	while (i * i < n)
		i++;
	return (i);
}

void update_board(t_board *board)
{
	t_tile tile;

	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			tile = board->tiles[i][j];
			wclear(tile.win.win);
			if (has_colors())
			{
				tile.win.color = ft_sqrt(tile.number) + 1;
				wbkgd(tile.win.win, COLOR_PAIR(tile.win.color));
			}
			if (tile.number != 0)
				print_centered_number(&tile.win, tile.win.size_y / 2, tile.number);
			wrefresh(tile.win.win);
		}
	}
}

void update_score(t_board *board)
{
	wclear(board->score_win.win);
	//TODO: not show when y >= x
	wattron(board->score_win.win, A_BOLD); 
	print_centered(&board->score_win, 1, SCORE_TITLE);
	wattroff(board->score_win.win, A_BOLD); 

	unsigned int i = 0;
	unsigned int j = 2;
	while  (j < board->score_win.size_y && board->score < board->top_scores[i])
	{
		if (board->top_scores[i] == 0)
			break;
		print_centered_number(&board->score_win, j++, board->top_scores[i++]);
	}
	if (j < board->score_win.size_y)
	{
		wattron(board->score_win.win, A_REVERSE);
		print_centered_number(&board->score_win, j++, board->score);
		wattroff(board->score_win.win, A_REVERSE);
	}
	while  (j < board->score_win.size_y)
	{
		if (board->top_scores[i] == 0)
			break;
		print_centered_number(&board->score_win, j++, board->top_scores[i++]);
	}
	
	box(board->score_win.win, 0, 0);
	wrefresh(board->score_win.win);
}

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
