#include "Game.h"
using namespace sf;

int setBoardToFEN(int board[], char FEN[]) 
{
	int p = 0;
	for (int i = 1; i <= 64; i++)
	{
		switch (FEN[p])
		{
		case '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8':

			for (int j = 0; j < ((int)FEN[j])-48; j++)
			{
				board[j] = 0;
				i++;
			}

		case 'r':
			board[i] = -2;
			break;
		case 'n':
			board[i] = -3;
			break;
		case 'b':
			board[i] = -4;
			break;
		case 'q':
			board[i] = -5;
			break;
		case 'k':
			board[i] = -6;
			break;
		case 'p':
			board[i] = -1;
			break;

		case 'R':
			board[i] = 2;
			break;
		case 'N':
			board[i] = 3;
			break;
		case 'B':
			board[i] = 4;
			break;
		case 'Q':
			board[i] = 5;
			break;
		case 'K':
			board[i] = 6;
			break;
		case 'P':
			board[i] = 1;
			break;

		case '/':
			if (i % 8 != 0) {
				return -1;
			}
			break;

		default:
			break;
		}
		p++;
	}
	return 0;
	
}