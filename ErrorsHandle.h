#ifndef CHECKERRORS_H
#define CHECKERRORS_H

const int MINIMUM_FILES = 3;

using namespace std;

class Errors
{
public:
  bool minimumArgs( int argc );
  /* Checks to see if argc is at least >= @MINIMUM_FILES. */
  bool correctRotorSetup( int argc, const char *posfile );
  /* Checks that the number of files provided as rotor files
   *are equal to the number of values provided in the 
   * rotor configuration file. */
  void validIndex( int intFromFile, const char *filename );
  /* Checks a if a value read in a file, passed as @intFromFile
   * is between the range 0-25. */
  void allNumerical( char charFromFile, const char *filename );
  /* Checks if a character read in from a file, and passed to
   * as @charFromFile is a digit character */
  bool noRepContFile( const char *filename, char fileSwitch );
  /* Checks a file to see if there are repeated contacts.
   * Can be used to check pluboards, reflector or rotor. 
   * Use @fileSwitch to check each type: .pb 'p', .rf 'f', .rot
   * 'r'*/
  bool repeatContacts( ifstream &file, const char *filename, int numContacts );
  /* Helper functon to @repeatContacts( const char, char ).
   * Scans through file and checks for repeats*/
  bool invUserInput( char keyInput );
  /* Checks each input into enigma keyboard is an uppercase
   * char */
private:
  bool repeatValue( const int contactArray[], const int contact, int counter );
   /* Helper function to @repeatContacts(ifstream, int ). Fills array with int values
    * from a file '@filename' and checks if a value appears twice.*/
                     
};  

#endif
