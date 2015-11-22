#include <iostream>
#include <fstream>
#include <vector>


#include "EnigmaMachine.h"
#include "IOPanel.h"
#include "PlugBoard.h"
#include "Rotor.h"
#include "Reflector.h"
#include "ErrorsHandle.h"
#include "Exceptions.h"
#include "errors.h"

using namespace std;

EnigmaMachine::EnigmaMachine( int argc, char **argv ): 
  plugBoard(argv[1]), 
  reflector(argv[2]){
  
  Errors errorCheck;

  /* Check if at least three arguments were provided*/
  errorCheck.minimumArgs( argc );

    numberOfRotors = argc - 4; // total args minus 

    /* Initialize rotor array */
    for( int i = 0; i < numberOfRotors; i++ ){
      rotorArray.push_back( Rotor( numberOfRotors-i, i, argv[ (argc-2)-i ], argv[argc-1] ));

  if( argc > 3 ){
    /* Check the number of rotors provided is equivalent to the number
     * of rotor configuration values given. */
    errorCheck.correctRotorSetup( argc, argv[argc-1] );

    }
  }
}

void EnigmaMachine::encryptCharacter(){

  Errors error;
  char encryptCh;
  

  /* Get next character for encryption from user.*/    
  userIO.getInputFromStream();
  encryptCh = userIO.passInputToEnigma();

  
  /* If character is whitespace, pass directly to 
     stdout*/
  if( encryptCh == ' ' || encryptCh == '\t' ||
      encryptCh == '\n' || encryptCh == '\r' ){
    }


  /* Otherwise, pass through enigma. */
  else{

    /* Check the character is in range. */
    error.invUserInput( encryptCh );


    /* Pass character through plugboard*/
    encryptCh = plugBoard.mapInput( encryptCh );


    /* Rotate rotor array. @rotateRotor is not 
     * called on the rotor closest to the reflector
     * as there is no more rotors to rotate */
    if ( numberOfRotors == 1 ){
      rotorArray[numberOfRotors - 1].rotateRotor();
    }
    else{
      for( int i = 0; i < numberOfRotors-1; i++ ){
          rotorArray[i].rotateRotor( rotorArray[i+1] );
      }
    }


    /* Pass character through rotor array towards reflector */
    for( int i = 0; i < numberOfRotors ; i++ ){
      rotorArray[i].inputValue = encryptCh;
      encryptCh = rotorArray[i].mapInput( 'U' );
    }


    /* Pass character through reflector*/
    encryptCh = reflector.mapInput( encryptCh );


    /* Pass character through rotor array towards plugboard */
    for( int i = (numberOfRotors-1); i >= 0; i-- ){
      rotorArray[i].inputValue = encryptCh; 
      encryptCh = rotorArray[i].mapInput( 'D' );
    }

  /* Pass character back through plugboard */
    encryptCh = plugBoard.mapInput( encryptCh );

    /* Pass character back to output panel*/
    userIO.storeLastOutput( encryptCh );
    userIO.printOutput();
  }
}
