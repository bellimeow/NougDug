#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <fstream>
#include "Character.h"

class Player : public Character
{
    private:
        //const int lives{3};
        //const int step{1};

    public:
        bool can_shoot{true};
        bool invulnerable{false};

        Player();
        void feed_nougat();
        void animate();
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite &player_sprite);
        void move(std::string direction);

        const int get_lives() const;
        const int get_step() const;
        int get_current_x() const;
        int get_current_y() const;

        sf::Texture get_sprite_sheet() override;

        bool check_not_passable(std::string) override;
};

#endif