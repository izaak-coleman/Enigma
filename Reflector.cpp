#include <iostream>
#include <fstream>

#include "errors.h"
#include "Exceptions.h"
#include "ErrorsHandle.h"
#include "Reflector.h"

using namespace std;

Reflector::Reflector( char *rfFileName )
{

  /* Error and format check file */
  Errors checkReflector; 
  checkReflector.noRepContFile( rfFileName, 'f' );



  /* Open given reflector file. */
  ifstream reflectorFile;
  reflectorFile.open( rfFileName );
  if( reflectorFile.fail() ){             // Throw error if cannot open
    throw FileOpenErrExptn( ERROR_OPENING_CONFIGURATION_FILE, rfFileName );
  }



  /* Initialize elements of reflectorMap, by convering the 
   * int values from given file into uppercase characters
   * and assign these characters to elements in @reflectorMap.
   * Each column contains a 'wired' pair of characters. */
  int contactOne;             // first value in 'wired' pair from file
  int contactTwo;             // second value in 'wired'  pair from file
  int pair = 0;
  while( !reflectorFile.eof() ){
    reflectorFile >> contactOne;
    reflectorFile >> contactTwo;
    if( !reflectorFile.eof() ){
      reflectorMap[pair][0] = (contactOne+65);  // +65 for u.case convert
      reflectorMap[pair][1] = (contactTwo+65);
      pair++;
    }
  }
}

char Reflector::mapInput( char input )
{
  /* Search @reflectorMap, pair by pair until 
   * @input is found. Upon finding this value 
   * return 'wired' pair. */
  for(int pair=0; pair < 13; pair++){           // loop through map

    if( reflectorMap[pair][0] == input ){       // if == to @input
      return reflectorMap[pair][1];             // return 'wired' value 
    }
    if( reflectorMap[pair][1] == input ){       // repeat for other row
      return reflectorMap[pair][0]; 
    }
  }
  return input;
}
