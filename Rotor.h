#ifndef ROTOR_H
#define ROTOR_H

const int SIZE_OF_ALPHABET = 26;

/* Objects of the Rotor class form the main scrambling unit of the enigma
 * machine. Rotors are organized into an array where each rotor takes an 
 * input at one of 26 positions and maps this input to another position.
 * Rotors contain notches. The position of the notch is at one of the 26
 * values. When one of these values enters the zero position on one rotor
 * object, this causes the rotor object to the 'left' to rotate. This 
 * alters the mapped positions */

class Rotor
{
public:

  Rotor( int leftMost, int rotorPosition, char *rotFilename, char *posFileName );
  /* Loads the rotor file into @rotorMap and @notches.
   * Sets the value of @rotorOffset to the rotors
   * corresponding .pos value */

  char mapInput( char direction );
  /* Takes the rotors input and maps it to its
   * paired output + @rotorOffset. @direction sets whether the character
   * is passing towards the reflector, entering the rotor from the upper 
   * position 'U'. Or entering the rotor, passing away from the reflector
   * 'D'. */

  void rotateRotor();
  /* If only one rotor is present in system, 
     this rotate function is used to rotate rotor*/
  
  void rotateRotor( Rotor &leftRot );
  /* Used in a multi-rotor system. Has the ability to rotate other
   * @leftRot if this rotors notches are in position*/
  
  void recalcMappedPosition();
  /*Function 'moves' the wirings by a value of @rotorOffset,
   * and the wirings are then used to recalculate each of the 
   * mapped posiitons*/

  void loopRotorOffset();
  /* If @rotorOffset reaches 26, reset it to 0. */

  char inputValue;
  /* Holds the last input value given to the rotor */

private:

  bool triggered;

  char *notches;
  /* Elements are the notching positions for the rotor */

  char rotorMap[SIZE_OF_ALPHABET][2];
  /* Holds the absolute position, rototMap[x][0] and
   * the mapped position rotorMap[x][1]. */

  int rotorWiring[SIZE_OF_ALPHABET];

  int sizeOfFile;
  /* Holds the total number of values in the rotor file*/

  int rotorOffset;
  /* Current position of rotor, relative to absolute 'A' */

  int rotorSlot;
  /* @rotorSlot== 1 if rightmost, @rotorSlot == 2
   * if leftmost rotor */
};

#endif


