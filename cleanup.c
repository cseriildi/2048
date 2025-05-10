#include "2048.h"

void cleanup_ncurses(t_board *board)
{
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->tiles[i][j].win.win != NULL)
			{
				delwin(board->tiles[i][j].win.win);
				board->tiles[i][j].win.win = NULL;
			}
		}
	}

	if (board->score_win.win != NULL)
	{
		delwin(board->score_win.win);
		board->score_win.win = NULL;
	}
	if (stdscr != NULL)
	{
		delwin(stdscr);
		stdscr = NULL;
	}
	endwin();
}


t_result write_score_to_file(t_board *board)
{
	int fd = open(SCORE_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return print_error(CANT_OPEN_FILE);
	
	ft_putnbr_fd(board->score, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return SUCCESS;
}

t_result print_error(t_result result)
{
	if (result == CANT_OPEN_FILE)
		ft_putstr_fd("Can't open file: " SCORE_FILE, 2);
	else if (result == NCURSES_FAILED)
		ft_putstr_fd("Ncurses failed to initialize", 2);
	else if (result == WIN_VALUE_ERROR)
		ft_putstr_fd("WIN_VALUE must be a power of 2", 2);
	else if (result == SCORE_LIST_SIZE_ERROR)
		ft_putstr_fd("SCORE_LIST_SIZE must be greater than 0", 2);

	return result;
}
