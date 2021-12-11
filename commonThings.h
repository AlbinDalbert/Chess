#define EMPTY 0
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

#define ROWS 8
#define COLS 8

// int is used to be able to easy destinguish between white and black
// while still it being easy to check which peace it is
int liveBoard[ROWS][COLS] =
{{ 2, 3, 4, 6, 5, 4, 3, 2},
 { 1, 1, 1, 1, 1, 1, 1, 1},
 { 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0},
 { 0, 0, 0, 0, 0, 0, 0, 0},
 {-1,-1,-1,-1,-1,-1,-1,-1},
 {-2,-3,-4,-6,-5,-4,-3,-2}};

typedef struct pos {
  int row, col;
  int val = liveBoard[row][col];
}pos;

int get_pos_status(pos A);

int get_pos_status(int row, int col);