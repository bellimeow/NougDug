//
// Created by isade842 on 12/5/17.
//

#include "PlayState.h"
#include "Score.h"
#include <iostream>

PlayState::PlayState( Game* game, sf::RenderWindow* window_ptr )
        : game{game}, window_ptr{window_ptr}
{
    //directory = "./";
    /*level*/ path = "level" + std::to_string(level_num ) + ".txt";
    //path = directory + level;
}

PlayState::~PlayState()
{
    delete(board);
}

void PlayState::player_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        board->player_action("up");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        board->player_action("down");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        board->player_action("left");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        board->player_action("right");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        board->player_action("shoot");
    }
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        /board->player_action("place");
    }*/
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

        return level_data;
    }
}

void PlayState::create_high_score()
{
    std::string high_score = std::to_string(get_high_score());

    sf::Font font;
    if (!font.loadFromFile("textures/lilliput steps.ttf"))
    {
        std::cerr << "Couldn't load font!" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("HIGH SCORE " + high_score);
    text.setCharacterSize(25);
    text.setColor(sf::Color::White);
    text.setPosition(5 + Game::DISPLAY_SIZE_MULTIPLIER,5);

    window_ptr->draw(text);
}

bool check_next_level (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void PlayState::display_player_lives()
{
    sf::Vector2f numbers_position{board_width * 16 * Game::DISPLAY_SIZE_MULTIPLIER -
                                          (Game::DISPLAY_SIZE_MULTIPLIER * 50), 2};
    int position_multiplier{Game::DISPLAY_SIZE_MULTIPLIER};

    for (int i = 1; i <= current_player_lives; ++i)
    {
        sf::Texture* t_ptr = sprite_sheets["lives"];
        sf::Sprite sprite_life;
        sprite_life.setTexture(*t_ptr);
        sprite_life.setTextureRect(sf::IntRect{
                Sprite::extract_texture_position(SpriteType::HEART)});

        sprite_life.setPosition((numbers_position.x + position_multiplier),
                                numbers_position.y);
        sprite_life.setScale(3, 3);
        position_multiplier += 17;
        numbers_position.x += 25;

        window_ptr->draw(sprite_life);
    }
}

void PlayState::check_state(){
    if (won())
    {
        game->win = true;

        if ( check_next_level( "level" + std::to_string( level_num + 1 ) + ".txt" ) )
        {
            ++level_num;

             path = "level" + std::to_string( level_num ) + ".txt";

            delete(board);
            initialize();
        }
        else
        {
            level_num = 1;
            change_state();
        }
    }
    else if (lose())
    {
        game->win = false;
        level_num = 1;
        change_state();
    }
}

bool PlayState::won()
{
    return board->get_enemy_count() == 0;
}

bool PlayState::lose()
{
    return current_player_lives == 0;
}

void PlayState::change_state()
{
    delete(board);
    game->change_state(2);
}

void PlayState::draw()
{
    board->draw();
}

void PlayState::update()
{
    board->update();
    check_state();
}

void PlayState::initialize() {

    std::ifstream game_board{load_game_board (path)};
    std::ifstream* level_ptr{&game_board};
    PlayState* p{this};
    board = new Board(level_ptr, board_width, board_height, p, window_ptr);
}

void PlayState::play_again() {
    std::cout << "Blah" << "\n";
}

void PlayState::set_high_score(int score)
{
    AbstractGameState::high_score += score;
}






