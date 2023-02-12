#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

/*
 * 1 : PlayState
 * 2 : MenuState
 * 3 : EndState
 *
 * */
class AbstractGameState;

/** Game is the engine that handles all the states and tells each state what to do
 *  The game object contains the main loop and all states.
 */

class Game
{
    private:
        std::vector<AbstractGameState*> states; /// Vector to hold all states
        int window_width{ 256 };
        int window_height{ 288 };

    public:

        /// How much larger than the base size we want the window and all item in it to be
        static const unsigned int DISPLAY_SIZE_MULTIPLIER{ 3 };
        int current_state{}; /// Holds current state
        bool win { false }; /// Remember i the game was won or not for states other than playstate
        sf::RenderWindow window; /// Renderwindow to draw in

        /// Constructor
        Game();
        /// Destructor
        ~Game();

        /// Sets the window and starts the first state and enters the main loop
        void run();

        /// changes state to state_index
        void change_state( int state_index );

        /// Pushes a State to the vector
        void push_state( AbstractGameState* state );

        /// Calls current states update
        void update();

        /// Getters height and width
        int get_window_width() const;
        int get_window_height() const;

        /// Removes dynamically allocated states
        void remove();
};

#endif