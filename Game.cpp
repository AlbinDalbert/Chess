
#ifndef GAME_H

#include "Game.h"
#endif // !GAME_H


void Game::initVar()
{
	this->window = nullptr;
    this->darkSquare = sf::Color::Color(143, 117, 219);
    this->lightSquare = sf::Color::Color(197, 187, 225);
    this->squareOutline = sf::Color::Color(109, 89, 168);

}

void Game::initWindow()
{
	this->videomode.height = HEIGHT;
	this->videomode.width = WIDTH;

	this->window = new sf::RenderWindow(this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}

void Game::initBoard() {
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

// Constructors / Destructors
Game::Game()
{
	this->initVar();
	this->initWindow();
    this->initBoard();
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
}

void Game::update()
{

    this->pollEvents();

    //Update mouse position
    this->updateMousePosition();

}

void Game::render()
{
    this->window->clear();

    //Draw the board (keep the board first after clear as this is the background)
    for (int i = 0; i < 64; i++)
    {
        this->window->draw(this->boardSquares[i]);
    }
 

    this->window->display();

}


