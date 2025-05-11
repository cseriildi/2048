#include "2048.h"

int get_power_of_two(int n)
{
    int power = 0;
    unsigned int tmp = (unsigned int)n;

	while (tmp > 1) {
        tmp >>= 1;
        power++;
    }

    return power;
}

void update_board(t_board *board)
{
	t_tile	tile;
	int		ascii_width;

	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			tile = board->tiles[i][j];
			wclear(tile.win.win);
			if (has_colors())
			{
				tile.win.color = ft_min(get_power_of_two(tile.number) + 1, NUMBER_OF_COLORS);
				wbkgd(tile.win.win, COLOR_PAIR(tile.win.color));
			}
			else
				box(tile.win.win, 0, 0);

			if (tile.number != 0)
			{
				if ((ascii_width = ascii_fits(&tile, board)) > 0)
				{
					wattron(tile.win.win, A_BOLD);
					print_ascii_centered(ascii_width, &tile, board);
					wattroff(tile.win.win, A_BOLD);
				}
				else
					print_centered_number(&tile.win, tile.win.size_y / 2, tile.number);
			}
			wrefresh(tile.win.win);
		}
	}
}

void update_score(t_board *board)
{
	wclear(board->score_win.win);
	//TODO: not show when y >= x

	unsigned int row = SCORE_PRINT_START;
	unsigned int max_row = board->score_win.size_y + MAX_TILE_PRINT_START;
	max_row -= (board->win || board->game_over) ? 2 : 0;

	wattron(board->score_win.win, A_BOLD); 
	print_centered(&board->score_win, row++, SCORE_TITLE);
	wattroff(board->score_win.win, A_BOLD); 

	unsigned int i = 0;
	while  (row < max_row && board->score < board->top_scores[i]
			&& board->top_scores[i] != 0)
		print_centered_number(&board->score_win, row++, board->top_scores[i++]);

	if (row < max_row)
	{
		wattron(board->score_win.win, A_REVERSE);
		print_centered_number(&board->score_win, row++, board->score);
		wattroff(board->score_win.win, A_REVERSE);
	}
	while  (row < max_row && board->top_scores[i] != 0)
		print_centered_number(&board->score_win, row++, board->top_scores[i++]);

	print_stats(board, row);

	wbkgd(board->score_win.win, COLOR_PAIR(ft_min(get_power_of_two(board->max_tile_value) + 1, NUMBER_OF_COLORS)));
	wrefresh(board->score_win.win);
}
