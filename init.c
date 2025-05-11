#include "2048.h"

void init_board(t_board *board)
{
	init_ascii_numbers(board);
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
	
	spawn_number(board);
	spawn_number(board);
	// board->tiles[0][0].number = 2;
	// board->tiles[0][1].number = 4;
	// board->tiles[0][2].number = 8;
	// board->tiles[0][3].number = 16;
	// board->tiles[0][4].number = 32;
	// board->tiles[1][0].number = 64;
	// board->tiles[1][1].number = 128;
	// board->tiles[1][2].number = 256;
	// board->tiles[1][3].number = 512;
	// board->tiles[1][4].number = 1024;
	// board->tiles[2][0].number = 2048;
	// board->tiles[2][1].number = 4096;
	// board->tiles[2][2].number = 8192;
	// board->tiles[2][3].number = 16384;
	// board->tiles[2][4].number = 32768;
	// board->tiles[3][0].number = 65536;
	// board->tiles[3][1].number = 131072;
	update_board(board);
	update_score(board);
}

static bool is_valid_score(char *score)
{
	for (int i = 0; score[i] != '\n'; i++)
	{
		if (i > 8 || !ft_isdigit(score[i]))
			return false;
	}
	return true;
}

t_result init_score(t_board *board)
{
	board->score_file = SCORE_FILE_4;
	if (board->size == 5)
		board->score_file = SCORE_FILE_5;
	if (SCORE_LIST_SIZE <= 0)
		return SCORE_LIST_SIZE_ERROR;
	int fd = open(board->score_file, O_RDONLY | O_CREAT, 0644);
	if ((fd) == -1)
		return CANT_OPEN_FILE;
	
	char *line = NULL;
	unsigned int score = 0;

	ft_memset(board->top_scores, 0, sizeof(board->top_scores));
	// ft_memcpy(board->top_scores, (unsigned int[SCORE_LIST_SIZE]){0}, sizeof(board->top_scores));
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_valid_score(line) == false)
		{
			free(line);
			continue;
		}
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
