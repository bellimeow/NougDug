#ifndef TUNNEL_H
#define TUNNEL_H

#include "Block.h"

class Tunnel : public Block
{

    private:
        sf::Texture four_way;
        int current_texture{0};
        int rotation_value{0};

        void get_tunnel_type( int count );
        void check_two_way_type( std::array<std::array<Sprite*, 3>, 3> tunnels );
        void get_rotation( std::array<std::array<Sprite *, 3>, 3> tunnels );

    public:

        Tunnel(int depth);

        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite dirt_sprite) override ;
        void animate() override;

        sf::Texture get_sprite_sheet() override ;


        bool check_not_passable(std::string character);

        void get_tunnels( std::array<std::array<Sprite*, 3>, 3>);
};

#endif