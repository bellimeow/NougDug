#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include "SpritesType.h"

class Sprite
{
    protected:

        //sf::Clock animation_clock;
        sf::Texture texture;
        sf::Vector2i current_position;
        std::string i_am_a{"sprite"};

        static std::map< std::string, sf::Texture*> sprite_sheets;

    public:
        static const std::string sprite_sheet_path;

        Sprite();
        Sprite(std::string);

        virtual void draw(sf::RenderWindow* window_ptr, int row, int column, sf::Sprite sprite);

        virtual sf::Texture get_sprite_sheet();
        static void load_sprite_sheets();

        virtual sf::IntRect extract_texture_position(SpriteType sprite_type);
        virtual void animate();

        virtual bool check_passable( std::string ) = 0;

        virtual const std::string &get_i_am_a() const = 0;
        virtual void set_position(int y, int x) = 0;
};

#endif