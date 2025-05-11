#include "2048.h"

void	init_ascii_numbers(t_board *board)
{
	board->ascii_numbers[0][0] = "  ";
	board->ascii_numbers[0][1] = "/\\";
	board->ascii_numbers[0][2] = "\\/";
	board->ascii_numbers[0][3] = NULL;
	board->ascii_numbers[1][0] = "  ";
	board->ascii_numbers[1][1] = "/|";
	board->ascii_numbers[1][2] = " |";
	board->ascii_numbers[1][3] = NULL;
	board->ascii_numbers[2][0] = "_ ";
	board->ascii_numbers[2][1] = " )";
	board->ascii_numbers[2][2] = "/_";
	board->ascii_numbers[2][3] = NULL;
	board->ascii_numbers[3][0] = "_ ";
	board->ascii_numbers[3][1] = "_)";
	board->ascii_numbers[3][2] = "_)";
	board->ascii_numbers[3][3] = NULL;
	board->ascii_numbers[4][0] = "   ";
	board->ascii_numbers[4][1] = "|_|";
	board->ascii_numbers[4][2] = "  |";
	board->ascii_numbers[4][3] = NULL;
	board->ascii_numbers[5][0] = " _ ";
	board->ascii_numbers[5][1] = "|_ ";
	board->ascii_numbers[5][2] = " _)";
	board->ascii_numbers[5][3] = NULL;
	board->ascii_numbers[6][0] = " _ ";
	board->ascii_numbers[6][1] = "|_ ";
	board->ascii_numbers[6][2] = "|_)";
	board->ascii_numbers[6][3] = NULL;
	board->ascii_numbers[7][0] = "_ ";
	board->ascii_numbers[7][1] = " |";
	board->ascii_numbers[7][2] = " |";
	board->ascii_numbers[7][3] = NULL;
	board->ascii_numbers[8][0] = " _ ";
	board->ascii_numbers[8][1] = "(_)";
	board->ascii_numbers[8][2] = "(_)";
	board->ascii_numbers[8][3] = NULL;
	board->ascii_numbers[9][0] = " _ ";
	board->ascii_numbers[9][1] = "(_|";
	board->ascii_numbers[9][2] = " _|";
	board->ascii_numbers[9][3] = NULL;
}
