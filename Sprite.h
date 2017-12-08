#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <map>

class Sprite
{
    protected:
        struct coordinate;
        sf::Clock animation_clock;
        sf::Texture texture;
        std::vector<coordinate> sprite_position;
        std::map< std::string, sf::Texture*> sprite_sheets;

        struct coordinate
        {
            int x;
            int y;
        };

    public:
        Sprite(); //implementera default konstruktor

        static std::string sprite_sheet_path{"/home/isade842/Documents/TDP005/NougDug/documents/Nougdug"};

        void draw();
        sf::Texture get_sprite_sheet( std::string path);
        void Sprite::load_sprite_sheets();

        virtual void animate();
};

#endif