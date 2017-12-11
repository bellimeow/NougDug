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
        //struct coordinate;
        //sf::Clock animation_clock;
        sf::Texture texture;
        //std::vector<coordinate> sprite_position;
        static std::map< std::string, sf::Texture*> sprite_sheets;

        /*struct coordinate
        {
            int x;
            int y;
        };*/

    public:
        Sprite();

        static const std::string sprite_sheet_path;

        virtual void draw(sf::RenderWindow* window_ptr, int row, int column, sf::Sprite sprite);
        virtual sf::Texture get_sprite_sheet();

        static void load_sprite_sheets();
        virtual sf::IntRect extract_texture_position(SpriteType sprite_type);

        virtual void animate();

        void set_position(int row, int column) ;
};

#endif