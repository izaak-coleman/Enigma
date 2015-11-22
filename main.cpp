#include <iostream>
#include <cstdio>
#include <fstream>

#include "errors.h"
#include "Exceptions.h"
#include "Rotor.h"
#include "PlugBoard.h"
#include "Reflector.h"
#include "ErrorsHandle.h"
#include "EnigmaMachine.h"


using namespace std;

int main( int argc, char **argv )
{
try{

  /* Check that the minimum number of files have been supplied.*/
  Errors errors;
  errors.minimumArgs( argc );



  /* Load enigma machine*/
	EnigmaMachine enigma( argc, argv );



  /* Stream characters into the enigma machine for encryption, and
   * output them to stdout */
	while( cin ){
		if( cin ){
			enigma.encryptCharacter();
		}
	}

	return NO_ERROR; // return 0
}


catch( InsuffParamsExptn &e ){        // Catch most specific error first
  if( e.insuffRotor == true ){        // number of rotor files is less than
    e.noRotExceptionMsg();            // number of config values
    return e.getExceptionCode();      // print specific exception message
  }
  else{
    e.exceptionMsg();
    return e.getExceptionCode();
  }
}

catch( ExceptionBase &e ){            // catch all other exceptions and 
  e.exceptionMsg();                   // run error handling routine
  e.exceptionMsg( e.getFileName() );
  return e.getExceptionCode();
}
}
