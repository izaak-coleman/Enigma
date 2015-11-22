#include <iostream>
#include <fstream>

#include "errors.h"
#include "Errorshandle.h"
#include "Exceptions.h"
#include "Rotor.h"


Rotor::Rotor( int leftMost, int rotorPosition, char *rotFileName, 
  char *posFileName )
  :rotorSlot(rotorPosition)
{

  /* Check errors and format of rotor file */
  Errors checkRotor;
  checkRotor.noRepContFile( rotFileName, 'r' );



  /* Set @rotorOffset for this rotor. Each rotors ID is given
   * by @rotorPosition. @rotorPosition is used to read in the
   * correct rotor configuration from the configuration file. */
  ifstream posFile;
  posFile.open( posFileName );
  for( int i=0; i < leftMost; i++ ){    // loop through file 
    posFile >> rotorOffset;
    if( !posFile.eof() ){
      if( i == leftMost ){       // assign value corresponding to rotor ID 
        break;
      }
    }
  }
  posFile.close();



  /* Set rotor trigger to false */
  triggered = false;



  /* Count total number of values in rotor file. This allows 
   * the size of the notches array to be defined */
  ifstream rotFile;
  rotFile.open( rotFileName );            // open the rotor file

  sizeOfFile = 0;                         // set to zero
  int storage;
  while( !rotFile.eof() ){
    rotFile >> storage;
    if( !rotFile.eof() ){
      sizeOfFile++;
    }
  }
  rotFile.clear();
  rotFile.seekg(0);                       // return filestream to start of file



  /* Declare size of notches array */
  notches = new char[ sizeOfFile - SIZE_OF_ALPHABET ];



  /* Initialize @rotorMap and @notches elements to values read in
   * from the file stream. These values read in are converted to 
   * uppercase alphabet symbols */
  for( int position=0; !rotFile.eof(); position++ ){
    rotFile >> storage;
    if( !rotFile.eof() ){
      if( position < SIZE_OF_ALPHABET ){
        rotorMap[position][0] = (position+65); // First row is A-Z
        /* find the wiring distance */
        rotorWiring[position] = (storage+65) - rotorMap[position][0];
        rotorMap[position][1] = (storage+65);     // second row is mapped value
      }
      else{   // remaining values are notches
        notches[position - SIZE_OF_ALPHABET] = (storage+65); 
      }
    }
  }
  recalcMappedPosition();
  rotFile.close();
}

char Rotor::mapInput( char direction )
{

  /* @direction refers to the direction in which the @inputValue
   * enters the rotor unit. Aproaching from the 'keyboard side', is 
   * denoted as 'U' for upper. Approaching from the 'reflector side'
   * is denoted as a 'D' for downwards. */
  switch( direction ){
    case 'U':{                           // Entering from keyboard side 
      for( int i=0; i < SIZE_OF_ALPHABET; i++ ){
        if( rotorMap[i][0] == inputValue ){         // seach upper side
          return rotorMap[i][1];         // return 'wired' value in bottom side
        }
      }
    }
      
    case 'D':{                           // Entering from relflector side
      for( int i=0; i < SIZE_OF_ALPHABET; i++ ){   
        if( rotorMap[i][1] == inputValue ){        // seach botom side 
          return rotorMap[i][0];         // return 'wired' value in top side
        }
      }
    }

    default:
      return inputValue;
  }
}

void Rotor::rotateRotor()
{
  rotorOffset++;            // Rotate yourself
  recalcMappedPosition();   // recalculate the mapped positions
  loopRotorOffset();        // prevent @rotorOffset overshooting
}

void Rotor::rotateRotor( Rotor &leftRot )
{
  if( rotorSlot == 0 ){               // if rotor is the rightmost rotor...
    rotorOffset++;                    // ...rotate yourself
    recalcMappedPosition();
    triggered = false;
  }
  loopRotorOffset();                  // prevent @rotorOffset overshooting



  /* If any of this rotors notches are currently in the absolute position
   * 'A', then rotate the rotor to the left. Upon rotating the rotor below,
   * set trigger to true. This allows the rotor to the left to be rotated
   * only one time whilst the notch remains in the absolute position. */
  int numberOfNotches = sizeOfFile - SIZE_OF_ALPHABET;
  for( int i=0; i < numberOfNotches; i++ ){             // if notch in position

    if( rotorMap[rotorOffset][0] == notches[i] && triggered == false ){
      triggered = true;                  // fire trigger
      leftRot.rotorOffset++;             // rotate leftmost rotor
      leftRot.loopRotorOffset();  
      leftRot.recalcMappedPosition();    // remap its positions.
      leftRot.triggered = false;         // reset trigger of left rotor to false
    }
  }
}

void Rotor::recalcMappedPosition(){
  
  for( int i=0; i < SIZE_OF_ALPHABET; i++ ){
    
    /* set the value of the mapped position*/ 
    rotorMap[i][1] = rotorMap[i][0] + rotorWiring[ (i+rotorOffset) % 26];

      if( rotorMap[i][1] < 'A' ){
        /* if the mapped position is less than 'A'.
         * loop back to 'Z' and minus negative value */
        rotorMap[i][1] = rotorMap[i][1] + 26; 
      }

      else if( rotorMap[i][1] > 'Z' ){
        /* if the mapped position is more than 'Z'.
         * loop back to 'A' add position value */
        rotorMap[i][1] = rotorMap[i][1] - 26;
      }
  }
}

void Rotor::loopRotorOffset(){
  rotorOffset %= 26;
}
