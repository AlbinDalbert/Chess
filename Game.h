#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "pieceMovements.h"
#include "convertions.h"
#define WIDTH 480
#define HEIGHT 480
#define BOARD_SIZE 480
#define CELL_SIZE (BOARD_SIZE  / 8)


#define EMPTY 0
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

/*
* the chess board is a one dimetional array
* where every cell is a square in the order
* documented in the figure below
*/



/*
*	Class that handles the game
*/
class Game
{

private:
	//Variables

/*
*			  BLACK
*	| 0| 1| 2| 3| 4| 5| 6| 7|
* 	| 8| 9|10|11|12|13|14|15|
* 	|16|17|18|19|20|21|22|23|
* 	|24|25|26|27|28|29|30|31|
* 	|32|33|34|35|36|37|38|39|
* 	|40|41|42|43|44|45|46|47|
* 	|48|49|50|57|52|53|54|55|
* 	|56|57|58|59|60|61|62|63|
*			  WHITE
*/
	std::vector<int> Board;

	bool lock_click; //bool used to detect only a click
	int pieceSelected;
	std::vector<int> validMoves;
	sf::Color darkSquare;
	sf::Color lightSquare;
	sf::Color squareOutline;
	sf::Color lightSelectedSquare;
	sf::Color darkSelectedSquare;
	sf::Color possibleSquareMoves;
	sf::Texture textures[12];

	//Window

	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	//Mouse Position
	sf::Vector2i mousePosWin;
	sf::Vector2f mousePosView;

	// Board Objects
	sf::RectangleShape boardSquares[64];
	sf::Sprite pieces[12];

	void initVar();
	void initWindow();
	void initBoard();
	void initSprites();
	void redrawSelectedSquare(int mousepos);
	std::vector<int> drawPossibleMoves(int mousepos);

public:
	
	Game();
	virtual ~Game();

	bool running();
	std::vector<int> getBoardVector();
	void pollEvents();
	void updateMousePosition();
	void updateBoard();
	void updatePiecesOnBoard();
	void update();
	void render();
};

#endif // !GAME_H