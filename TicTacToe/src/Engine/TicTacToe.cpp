#include "TicTacToe.h"

uint16_t setMask[9] =
{
	0b0000000000000001, 0b0000000000000010, 0b0000000000000100,
	0b0000000000001000, 0b0000000000010000, 0b0000000000100000,
	0b0000000001000000, 0b0000000010000000, 0b0000000100000000
};
uint16_t clearMask[9] =
{
	0b1111111111111110, 0b1111111111111101, 0b1111111111111011,
	0b1111111111110111, 0b1111111111101111, 0b1111111111011111,
	0b1111111110111111, 0b1111111101111111, 0b1111111011111111
};
uint16_t winMask[8] =
{
	0b000000111,		// 0 1 2
	0b001001001,		// 0 3 6
	0b100010001,		// 0 4 8
	0b010010010,		// 1 4 7
	0b000111000,		// 3 4 5
	0b001010100,		// 2 4 6
	0b100100100,		// 2 5 8
	0b111000000			// 6 7 8
};
uint8_t fieldWeight[9] =
{
	3, 1, 3,
	1, 4, 1,
	3, 1, 3
};
uint8_t bitTable[16] =
{
	/*	0, 1, 8, 2, 6,  9, 3, 11, 15, 7, 5, 10, 14, 4, 13, 12 */
		0, 1, 8, 2, 6, (uint8_t)-1, 3, (uint8_t)-1, (uint8_t)-1, 7, 5,
        (uint8_t)-1, (uint8_t)-1, 4, (uint8_t)-1, (uint8_t)-1
};

TTTBoard& TTTBoard::operator+= (const TTTMove& move)
{
	fields[(uint8_t)move.place] = move.player;

	if (move.player == TTTPlayer::Circle)
		circles |= setMask[(uint8_t)move.place];
	else
		crosses |= setMask[(uint8_t)move.place];

	return *this;
}

TTTBoard operator+(TTTBoard result, const TTTMove& move)
{
	return result += move;
}
