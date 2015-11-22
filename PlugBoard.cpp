#include <iostream>
#include <fstream>

#include "errors.h"
#include "PlugBoard.h"
#include "ErrorsHandle.h"
#include "Exceptions.h"

using namespace std;


PlugBoard::PlugBoard( char *pbFileName )
{
  
  /* Error and format check file */
  Errors checkPlugBoard; 
  checkPlugBoard.noRepContFile( pbFileName, 'p' );



  /* Open plugboard file. Loop through the file, counting
   * the total number of values in the file */
  ifstream pbfile;
  pbfile.open( pbFileName );
  int contact;
  mapLength = 0;                          // set @mapLength to zero
  if( pbfile.fail() ){                    // Throw error if cannot open 
    throw FileOpenErrExptn( ERROR_OPENING_CONFIGURATION_FILE, pbFileName );
  }

  while( !pbfile.eof() ){                 // Loop through file counting values
    if( !pbfile.eof() ){
      pbfile >> contact;
      mapLength++;
    }
  }

  pbfile.clear();
  pbfile.seekg(0);  // clear EOF bit and return to start of file stream


  
  /* Declare and initialze @plugBoardMap. Row size of @plugBoardMap
   * is half the length of @mapLength. Each pair of values read
   * in from @pbfile are assigned to a single 'pair' column */
  mapLength = mapLength/2;                // half file length
  plugBoardMap = new char*[mapLength];    // Array of pointers

  /* Declare 2D array */
  for(int i=0; i < mapLength; i++){
    char *array = new char[2];            // two rows
    plugBoardMap[i] = array;              // pbMap is now 2*mapLength matrix
  }

  /* Initialize array elements with file values converted into chars */
  int topPosition;
  int bottomPosition;
  int pair = 0;
  while(!pbfile.eof()){
    pbfile >> topPosition;
    pbfile >> bottomPosition;
    if( !pbfile.eof() ){ 
        plugBoardMap[pair][0] = (topPosition+65);    // Convert 1st row to char
        plugBoardMap[pair][1] = (bottomPosition+65); // Convert 2nd row to char
        pair++;
      }
    }
  pbfile.close();
}

char PlugBoard::mapInput( char input )
{

  /* Search @plugBoard map, pair by pair until
   * a value == to @input is found. Upon finding
   * this value, return the paired value. */ 
  for(int pair=0; pair < mapLength; pair++ )     // loop through map
  {
    if(plugBoardMap[pair][0] == input){          // if == to @input
      return plugBoardMap[pair][1];              // return 'wired' value
    }

    if(plugBoardMap[pair][1] == input){          // repeat for other row
      return plugBoardMap[pair][0];

    }
  }
  return input;           // if cant value == to @input, return @input
}

