#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector
{
/* Reflector class contains a mapping between uppercase alphabet characters.
The mapping, 'wires' two alphabet characters together. When a character
is input into @Reflector, the corresponding 'wired' contact is output.
When a character is encrypted by an enigma machine, the character should
pass through the reflector once; after the first passage through the
rotor array, and therefore before the character is passed back through
the rotor array. */

public:

  Reflector( char *rfFileName );
  /* Checks errors and format of given reflector
   * file, and loads the file values into @reflectorMap. */

  char mapInput( char input );
  /* Searches for the value 'wired' to the @input value
   * in @reflectorMap, and returns this value. */ 

private:
char reflectorMap[13][2];
  /* Array containing two rows. Each row contains half
   * the characters of the alphabet. The columns 
   * containing two characters are 'wired' together */
};

#endif
