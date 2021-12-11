#include "Game.h"

std::vector<pos> valid_moves_from(pos A);

bool if_enemy(pos A, pos B);

bool within_bounds(pos A);

void pawn_movement(std::vector<pos>* posList, pos A);

void rook_movement(std::vector<pos>* posList, pos A);

void knight_movement(std::vector<pos>* posList, pos A);

void bishop_movement(std::vector<pos>* posList, pos A);

void queen_movement(std::vector<pos>* posList, pos A);

void king_movement(std::vector<pos>* posList, pos A);