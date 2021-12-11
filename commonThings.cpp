#include "commonThings.h"

int get_pos_status(pos A) { 
  return liveBoard[A.row][A.col];
}
int get_pos_status(int row, int col) { 
  return liveBoard[row][col];
}