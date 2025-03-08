#include <iostream>
#include "game.h"

/**
 * Main entry point for the program.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 on successful execution, or 1 on error.
 */
int main(int argc, char *argv[]) 
{
  if (argc < 2) 
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::string input_filename = argv[1];
  
  try 
  {
    GameManager game;
    game.loadCharacters(input_filename);
    game.runBattle();
    game.printResults();
  } 
  catch (const std::exception &e) 
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
