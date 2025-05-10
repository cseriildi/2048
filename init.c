#include "2048.h"
#include <fcntl.h>

void init_board(t_board *board)
{
	srand(time(NULL));
	for (int x = 0; x < board->size; x++)
	{
		for (int y = 0; y < board->size; y++)
		{
			board->tiles[y][x].number = 0;
			board->tiles[y][x].merged = false;
		}
	}
	board->empty_tiles = board->size * board->size;
	board->game_over = false;
	board->spawn = true;
	spawn_number(board);
	board->spawn = true;
	spawn_number(board);
	update_board(board);
}

int init_score(t_board *board)
{
	if (SCORE_LIST_SIZE <= 0)
		return 0;
	int fd = open(SCORE_FILE, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		//TODO: print later
		ft_putstr_fd("Can't open file: " SCORE_FILE, fd);
		return 1;
	}
	char *line = NULL;
	unsigned int score = 0;
	// either of those lines fixes it
	ft_memset(board->top_scores, 0, sizeof(board->top_scores));
	// ft_memcpy(board->top_scores, (unsigned int[SCORE_LIST_SIZE]){0}, sizeof(board->top_scores));
	while ((line = get_next_line(fd)) != NULL)
	{
		//TODO: check the number? only digits and max 6 digits
		score = ft_atoi(line);
		int i = 0;
		while (i < SCORE_LIST_SIZE && board->top_scores[i] >= score)
			i++;
		if (i < SCORE_LIST_SIZE)
		{
			unsigned int tmp1 = board->top_scores[i];
			unsigned int tmp2;
			for (int j = i; j < SCORE_LIST_SIZE - 1; j++)
			{
				tmp2 = board->top_scores[j + 1];
				board->top_scores[j + 1] = tmp1;
				tmp1 = tmp2;
			}
			board->top_scores[i] = score;

		}
		free(line);
	}
	close(fd);
	update_score(board);
	return 0;
}

int write_score_to_file(t_board *board)
{
	int fd = open(SCORE_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		//TODO: print error after closing ncurses
		return 1;
	}
	ft_putnbr_fd(board->score, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return 0;
}
