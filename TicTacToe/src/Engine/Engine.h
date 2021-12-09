#pragma once

#include "TicTacToe.h"

class TTTEngine
{
public:
	/* Constructor for the TicTacToe engine. */
	TTTEngine(TTTPlayer startingPlayer);
	/* Destructor for the TicTacToe engine. */
	~TTTEngine();

	/*
		Checks legality and validity of passed move.
		Returns true on valid move, false otherwise.
	*/
	bool CheckMove(TTTMove& move);

	/*
		This function is used to get best next move for current player for current position.
		It's generates all possible moves and then checks them using minimax algorithm to find best.
		Returns move with the best evaluation.
	*/
	TTTMove GetBestMove(int maxPly);

	/*
		Performs passed move and returns numerical code of game state after this move.
		The codes are as follows:
			0 - game is in play
			1 - circle won
			2 - cross won
			3 - draw
	*/
	int PerformMove(TTTMove move);

	/* Returns poiter to the internal board object. */
	TTTBoard* GetBoard();

private:
	/* Counts bits in given bitboard */
	int CountBitboard(uint16_t bitboard);
	/* Pops least significant bit of given bitboard and returns index of popped bit. */
	int PopBitboard(uint16_t* bitboard);

	/* Returns static evaluation of given board. */
	int EvaluatePosition(TTTBoard* board);
	/*
		The minimax algorithm implementation, which is used to find best moves in position.
		Uses alpha-beta pruning for performence and calls itself until the maxPly isn't equal to 0.
		Returns static evaluation of best move found.
	*/
	int Minimax(TTTBoard* position, int maxPly, int& alpha, int& beta, bool maximizing);

private:
	TTTBoard m_board;
	TTTPlayer m_player;
};