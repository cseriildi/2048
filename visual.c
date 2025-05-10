#include "2048.h"

void update_board(t_board *board)
{
	t_tile tile;

	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			tile = board->tiles[i][j];
			wclear(tile.win.win);
			wbkgd(tile.win.win, COLOR_PAIR(tile.win.color));
			if (tile.number != 0)
			//TODO: center the number
				mvwprintw(tile.win.win, 1, 2, "%d", tile.number);
			wrefresh(tile.win.win);
		}
	}
}

void update_score(t_board *board)
{
	wclear(board->score_win.win);
	//TODO: check window size, maybe add title
	mvwprintw(board->score_win.win, 1, 1, "Top Scores");
	unsigned int i = 0;
	unsigned int j = 2;
	while  (j < board->score_win.size_y && board->score < board->top_scores[i])
	{
		if (board->top_scores[i] == 0)
			break;
		mvwprintw(board->score_win.win, j++, 1, "%d", board->top_scores[i++]);
	}
	if (j < board->score_win.size_y)
	{
		wattron(board->score_win.win, A_REVERSE);
		mvwprintw(board->score_win.win, j++, 1, "%d", board->score);
		wattroff(board->score_win.win, A_REVERSE);
	}
	while  (j < board->score_win.size_y)
	{
		if (board->top_scores[i] == 0)
			break;
		mvwprintw(board->score_win.win, j++, 1, "%d", board->top_scores[i++]);

	}
	
	box(board->score_win.win, 0, 0);
	wrefresh(board->score_win.win);
}

void cleanup_ncurses(t_board *board)
{
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->tiles[i][j].win.win != NULL)
				delwin(board->tiles[i][j].win.win);
		}
	}

	if (board->score_win.win != NULL)
		delwin(board->score_win.win);
	if (stdscr != NULL)
		delwin(stdscr);
	endwin();
}

