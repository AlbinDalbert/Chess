
#include <iostream>
#include <vector>
#include "pieceMovements.h"



std::vector<pos> valid_moves_from(pos A) {

    std::vector<pos> posList;

    switch (abs(get_pos_status(A))) {
    case EMPTY:
        break;

    case PAWN:
        pawn_movement(&posList, A);
        break;

    case ROOK:
        rook_movement(&posList, A);
        break;

    case KNIGHT:
        knight_movement(&posList, A);
        break;

    case BISHOP:
        bishop_movement(&posList, A);
        break;

    case QUEEN:
        queen_movement(&posList, A);
        break;

    case KING:
        king_movement(&posList, A);
        break;

    default:
        break;
    }

    return posList;
}

bool if_enemy(pos A, pos B) {
    if (A.val > 0 && B.val < 0) {
        return true;
    }
    if (A.val < 0 && B.val > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool within_bounds(pos A) {
    if (A.row < ROWS && A.row >= 0) {
        if (A.col < COLS && A.col >= 0) {
            return true;
        }
    }
    return false;
}


void pawn_movement(std::vector<pos>* posList, pos A) {
    pos tempPos;
    //checks if A is a white pawn
    if (get_pos_status(A) > 0) {
        if (get_pos_status(A.row + 1, A.col) == EMPTY && A.row < ROWS) {
            tempPos.row = A.row + 1;
            tempPos.col = A.col;
            posList->push_back(tempPos);
        }
        if ((A.row == 1) && (get_pos_status(A.row + 2, A.col) == EMPTY)) {
            tempPos.row = A.row + 2;
            tempPos.col = A.col;
            posList->push_back(tempPos);
        }
        if (get_pos_status(A.row + 1, A.col + 1) < 0 && A.row + 1 < ROWS && A.col + 1 < COLS) {
            tempPos.row = A.row + 1;
            tempPos.col = A.col + 1;
            posList->push_back(tempPos);
        }
        if (get_pos_status(A.row + 1, A.col - 1) < 0 && A.row + 1 < ROWS && A.col - 1 >= 0) {
            tempPos.row = A.row + 1;
            tempPos.col = A.col - 1;
            posList->push_back(tempPos);
        }
    }
    //checks if A is a black pawn
    if (get_pos_status(A) < 0) {
        if (get_pos_status(A.row - 1, A.col) == EMPTY && A.row > 0) {
            tempPos.row = A.row - 1;
            tempPos.col = A.col;
            posList->push_back(tempPos);
        }
        if ((A.row == 7) && (get_pos_status(A.row - 2, A.col) == EMPTY)) {
            tempPos.row = A.row - 2;
            tempPos.col = A.col;
            posList->push_back(tempPos);
        }
        if (get_pos_status(A.row - 1, A.col - 1) < 0 && A.row - 1 < ROWS && A.col + 1 < COLS) {
            tempPos.row = A.row + 1;
            tempPos.col = A.col + 1;
            posList->push_back(tempPos);
        }
        if (get_pos_status(A.row - 1, A.col + 1) < 0 && A.row - 1 < ROWS && A.col - 1 >= 0) {
            tempPos.row = A.row - 1;
            tempPos.col = A.col - 1;
            posList->push_back(tempPos);
        }
    }
}

void rook_movement(std::vector<pos>* posList, pos A) {
    pos tempPos;
    for (int i = A.row + 1; i < ROWS; i++) {
        tempPos.row = i;
        tempPos.col = A.col;
        // checks if the pos is empty
        if (get_pos_status(i, A.col) == EMPTY) {
            posList->push_back(tempPos);
            // checks if the pos is a enemy
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            break;
        }
        // breaks the loop
        else {
            break;
        }
    }
    for (int i = A.row - 1; i >= 0; i--) {
        if (get_pos_status(i, A.col) == EMPTY) {
            tempPos.row = i;
            tempPos.col = A.col;
            posList->push_back(tempPos);
            // checks if the pos is a enemy
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            break;
            // breaks the loopelse 
        }
        else {

            break;
        }
    }
    for (int i = A.col + 1; i < COLS; i++) {
        if (get_pos_status(A.row, i) == EMPTY) {
            tempPos.row = A.row;
            tempPos.col = i;
            posList->push_back(tempPos);
            // checks if the pos is a enemy
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            break;
            // breaks the loopelse 
        }
        else {
            break;
        }
    }
    for (int i = A.col - 1; i >= 0; i--) {
        if (get_pos_status(A.row, i) == EMPTY) {
            tempPos.row = A.row;
            tempPos.col = i;
            posList->push_back(tempPos);
            // checks if the pos is a enemy
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            break;
            // breaks the loopelse 
        }
        else {
            break;
        }
    }
}

void knight_movement(std::vector<pos>* posList, pos A) {
    pos tempPos;
    tempPos.row = A.row + 2;
    tempPos.col = A.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 2;
    tempPos.col = A.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 2;
    tempPos.col = A.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 2;
    tempPos.col = A.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 1;
    tempPos.col = A.col + 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 1;
    tempPos.col = A.col + 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 1;
    tempPos.col = A.col - 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 1;
    tempPos.col = A.col - 2;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
}

void bishop_movement(std::vector<pos>* posList, pos A) {
    pos tempPos;
    bool dir1, dir2, dir3, dir4 = true;
    for (int i = 1; i < ROWS; i++) {
        tempPos.row = A.row + i;
        tempPos.col = A.col + i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir1) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir1 = false;
        }

        tempPos.row = A.row + i;
        tempPos.col = A.col - i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir2) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir2 = false;
        }

        tempPos.row = A.row - i;
        tempPos.col = A.col + i;
        if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY)) && within_bounds(tempPos) && dir3) {
            posList->push_back(tempPos);
        }
        else if (if_enemy(A, tempPos)) {
            posList->push_back(tempPos);
            dir3 = false;
        }

        tempPos.row = A.row - i;
        tempPos.col = A.col - i;
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

void queen_movement(std::vector<pos>* posList, pos A) {
    rook_movement(posList, A);
    bishop_movement(posList, A);
}

void king_movement(std::vector<pos>* posList, pos A) {
    pos tempPos;
    tempPos.row = A.row;
    tempPos.col = A.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row;
    tempPos.col = A.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 1;
    tempPos.col = A.col;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 1;
    tempPos.col = A.col;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 1;
    tempPos.col = A.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row + 1;
    tempPos.col = A.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 1;
    tempPos.col = A.col - 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
    tempPos.row = A.row - 1;
    tempPos.col = A.col + 1;
    if (((get_pos_status(tempPos.row, tempPos.col) == EMPTY) || if_enemy(A, tempPos)) && within_bounds(tempPos)) {
        posList->push_back(tempPos);
    }
}