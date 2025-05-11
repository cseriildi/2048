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

	// board->ascii_numbers[0] = (char *[]){
	// 	"  ",
	// 	"/\\",
	// 	"\\/",
	// 	NULL};
	// board->ascii_numbers[1] = (char *[]){
	// 	"  ",
	// 	"/|",
	// 	" |",
	// 	NULL};
	// board->ascii_numbers[2] = (char *[]){
	// 	"_ ",
	// 	" )",
	// 	"/_",
	// 	NULL};
	// board->ascii_numbers[3] = (char *[]){
	// 	"_ ",
	// 	"_)",
	// 	"_)",
	// 	NULL};
	// board->ascii_numbers[4] = (char *[]){
	// 	"   ",
	// 	"|_|",
	// 	"  |",
	// 	NULL};
	// board->ascii_numbers[5] = (char *[]){		
	// 	" _ ",
	// 	"|_ ",
	// 	" _)",
	// 	NULL};
	// board->ascii_numbers[6] = (char *[]){
	// 	" _ ",
	// 	"|_ ",
	// 	"|_)",
	// 	NULL};
	// board->ascii_numbers[7] = (char *[]){
	// 	"_ ",
	// 	" |",
	// 	" |",
	// 	NULL};
	// board->ascii_numbers[8] = (char *[]){
	// 	" _ ",
	// 	"(_)",
	// 	"(_)",
	// 	NULL};
	// board->ascii_numbers[9] = (char *[]){
	// 	" _ ",
	// 	"(_|",
	// 	" _|",
	// 	NULL};
	
	
	// = { {
	// 	"  ",
	// 	"/|",
	// 	" |",
	// 	NULL},
	// 	{
	// 	"_ ",
	// 	" )",
	// 	"/_",
	// 	NULL},
	// 	{
	// 	"_ ",
	// 	"_)",
	// 	"_)",
	// 	NULL},
	// 	{
	// 	"   ",
	// 	"|_|",
	// 	"  |",
	// 	NULL},
	// 	{
	// 	" _ ",
	// 	"|_ ",
	// 	" _)",
	// 	NULL},
	// 	{
	// 	" _ ",
	// 	"|_ ",
	// 	"|_)",
	// 	NULL},
	// 	{
	// 	"_ ",
	// 	" |",
	// 	" |",
	// 	NULL},
	// 	{
	// 	" _ ",
	// 	"(_)",
	// 	"(_)",
	// 	NULL},
	// 	{
	// 	" _ ",
	// 	"(_|",
	// 	" _|",
	// 	NULL},
	// 	{	
	// 	"  ",
	// 	"/\\",
	// 	"\\/",
	// 	NULL},
	// }};

	// switch (num)
	// {
	// case 1:
	// 	return ((char *[]){
	// 			"  ",
	// 			"/|",
	// 			" |",
	// 			NULL});
	// case 2:
	// 	return ((char *[]){
	// 			"_ ",
	// 			" )",
	// 			"/_",
	// 			NULL});
	// case 3:
	// 	return ((char *[]){
	// 			"_ ",
	// 			"_)",
	// 			"_)",
	// 			NULL});
	// case 4:
	// 	return ((char *[]){
	// 			"   ",
	// 			"|_|",
	// 			"  |",
	// 			NULL});
	// case 5:
	// 	return ((char *[]){
	// 			" _ ",
	// 			"|_ ",
	// 			" _)",
	// 			NULL});
	// case 6:
	// 	return ((char *[]){
	// 			" _ ",
	// 			"|_ ",
	// 			"|_)",
	// 			NULL});
	// case 7:
	// 	return ((char *[]){
	// 			"_ ",
	// 			" |",
	// 			" |",
	// 			NULL});

	// case 8:
	// 	return ((char *[]){
	// 			" _ ",
	// 			"(_)",
	// 			"(_)",
	// 			NULL});
	// case 9:
	// 	return ((char *[]){
	// 			" _ ",
	// 			"(_|",
	// 			" _|",
	// 			NULL});
	// case 0:
	// 	return ((char *[]){
	// 			"  ",
	// 			"/\\",
	// 			"\\/",
	// 			NULL});
	// default:
	// 	return (NULL);
	// }
}
