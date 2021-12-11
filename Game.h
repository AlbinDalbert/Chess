#ifndef GAME_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define WIDTH 640
#define HEIGHT 640
#define BOARD_SIZE 640
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
*			  BLACK
*	| 1| 2| 3| 4| 5| 6| 7| 8|
* 	| 9|10|11|12|13|14|15|16|
* 	|17|18|19|20|21|22|23|24|
* 	|25|26|27|28|29|30|31|32|
* 	|33|34|35|36|37|38|39|40|
* 	|41|42|43|44|45|46|47|48|
* 	|49|50|51|52|53|54|55|56|
* 	|57|58|59|60|61|62|63|64|
*			  WHITE
*/
int Board[];


/*
*	Class that handles the game
*/
class Game
{

private:
	//Variables
	//Window
	sf::Color darkSquare;
	sf::Color lightSquare;
	sf::Color squareOutline;

	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	//Mouse Position
	sf::Vector2i mousePosWin;

	// Board Objects
	sf::RectangleShape boardSquares[64];

	void initVar();
	void initWindow();
	void initBoard();

public:
	
	Game();
	virtual ~Game();

	bool running();

	void pollEvents();
	void updateMousePosition();
	void update();
	void render();
};

#endif // !GAME_H