#ifndef TUNNEL_H
#define TUNNEL_H

#include "Block.h"

class Tunnel : public Block
{

    /** Tunnel inherits from Block and represents the navigatable tunnels in
     * on the board.
     *
     * Unlike other blocks it handles an extra possible texture as well as
     * it's own rotation

    */
    private:
        sf::Texture four_way;/// Extra texture variable to handle four_way tunnels
        int current_texture { 17 }; /// Variable to handle the current texture to use, defaults to four way ( 17 )
        int rotation_value { 0 };  /// Rotation value of the tunnel, default to 0, i.e. no rotation

        /// Get what tunnel type to use. Takes integer for the number of adjacent tunnels.
        void get_tunnel_type ( int count );

        /// Handles two way tunnels. as there's two options. Takes array with pointers to adjacent tunnels
        void set_two_way_type( std::array<std::array<Sprite*, 3>, 3> tunnels );

        /// Sets the rotation. Takes array with pointers to adjacent tunnels
        void set_rotation( std::array<std::array<Sprite *, 3>, 3> tunnels );

    public:

        /// Constructor, takes the tunnels depth level as an integer
        explicit Tunnel ( int depth );

        /// Override of Sprite::draw, takes a window, position & sprite
        void draw ( sf::RenderWindow* window, int row, int column, sf::Sprite& tunnel_sprite ) override;

        /// Override of Sprite::animate, currently unused
        void animate () override;

        /// Override of Sprite::get_sprite_sheet. Gets the textures needed for tunnels.
        sf::Texture get_sprite_sheet () override ;

        /// Override of Sprite::check_not_passable, checks what may pass through tunnels
        bool check_not_passable ( std::string character ) const override;

        /// Takes array of adjacent blocks, and removes none tunnels, counting the tunnels in the meantime.
        void get_tunnels( std::array<std::array<Sprite*, 3>, 3> );
};

#endif