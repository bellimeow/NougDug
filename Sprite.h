#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

class Sprite
{
    protected:
        struct coordinate;
        sf::Clock animation_clock;
        std::string sprite_sheet_path;
        sf::Texture texture;
        std::vector<coordinate> sprite_position;

        struct coordinate
        {
            int x;
            int y;
        };

    public:
        Sprite();
        Sprite(const std::string &sprite_sheet_path); //implementera default konstruktor

        virtual void draw();
        virtual sf::Texture get_sprite_sheet( std::string path);
        virtual void animate() = 0;
        virtual void set_position(int row, int column) = 0;
};

#endif