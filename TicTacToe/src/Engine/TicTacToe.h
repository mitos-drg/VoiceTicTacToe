#pragma once

#include <cstdint>

/* Set bitmasks for bitboards*/
extern uint16_t setMask[9];
/* Clear bitmasks for bitboards */
extern uint16_t clearMask[9];
/* Masks for win conditions */
extern uint16_t winMask[8];
/* Fields values for evaluation */
extern uint8_t fieldWeight[9];
/* The bit index table for gettings indices of bits in bitboards using de Bruijin technique*/
extern uint8_t bitTable[16];
/* 
	Since every bit board uses only 9 out of 16 bits its clamping mask.
	Also used to check whether the board is full.
*/
const uint16_t fullBoard = 0b111111111;

/* Enum class for possible players/fields states. */
enum class TTTPlayer : uint8_t
{
	Empty = 0, Circle = 1, Cross = 2, Invalid = 2
};

/* Enum class for all possible positions on board with special off board position. */
enum class TTTSquare : uint8_t
{
	TopLeft = 0,	Top = 1,	TopRight = 2,
	Left = 3,		Centre = 4,	Right = 5,
	BottomLeft = 6,	Bottom = 7,	BottomRight = 8,
	NoSquare = (uint8_t)-1
};

/* 
	The Tic-Tac-Toe internal move.
	Consists of moving player and field on which their pawn is to be set
*/
struct TTTMove
{
	TTTPlayer player;
	TTTSquare place;
};

/*
	Internal Tic-Tac-Toe playing board.
	Has 3 by 3 fields board for convienence and separated bitboards for both players.
*/
struct TTTBoard
{
	TTTPlayer fields[9];

	uint16_t crosses;
	uint16_t circles;

	/* Helper function to get all nonempty fields. */
	uint16_t occupied() { return crosses | circles; }
	/* Helper function to get all empty fields. */
	uint16_t freeFields() { return ((~(crosses | circles)) & fullBoard); }

	/* Perform move on this board. */
	TTTBoard& operator+= (const TTTMove& move);
};

/* The TTTBoard and TTTMove addition operator. */
TTTBoard operator+ (TTTBoard board, const TTTMove& move);
