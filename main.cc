#include "Game.h"

/**Creates a Game and runs it, starting the game
 * Then calls remove to clean up some
 *
 */

int main(/*int argc, char const *argv[]*/)
{

  Game game;

  game.run();
  game.remove();
  return 0;
}
