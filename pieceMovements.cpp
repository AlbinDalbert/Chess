#include <iostream>
#include <vector>
#include "pieceMovements.h"

std::vector<int> Board;



bool if_enemy(int origin, int B) {
    if (Board.at(origin) > 0 && Board.at(B) < 0) {
        return true;
    }
    if (Board.at(origin) < 0 && Board.at(B) > 0) {
        return true;
    }
    else {
        return false;
    }
}

// return -1 outside of bound
// return 0 is edge
// return 1 inside but not edge

int is_edge(int pos) {
    if (pos < 0 || pos > 63) {
        return -1;
    }

    else if (pos < 9 || pos > 54) {
        return 0;
    }

    else if ((pos % 8) == 0 || (pos % 8) == 7) {
        return 0;
    }
    
    else {
        return 1;
    }
}


void pawn_movement(std::vector<int>* posList, int origin) {
    //checks if origin is a white pawn
    if (Board.at(origin) > 0) {

        if ((origin - 8) > 0) {
            if(Board.at(origin - 8) == EMPTY)
                posList->push_back(origin - 8);
        }

        if (origin > 47 && origin < 56) {
            if (Board.at(origin - 16) == EMPTY && Board.at(origin - 8) == EMPTY)
                posList->push_back(origin - 16);
        }

        if ((origin - 7) > 0) {
            if(if_enemy(origin, origin - 7))
                posList->push_back(origin - 7);
        }

        if ((origin - 9) > 0) {
            if(if_enemy(origin, origin - 9))
                posList->push_back(origin - 9);
        }
    }
    //checks if origin is a black pawn
    if (Board.at(origin) < 0) {

        if ((origin + 8) < 65) {
            if(Board.at(origin + 8) == EMPTY)
                posList->push_back(origin + 8);
        }

        if (origin > 7 && origin < 16) {
            if(Board.at(origin + 16) == EMPTY && Board.at(origin + 8) == EMPTY)
                posList->push_back(origin + 16);
        }

        if ((origin + 7) < 65) {
            if(if_enemy(origin, origin + 7))
                posList->push_back(origin + 7);
        }

        if ((origin + 9) < 65) {
            if(if_enemy(origin, origin + 9))
                posList->push_back(origin + 9);
        }
    }
}

void rook_movement(std::vector<int>* posList, int origin) {

#define LOOPCONTENT \
    std::cout << i << i%8 << "\n"; \
    if(i < 0 || i > 63) break; \
\
    if (Board.at(i) == EMPTY) { \
        posList->push_back(i); \
    } \
    else if (if_enemy(origin, i)) { \
        posList->push_back(i); \
        break; \
    } \
    else { \
        break; \
    }

    for (int i = origin + 1; (i % 8) > 0 && i < 64; i++) {
        LOOPCONTENT
    }

    for (int i = origin - 1; (i % 8) < 7 && i > 0; i--) {
        LOOPCONTENT
    }

    for (int i = origin + 8; i < 64; i += 8) {
        LOOPCONTENT
    }

    for (int i = origin - 8; i >= 0; i -= 8) {
        LOOPCONTENT
    }

}


void knight_movement(std::vector<int>* posList, int origin) {
    int knightOffsets[] = { -17, -15, -10,-6, 6, 10, 15, 17 };
    int pos;

    for (int i : knightOffsets)
    {
        pos = origin + i;
        if (pos >= 0 && pos < 64 && (Board.at(pos) == EMPTY || if_enemy(origin, pos))) {

            // this is on i 10 is special case for when offset could wrap around the board
            // example at the start when the knight is on 57, without this 47 will be valid
      /*      if (abs(abs(origin % 8) - abs(i % 8)) < 2) {
                posList->push_back(pos);
            }*/
           /* if (abs(i) == 10) {

            }
            else {
                posList->push_back(pos);
            }*/
            if (abs(abs(origin % 8) - abs((origin + i) % 8)) < 3) {
                posList->push_back(pos);
            }
            
        }
    }
}

void bishop_movement(std::vector<int>* posList, int origin) {
#define LOOPCONTENT \
    if (Board.at(i) == EMPTY) { \
        posList->push_back(i); \
    } \
    else if (if_enemy(origin, i)) { \
        posList->push_back(i); \
        break; \
    } \
    else { \
        break; \
    }

    for (int i = origin + 9; (i % 8) > 0 && i < 64; i += 9) {
        std::cout << i % 8 << "\n";
        std::cout << i % 8 << "\n";
        if (Board.at(i) == EMPTY) {

            posList->push_back(i);
        }
        else if (if_enemy(origin, i)) {

            posList->push_back(i);
            break;
        }
        else {

            break;
        }
    }

    for (int i = origin + 7; (i % 8) < 7 && i < 64; i += 7) {
        LOOPCONTENT
    }

    for (int i = origin - 9; (i % 8) < 7 && i > 0; i -= 9) {
        LOOPCONTENT
    }

    for (int i = origin - 7; (i % 8) > 0 && i > 0; i -= 7) {
        LOOPCONTENT
    }
}

void queen_movement(std::vector<int>* posList, int origin) {
    rook_movement(posList, origin);
    bishop_movement(posList, origin);
}

void king_movement(std::vector<int>* posList, int origin) {

    int kingOffsets[] = { -9, -8, -7,-1, 1, 7, 8, 9 };
    int pos;

    for (int i : kingOffsets)
    {
        pos = origin + i;
        if (pos >= 0 && pos < 64 && (Board.at(pos) == EMPTY || if_enemy(origin, pos))) {
            posList->push_back(pos);
        }
    }
}

std::vector<int> valid_moves_from(std::vector<int> inBoard, int origin) {
    Board = inBoard;

    std::vector<int> posList;

    switch (abs(Board.at(origin))) {
    case EMPTY:
        break;

    case PAWN:
        pawn_movement(&posList, origin);
        break;

    case ROOK:
        rook_movement(&posList, origin);
        break;

    case KNIGHT:
        knight_movement(&posList, origin);
        break;

    case BISHOP:
        bishop_movement(&posList, origin);
        break;

    case QUEEN:
        queen_movement(&posList, origin);
        break;

    case KING:
        king_movement(&posList, origin);
        break;

    default:
        break;
    }

    return posList;
}