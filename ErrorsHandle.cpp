#include <iostream>
#include <cstring>
#include <fstream>

#include "ErrorsHandle.h"
#include "Exceptions.h"
#include "errors.h"

using namespace std;


bool Errors::minimumArgs( int argc )
{
  if( argc < MINIMUM_FILES ){ // if less than three args
    throw InsuffParamsExptn( INSUFFICIENT_NUMBER_OF_PARAMETERS, false );
  }
  return true; // minimum number of files present
}

bool Errors::correctRotorSetup( int argc, const char *posfile )
{
  /* Remove enigma, reflector, rotor config and plugboard to get @numRotFiles */
  int numRotFiles = argc-4; 
  int numberOfVals = 0; // number of configs in rotor config file (.pos)


  /* Open file and check all characters are numeric */
  ifstream file;
  file.open( posfile );
  if( file.fail() ){
    throw FileOpenErrExptn( ERROR_OPENING_CONFIGURATION_FILE, posfile );
  }

  char charFromFile; // takes char from file stream
  while( !file.eof() ){
    file >> charFromFile;
    if( !file.eof() ){
      allNumerical( charFromFile, posfile );
    }
  }
  file.clear();
  file.seekg(0); // Return to start of filestream


  /* Open file and check all values are in range.
   * Also, count total number of config values*/

  int intFromFile; // takes in from file stream
  while( !file.eof() ){
    file >> intFromFile;
    if( !file.eof() ){
      validIndex( intFromFile, posfile );
      numberOfVals++;
    }
  }
  file.close();

  
  /* If number of rotor files exceeds number of specified configs,
   * throw not enough configs error */
  if( numberOfVals < numRotFiles ){
    throw NoRotStartPosExptn( NO_ROTOR_STARTING_POSITION );
  }

  /* If number of rotor files is less than number of specfied configs,
   * throw not enough rotor files error */
  if( numberOfVals > numRotFiles ){
    throw InsuffParamsExptn( INSUFFICIENT_NUMBER_OF_PARAMETERS, true );
  }
  /* else number of rotor files == number of suplied rotor configs */  
  return true;
}

void Errors::validIndex( int intFromFile, const char *filename )
{
  if( intFromFile < 0 || intFromFile > 25 ){  // if out of range
    throw InvalidIndexExptn( INVALID_INDEX, filename ); // throw exception
  }
}

void Errors::allNumerical( char charFromFile, const char *filename )
{
  if( charFromFile < '0' || charFromFile > '9' ){ // if not digit char
    throw NonNumCharExptn( NON_NUMERIC_CHARACTER, filename ); // throw exception
  }
}

bool Errors::noRepContFile( const char *filename, char fileSwitch )
{
  
  /* open file and check if all digits are numerical. 
   * Throw exception if fail to open */
  ifstream file;
  file.open( filename ); 
  if( file.fail() ){
    throw FileOpenErrExptn( ERROR_OPENING_CONFIGURATION_FILE, filename );
  }
  char charFromFile;
  while( !file.eof() ){
    file >> charFromFile;
    if( !file.eof() ){
      allNumerical( charFromFile, filename );
    }
  }
  file.clear(); // clear eofbit
  file.seekg(0); // return filstream to start


  /* Count the number of int values in the file, and check they are in
   * range. */
  int countFileVals = 0;
  int intFromFile;

  while( !file.eof() ){
    file >> intFromFile;
    if( !file.eof() ){
      validIndex( intFromFile, filename );
      countFileVals++;
    }
  }
  file.clear(); // clear eofbit
  file.seekg(0); // return to start of filstream


  switch( fileSwitch ){

    case 'p':{ // case plugboard
      /* throw exception if not even or over 26 values given */
      if( countFileVals % 2 != 0 || countFileVals > 26 ){
        throw IncorNumParamsExptn( INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS,
            filename );
      }
      /* check if file contains repeated values */
      if( repeatContacts( file, filename, countFileVals )){
        throw ImposConfigExptn( IMPOSSIBLE_PLUGBOARD_CONFIGURATION, filename );
      }
      break;
    }

    case 'f':{ // case reflector
      /* throw exception if more than 26 values give */
      if (!(countFileVals == 26)){ // should be exactly 26
        throw IncorNumParamsExptn( INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS,
            filename );
      }

      /* check if file contains repeated values */
      if( repeatContacts( file, filename, countFileVals )){
        throw ImposConfigExptn( INVALID_REFLECTOR_MAPPING, filename );
      }
      break;
    }

    case 'r':{ // case rotor
      if( repeatContacts( file, filename, countFileVals ) 
          || countFileVals > 52 || countFileVals < 26 ){
        throw ImposConfigExptn( INVALID_ROTOR_MAPPING, filename );
      }
      break;
    }
    
  }
  return true; // signal no repeats found
}

bool Errors::repeatContacts( ifstream &file, const char *fileName,
    int numContacts )
{
  int *contacts = new int[numContacts];
  for( int i=0; i < numContacts; i++){
    contacts[i] = -1; // intialize elements to -1
  } 
  file.clear(); // clear eofbit
  file.seekg(0); // return to start of filstream

  /* Check that the first 26 file values do not contain repeats */
  int counter = 0;
  int intFromFile = 0;
  while( !file.eof() ){
    file >> intFromFile;
    
    /* If @intFromFile is not eof value, check if it is a repeat, by calling 
     * @repeatValues */
    if( !file.eof()  ){
      if( counter < 26 ){
        contacts[counter] = intFromFile; // fill array with file data 
        if( repeatValue( contacts, intFromFile, counter )){ // check for repeats
          return true; // signal repeat found
         } 
      }

      /* If a 27th value is read in, and this value is not EOF value, then the 
       * file contains more than 26 values and is a rotor file. Break from loop */
      else if (counter == 26){
        break; // file not at end, but contains more than 26 characters
      }
    }
    
    /* If @infFromFile was the EOF flag, and no repeats have occured, then
     * exit, signalling no repeats*/  
    if( file.eof() ){ // If file stream is at end and no repeats signalled return
      file.close();
      return false;
    }
     counter++;
  }  

  delete [] contacts; // delete contacts array
  contacts = NULL;


  /* Assuming error checks have been used correctly, files with
   * more than 26 values that have yet to reach the end are 
   * rotor files that contain notches. Therefore, repeats between the 
   * first 26 values and the values thereafter are permitted. Thus
   * notches and contacts must be checked separately. */


  /* Declare and initialize notches array*/
  counter = 0; // reset counter
  int *notches;
  notches = new int [numContacts - 26];  // file size minus the first 26 file values
  for( int i=0; i < numContacts - 26; i++ ){
    notches[i] = -1; // intitalize elements to  -1
  }
  notches[counter] = intFromFile; // add the current value read from file to notches
  counter++;

  while( !file.eof() ){ // read through rest of file. signal repeats.
    file >> intFromFile;
    if( !file.eof() ){
      notches[counter] = intFromFile;
      if(repeatValue( notches, intFromFile, counter )){
        return true;
      }
    counter++;
    }
  }

  file.close();
  delete [] notches;
  notches = NULL;
  return false; // if no repeats found
}

bool Errors::repeatValue( const int contactArray[], const int contact,
    int counter )
{
  for(int i=0; i<= counter ; i++){
  }
  int repeat = 0;
  for(int i=0; i <= counter; i++ ){
    if(contactArray[i] == contact){
      repeat++;
    }
    if( repeat > 1 ){
      return true;
    }
  }
  return false;
}

bool Errors::invUserInput( char keyInput )
{
  if( keyInput > 'Z' || keyInput < 'A' ){ // check uppercase
    throw InvUserInputExptn( INVALID_INPUT_CHARACTER );
  }
  return false; // input fine
}
