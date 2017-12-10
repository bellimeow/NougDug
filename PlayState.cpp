//
// Created by isade842 on 12/5/17.
//

#include "PlayState.h"
#include <iostream>

std::string AbstractGameState::directory;
std::string AbstractGameState::level;

PlayState::PlayState( Game* game, sf::RenderWindow* window_ptr )
        : game{game}, window_ptr{window_ptr}
{
    directory = "/home/seblu114/TDP005/NougDug/";
    level = "level1.txt";
    path = directory + level;
    //load_game_board (")
    // board = new Board

}

int PlayState::get_player_lives()
{
    return 0;
}

void PlayState::player_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        board->player_action("up");
        std::cout << "Up!\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        board->player_action("down");
        std::cout << "Down!\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        board->player_action("left");
        std::cout << "Left!\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        board->player_action("right");
        std::cout << "Right!\n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        board->player_action("shoot");
        std::cout << "Shoot!\n";
    }
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        /board->player_action("place");
    }*/
}

void PlayState::set_high_score()
{

}

void PlayState::intro_sequence()
{

}

std::ifstream PlayState::load_game_board(std::string filename) {
    std::ifstream level_data;
    level_data.open(filename, std::ifstream::in);

    if ( level_data.fail() )
    {
        std::cerr << "Couldn't open file!\n";
    }
    else
    {

        level_data >> board_height >> board_width;
        std::cout << board_height << " " << board_width << "\n";

        return level_data;
    }
}

void PlayState::check_state(){
    if (won())
    {
        game->win = true;
        change_state();
    }
    else if (lose())
    {
        change_state();
    }
}

bool PlayState::won()
{
    //return board->enemy_count == 0;
    return true;
}

bool PlayState::lose()
{
    return current_player_lives == 0;
}

void PlayState::change_state()
{
    //game->change_state(Endstate* , 2);
    std::cout << "StateChange\n";
}

void PlayState::draw()
{
    sf::Texture text;

    if (!text.loadFromFile("/home/isade842/Documents/TDP005/NougDug/documents/Nougdug/deathp.png"))

    {
        std::cerr<< "gick inte att ladda, deathp.png";
    }
    sf::Sprite sprite;
    sprite.setPosition(sf::Vector2f(200, 150));
    sprite.setScale(sf::Vector2f(3, 3));

    sprite.setTexture(text);

    window_ptr->draw(sprite);
}

void PlayState::update()
{
    //std::cout << "Blah" << "\n";
}

void PlayState::initialize() {

    std::ifstream game_board{load_game_board (path)};
    std::ifstream* level_ptr{&game_board};
    PlayState* p{this};
    board = new Board(level_ptr, board_width, board_height, p);
    std::cout << "Init" << "\n";
}

void PlayState::play_again() {
    std::cout << "Blah" << "\n";
}

int PlayState::get_high_score() {
    return 0;
}



