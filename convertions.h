#ifndef CONVERTIONS_H
#define CONVERTIONS_H


#include <vector>
#include <SFML/Graphics.hpp>

int setBoardToFEN(int board[], char FEN[]);

int mousePosToCell(sf::Vector2i mousePosWin);

void boardStateToSpritePos(std::vector<int> board, sf::Sprite pieces[], sf::RenderWindow* window);
#endif // !CONVERTIONS_H