#include "2048.h"

void cleanup_ncurses(t_board *board)
{
	keypad(stdscr, FALSE);
	keypad(board->menu.win, FALSE);
	keypad(board->score_win.win, FALSE);
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
	if (board->menu.win != NULL)
	{
		delwin(board->menu.win);
		board->menu.win = NULL;
	}
	nocbreak();
	echo();
	curs_set(1);
	endwin();
}


t_result write_score_to_file(t_board *board)
{
	int fd = open(board->score_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return CANT_OPEN_FILE;
	
	ft_putnbr_fd(board->score, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return SUCCESS;
}

t_result print_error(t_result result)
{
	if (result == CANT_OPEN_FILE)
		ft_putendl_fd("Can't open score file.", 2);
	else if (result == NCURSES_FAILED)
		ft_putendl_fd("Ncurses failed to initialize", 2);
	else if (result == SCORE_LIST_SIZE_ERROR)
		ft_putendl_fd("SCORE_LIST_SIZE must be greater than 0", 2);

	return result == USER_EXIT ? SUCCESS : result;
}
