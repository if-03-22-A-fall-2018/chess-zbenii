/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.h
 * Author:			P. Bauer
 * Due Date:		October 15, 2014
 * ----------------------------------------------------------
 * Description:
 * Basic chess functions.
 * ----------------------------------------------------------
 */
 #ifndef ___CHESS_H
 #define ___CHESS_H

#include <stdbool.h>

enum PieceType
{
  pawn,rook,queen,king,knight,bishop
};

enum PieceColor
{
  Black,White
};

struct ChessPiece
{
  enum PieceType piecetype;
  enum PieceColor color;
};

struct ChessSquare
{
  bool is_occupied;
  struct ChessPiece chesspiece;
};

typedef struct ChessSquare ChessBoard [8][8];
typedef char File;
typedef int Rank;

bool is_piece(struct ChessPiece chesspiece,enum PieceColor color,enum PieceType piecetype);
void init_chess_board(ChessBoard chess_board);
struct ChessSquare get_square(ChessBoard chess_board,File file,Rank rank);
bool is_square_occupied(Chessboard chess_board,File file, Rank rank);
bool add_piece(ChessBoard chess_board,File file, Rank rank,struct ChessPiece chesspiece);
struct ChessPiece get_piece(ChessBoard chess_board,File file,Rank rank);
void setup_chess_board(ChessBoard chess_board);
bool remove_piece(ChessBoard chess_board,File file,Rank rank);
bool squares_share_file(File file,Rank rank,File file2,Rank rank2);
bool squares_share_rank(File file,Rank rank,File file2,Rank rank2);
bool squares_share_diagonal(File file,Rank rank,File file2,Rank rank2);
bool squares_share_knights_move(File file,Rank rank,File file2,Rank rank2);
bool squares_share_queens_move(File file,Rank rank,File file2,Rank rank2);
bool squares_share_kings_move(File file,Rank rank,File file2,Rank rank2);

 #endif
