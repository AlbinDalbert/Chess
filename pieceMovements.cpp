
#include <iostream>
#include <vector>
#include "pieceMovements.h"

std::vector<int> Board;

std::vector<int> valid_moves_from(std::vector<int> inBoard, int origin) {
    Board = inBoard;

    std::vector<int> posList;

    switch (abs(origin)) {
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

bool if_enemy(int origin, int B) {
    if (origin > 0 && B < 0) {
        return true;
    }
    if (origin < 0 && B > 0) {
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
    if (origin > 0) {

        if (Board.at(origin - 8) == EMPTY && (origin - 8) > 0) {
            posList->push_back(origin - 8);
        }

        if (origin > 47 && origin < 56 && Board.at(origin - 16) == EMPTY) {
            posList->push_back(origin - 16);
        }

        if (if_enemy(origin, origin - 7) && (origin - 7) > 0) {
            posList->push_back(origin - 7);
        }

        if (if_enemy(origin, origin - 9) && (origin - 9) > 0) {
            posList->push_back(origin - 9);
        }
    }
    //checks if origin is a black pawn
    if (origin < 0) {

        if (Board.at(origin + 8) == EMPTY && (origin + 8) < 65) {
            posList->push_back(origin + 8);
        }

        if (origin > 7 && origin < 16 && Board.at(origin + 16) == EMPTY) {
            posList->push_back(origin + 16);
        }

        if (if_enemy(origin, origin + 7) && (origin + 7) < 65) {
            posList->push_back(origin + 7);
        }

        if (if_enemy(origin, origin + 9) && (origin + 9) < 65) {
            posList->push_back(origin + 9);
        }
    }
}

void rook_movement(std::vector<int>* posList, int origin) {

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

    for (int i = origin + 1; i < 8; i++) {
        LOOPCONTENT
    }

    for (int i = origin - 1; i >= 0; i--) {
        LOOPCONTENT
    }

    for (int i = origin; i < 64; i += 8) {
        LOOPCONTENT
    }

    for (int i = origin; i >= 0; i -= 8) {
        LOOPCONTENT
    }

}

void knight_movement(std::vector<int>* posList, int origin) {
    int tempPos;
    tempPos.row = origin.row + 2;
    tempPos.col = origin.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 2;
    tempPos.col = origin.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 2;
    tempPos.col = origin.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 2;
    tempPos.col = origin.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 1;
    tempPos.col = origin.col + 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 1;
    tempPos.col = origin.col + 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 1;
    tempPos.col = origin.col - 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 1;
    tempPos.col = origin.col - 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
}

void bishop_movement(std::vector<int>* posList, int origin) {
    int tempPos;
    bool dir1, dir2, dir3, dir4 = true;
    for (int i = 1; i < ROWS; i++) {
        tempPos.row = origin.row + i;
        tempPos.col = origin.col + i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir1) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir1 = false;
        }

        tempPos.row = origin.row + i;
        tempPos.col = origin.col - i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir2) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir2 = false;
        }

        tempPos.row = origin.row - i;
        tempPos.col = origin.col + i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir3) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir3 = false;
        }

        tempPos.row = origin.row - i;
        tempPos.col = origin.col - i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir4) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir4 = false;
        }

        if (!dir1 && !dir2 && !dir3 && dir4) {
            i = ROWS;
        }

    }
}

void queen_movement(std::vector<int>* posList, int origin) {
    rook_movement(posList, origin);
    bishop_movement(posList, origin);
}

void king_movement(std::vector<int>* posList, int origin) {
    int tempPos;
    tempPos.row = origin.row;
    tempPos.col = origin.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row;
    tempPos.col = origin.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 1;
    tempPos.col = origin.col;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 1;
    tempPos.col = origin.col;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 1;
    tempPos.col = origin.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row + 1;
    tempPos.col = origin.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 1;
    tempPos.col = origin.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = origin.row - 1;
    tempPos.col = origin.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
}