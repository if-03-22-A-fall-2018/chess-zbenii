/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHIF
 * ---------------------------------------------------------
 * Exercise Number: 6
 * Title:			test_chess.c
 * Author:		Benjamin Besic
 * Due Date:		6.11.2018
 * ----------------------------------------------------------
 * Description:
 * Test functions for chess.
 * ----------------------------------------------------------
 */
#include "shortcut.h"
#include "test_chess.h"
#include "chess.h"

static ChessBoard chess_board;

static struct ChessPiece white_pawn = {White, Pawn};
static struct ChessPiece white_rook = {White, Rook};
static struct ChessPiece white_knight = {White, Knight};
static struct ChessPiece white_bishop = {White, Bishop};
static struct ChessPiece white_queen = {White, Queen};
static struct ChessPiece white_king = {White, King};

static struct ChessPiece black_pawn = {Black, Pawn};
static struct ChessPiece black_rook = {Black, Rook};
static struct ChessPiece black_knight = {Black, Knight};
static struct ChessPiece black_bishop = {Black, Bishop};
static struct ChessPiece black_queen = {Black, Queen};
static struct ChessPiece black_king = {Black, King};

TEST(test_is_piece)
{
	ASSERT_TRUE(is_piece(white_pawn, White, Pawn), "Piece is white pawn");
	ASSERT_TRUE(is_piece(white_rook, White, Rook), "Piece is white rook");
	ASSERT_TRUE(is_piece(white_knight, White, Knight), "Piece is white knight");
	ASSERT_TRUE(is_piece(white_bishop, White, Bishop), "Piece is white bishop");
	ASSERT_TRUE(is_piece(white_queen, White, Queen), "Piece is white queen");
	ASSERT_TRUE(is_piece(white_king, White, King), "Piece is white king");

	ASSERT_TRUE(is_piece(black_pawn, Black, Pawn), "Piece is black pawn");
	ASSERT_TRUE(is_piece(black_rook, Black, Rook), "Piece is black rook");
	ASSERT_TRUE(is_piece(black_knight, Black, Knight), "Piece is black knight");
	ASSERT_TRUE(is_piece(black_bishop, Black, Bishop), "Piece is black bishop");
	ASSERT_TRUE(is_piece(black_queen, Black, Queen), "Piece is black queen");
	ASSERT_TRUE(is_piece(black_king, Black, King), "Piece is black king");

	ASSERT_FALSE(is_piece(black_king, White, King), "Piece is not white king");
}

static void check_board_for_being_empty(struct TestCase* tc);
TEST(test_init_chess_board)
{
	init_chess_board(chess_board);
	check_board_for_being_empty(tc);

	chess_board[5][6].is_occupied = true;
	ChessPiece p = {White, Queen};
	chess_board[5][6].piece = p;

	init_chess_board(chess_board);
	check_board_for_being_empty(tc);
}

static void check_board_for_being_empty(struct TestCase* tc)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			ASSERT_FALSE(chess_board[i][j].is_occupied, "Chessboard not empty");
		}
	}
}

TEST(test_get_square)
{
	struct ChessSquare *square;
	int rank;
	int file;

	init_chess_board(chess_board);

	chess_board[4][2].is_occupied = true;
	chess_board[4][2].piece = black_rook;

	for (rank = 1; rank <= 8; rank++) {
		for (file = 'a'; file <= 'h'; file++) {
			square = get_square(chess_board, file, rank);
			ASSERT_TRUE(square != 0, "Square must not be 0");
			if (square) {
				if (file == 'c' && rank == 5) {
					ASSERT_TRUE(square->is_occupied, "Position c5 must be occupied");
					ASSERT_TRUE(is_piece(square->piece, Black, Rook), "Piece at c5 must be black rook");
				}
				else {
					ASSERT_FALSE(square->is_occupied, "Square must NOT be occupied");
				}
			}
		}
	}

	square = get_square(chess_board, 'i', 8);
	ASSERT_TRUE(square == 0, "Position out of range, 0 expected");
}

TEST(test_is_square_occupied)
{
	int rank;
	int file;

	init_chess_board(chess_board);

	for (rank = 1; rank <= 8; rank++) {
		for (file = 'a'; file <= 'h'; file++) {
			ASSERT_FALSE(is_square_occupied(chess_board, file, rank), "Chessboard not empty");
		}
	}

	chess_board[4][2].is_occupied = true;
	chess_board[4][2].piece = black_rook;

	ASSERT_TRUE(is_square_occupied(chess_board, 'c', 5), "Square must be occupied");
}

TEST(test_add_piece)
{
	bool add_ok;

	init_chess_board(chess_board);
	add_ok = add_piece(chess_board, 'a', 1, black_rook);

	ASSERT_TRUE(add_ok, "Adding black rook returned False though adding should be possible");
	ASSERT_TRUE(is_square_occupied(chess_board, 'a', 1), "Black rook is not placed properly");
	if (is_square_occupied(chess_board, 'a', 1)) {
		ASSERT_TRUE(is_piece(get_piece(chess_board, 'a', 1), Black, Rook), "Piece at a1 must be black rook");
	}

	add_ok = add_piece(chess_board, 'h', 8, white_rook);
	ASSERT_TRUE(add_ok, "Adding white rook returned False though adding is possible");
	ASSERT_TRUE(is_square_occupied(chess_board, 'h', 8), "White rook is not placed properly");
	if (is_square_occupied(chess_board, 'h', 8)) {
		ASSERT_TRUE(is_piece(get_piece(chess_board, 'h', 8), White, Rook), "Piece at h8 must be white rook");
	}

	add_ok = add_piece(chess_board, 'i', 8, white_rook);
	ASSERT_FALSE(add_ok, "Adding white_rook returned True though adding is impossible");

	add_ok = add_piece(chess_board, 'h', 9, white_rook);
	ASSERT_FALSE(add_ok, "Adding white_rook returned True though adding is impossible");
}

TEST(test_get_piece)
{
	init_chess_board(chess_board);
	add_piece(chess_board, 'c', 4, black_pawn);

	ASSERT_TRUE(is_piece(get_piece(chess_board, 'c', 4), Black, Pawn), "Piece at c4 must be black pawn");

	ASSERT_EQUALS(NoPiece, get_piece(chess_board, 'c', 5).type);

	ASSERT_EQUALS(NoPiece, get_piece(chess_board, 'i', 8).type);
	ASSERT_EQUALS(NoPiece, get_piece(chess_board, 'h', 9).type);
	ASSERT_EQUALS(NoPiece, get_piece(chess_board, 'i', 9).type);
}

TEST(test_setup_chess_board)
{
	File file;
	Rank rank;

	init_chess_board(chess_board);
	add_piece(chess_board, 'd', 4, white_pawn);

	setup_chess_board(chess_board);

	for (file = 'a'; file <= 'h'; file++) {
		ASSERT_TRUE(is_piece(get_piece(chess_board, file, 2), White, Pawn), "Rank 2 must be white");
		ASSERT_TRUE(is_piece(get_piece(chess_board, file, 7), Black, Pawn), "Rank 7 must be black");
	}

	ASSERT_TRUE(is_piece(get_piece(chess_board, 'a', 1), White, Rook), "a1 must be white rook");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'h', 1), White, Rook), "h1 must be white rook");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'b', 1), White, Knight), "b1 must be white knight");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'g', 1), White, Knight), "g1 must be white knight");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'c', 1), White, Bishop), "c1 must be white bishop");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'f', 1), White, Bishop), "f1 must be white bishop");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'd', 1), White, Queen), "d1 must be white queen");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'e', 1), White, King), "e1 must be white king");

	ASSERT_TRUE(is_piece(get_piece(chess_board, 'a', 8), Black, Rook), "a7 must be black rook");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'h', 8), Black, Rook), "h7 must be black rook");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'b', 8), Black, Knight), "b7 must be black knight");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'g', 8), Black, Knight), "g7 must be black knight");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'c', 8), Black, Bishop), "c7 must be black bishop");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'f', 8), Black, Bishop), "f7 must be black bishop");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'd', 8), Black, Queen), "d7 must be black queen");
	ASSERT_TRUE(is_piece(get_piece(chess_board, 'e', 8), Black, King), "e7 must be black king");

	for (file = 'a'; file <= 'h'; file++) {
		for (rank = 3; rank <= 6; rank++) {
			ASSERT_FALSE(is_square_occupied(chess_board, file, rank), "Ranks 3 to 6 must not be occupied");
		}
	}
}

TEST(test_remove_piece)
{
	bool remove_ok;

	init_chess_board(chess_board);
	add_piece(chess_board, 'a', 1, black_rook);
	ASSERT_TRUE(is_square_occupied(chess_board, 'a', 1), "black rook not placed properly");

	remove_ok = remove_piece(chess_board, 'a', 1);
	ASSERT_TRUE(remove_ok, "returned false though removing is possible");
	ASSERT_FALSE(is_square_occupied(chess_board, 'a', 1), "piece at a1 was not removed");

	remove_ok = remove_piece(chess_board, 'c', 2);
	ASSERT_FALSE(remove_ok, "returned true though removing is impossible");
}

TEST(test_squares_share_file)
{
	ASSERT_TRUE(squares_share_file('a', 1, 'a', 8), "Squares share file in a");
	ASSERT_TRUE(squares_share_file('h', 1, 'h', 8), "Squares share file in h");
	ASSERT_TRUE(squares_share_file('c', 3, 'c', 7), "Squares share file in c");

	ASSERT_FALSE(squares_share_file('a', 1, 'h', 1), "Squares DON'T share file in 1");
	ASSERT_FALSE(squares_share_file('a', 0, 'a', 7), "Squares DON'T share file because of invalid position");
}

TEST(test_squares_share_rank)
{
	ASSERT_TRUE(squares_share_rank('a', 1, 'h', 1), "Squares share rank in 1");
	ASSERT_TRUE(squares_share_rank('a', 8, 'h', 8), "Squares share rank in 8");
	ASSERT_TRUE(squares_share_rank('c', 3, 'f', 3), "Squares share rank in 3");

	ASSERT_FALSE(squares_share_rank('a', 1, 'a', 8), "Squares DON'T share rank in a");
	ASSERT_FALSE(squares_share_rank('a', 1, 'i', 1), "Squares DON'T share rank because of invalid position");
}

TEST(test_squares_share_diagonal)
{
	ASSERT_TRUE(squares_share_diagonal('a', 1, 'h', 8), "Squares share diagonal right up");
	ASSERT_TRUE(squares_share_diagonal('h', 1, 'a', 8), "Squares share diagonal left up");
	ASSERT_TRUE(squares_share_diagonal('a', 7, 'b', 8), "Squares share diagonal from a7 to b8");
	ASSERT_TRUE(squares_share_diagonal('f', 8, 'h', 6), "Squares share diagonal right down");
	ASSERT_TRUE(squares_share_diagonal('e', 5, 'b', 2), "Squares share diagonal left down");

	ASSERT_FALSE(squares_share_diagonal('c', 0, 'f', 3), "Squares DON'T share diagonal because of invalid position");
}

TEST(test_squares_share_knights_move)
{
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'd', 5), "Squares share knights move 11 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'f', 5), "Squares share knights move 1 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'c', 4), "Squares share knights move 10 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'g', 4), "Squares share knights move 2 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'c', 2), "Squares share knights move 8 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'g', 2), "Squares share knights move 4 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'd', 1), "Squares share knights move 7 o'clock");
	ASSERT_TRUE(squares_share_knights_move('e', 3, 'f', 1), "Squares share knights move 5 o'clock");
}

TEST(test_squares_share_pawns_move)
{
	ASSERT_TRUE(squares_share_pawns_move(White, NormalMove, 'a', 2, 'a', 4), "Squares share opening move for white pawn");
	ASSERT_TRUE(squares_share_pawns_move(Black, NormalMove, 'f', 7, 'f', 5), "Squares share opening move for black pawn");
	ASSERT_TRUE(squares_share_pawns_move(White, NormalMove, 'd', 2, 'd', 3), "Squares share normal move for white pawn from base line");
	ASSERT_TRUE(squares_share_pawns_move(Black, NormalMove, 'f', 7, 'f', 6), "Squares share normal move for black pawn from base line");
	ASSERT_TRUE(squares_share_pawns_move(White, NormalMove, 'e', 3, 'e', 4), "Squares share normal move for white pawn from arbitrary position");
	ASSERT_TRUE(squares_share_pawns_move(Black, NormalMove, 'c', 5, 'c', 4), "Squares share normal move for black pawn from arbitrary position");
	ASSERT_TRUE(squares_share_pawns_move(White, CaptureMove, 'b', 2, 'a', 3), "Squares share capture move for white pawn");
	ASSERT_TRUE(squares_share_pawns_move(White, CaptureMove, 'b', 2, 'c', 3), "Squares share capture move for white pawn");
	ASSERT_TRUE(squares_share_pawns_move(Black, CaptureMove, 'c', 6, 'b', 5), "Squares share capture move for black pawn");
	ASSERT_TRUE(squares_share_pawns_move(Black, CaptureMove, 'c', 6, 'd', 5), "Squares share capture move for black pawn");

	ASSERT_FALSE(squares_share_pawns_move(White, NormalMove, 'f', 7, 'f', 5), "Squares DON'T share backward move for white pawn");
	ASSERT_FALSE(squares_share_pawns_move(Black, NormalMove, 'a', 2, 'a', 4), "Squares DON'T share backward move for black pawn");
	ASSERT_FALSE(squares_share_pawns_move(White, NormalMove, 'e', 3, 'e', 5), "Squares DON'T share opening move for white pawn from arbitrary position");
	ASSERT_FALSE(squares_share_pawns_move(Black, NormalMove, 'g', 5, 'g', 3), "Squares DON'T share opening move for black pawn from arbitrary position");
	ASSERT_FALSE(squares_share_pawns_move(White, NormalMove, 'd', 1, 'd', 2), "Squares DON'T share white pawn to start from rank 1");
	ASSERT_FALSE(squares_share_pawns_move(Black, NormalMove, 'd', 8, 'd', 7), "Squares DON'T share black pawn to start from rank 7");
	ASSERT_FALSE(squares_share_pawns_move(White, CaptureMove, 'c', 4, 'd', 3), "Squares DON'T share backward capture move for white pawn");
	ASSERT_FALSE(squares_share_pawns_move(Black, CaptureMove, 'e', 4, 'd', 5), "Squares DON'T share backward capture move for black pawn");
}

TEST(test_squares_share_queens_move)
{
	ASSERT_TRUE(squares_share_queens_move('d', 1, 'd', 6), "Square share queens move up");
	ASSERT_TRUE(squares_share_queens_move('d', 6, 'g', 3), "Square share queens move right down");
	ASSERT_TRUE(squares_share_queens_move('g', 3, 'e', 1), "Square share queens move left down");
	ASSERT_TRUE(squares_share_queens_move('e', 1, 'h', 1), "Square share queens move right");
	ASSERT_TRUE(squares_share_queens_move('h', 1, 'a', 8), "Square share queens move left up");
	ASSERT_TRUE(squares_share_queens_move('a', 8, 'a', 3), "Square share queens move down");
	ASSERT_TRUE(squares_share_queens_move('h', 1, 'e', 4), "Square share queens move left up");
	ASSERT_TRUE(squares_share_queens_move('e', 4, 'b', 4), "Square share queens move left");
}

 TEST(test_squares_share_kings_move)
{
	ASSERT_TRUE(squares_share_kings_move('e', 1, 'e', 2), "Squares share kings move up");
	ASSERT_TRUE(squares_share_kings_move('e', 8, 'e', 7), "Squares share kings move down");
	ASSERT_TRUE(squares_share_kings_move('e', 1, 'f', 1), "Squares share kings move right");
	ASSERT_TRUE(squares_share_kings_move('e', 8, 'd', 8), "Squares share kings move left");
	ASSERT_TRUE(squares_share_kings_move('g', 5, 'h', 4), "Squares share kings move right down");
	ASSERT_TRUE(squares_share_kings_move('g', 5, 'h', 6), "Squares share kings move right up");
	ASSERT_TRUE(squares_share_kings_move('g', 5, 'f', 4), "Squares share kings move left down");
	ASSERT_TRUE(squares_share_kings_move('g', 5, 'f', 6), "Squares share kings move left up");
}
