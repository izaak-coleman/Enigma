#ifndef ENIGMAMACHINE_H
#define ENIGMAMACHINE_H
#include <vector>

#include "IOPanel.h"
#include "PlugBoard.h"
#include "Reflector.h"
class Rotor;


/* Class EnigmaMachine is a cypher class. It is able to encrypt characters
 * passed to it via stdinput. Files passed in the command line are
 * required to configure the enigma machine. 
 * Usage ./enigma <plugboard> <reflector> <rotor> ... <rotorconfig>*/
class EnigmaMachine
{
public:
  EnigmaMachine( int argc, char **argv );
  /* Constructor initializes classes PlugBoard, 
     Rotor, IOPanel, Reflector. 
     Files from **argv are passed to the various classes
     and the data is loaded into these classes. 
     After constructor call, machine is fully assembled
     and ready to take user input */

  void encryptCharacter();
  /* Passes a character through the engima machine, either encytpting
     or decrypting the character */

private:
  std::vector< Rotor > rotorArray;
  /* Will contain the array of rotors, configured by the rotor arrays input
   * from the user */

  PlugBoard plugBoard;
  
  IOPanel userIO;
  
  Reflector reflector;

  int numberOfRotors;
  /* Contains the count of the number of rotors.*/

};

#endif
