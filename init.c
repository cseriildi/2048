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
	update_score(board);
}

t_result init_score(t_board *board)
{
	if (SCORE_LIST_SIZE <= 0)
		return SCORE_LIST_SIZE_ERROR;
	int fd = open(SCORE_FILE, O_RDONLY | O_CREAT, 0644);
	if ((fd) == -1)
		return CANT_OPEN_FILE;
	
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
	return 0;
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
