#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class PlugBoard
{

/* @Plugboard class contains a mapping between uppercase alphabet characters.
 * This mapping is defined by a cline argument. When a character is input
 * into a @PlugBoard, the mapped character is output. In an enigma machine
 * characters should be passed through the same @PlugBoard mapping directly
 * after keyboard input, and directly before screen (light) output. */

public:
  PlugBoard( char *pbFileName );
  /* Error checks and format checks given file. 
   * Loads the file values into @plugBoardMap. */

  char mapInput( char input );
  /* Maps an input char to connected char based on
   * the given plugboard file. Outputs the connected
   * char.*/

private:
  char **plugBoardMap;
  /* Will point two a multi-dimensional array, containing the 
   * mapped pairs from the input file. */

  int mapLength;
  /* File length / 2*/
};

#endif
