
#ifndef GAME_H

#include "Game.h"
#endif // !GAME_H


void Game::initVar()
{
	this->window = nullptr;
    this->darkSquare = sf::Color::Color(143, 117, 219);
    this->lightSquare = sf::Color::Color(197, 187, 225);
    this->squareOutline = sf::Color::Color(109, 89, 168);
    this->lightSelectedSquare = sf::Color::Color(223, 88, 67);
    this->darkSelectedSquare = sf::Color::Color(218, 30, 1);
    this->lock_click = false;
}

void Game::initWindow()
{
	this->videomode.height = HEIGHT;
	this->videomode.width = WIDTH;

	this->window = new sf::RenderWindow(this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}


/*
* initialises the squares that makes up the board.
*/
void Game::initBoard() 
{
    this->Board.assign({-2,-3,-4,-5,-6,-4,-3,-2,
                    -1,-1,-1,-1,-1,-1,-1,-1,
                    0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,
                    1,1,1,1,1,1,1,1,
                    2,3,4,5,6,4,3,2 });

    int row = 0;
    for (int i = 0; i < 64; i++) {

        if (((i*CELL_SIZE) % (BOARD_SIZE) == 0) && i != 0) {
            row++;
        }
        this->boardSquares[i].setPosition((i*(CELL_SIZE))%BOARD_SIZE, row * (CELL_SIZE));
        this->boardSquares[i].setSize(sf::Vector2f(((float)BOARD_SIZE / 8), ((float)BOARD_SIZE / 8)));

        if ((row % 2) == 0)
        {
            if ((i % 2) == 0) {
                this->boardSquares[i].setFillColor(lightSquare);
            }
            else
            {
                this->boardSquares[i].setFillColor(darkSquare);
            }
        }
        else 
        {
            if ((i % 2) == 1) {
                this->boardSquares[i].setFillColor(lightSquare);
            }
            else
            {
                this->boardSquares[i].setFillColor(darkSquare);
            }
        }

        this->boardSquares[i].setOutlineColor(squareOutline);
        this->boardSquares[i].setOutlineThickness(1.f);
    }
}

void Game::initSprites()
{
    float scale = 1;
    int index = 0;

    this->textures[index].loadFromFile("textures/White-King.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-King.png");
    index++;
    this->textures[index].loadFromFile("textures/White-Queen.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-Queen.png");
    index++;
    this->textures[index].loadFromFile("textures/White-Bishop.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-Bishop.png");
    index++;
    this->textures[index].loadFromFile("textures/White-Knight.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-Knight.png");
    index++;
    this->textures[index].loadFromFile("textures/White-Rook.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-Rook.png");
    index++;
    this->textures[index].loadFromFile("textures/White-Pawn.png");
    index++;
    this->textures[index].loadFromFile("textures/Black-Pawn.png");
    index++;

    for (int i = 0; i < 12; i++) {
        this->pieces[i].setTexture(this->textures[i]);
        this->pieces[i].scale(scale, scale);

    }
    
//    for (int i = 0; i < 6; i++) 
//    {
//
//        for (int j = 0; j < 2; j++) 
//        {
////            if (!this->textures[index].loadFromFile("textures/pieces.png")) {
//            /*if (!this->textures[index].loadFromFile("textures/pieces.png", sf::IntRect(i*314, j*302, 314, 302))) {
//                std::cout << "error loading texture file\n";
//            }*/

//            
//        }
//
//    }
    
}

// Constructors / Destructors
Game::Game()
{
	this->initVar();
	this->initWindow();
    this->initBoard();
    this->initSprites();
}

Game::~Game()
{
	delete this->window;
}


//Accessors

bool Game::running()
{
	return this->window->isOpen();
}

//Functions

void Game::pollEvents() {

    //Event Polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
            break;
        }
    }

}

void Game::updateMousePosition()
{
    this->mousePosWin = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWin);
}

/*
*   Updates the the board. 
*   listens for mouse clicks on it and updates the selected square
*   There is also a locking mechanism that locks the listener until the butten is pressed again
*/
void Game::updateBoard() {
    
    // listen for click

    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (ev.mouseButton.button == sf::Mouse::Left && lock_click != true) //specifies
        {
            //execute the click here
            std::cout << "click on cell " << mousePosToCell(mousePosWin) << "\n";
            redrawSelectedSquare(mousePosToCell(mousePosWin)-1);
            lock_click = true;
            
        }
    }
    //unlocks the button
    if (ev.type == sf::Event::MouseButtonReleased) 
    {
        if (ev.mouseButton.button == sf::Mouse::Left) 
        {
            
            lock_click = false;
        }
    }

}

void Game::updatePiecesOnBoard() {

    boardStateToSpritePos(this->Board, this->pieces, this->window);

}

void Game::update()
{

    this->pollEvents();

    //Update mouse position
    this->updateMousePosition();
    updateBoard();
    

}

void Game::render()
{
    this->window->clear();

    //Draw the board (keep the board first after clear as this is the background)
    for (int i = 0; i < 64; i++)
    {
        this->window->draw(this->boardSquares[i]);
    }

    updatePiecesOnBoard();
    //for (int i = 0; i < 12; i++) 
    //{
    //    this->window->draw(this->pieces[i]);
    //}

    this->window->display();

}

void Game::redrawSelectedSquare(int mousepos) {
    

    int row = 0;
    for (int i = 0; i < 64; i++) {

        if (((i * CELL_SIZE) % (BOARD_SIZE) == 0) && i != 0) {
            row++;
        }
        //this->boardSquares[i].setPosition((i * (CELL_SIZE)) % BOARD_SIZE, row * (CELL_SIZE));
        //this->boardSquares[i].setSize(sf::Vector2f(((float)BOARD_SIZE / 8), ((float)BOARD_SIZE / 8)));

        if ((row % 2) == 0)
        {   
            if (mousepos == i && (i % 2) == 0) 
            {
                this->boardSquares[i].setFillColor(lightSelectedSquare);
            }
            else if (mousepos == i) 
            {
                this->boardSquares[i].setFillColor(darkSelectedSquare);
            }
            else if ((i % 2) == 0) 
            {
                this->boardSquares[i].setFillColor(lightSquare);
            }
            else
            {
                this->boardSquares[i].setFillColor(darkSquare);
            }
        }
        else
        {
            if (mousepos == i && (i % 2) == 1)
            {
                this->boardSquares[i].setFillColor(lightSelectedSquare);
            }
            else if (mousepos == i)
            {
                this->boardSquares[i].setFillColor(darkSelectedSquare);
            }
            else if ((i % 2) == 1) {
                this->boardSquares[i].setFillColor(lightSquare);
            }
            else
            {
                this->boardSquares[i].setFillColor(darkSquare);
            }
        }

        this->boardSquares[i].setOutlineColor(squareOutline);
        this->boardSquares[i].setOutlineThickness(1.f);
    }
}


